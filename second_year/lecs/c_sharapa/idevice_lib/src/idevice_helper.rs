use crate::idevice_utils::{RecursiveFind, get_string_value_or_default};
use std::{
    ffi::{CString, c_char},
    net::SocketAddr,
    str::FromStr as _,
};

pub use idevice::{
    IdeviceService,
    lockdown::LockdownClient,
    provider::{IdeviceProvider, UsbmuxdProvider},
    usbmuxd::{UsbmuxdAddr, UsbmuxdConnection, UsbmuxdDevice},
};
use idevice::{diagnostics_relay::DiagnosticsRelayClient, syslog_relay::SyslogRelayClient};

#[repr(C)]
#[derive(Debug)]
pub enum Event {
    Connected,
    Disconnected,
}

async fn get_devices() -> Result<Vec<UsbmuxdDevice>, String> {
    let mut usbmuxd = if let Ok(var) = std::env::var("USBMUXD_SOCKET_ADDRESS") {
        let socket =
            SocketAddr::from_str(&var).map_err(|e| format!("Bad USBMUXD_SOCKET_ADDRESS: {e:?}"))?;
        let socket = tokio::net::TcpStream::connect(socket)
            .await
            .map_err(|e| format!("unable to connect to socket address: {e:?}"))?;
        UsbmuxdConnection::new(Box::new(socket), 1)
    } else {
        UsbmuxdConnection::default()
            .await
            .map_err(|e| format!("Unable to connect to usbmxud: {e:?}"))?
    };
    let devices = usbmuxd
        .get_devices()
        .await
        .map_err(|e| format!("Unable to get devices from usbmuxd: {e:?}"))?;

    Ok(devices)
}

async fn get_device() -> Result<UsbmuxdDevice, String> {
    let mut devices = get_devices().await?;

    if devices.is_empty() {
        return Err("devices are empty".into());
    }

    Ok(devices.remove(0))
}

pub async fn get_provider() -> Result<UsbmuxdProvider, String> {
    let device = get_device().await?;

    let muxaddr = UsbmuxdAddr::from_env_var()
        .map_err(|e| format!("failed to create a usbmuxd address from env: {e:?}"))?;

    Ok(device.to_provider(muxaddr, "openitools-idevice"))
}

pub async fn get_lockdownd_client(provider: &UsbmuxdProvider) -> Result<LockdownClient, String> {
    let mut lockdownd_client = LockdownClient::connect(provider)
        .await
        .map_err(|e| format!("failed to connect to lockdownd service: {e:?}"))?;

    lockdownd_client
        .start_session(
            &provider
                .get_pairing_file()
                .await
                .map_err(|e| format!("Failed to get the pairing file: {e:?}"))?,
        )
        .await
        .map_err(|e| format!("Failed to start a new lockdownd session: {e:?}"))?;

    Ok(lockdownd_client)
}

pub async fn get_diag_client(provider: &UsbmuxdProvider) -> Result<DiagnosticsRelayClient, String> {
    DiagnosticsRelayClient::connect(provider)
        .await
        .map_err(|e| format!("failed to connect to lockdownd service: {e:?}"))
}

pub async fn get_syslog_client(provider: &UsbmuxdProvider) -> Result<SyslogRelayClient, String> {
    SyslogRelayClient::connect(provider)
        .await
        .map_err(|e| format!("failed to create a syslog relay: {e:?}"))
}

pub async fn install_package(
    provider: &UsbmuxdProvider,
    data: impl AsRef<[u8]>,
) -> Result<(), String> {
    idevice::utils::installation::install_bytes(provider, data, None)
        .await
        .map_err(|e| format!("failed to install package: {e:?}"))
}

pub async fn is_device_connected() -> Result<(), String> {
    get_device().await.map(|_| ())
}

#[repr(C)]
#[derive(Clone, Copy, Default, Debug)]
pub struct Storage {
    pub total: u64,
    pub used: u64,
    pub available: u64,
}

pub async fn handle_device_storage(provider: &UsbmuxdProvider) -> Result<Storage, String> {
    let mut lockdownd_client = get_lockdownd_client(provider).await?;
    let total = lockdownd_client
        .get_value(Some("TotalDiskCapacity"), Some("com.apple.disk_usage"))
        .await
        .map_or(0, |s| {
            s.as_unsigned_integer().unwrap_or_default() / 1e+9 as u64
        });

    let available = lockdownd_client
        .get_value(Some("AmountRestoreAvailable"), Some("com.apple.disk_usage"))
        .await
        .map_or(0, |s| {
            s.as_unsigned_integer().unwrap_or_default() / 1e+9 as u64
        });

    Ok(Storage {
        total,
        used: total - available,
        available,
    })
}

#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub struct Battery {
    pub level: u64,
    pub health: f32,
    pub cycle_counts: u64,
}

pub async fn handle_device_battery(provider: &UsbmuxdProvider) -> Result<Battery, String> {
    let mut device_diag = match get_diag_client(provider).await {
        Ok(diag) => diag,
        Err(e) => {
            // log::error!("Something went wrong while getting the diagnistics relay client: {e:?}");
            return Err(format!("was not able to get the diagnistics relay: {e}"));
        }
    };

    let battery_plist_key = get_battery_plist_key(provider).await?;
    let battery_plist = device_diag
        .ioregistry(None, Some(battery_plist_key.as_str()), None)
        .await
        .unwrap_or_default()
        .unwrap_or_default();

    let level = battery_plist
        .rfind("CurrentCapacity")
        .map_or(0, |n| n.as_unsigned_integer().unwrap_or_default());

    let cycle_counts = battery_plist
        .rfind("CycleCount")
        .map_or(0, |n| n.as_unsigned_integer().unwrap_or_default());

    let health = {
        let designed_capa = battery_plist
            .rfind("DesignCapacity")
            .map_or(0, |n| n.as_unsigned_integer().unwrap_or_default())
            as f32;

        let max_capa = battery_plist
            .rfind("NominalChargeCapacity")
            .map_or(0, |n| n.as_unsigned_integer().unwrap_or_default())
            as f32;

        ((max_capa / designed_capa) * 100.0 * 100.0).round() / 100.0
    };

    Ok(dbg!(Battery {
        level,
        health,
        cycle_counts,
    }))
}

async fn get_battery_plist_key(provider: &UsbmuxdProvider) -> Result<String, String> {
    let mut lockdownd_client = match get_lockdownd_client(provider).await {
        Ok(lockdownd) => lockdownd,
        Err(e) => {
            // log::error!("Something went wrong while getting the lockdownd client: {e:?}");
            return Err(format!("was not able to get the lockdownd: {e}"));
        }
    };

    let model = get_string_value_or_default(&mut lockdownd_client, Some("ProductType"), None)
        .await
        .unwrap_or("Unknown".into());

    let model_version = model.trim_start_matches("iPhone");
    let model_version_first_num = model_version
        .split_once(',')
        .map(|(code, _)| code.parse::<u8>().unwrap_or_default())
        .unwrap_or_default();

    if model_version_first_num <= 9 {
        // only to iPhone 7 and earlier
        Ok("AppleARMPMUCharger".into())
    } else {
        Ok("AppleSmartBattery".into())
    }
}

#[repr(C)]
#[derive(Debug, Clone, Default)]
pub struct RawHardware {
    pub model: *mut c_char,
    pub model_number: *mut c_char,
    pub region: *mut c_char,
}

#[derive(Debug, Clone, Default)]
pub struct Hardware {
    pub model: CString,
    pub model_number: CString,
    pub region: CString,
}

pub async fn handle_device_hardware(provider: &UsbmuxdProvider) -> Result<Hardware, String> {
    let mut lockdownd_client = match get_lockdownd_client(provider).await {
        Ok(lockdown) => lockdown,
        Err(e) => {
            return Err(format!(
                "Something went wrong while getting the lockdownd client: {e:?}"
            ));
        }
    };

    let region_code = get_string_value_or_default(&mut lockdownd_client, Some("RegionInfo"), None)
        .await
        .unwrap_or_default();

    let region: String = match region_code.as_str() {
        "LL/A" => "United States".into(),
        "B/A" => "Canada".into(),
        "C/A" => "Europe".into(),
        "J/A" => "Japan".into(),
        "X/A" => "China".into(),
        "ZP/A" => "Global/International".into(),
        "KH/A" => "Hong Kong".into(),
        "M/A" => "Mexico".into(),
        "A/A" => "Argentina".into(),
        "T/A" => "Taiwan".into(),
        "V/A" => "United Kingdom".into(),
        "R/A" => "Russia".into(),
        _ => "unknown".into(),
    };

    let model_number_code =
        get_string_value_or_default(&mut lockdownd_client, Some("ModelNumber"), None)
            .await
            .unwrap_or_default();

    let model_meaning = match model_number_code.chars().next().unwrap_or_default() {
        'F' => "Refurbished Device",
        'M' => "New Device",
        'N' => "Warranty Replacement Device",
        'P' => "Personalized Device",
        '3' => "Demo Device",
        _ => "Unknown",
    };

    let model_number = format!("{model_number_code} ({model_meaning})",);

    let model = get_string_value_or_default(&mut lockdownd_client, Some("ProductType"), None)
        .await
        .unwrap_or("Unknown".into());

    Ok(dbg!(Hardware {
        model: CString::new(model).unwrap(),
        model_number: CString::new(model_number).unwrap(),
        region: CString::new(region).unwrap(),
    }))
}

#[derive(Clone, Debug, Default)]
pub struct OS {
    pub ios_ver: CString,
    pub build_num: CString,
}

#[repr(C)]
#[derive(Clone, Debug, Default)]
pub struct RawOS {
    pub ios_ver: *mut c_char,
    pub build_num: *mut c_char,
}

pub async fn handle_device_os(provider: &UsbmuxdProvider) -> Result<OS, String> {
    let mut lockdownd_client = match get_lockdownd_client(provider).await {
        Ok(lockdown) => lockdown,
        Err(e) => {
            return Err(format!(
                "Something went wrong while getting the lockdownd client: {e:?}"
            ));
        }
    };

    let ios_ver = get_string_value_or_default(&mut lockdownd_client, Some("ProductVersion"), None)
        .await
        .unwrap_or_default();

    let build_num = get_string_value_or_default(&mut lockdownd_client, Some("BuildVersion"), None)
        .await
        .unwrap_or_default();

    Ok(OS {
        ios_ver: CString::new(ios_ver).unwrap(),
        build_num: CString::new(build_num).unwrap(),
    })
}
