mod defs;

use defs::{Token, TokenType};
use std::env;
use std::fs::File;
use std::process::exit;

pub static mut LINE: i32 = 1;
pub static mut PUTBACK: char = '\n';
pub static mut TOKEN: Token = Token {
    token: TokenType::T_EOF,
    intvalue: 0,
};

unsafe fn init() {
    LINE = 1;
    PUTBACK = '\n';
}

// Print out a usage if started incorrectly
fn usage(prog: &str) {
    eprintln!("Usage: {} infile\n", prog);
    exit(1);
}

fn main() -> std::io::Result<()> {
    let argc = env::args().count();
    let argv: Vec<String> = env::args().collect();

    if argc != 2 {
        usage(&argv[0]);
    }

    unsafe {
        init();
    }

    let infile = File::open(&argv[1])?;

    Ok(())
}
