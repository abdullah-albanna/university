use std::collections::HashMap;

use idevice::{lockdown::LockdownClient, plist_macro::PlistConvertible};
use plist::Value;

pub async fn get_string_value_or_default(
    device: &mut LockdownClient,
    domain: Option<&str>,
    key: Option<&str>,
) -> Option<String> {
    match device.get_value(domain, key).await {
        Ok(value) => Some(
            value
                .as_string()
                .map(ToString::to_string)
                .unwrap_or_default(),
        ),
        Err(_) => None,
    }
}

pub trait RecursiveFind {
    fn rfind(&self, key: &str) -> Option<Value>;
}

impl RecursiveFind for plist::Dictionary {
    fn rfind(&self, key: &str) -> Option<Value> {
        for (k, v) in self {
            if k == key {
                return Some(v.clone());
            }

            if let Value::Dictionary(dict) = v {
                if let Some(found) = dict.rfind(key) {
                    return Some(found);
                }
            }
        }
        None
    }
}

pub fn value_to_dict(value: plist::Value) -> HashMap<String, String> {
    let mut output = HashMap::new();
    for dict in value.into_dictionary() {
        for k in dict.keys() {
            let value = dict.get(k).unwrap().clone();

            if let Some(d) = value.clone().into_dictionary() {
                output.extend(value_to_dict(d.to_plist_value()).into_iter());
                continue;
            }

            let value = if let Some(s) = value.as_string().and_then(|s| Some(s.to_string())) {
                s
            } else {
                continue;
            };
            output.insert(k.clone(), value);
        }
    }

    output
}
