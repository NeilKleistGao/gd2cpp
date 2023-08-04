use std::fs;

extern crate serde_yaml;
extern crate serde;

use serde::{Serialize, Deserialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct Config {
  pub output_project: String,
  pub intermediate_representation: String
}

impl Config {
  pub fn new(filename: String) -> Config {
    let content = &fs::read_to_string(filename).unwrap_or(String::default())[..];
    let config: Config = serde_yaml::from_str(content)
      .expect("can not read configuration file.");
    config
  }
}
