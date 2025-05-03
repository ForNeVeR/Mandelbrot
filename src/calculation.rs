// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use std::sync::{Arc, Barrier};
use sdl2::pixels::PixelFormat;
use threadpool::ThreadPool;

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

fn update_map(map: MandelMap, pool: ThreadPool) {
    let thread_count = pool.max_count();
    let barrier = Arc::new(Barrier::new(thread_count));
    for i in 0..thread_count {
        let from_y = screen_height * i / thread_count;
        let to_y = if i == thread_count - 1 { screen_height } else { screen_height * (i + 1) / thread_count };

        let barrier = barrier.clone();

        launch_calculation(barrier, from_y, to_y);
    }

    barrier.wait(); // wait for all the workers to report the results
}
