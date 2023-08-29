use std::mem::ManuallyDrop;
use super::Variant;

pub struct ASTBase {
  next: Box<ASTNode>,
  annotations: Vec<Annoation>,
}

macro_rules! declare_node {
  ($name: ident) => {
    pub struct $name {
      base: ASTBase
    }
  };
  ($name: ident, $($f: ident, $t: ty), *) => {
      pub struct $name {
        base: ASTBase,
        $($f: $t),*
      }
  };
}

declare_node!(Annoation, args, Vec<Expression>);
declare_node!(Array, elements, Vec<Expression>);
declare_node!(Assert,
  cond, Expression,
  message, Expression
);
declare_node!(Assignment,
  assignee, Expression,
  value, Expression
);
declare_node!(Await, to, Expression);
declare_node!(BinaryOp, lhs, Expression, rhs, Expression); // TODO: operators
declare_node!(Break);
declare_node!(Breakpoint);
declare_node!(Call, callee, Expression, args, Vec<Expression>);
declare_node!(Cast, oprand, Expression); // TODO: type node
declare_node!(Expression, value, Variant);

macro_rules! md {
  ($t: ty) => {
    ManuallyDrop<$t>
  };
}

pub union ASTNode {
  annotation: md!(Annoation),
  array: md!(Array),
  assert: md!(Assert),
  assign: md!(Assignment),
  awa: md!(Await),
  biop: md!(BinaryOp),
  brk: md!(Break),
  bkpoint: md!(Breakpoint),
  call: md!(Call),
  cast: md!(Cast),
  expr: md!(Expression)
}

impl ASTNode {
  fn is_expression(&self) -> bool {
    false // TODO
  }
}
