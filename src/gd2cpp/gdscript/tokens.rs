use super::Variant;

pub enum Token {
  Keyword(String),
  Punctuation(String),
  Identifier(String),
  Literal(Variant)
}
