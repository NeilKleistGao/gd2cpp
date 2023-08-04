use std::env;
use std::path::Path;
use std::result;
use walkdir::WalkDir;
use std::process::Command;

use super::Config;

pub struct Converter {
  base: String,
  project: String,
  config: Config
}

impl Converter {
  pub fn new(project: String) -> Converter {
    let base: String = env::current_dir().unwrap().display().to_string();
    let filename = String::from("gd2cpp.yml");
    let path = Path::new(&base);
    let work_dir = path.join(&project);
    let config_path: String = work_dir.join(&filename).to_str().unwrap_or(&filename).to_string();
    Converter{
      base: base,
      project: project,
      config: Config::new(config_path)
    }
  }

  pub fn start(&self) -> result::Result<(), &str> {
    let rel_dir = &self.config.output_project;
    let path = Path::new(&self.base);
    let input_dir = path.join(&self.project);
    let output_dir = input_dir.join(rel_dir);

    if Path::exists(&output_dir) {
      let _ = Command::new("rm").arg("-r").arg(&output_dir).output();
    }

    let _ = Command::new("cp").arg("-r").arg(&input_dir).arg(&output_dir).output();
    return self.visit(&output_dir);
  }

  fn visit(&self, dir: &Path) -> result::Result<(), &str> {
    if !dir.is_dir() {
      return Err("the given project directory is invalid.");
    }

    for entry in WalkDir::new(&dir).into_iter().filter_map(Result::ok) {
      if !entry.file_type().is_dir() {
        let filename = entry.path().display().to_string();
        if filename.ends_with(".gd") {
          println!("translating {}", &filename);
          self.translate(filename);
        }
      }
    }

    return Ok(());
  }

  fn translate(&self, filename: String) {
    // TODO:
  }

}
