// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

extern crate sdl2;

use crate::Mode::{Fullscreen, Windowed};

const DEFAULT_VIDEO_WIDTH: i32 = 400;
const DEFAULT_VIDEO_HEIGHT: i32 = 400;

#[derive(Debug)]
enum Mode {
    Windowed(i32, i32),
    Fullscreen,
}

fn main() -> Result<(), String> {
    let sdl_context = sdl2::init()?;

    let args: Vec<String> = std::env::args().collect();
    let mode = match args.len() {
        1 => Windowed(DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT),
        2 if args[1] == "--full" => Fullscreen,
        3 => Windowed(
            args[1].parse().map_err(|e| format!("Invalid width: {}", e))?,
            args[2].parse().map_err(|e| format!("Invalid height: {}", e))?,
        ),
        _ => return Err(String::from("Usage: Mandelbrot [W H] | [--full]"))
    };

    println!("TODO: Initialize SDL with mode: {:?}", mode);
    
    Ok(())
}
