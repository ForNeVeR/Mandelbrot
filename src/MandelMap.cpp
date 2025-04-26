// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

#include "MandelMap.h"

#include <cassert>

using namespace std;

MandelMap::MandelMap(int width, int height)
{
    minMaxCached = false;
    this->width = width;
    this->height = height;
    data = new int[width * height];
}

MandelMap::~MandelMap()
{
    delete[] data;
}

int MandelMap::getWidth() const
{
    return width;
}

int MandelMap::getHeight() const
{
    return height;
}

void MandelMap::set(int x, int y, int value)
{
#ifdef _DEBUG
    assert(x < width && y < height && y * width + x < width * height);
#endif

    data[y * width + x] = value;
}

void MandelMap::draw(SDL_PixelFormat *pixelFormat, vector<Uint32> &pixels)
{
    minMaxCached = false;

    int maxIteration = getMax();
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            float grade = (float)(get(x, y)) / maxIteration;
            auto &p_pixel = pixels[x + y * width];
            Uint8 R = grade * 256;
            Uint8 G = 128 + grade * 128;
            Uint8 B = 256 - grade * 256;
            auto color = SDL_MapRGB(pixelFormat, R, G, B);
            p_pixel = color;
        }
    }
    getMin();
}

int MandelMap::get(int x, int y) const
{
#ifdef _DEBUG
    assert(x < width && y < height && y * width + x < width * height);
#endif

    return data[y * width + x];
}

int MandelMap::getMin()
{
    if(!minMaxCached)
        cacheMinMax();

    return min;
}

int MandelMap::getMax()
{
    if(!minMaxCached)
        cacheMinMax();

    return max;
}

void MandelMap::cacheMinMax()
{
    min = max = data[0];
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            if(get(x, y) < min)
                min = get(x, y);
            if(get(x, y) > max)
                max = get(x, y);
        }
    }
    minMaxCached = true;
}
