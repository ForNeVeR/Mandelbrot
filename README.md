<!--
SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>

SPDX-License-Identifier: GPL-3.0-only
-->

Mandelbrot
==========

Mandelbrot is program for real-time visualizing of the Mandelbrot set. Points
are drawn with various colors according to 'depth' (how many iterations taken
to determine that point is NOT part of Mandelbrot set). If point really IS part
of set, it will be drawn with black color.

![Screenshot][screenshot]

Build
-----

**On Windows**, install [vcpkg] and invoke `build-windows.ps1` script. Consult
the script parameters for additional information.

After that, the program can be built with Visual Studio 2017; open
`build/Mandelbrot.sln` file.

**On Linux**, install the necessary developer packages and start CMake
afterwards:

```
$ mkdir build
$ cd build
$ cmake ..
```

Starting the program
--------------------

Windowed mode with window size W x H:

```console
$ Mandelbrot W H
```

Fullscreen mode:

```console
$ Mandelbrot --full
```

Windowed with default window size:

```console
$ Mandelbrot
```

Please note that running with big window size or fullscreen takes many system
resources.

Usage
-----

You can just relax and watch as Mandelbrot set view is zooming on your screen.
Default zoom position in selected for some interesting figures showing in it.

- **Arrow keys**: change projection center
- **ESC**: exit

License
-------
The license indication in the project's sources is compliant with the [REUSE specification v3.3][reuse.spec].

[reuse.spec]: https://reuse.software/spec-3.3/
[screenshot]: docs/screenshot.png
[vcpkg]: https://github.com/Microsoft/vcpkg
