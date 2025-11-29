<!--
SPDX-FileCopyrightText: 2025 Friedrich von Never <friedrich@fornever.me>

SPDX-License-Identifier: MIT
-->

Contributor Guide
=================

Prerequisites
-------------
To build Mandelbrot, you'll need a Rust toolchain.

## Windows
- Rust toolchain:
  ```console
  $ choco install rust-ms
  ```
- CMake (for SDL2):
  ```console
  $ choco install cmake --version 3.31.7
  ```

## macOS
- Rust toolchain: Install via rustup from https://rustup.rs/
- CMake (for SDL2):
  ```console
  $ brew install cmake
  ```
- **Important**: Set the following environment variable before building:
  ```console
  $ export CMAKE_POLICY_VERSION_MINIMUM=3.5
  ```
  This is required due to a compatibility issue with the bundled SDL2 build on modern macOS CMake versions.

  See the upstream issue for details: https://github.com/Rust-SDL2/rust-sdl2/issues/1481

Building
--------
Run the following shell command:
```
$ cargo build
```
To build the release version:
```
$ cargo build --release
```
