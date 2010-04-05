// Global TODO: rewrite some parts in C++-style (especially - working with
// strings).

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <boost/thread/thread.hpp>
#include <SDL.h>

#include "drawing.h"
#include "text_rendering.h"
#include "MandelThread.h"

using namespace boost;
using namespace std;

const int VIDEO_W_DEFAULT = 400;
const int VIDEO_H_DEFAULT = 400;
const int BPP_DEFAULT = 16;
const Uint32 VIDEO_MODE_DEFAULT = SDL_SWSURFACE;

inline void frameCounter(SDL_Surface *screen);
void mainLoop(SDL_Surface *screen);

int main(int argc, char *argv[])
{
    int video_w = 0;
    int video_h = 0;
    Uint32 video_mode = VIDEO_MODE_DEFAULT;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << "Unable to init SDL: " << SDL_GetError() << endl;
        exit(1);
    }
    atexit(SDL_Quit);
    
    // Parse command line parameters:
    if(argc == 2)
    {
        if(strcmp("--full", argv[1]) == 0)
        {
            video_mode = SDL_FULLSCREEN;
            video_w = SDL_GetVideoInfo()->current_w;
            video_h = SDL_GetVideoInfo()->current_h;
        }
    }
    else if(argc >= 3)
    {
        video_w = atoi(argv[1]);
        video_h = atoi(argv[2]);
    }

    // Set default values on errors:
    if(!SDL_VideoModeOK(video_w, video_h, BPP_DEFAULT, video_mode))
    {
        video_w = VIDEO_W_DEFAULT;
        video_h = VIDEO_H_DEFAULT;
        video_mode = VIDEO_MODE_DEFAULT;
    }

    SDL_Surface *screen = SDL_SetVideoMode(video_w, video_h, BPP_DEFAULT,
        video_mode);
    if(screen == NULL)
    {
        cerr << "Unable to set video mode: " << SDL_GetError() << endl;
        exit(1);
    }

    mainLoop(screen);    

    return 0;
}

void mainLoop(SDL_Surface *screen)
{
    int thread_count = thread::hardware_concurrency();
    vector<MandelThread *> threads;
    for(int i = 0; i < thread_count; ++i)
    {
        threads.push_back(new MandelThread(screen,
            screen->h * i / thread_count,
            i == thread_count - 1 ? screen->h :   // last thread gets remainder
            screen->h * (i + 1) / thread_count)); // of the whole screen
    }
    
    for(;;)
    {
        // Process full screen through threads:
        double scale = getScale();
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i]->draw(scale);
        }
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i]->join();
        }

        frameCounter(screen);

        // Draw screen:
        SDL_UpdateRect(screen, 0, 0, screen->w, screen->h);
        
        // Process events:
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            // Exit program on SDL_QUIT event or on ESC key press.
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym != SDLK_ESCAPE)
                    break;
            case SDL_QUIT:
                for(int i = 0; i < thread_count; ++i)
                    delete threads[i];
                exit(0);
                break;
            }
        }
    }
}

/* An FPS counter (recounts every 25 frames). Should be called every frame. */
void frameCounter(SDL_Surface *screen)
{
    const int recount_threshold = 25;

    static Uint32 last_tick = 0;
    
    static int frame = 0;
    static char buff[10] = "";

    ++frame;

    if(frame > recount_threshold)
    {
        Uint32 tick = SDL_GetTicks();

        float avg_fps = (float)frame * 1000 / (tick - last_tick);
        // Buffer overflow protection:
        if (avg_fps >= 100000) // yeah, I know, this is almost unbelievable
            avg_fps = 99999;
        sprintf(buff, "FPS: %i", (int)avg_fps);

        frame = 0;
        last_tick = tick;
    }

    render_text(screen, buff);
}