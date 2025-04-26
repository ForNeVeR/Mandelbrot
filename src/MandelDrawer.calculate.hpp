// SPDX-FileCopyrightText: 2010-2025 Mandelbrot contributors <https://github.com/ForNeVeR/Mandelbrot>
//
// SPDX-License-Identifier: GPL-3.0-only

#include "MandelDrawer.h"
#include <algorithm>

/* Draws screen pixels from line start_y to line end_y with specified scale. */
void MandelDrawer::calculate(double scale)
{
    int square_size = std::min(map->getWidth(), map->getHeight());
    double scale_x = scale * map->getWidth() / square_size;
    double scale_y = scale * map->getHeight() / square_size;
    for(int x0 = 0; x0 < map->getWidth(); ++x0)
    {
        for(int y0 = from_y; y0 < to_y; ++y0)
        {
            double x1 = scaleX(x0, scale_x);
            double y1 = scaleY(y0, scale_y);

            double x = x1;
            double y = y1;

            int iteration = 0;

            while(x * x + y * y <= 2 * 2 && iteration < MAX_ITERATION)
            {
                double xtemp = x * x - y * y + x1;
                double ytemp = 2 * x * y + y1;

                x = xtemp;
                y = ytemp;
                ++iteration;
            }

            map->set(x0, y0, iteration);
        }
    }
}
