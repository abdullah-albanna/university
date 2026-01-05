mod idevice_fs;
mod idevice_helper;
mod idevice_utils;

use idevice::IdeviceService;
use idevice::afc::AfcClient;
use idevice::lockdown::LockdownClient;
use idevice::provider::UsbmuxdProvider;
use tokio::io::{AsyncReadExt, AsyncWriteExt};
use tokio::runtime::{self, Runtime};
use tokio::time::sleep;

use std::any::Any;
use std::collections::VecDeque;
use std::ffi::{CString, c_char, c_int, c_void};
use std::sync::{LazyLock, Mutex};
use std::time::Duration;
use std::{panic, ptr};

use crate::idevice_fs::{FSTreeFFI, convert_to_ffi, list_path};
use crate::idevice_helper::{
    Event, RawHardware, RawOS, get_lockdownd_client, handle_device_battery, handle_device_hardware,
    handle_device_os, handle_device_storage,
};
use crate::idevice_utils::value_to_dict;

#[repr(C)]
pub struct RustResult {
    pub ok: *mut c_void,
    pub err: *mut c_char,
}

static GLOBAL_RUNTIME: LazyLock<Runtime> = LazyLock::new(|| {
    runtime::Builder::new_multi_thread()
        .enable_io()
        .enable_time()
        .build()
        .unwrap()
});

pub fn run_sync<F, R>(fut: F) -> R
where
    F: std::future::Future<Output = R> + Send + 'static,
    R: Send + 'static,
{
    let (tx, rx) = std::sync::mpsc::sync_channel(1);

    GLOBAL_RUNTIME.handle().spawn(async move {
        let res = fut.await;
        // best-effort send; ignore if receiver dropped
        let _ = tx.send(res);
    });

    rx.recv().expect("runtime worker panicked")
}

static EVENT_QUEUE: Mutex<VecDeque<Event>> = Mutex::new(VecDeque::new());

fn push_event(e: Event) {
    EVENT_QUEUE.lock().unwrap().push_back(e);
}

#[unsafe(no_mangle)]
pub extern "C" fn poll_event(out_event: *mut c_int) -> bool {
    if out_event.is_null() {
        return false;
    }

    let mut queue = EVENT_QUEUE.lock().unwrap();
    if let Some(e) = queue.pop_front() {
        unsafe {
            *out_event = e as c_int;
        }
        true
    } else {
        false
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn start_device_watcher() {
    GLOBAL_RUNTIME.spawn(async move {
        let mut was_connected = false;

        loop {
            match (
                was_connected,
                idevice_helper::is_device_connected().await.is_ok(),
            ) {
                (false, true) => {
                    was_connected = true;
                    push_event(Event::Connected);
                }
                (true, false) => {
                    was_connected = false;
                    push_event(Event::Disconnected);
                }
                _ => {}
            }

            sleep(Duration::from_secs(1)).await;
        }
    });
}

#[unsafe(no_mangle)]
pub extern "C" fn get_device_info(provider: *mut UsbmuxdProvider) -> RustResult {
    let provider = unsafe { &(*provider) };
    let device_info = match run_sync(async move {
        let mut lockdownd = get_lockdownd_client(provider).await?;
        lockdownd
            .get_value(None, None)
            .await
            .map_err(|e| e.to_string())
    }) {
        Ok(v) => v,
        Err(e) => {
            let err = CString::new(e).unwrap().into_raw();

            return RustResult {
                ok: ptr::null_mut(),
                err,
            };
        }
    };

    let info_dict = value_to_dict(device_info);
    let info_dict_str = serde_json::to_string(&info_dict).unwrap();
    RustResult {
        ok: CString::new(info_dict_str).unwrap().into_raw() as *mut c_void,
        err: ptr::null_mut(),
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn list_path_ffi(
    path: *const c_char,
    provider: *mut UsbmuxdProvider,
) -> *mut FSTreeFFI {
    let c_str = unsafe { std::ffi::CStr::from_ptr(path) };
    let path_str = c_str.to_str().unwrap_or("/");

    let provider_ref = unsafe { &*provider };

    let tree = run_sync(list_path(path_str.to_string(), provider_ref));

    convert_to_ffi(tree)
}

#[unsafe(no_mangle)]
pub extern "C" fn download_a_file(
    path: *const c_char,
    dest: *const c_char,
    provider: *mut UsbmuxdProvider,
    callback: extern "C" fn(u8),
) {
    let path_c_str = unsafe { std::ffi::CStr::from_ptr(path) };
    let dest_c_str = unsafe { std::ffi::CStr::from_ptr(dest) };
    let path_str = path_c_str.to_str().unwrap_or("/");
    let dest_str = dest_c_str.to_str().unwrap();

    let provider = unsafe { &*provider };

    run_sync(async move {
        let mut afc = AfcClient::connect(provider).await.unwrap();

        let src_size = afc.get_file_info(path_str).await.unwrap().size;

        let mut src = afc
            .open(path_str, idevice::afc::opcode::AfcFopenMode::RdOnly)
            .await
            .unwrap();

        let mut dst = tokio::fs::File::options()
            .write(true)
            .truncate(true)
            .create(true)
            .open(dest_str)
            .await
            .unwrap();

        let mut buf = vec![0u8; 512 * 1024];
        let mut amount_read: u64 = 0;
        let mut last_progress = 0;

        loop {
            let n = src.read(&mut buf).await.unwrap();
            if n == 0 {
                break;
            }

            dst.write_all(&buf[..n]).await.unwrap();
            amount_read += n as u64;

            let progress = ((amount_read * 100) / src_size as u64) as u8;
            if progress != last_progress {
                callback(progress);
                last_progress = progress;
            }
        }

        dst.flush().await.unwrap();
        callback(100);
        src.close().await.unwrap();
    });
}

#[unsafe(no_mangle)]
pub extern "C" fn get_provider() -> RustResult {
    match panic::catch_unwind(|| {
        let provider = run_sync(idevice_helper::get_provider());

        match provider {
            Ok(p) => RustResult {
                ok: Box::into_raw(Box::new(p)) as *mut c_void,
                err: ptr::null_mut(),
            },
            Err(e) => RustResult {
                ok: ptr::null_mut(),
                err: CString::new(e).unwrap().into_raw(),
            },
        }
    }) {
        Ok(v) => v,
        Err(e) => RustResult {
            ok: ptr::null_mut(),
            err: CString::new(format!(
                "rust get_provider function paniced: {}",
                get_panic_msg(&e)
            ))
            .unwrap()
            .into_raw(),
        },
    }
}

pub fn get_panic_msg(e: &(dyn Any + Send)) -> String {
    if let Some(s) = e.downcast_ref::<&str>() {
        (*s).to_string()
    } else if let Some(s) = e.downcast_ref::<String>() {
        s.as_str().to_string()
    } else {
        "Unknown panic".to_string()
    }
}
#[unsafe(no_mangle)]
pub extern "C" fn free_c_string(s: *mut c_char) {
    if !s.is_null() {
        unsafe {
            CString::from_raw(s);
        }
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn free_lockdownd_client(lockdownd: *mut LockdownClient) {
    if !lockdownd.is_null() {
        unsafe {
            Box::from_raw(lockdownd);
        }
    }
}

#[unsafe(no_mangle)]
pub extern "C" fn free_provider(provider: *mut UsbmuxdProvider) {
    if !provider.is_null() {
        unsafe {
            Box::from_raw(provider);
        }
    }
}

#[unsafe(no_mangle)]
pub unsafe extern "C" fn free_fstree(tree: *mut FSTreeFFI) {
    if tree.is_null() {
        return;
    }
    let tree_box = unsafe { Box::from_raw(tree) };

    if !tree_box.children.is_null() {
        let children_slice =
            unsafe { std::slice::from_raw_parts_mut(tree_box.children, tree_box.children_count) };

        for &mut child in children_slice {
            free_fstree(child);
        }
        Box::from_raw(tree_box.children); // free the array itself
    }

    // free strings
    if !tree_box.path.is_null() {
        CString::from_raw(tree_box.path);
    }
    if !tree_box.info.nlink.is_null() {
        CString::from_raw(tree_box.info.nlink);
    }
}
