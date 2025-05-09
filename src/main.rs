// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

extern crate sdl2;
mod calculation;
mod render;
mod text;
mod font;

use crate::calculation::{update_map, MandelMap};
use crate::render::{draw_screen, RenderInfo};
use crate::Mode::{Fullscreen, Windowed};
use sdl2::event::Event;
use sdl2::keyboard::Keycode;
use sdl2::pixels::PixelFormat;
use sdl2::pixels::PixelFormatEnum::ARGB8888;
use sdl2::render::{Texture, WindowCanvas};
use sdl2::Sdl;

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
    let pixel_format_enum = window.window_pixel_format();
    let canvas = window.into_canvas().build().map_err(|e| e.to_string())?;
    let (w, h) = canvas.window().size();
    let creator = canvas.texture_creator();
    let texture = creator.create_texture_streaming(ARGB8888, w, h) .map_err(|e| e.to_string())?;
    let pixel_format = PixelFormat::try_from(pixel_format_enum)?;

    main_loop(&sdl, w, h, pixel_format, texture, canvas)?;

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

fn main_loop(
    sdl: &Sdl,
    screen_width: u32,
    screen_height: u32,
    pixel_format: PixelFormat,
    texture: Texture,
    mut canvas: WindowCanvas
) -> Result<(), String> {
    let mut center_x = DEFAULT_CENTER_X;
    let mut center_y = DEFAULT_CENTER_Y;
    let mut map = MandelMap::new(screen_width as usize, screen_height as usize);
    
    let mut pump = sdl.event_pump()?;
    let mut render_info = RenderInfo::new();
    let mut texture = texture;
    loop {
        let scale = get_scale(sdl);
        update_map(&mut map, scale, center_x, center_y);
        render_info = draw_screen(sdl, render_info, &mut map, &pixel_format, &mut texture, &mut canvas, scale);
        
        let event = pump.poll_event();
        if let Some(event) = event {
            match event {
                Event::KeyDown { keycode: Some(keycode), .. } => {
                    match keycode {
                        Keycode::Escape => break,
                        Keycode::Up => center_y += 0.1 * get_scale(sdl),
                        Keycode::Down => center_y -= 0.1 * get_scale(sdl),
                        Keycode::Left => center_x -= 0.1 * get_scale(sdl),
                        Keycode::Right => center_x += 0.1 * get_scale(sdl),
                        _ => {}
                    }
                }
                Event::Quit { .. } => break,
                _ => {}
            }    
        }
    };
    
    println!("Bye!");
    Ok(())
}

const SPEED: f64 = 1.1;
fn get_scale(sdl: &Sdl) -> f64 {
    6.0 / SPEED.powf(sdl.timer().unwrap().ticks() as f64 / 300.0)
}