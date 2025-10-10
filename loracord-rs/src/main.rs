use std::io::{stdin, stdout, Write};
use std::{thread, time};
use termion::cursor::{Goto, Hide, Show};
use termion::raw::IntoRawMode;
use termion::{clear, event::Key, input::TermRead, async_stdin};

fn main() {
    let stdin = stdin();
    let mut stdout = stdout().into_raw_mode().unwrap();

    write!(stdout, "{}{}", clear::All, Hide).unwrap();
    stdout.flush().unwrap();

    let mut messages: Vec<String> = vec![];
    messages.push("Goofy".to_string());
    let mut input = String::new();
    let height = 10; // Number of lines to use for message display

    for evt in stdin.keys() {
        match evt.unwrap() {
            Key::Char('\n') => {
                // Add the input to the messages
                messages.push(input.clone());
                if messages.len() > height {
                    messages.remove(0); // Keep message list within height
                }
                input.clear();
            }
            Key::Char(c) => {
                input.push(c);
            }
            Key::Backspace => {
                input.pop();
            }
            Key::Ctrl('c') => break,
            _ => {}
        }

        // Redraw screen
        write!(stdout, "{}{}", Goto(1, 1), clear::All).unwrap();

        // Draw messages
        for (i, msg) in messages.iter().enumerate() {
            write!(stdout, "{}{}", Goto(1, (i + 1) as u16), msg).unwrap();
        }

        // Draw input line
        write!(
            stdout,
            "{}> {}",
            Goto(1, (height + 2) as u16),
            input
        )
        .unwrap();

        stdout.flush().unwrap();
    }

    write!(stdout, "{}", Show).unwrap(); // Show cursor again
}

