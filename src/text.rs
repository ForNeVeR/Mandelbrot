// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use crate::font::get_glyph;
use sdl2::pixels::{Color, PixelFormat};

pub fn render_text(pixel_format: &PixelFormat, text: String, screen_width: usize, pixels: &mut [u32]) {
    const TOP_MARGIN: usize = 5;
    const RIGHT_MARGIN: usize = 5;
    const CHAR_SIZE: usize = 8;

    let lines = text.lines();
    for (l, line) in lines.enumerate() {
        let glyph_base_y = TOP_MARGIN + l * 10;
        
        for i in 0..line.len() {
            let glyph_base_x = screen_width - RIGHT_MARGIN - (line.len() - i) * CHAR_SIZE;
            
            let char = line.chars().nth(i).unwrap();
            let glyph = get_glyph(char);
            for x in 0..CHAR_SIZE {
                for y in 0..CHAR_SIZE {
                    if glyph[y][x] != 0 {
                        let color = Color::from((0, 0, 0)).to_u32(pixel_format);
                        pixels[(glyph_base_y + y) * screen_width + glyph_base_x + x] = color;
                    }
                }
            }
        }
    }
}
