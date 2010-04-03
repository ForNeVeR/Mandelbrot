/* Main file for drawing routines. */
#include "drawing.h"

#include <SDL.h>

const double ACC = 0.00001;
const double CENTER_X = 0.001643721971153;
const double CENTER_Y = 0.822467633298876;
const int MAX_ITERATION = 128;

/* Returns scale at current moment of time. */
double getScale()
{
    return 6.0 / (ACC * SDL_GetTicks() * SDL_GetTicks() + 1);
}

inline double scaleX(int coord, int screen_size_x, double scale)
{
    return CENTER_X + coord * scale /  screen_size_x - scale / 2;
}

inline double scaleY(int coord, int screen_size_y, double scale)
{
    return CENTER_Y - coord * scale / screen_size_y + scale / 2;
}

/* Draws screen pixels from line start_y to line end_y with specified scale. */
void draw_part(SDL_Surface *screen, int start_y, int end_y, double scale)
{
    int square_size = SDL_min(screen->w, screen->h);
    double scale_x = scale * screen->w / square_size;
    double scale_y = scale * screen->h / square_size;
    for(int x0 = 0; x0 < screen->w; ++x0)
    {
        for(int y0 = start_y; y0 < end_y; ++y0)
        {
            Uint16 *pPixel = (Uint16 *)screen->pixels +
                y0 * screen->pitch / 2 + x0;
            
            double x1 = scaleX(x0, screen->w, scale_x);
            double y1 = scaleY(y0, screen->h, scale_y);

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
            Uint8 R = grade * 256;
            Uint8 G = 128 + grade * 128;
            Uint8 B = 256 - grade * 256;
            Uint32 color = SDL_MapRGB(screen->format, R, G, B);
            *pPixel = color;
        }
    }
}
