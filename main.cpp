#include <iostream>
#include <boost/thread/thread.hpp>
#include <SDL.h>

#include "drawing.h"
#include "MandelThread.h"

using namespace boost;
using namespace std;

const int VIDEO_X = 400;
const int VIDEO_Y = 400;

SDL_Surface *init()
{
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
    {
        cerr << "Unable to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    atexit(SDL_Quit);

    SDL_Surface *screen = SDL_SetVideoMode(VIDEO_X, VIDEO_Y, 16, SDL_SWSURFACE);
    if(screen == NULL)
    {
        cerr << "Unable to set video mode: " << SDL_GetError() << endl;
        exit(1);
    }

    return screen;
}

void mainLoop(SDL_Surface *screen)
{
    int thread_count = thread::hardware_concurrency();
    MandelThread *threads = new MandelThread[thread_count];
    
    for(;;)
    {
        // Process full screen through threads:
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i].start(screen, screen->h * i / thread_count,
                screen->h * (i + 1) / thread_count, getScale());
        }
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i].join();
        }
        
        // Draw screen:
        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
        
        // Process events:
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                delete[] threads;
                exit(0);
                break;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    SDL_Surface *screen = init();
    mainLoop(screen);    

    return 0;
}
