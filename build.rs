// SPDX-FileCopyrightText: 2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

fn main() {
    // This is a workaround for a rustc change in behavior
    // where it no longer automatically links to advapi32
    // See: https://github.com/Rust-SDL2/rust-sdl2/issues/1491
    if cfg!(windows) {
        println!("cargo:rustc-link-lib=advapi32");
    }
}
