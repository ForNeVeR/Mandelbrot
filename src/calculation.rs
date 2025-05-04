// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use std::cmp::min;
use std::sync::{Arc, Barrier};
use sdl2::pixels::PixelFormat;
use threadpool::ThreadPool;

const MAX_ITERATIONS: i32 = 256;

pub struct MandelMap {
    width: usize,
    height: usize,
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

    fn draw(&self, pixel_format: PixelFormat, pixels: &mut Vec<u32>) {
        panic!("Not implemented");
    }

    fn calc_min_max(&mut self) {
        panic!("Not implemented");
    }
}

fn update_map(map: &'static mut MandelMap, pool: ThreadPool, scale: f64, center_x: f64, center_y: f64) {
    let thread_count = pool.max_count();
    let barrier = Arc::new(Barrier::new(thread_count));
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

        let barrier = barrier.clone();

        launch_calculation(barrier, from_y, to_y, &pool, scale, center_x, center_y, map.width, map.height, data_slice);
    }

    barrier.wait(); // wait for all the workers to report the results
}

fn launch_calculation(barrier: Arc<Barrier>,
                      from_y: usize, to_y: usize,
                      pool: &ThreadPool,
                      scale: f64,
                      center_x: f64, center_y: f64,
                      width: usize, height: usize,
                      data: &'static mut [i32]) {
    assert!(from_y <= to_y);
    let barrier = barrier.clone();
    pool.execute(move || {
        for y in from_y..=to_y {
            for x in 0..width {
                let map_dimension = min(width, height) as f64;
                let scale_x = scale * width as f64 / map_dimension;
                let scale_y = scale * height as f64 / map_dimension;
                data[(y - from_y) * width + x] = mandelbrot_depth(x, y, center_x, center_y, scale_x, scale_y, width, height);
            }
        }
        barrier.wait();
    })
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