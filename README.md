<!--
SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>

SPDX-License-Identifier: MIT
-->

Mandelbrot
==========

Mandelbrot is program for real-time visualizing of the Mandelbrot set. Points
are drawn with various colors according to 'depth' (how many iterations taken
to determine that point is NOT part of Mandelbrot set). If point really IS part
of set, it will be drawn with black color.

![Screenshot][screenshot]

Installation
------------
Download the latest version of the binaries from CI, or build from source (see [the contributor guide][docs.contributing] for details).

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

Documentation
-------------
- [Contributor Guide][docs.contributing]
- [Maintainer Guide][docs.maintainer-guide]

License
-------
The project is distributed under the terms of [the MIT license][docs.license].

The license indication in the project's sources is compliant with the [REUSE specification v3.3][reuse.spec].

[docs.contributing]: CONTRIBUTING.md
[docs.license]: LICENSES/MIT.txt
[docs.maintainer-guide]: MAINTAINING.md
[reuse.spec]: https://reuse.software/spec-3.3/
[screenshot]: docs/screenshot.png
