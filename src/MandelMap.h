/*
 * SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
 *
 * SPDX-License-Identifier: MIT
 */

/* MandelMap is a class for storing results of MandelThreads work. It stores
 * count of iterations for every pixel of the screen. */
#ifndef MANDELMAP_H
#define MANDELMAP_H

#include <vector>

#include <SDL2/SDL.h>

class MandelMap
{
public:
    MandelMap(int width, int height);
    ~MandelMap();

    int getWidth() const;
    int getHeight() const;

    void set(int x, int y, int value);
    void draw(SDL_PixelFormat *pixelFormat, std::vector<Uint32> &pixels);

private:
    int width, height;
    int *data;
    
    bool minMaxCached;
    int min, max;

    int get(int x, int y) const;    
    
    int getMin();
    int getMax();

    void cacheMinMax();
};

#endif // MANDELMAP_H
