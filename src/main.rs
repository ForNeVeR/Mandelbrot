// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

mod mandel_map;

extern crate sdl2;

use crate::Mode::{Fullscreen, Windowed};
use sdl2::event::Event;
use sdl2::pixels::PixelFormatEnum::ARGB8888;
use crate::mandel_map::MandelMap;

const DEFAULT_VIDEO_WIDTH: u32 = 400;
const DEFAULT_VIDEO_HEIGHT: u32 = 400;
const DEFAULT_CENTER_X: f64 = 0.001643721971153;
const DEFAULT_CENTER_Y: f64 = 0.822467633298876;

#[derive(Debug)]
enum Mode {
    Windowed(u32, u32),
    Fullscreen,
}

fn main() -> Result<(), String> {
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

    let sdl = sdl2::init()?;
    let video_subsystem = sdl.video()?;
    let window = initialize_window(video_subsystem, mode)?;
    let canvas = window.into_canvas().build().map_err(|e| e.to_string())?;
    let (w, h) = canvas.window().size();
    let creator = canvas.texture_creator();
    let texture = creator.create_texture_streaming(ARGB8888, w, h) .map_err(|e| e.to_string())?;

    main_loop(&sdl, w, h)?;

    Ok(())
}

fn initialize_window(video_subsystem: sdl2::VideoSubsystem, mode: Mode) -> Result<sdl2::video::Window, String> {
    let (width, height) = match mode {
        Windowed(w, h) => (w, h),
        Fullscreen => (DEFAULT_VIDEO_WIDTH, DEFAULT_VIDEO_HEIGHT),
    };

    let mut builder = video_subsystem.window("Mandelbrot", width, height);
    match mode {
        Fullscreen => builder.fullscreen_desktop(),
        Windowed(_, _) => builder.position_centered()
    }.build().map_err(|e| e.to_string())
}

fn main_loop(sdl: &sdl2::Sdl, screen_width: u32, screen_height: u32) -> Result<(), String> {
    let mut center_x = DEFAULT_CENTER_X;
    let mut center_y = DEFAULT_CENTER_Y;
    let mut map = MandelMap::new(screen_width as usize, screen_height as usize);
    
    let mut pump = sdl.event_pump()?;
    loop {
        let event = pump.wait_event();
        match event {
            Event::KeyDown { .. } => {}
            Event::Quit { .. } => break,
            _ => {}
        }
    };
    
    println!("Bye!");
    Ok(())
}
