mod idevice_fs;
mod idevice_helper;
mod idevice_utils;

use std::collections::HashMap;

use idevice::plist_macro::PlistConvertible;
use idevice_fs::list_path;

use crate::idevice_helper::{get_lockdownd_client, get_provider};

#[tokio::main]
async fn main() {
    // let path_str = "/DCIM//103APPLE";
    //
    // let provider = get_provider().await.unwrap();
    // let tree = list_path(path_str.to_string(), &provider).await;

    // println!("{tree:#?}");
}
