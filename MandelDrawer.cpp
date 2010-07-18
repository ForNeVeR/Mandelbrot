/* Main file for class that performs drawing operations. */
#include "MandelDrawer.h"

MandelDrawer::MandelDrawer(SDL_Surface *screen, double center_x,
    double center_y, int start_y, int end_y)
{
    this->screen = screen;
    this->center_x = center_x;
    this->center_y = center_y;
    this->start_y = start_y;
    this->end_y = end_y;
}

void MandelDrawer::setCenter(double x, double y)
{
    center_x = x;
    center_y = y;
}

double MandelDrawer::scaleX(int x, double scale)
{
    return center_x + x * scale / screen->w - scale / 2;
}

double MandelDrawer::scaleY(int y, double scale)
{
    return center_y - y * scale / screen->h + scale / 2;
}

/* Draws screen pixels from line start_y to line end_y with specified scale. */
void MandelDrawer::draw(double scale)
{
    int square_size = SDL_min(screen->w, screen->h);
    double scale_x = scale * screen->w / square_size;
    double scale_y = scale * screen->h / square_size;
    for(int x0 = 0; x0 < screen->w; ++x0)
    {
        for(int y0 = start_y; y0 < end_y; ++y0)
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

            float grade = (float)iteration / MAX_ITERATION;
            Uint16 *p_pixel = (Uint16 *)screen->pixels +
                y0 * screen->pitch / 2 + x0;
            Uint8 R = grade * 256;
            Uint8 G = 128 + grade * 128;
            Uint8 B = 256 - grade * 256;
            Uint32 color = SDL_MapRGB(screen->format, R, G, B);
            *p_pixel = color;
        }
    }
}