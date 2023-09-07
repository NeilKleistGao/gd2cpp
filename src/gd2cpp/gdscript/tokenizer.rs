const tokenizer_debug: bool = true;

macro_rules! debug {
  ($fmt: literal) => {
    if (tokenizer_debug) {
      println!($fmt);
    }
  }
}

pub fn tokenize(code: &str) {
  debug!("tokenizing...");
}
