use std::env;
use std::io::{self, IsTerminal, Read};

const ASCII_CONTROL_NAMES: [&str; 33] = [
    "NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "HT", "LF", "VT", "FF", "CR",
    "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC",
    "FS", "GS", "RS", "US", "SPACE",
];

fn binary_string(byte: u8) -> String {
    format!("{byte:08b}")
}

fn symbol_label(byte: u8) -> String {
    match byte {
        0..=32 => ASCII_CONTROL_NAMES[byte as usize].to_string(),
        127 => "DEL".to_string(),
        33..=126 => char::from(byte).to_string(),
        _ => format!("0x{byte:02X}"),
    }
}

fn print_row(byte: u8) {
    println!(
        "{:<8} {:<5} 0x{:02X}   {}",
        symbol_label(byte),
        byte,
        byte,
        binary_string(byte)
    );
}

fn print_header() {
    println!("{:<8} {:<5} {:<6} binary", "symbol", "value", "hex");
}

fn print_bytes(bytes: impl IntoIterator<Item = u8>) {
    for byte in bytes {
        print_row(byte);
    }
}

#[cfg(unix)]
fn argument_bytes(arg: &std::ffi::OsStr) -> Vec<u8> {
    use std::os::unix::ffi::OsStrExt;

    arg.as_bytes().to_vec()
}

#[cfg(not(unix))]
fn argument_bytes(arg: &std::ffi::OsStr) -> Vec<u8> {
    arg.to_string_lossy().into_owned().into_bytes()
}

fn main() -> io::Result<()> {
    print_header();

    let args: Vec<_> = env::args_os().skip(1).collect();

    if args.is_empty() {
        if io::stdin().is_terminal() {
            print_bytes(0u8..=127);
        } else {
            let mut input = Vec::new();
            io::stdin().read_to_end(&mut input)?;
            print_bytes(input);
        }
    } else {
        for (index, arg) in args.iter().enumerate() {
            if index > 0 {
                print_row(b' ');
            }
            print_bytes(argument_bytes(arg));
        }
    }

    Ok(())
}
