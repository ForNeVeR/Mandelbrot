// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use crate::calculation::MandelMap;
use crate::text::render_text;
use sdl2::pixels::PixelFormat;
use sdl2::render::{Texture, WindowCanvas};
use sdl2::Sdl;

pub struct RenderInfo {
    frame: u32,
    last_tick: u32
}
impl RenderInfo {
    pub fn new() -> Self {
        Self {
            frame: 0,
            last_tick: 0
        }
    }
}

pub fn draw_screen(
    sdl: &Sdl,
    render_info: RenderInfo,
    map: &mut MandelMap,
    pixel_format: &PixelFormat,
    texture: &mut Texture,
    canvas: &mut WindowCanvas,
    scale: f64
) -> RenderInfo {
    let mut pixels = generate_pixels(map, pixel_format);
    let render_info = calculate_render_info(sdl, pixel_format, render_info, pixels.as_mut_slice(), scale, map.width);
    update_texture(pixels, texture, map.width);
    render_texture(canvas, texture);
    render_info
}

fn generate_pixels(map: &mut MandelMap, pixel_format: &PixelFormat) -> Vec<u32> {
    let mut pixels = vec![0u32; map.width * map.height];
    map.draw(pixel_format, pixels.as_mut_slice());
    pixels
}

fn calculate_render_info(sdl: &Sdl, pixel_format: &PixelFormat, render_info: RenderInfo, pixels: &mut [u32], scale: f64, screen_width: usize) -> RenderInfo {
    let mut render_info = render_info;
    render_info.frame += 1;
    const RECOUNT_THRESHOLD: u32 = 25;
    
    let mut fps = String::new();
    if render_info.frame > RECOUNT_THRESHOLD {
        let tick = sdl.timer().unwrap().ticks();
        let avg_fps = render_info.frame as f64 / (tick - render_info.last_tick) as f64;
        fps = format!("FPS: {:}", avg_fps as u32);
        
        render_info.frame = 0;
        render_info.last_tick = tick;
    }
    
    let output = format!("{}\nSCALE:{:}", fps, scale);
    render_text(pixel_format, output, screen_width, pixels);
    render_info
}

fn update_texture(pixels: Vec<u32>, texture: &mut Texture, screen_width: usize) {
    let bytes = unsafe {
        let (a, b, c ) = pixels.as_slice().align_to::<u8>();
        assert!(a.is_empty());
        assert!(c.is_empty());
        b
    };
    texture.update(None, bytes, screen_width * size_of::<u32>()).unwrap();
}

fn render_texture(canvas: &mut WindowCanvas, texture: &Texture) {
    canvas.clear();
    canvas.copy(texture, None, None).unwrap();
    canvas.present();
}
