/* Main file for class that performs drawing operations. */
#include "MandelDrawer.h"

#include <algorithm>

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

/* Draws screen pixels from line start_y to line end_y with specified scale. */
void MandelDrawer::calculate(double scale)
{
    int square_size = min(map->getWidth(), map->getHeight());
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