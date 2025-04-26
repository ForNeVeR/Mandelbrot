// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: MIT

/* Main file for class that performs drawing operations. */
#include "MandelDrawer.h"

#include "MandelMap.h"

using namespace std;

MandelDrawer::MandelDrawer(MandelMap *map, double center_x, double center_y,
    int from_y, int to_y)
{
    this->map = map;
    this->center_x = center_x;
    this->center_y = center_y;
    this->from_y = from_y;
    this->to_y = to_y;
}

void MandelDrawer::setCenter(double x, double y)
{
    center_x = x;
    center_y = y;
}

double MandelDrawer::scaleX(int x, double scale) const
{
    return center_x + x * scale / map->getWidth() - scale / 2;
}

double MandelDrawer::scaleY(int y, double scale) const
{
    return center_y - y * scale / map->getHeight() + scale / 2;
}

#include "MandelDrawer.calculate.hpp"
