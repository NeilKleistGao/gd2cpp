use std::env;

mod gd2cpp;

fn main() {
  let args: Vec<String> = env::args().collect();
  let project_dir: String = {
    let default_dir = String::from("./");
    args.get(1).unwrap_or(&default_dir).to_string()
  };

  let converter = gd2cpp::Converter::new(project_dir);
  let res = converter.start();

  if let Err(reason) = res {
    panic!("{}", reason);
  }
  else {
    println!("finished.");
  }
}
