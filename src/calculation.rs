// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use sdl2::pixels::PixelFormat;
use std::cmp::min;
use threadpool::ThreadPool;
use threadpool_scope::scope_with;

const MAX_ITERATIONS: i32 = 256;

pub struct MandelMap {
    pub width: usize,
    pub height: usize,
    data: Vec<i32>,
    min: Option<i32>,
    max: Option<i32>,
}

impl MandelMap {
    pub fn new(width: usize, height: usize) -> Self {
        let mut data = Vec::with_capacity(width * height);
        data.resize(width * height, 0);
        Self {
            width,
            height,
            data,
            min: None,
            max: None,
        }
    }

    fn set(&mut self, x: usize, y: usize, value: i32) {
        self.data[y * self.width + x] = value;
    }

    pub fn draw(&self, pixel_format: &PixelFormat, pixels: &mut Vec<u32>) {
        panic!("Not implemented");
    }

    fn calc_min_max(&mut self) {
        panic!("Not implemented");
    }
}

pub fn update_map(map: &mut MandelMap, pool: &ThreadPool, scale: f64, center_x: f64, center_y: f64) {
    let thread_count = pool.max_count();
    let width = map.width;
    let height = map.height;
    
    scope_with(pool, |scope| {
        let mut data = map.data.as_mut_slice();
        let rows_per_thread = map.height / thread_count;
    
        for i in 0..thread_count {
            let data_slice = if i == thread_count - 1 {
                let head = data;
                data = &mut [];
                head
            } else {
                let (head, rest) = data.split_at_mut(rows_per_thread * map.width);
                data = rest;
                head
            };

            let from_y = map.height * i / thread_count;
            let to_y = if i == thread_count - 1 { map.height } else { map.height * (i + 1) / thread_count };

            scope.execute(move || {
                calculate(from_y, to_y, scale, center_x, center_y, width, height, data_slice);
            });
        }
    });
    pool.join();
}

fn calculate(
    from_y: usize, to_y: usize,
    scale: f64,
    center_x: f64, center_y: f64,
    width: usize, height: usize,
    data: &mut [i32]
) {
    assert!(from_y <= to_y);
    for y in from_y..=to_y {
        for x in 0..width {
            let map_dimension = min(width, height) as f64;
            let scale_x = scale * width as f64 / map_dimension;
            let scale_y = scale * height as f64 / map_dimension;
            data[(y - from_y) * width + x] = mandelbrot_depth(x, y, center_x, center_y, scale_x, scale_y, width, height);
        }
    }
}
    
fn mandelbrot_depth(x: usize, y: usize,
                    center_x: f64, center_y: f64,
                    scale_x: f64, scale_y: f64,
                    width: usize, height: usize) -> i32 {
    let mut iteration = 0;
    let initial_x = scale(x, center_x, scale_x, width);
    let initial_y = scale(y, center_y, scale_y, height);

    let mut x = scale(x, center_x, scale_x, width);
    let mut y = scale(y, center_y, scale_y, height);
    while iteration < MAX_ITERATIONS && x * x + y * y < 4.0 {
        x = x * x - y * y + initial_x;
        y = 2.0 * x * y + initial_y;
        iteration += 1;
    }
    iteration
}

fn scale(v: usize, center: f64, scale: f64, size: usize) -> f64 {
    center - v as f64 * scale / size as f64 + scale / 2.0
}