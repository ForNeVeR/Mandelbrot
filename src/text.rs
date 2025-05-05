// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use crate::font::get_character;
use sdl2::pixels::{Color, PixelFormat};

pub fn render_text(pixel_format: &PixelFormat, text: String, screen_width: usize, pixels: &mut [u32]) {
    const TOP_MARGIN: usize = 5;
    const RIGHT_MARGIN: usize = 5;
    let mut y0 = TOP_MARGIN;
    let mut x0 = screen_width - RIGHT_MARGIN;

    for i in 0..text.len() {
        let char = text.chars().nth(i).unwrap();
        if char == '\n' {
            y0 += 10;
            x0 = screen_width - RIGHT_MARGIN;
        } else {
            let character = get_character(char);
            for x in 0..8 {
                for y in 0..8 {
                    if character[x][y] {
                        let color = Color::from((0, 0, 0)).to_u32(pixel_format);
                        pixels[(y0 + y) * screen_width + x0 + x] = color;
                    }
                }
            }
            x0 -= 8;
        }
    }
}
