// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use rayon::iter::*;
use rayon::prelude::*;
use sdl2::pixels::{Color, PixelFormat};
use std::cmp::min;

const MAX_ITERATIONS: u32 = 256;

pub struct MandelMap {
    pub width: usize,
    pub height: usize,
    data: Vec<u32>,
    max: Option<u32>,
}

impl MandelMap {
    pub fn new(width: usize, height: usize) -> Self {
        let mut data = Vec::with_capacity(width * height);
        data.resize(width * height, 0);
        Self {
            width,
            height,
            data,
            max: None,
        }
    }

    fn get(&self, x: usize, y: usize) -> u32 {
        self.data[x + y * self.width]
    }

    pub fn draw(&mut self, format: &PixelFormat, pixels: &mut [u32]) {
        self.max = None;

        let max_iteration = self.get_max();
        for y in 0..self.height {
            for x in 0..self.width {
                let v = self.get(x, y);
                let (r, g, b) = if v == max_iteration {
                    (0.0, 0.0, 0.0)
                } else {
                    let grade = v as f64 / max_iteration as f64;
                    (grade * 255.0, 127.5 + grade * 127.5, 255.0 - grade * 255.0)
                };

                let color = Color::RGB(r as u8, g as u8, b as u8);
                pixels[x + y * self.width] = color.to_u32(format);
            }
        }
    }

    fn cache_max(&mut self) -> u32 {
        let mut max = 0;
        for value in &self.data {
            if *value > max {
                max = *value;
            }
        }
        self.max = Some(max);
        max
    }

    fn get_max(&mut self) -> u32 {
        self.max.unwrap_or_else(|| {
            self.cache_max()
        })
    }
}

pub fn update_map(map: &mut MandelMap, scale: f64, center_x: f64, center_y: f64) {
    let width = map.width;
    let height = map.height;

    let mut chunks = map.data.par_chunks_exact_mut(width);
    assert!(chunks.take_remainder().is_empty());
    chunks
        .enumerate()
        .for_each(|(y, line)| {
            calculate(y, scale, center_x, center_y, width, height, line);
        });
}

fn calculate(
    y: usize,
    scale: f64,
    center_x: f64, center_y: f64,
    width: usize, height: usize,
    data: &mut [u32]
) {
    assert_eq!(data.len(), width);

    let map_dimension = min(width, height) as f64;
    let scale_x = scale * width as f64 / map_dimension;
    let scale_y = scale * height as f64 / map_dimension;

    for x in 0..width {
        data[x] = mandelbrot_depth(x, y, center_x, center_y, scale_x, scale_y, width, height);
    }
}
    
fn mandelbrot_depth(x: usize, y: usize,
                    center_x: f64, center_y: f64,
                    scale_x: f64, scale_y: f64,
                    width: usize, height: usize) -> u32 {
    let mut iteration = 0u32;
    let initial_x = center_x + x as f64 * scale_x / width as f64 - scale_x / 2.0;
    let initial_y = center_y - y as f64 * scale_y / height as f64 + scale_y / 2.0;

    let mut x = initial_x;
    let mut y = initial_y;
    while iteration < MAX_ITERATIONS && x * x + y * y <= 2.0 {
        let x1 = x * x - y * y + initial_x;
        let y1 = 2.0 * x * y + initial_y;
        x = x1;
        y = y1;
        iteration += 1;
    }
    iteration
}
