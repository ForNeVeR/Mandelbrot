// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

use sdl2::pixels::PixelFormat;

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
