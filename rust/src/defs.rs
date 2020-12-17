pub enum TokenType {
    T_EOF,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_INTLIT,
}

pub struct Token {
    pub token: TokenType,
    pub intvalue: i32,
}

pub enum ASTNodeType {
    A_ADD,
    A_SUBTRACT,
    A_MULTIPLY,
    A_DIVIDE,
    A_INTLIT,
}

pub struct ASTNode {
    op: ASTNodeType,
    left: Box<ASTNode>,
    right: Box<ASTNode>,
    intvalue: i32,
}
