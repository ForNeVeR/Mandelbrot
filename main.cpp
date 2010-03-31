#include <cstdio>
#include "SDL.h"

using namespace std;

SDL_Surface *init()
{
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(400, 400, 16, SDL_SWSURFACE);
    if(screen == NULL)
    {
        fprintf(stderr, "Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }

    return screen;
}

void processEvents()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        }
    }
}

const double velocity = 0.0001;

double scaleX(int coord)
{
    const double centerX = -1;
    double scale = 6 / (velocity * SDL_GetTicks() + 1);
    
    return centerX + coord * scale / 400 - scale / 2;
}

double scaleY(int coord)
{
    const double centerY = 0.2;
    double scale = 6 / (velocity * SDL_GetTicks() + 1);
    return centerY - coord * scale / 400 + scale / 2;
}

void draw(SDL_Surface *screen)
{
    for(;;)
    {
        for(int x0 = 0; x0 < screen->w; ++x0)
        {
            for(int y0 = 0; y0 < screen->h; ++y0)
            {
                Uint16 *pPixel = (Uint16 *)screen->pixels +
                    y0 * screen->pitch / 2 + x0;
                
                double x1 = scaleX(x0);
                double y1 = scaleY(y0);

                double x = x1;
                double y = y1;

                int iteration = 0;
                const int max_iteration = 32;
                
                while(x * x + y * y <= 2 * 2 && iteration < max_iteration) 
                {
                    double xtemp = x * x - y * y + x1;
                    double ytemp = 2 * x * y + y1;

                    x = xtemp;
                    y = ytemp;
                    ++iteration;
                }

                if(iteration == max_iteration) 
                {
                    *pPixel = SDL_MapRGB(screen->format, 0, 0, 0);
                }
                else
                {
                    Uint8 clr = 0xFF - (float)iteration / max_iteration * 0xFF;
                    Uint32 color = SDL_MapRGB(screen->format, clr, clr, clr);
                    *pPixel = color;
                }
            }
        }
        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);

        processEvents();
    }
}

int main(int argc, char *argv[])
{
    SDL_Surface *screen = init();
    draw(screen);    

    return 0;
}