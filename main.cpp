#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/thread/thread.hpp>
#include <SDL2/SDL.h>

#include "MandelMap.h"
#include "MandelThread.h"
#include "text_rendering.h"

using namespace boost;
using namespace std;

const int VIDEO_W_DEFAULT = 400;
const int VIDEO_H_DEFAULT = 400;

const double CENTER_X_DEFAULT = 0.001643721971153;
const double CENTER_Y_DEFAULT = 0.822467633298876;

void renderInfo(SDL_PixelFormat *pixelFormat, const int screenWidth, double scale, vector<Uint32> &pixels);
inline double getScale();
void mainLoop(
    SDL_Window *window,
    SDL_Renderer *renderer,
    SDL_Texture *texture,
	SDL_PixelFormat *pixelFormat,
    const int screenWidth,
    const int screenHeight);

int main(int argc, char *argv[])
{
    int video_w = VIDEO_W_DEFAULT;
    int video_h = VIDEO_H_DEFAULT;
    Uint32 videoMode = 0;

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
            videoMode |= SDL_WINDOW_FULLSCREEN;

            SDL_DisplayMode displayMode;
            if (SDL_GetDesktopDisplayMode(0, &displayMode))
            {
                throw std::exception(SDL_GetError());
            }

            video_w = displayMode.w;
            video_h = displayMode.h;
        }
    }
    else if(argc >= 3)
    {
        video_w = atoi(argv[1]);
        video_h = atoi(argv[2]);
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(
        video_w,
        video_h,        
        videoMode,
        &window,
        &renderer))
    {
        throw std::exception(SDL_GetError());
    }

    auto texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        video_w,
        video_h);
    auto pixelFormatEnum = SDL_GetWindowPixelFormat(window);
    auto pixelFormat = SDL_AllocFormat(pixelFormatEnum);

    mainLoop(window, renderer, texture, pixelFormat, video_w, video_h);

    return 0;
}

void mainLoop(
    SDL_Window *window,
    SDL_Renderer *renderer,
    SDL_Texture *texture,
    SDL_PixelFormat *pixelFormat,
    const int screenWidth,
    const int screenHeight)
{
    double center_x = CENTER_X_DEFAULT;
    double center_y = CENTER_Y_DEFAULT;

    MandelMap map(screenWidth, screenHeight);

    int thread_count = thread::hardware_concurrency();
    vector<MandelThread *> threads;
    for(int i = 0; i < thread_count; ++i)
    {
        threads.push_back(new MandelThread(&map, center_x, center_y,
            screenHeight * i / thread_count,
            i == thread_count - 1 ? screenHeight : // last thread gets remainder
            screenHeight * (i + 1) / thread_count)); // of the whole screen
    }
    
    auto pixels = vector<Uint32>(screenWidth * screenHeight);
    for(;;)
    {
        // Process full screen through threads:
        double scale = getScale();
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i]->calculate(scale);
        }
        for(int i = 0; i < thread_count; ++i)
        {
            threads[i]->join();
        }

        map.draw(pixelFormat, pixels);
        renderInfo(pixelFormat, screenWidth, scale, pixels);

        // Draw screen:
        SDL_UpdateTexture(texture, nullptr, pixels.data(), screenWidth * sizeof(Uint32));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);

        // Process events:
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                {
                    auto key = event.key.keysym.sym;
                    bool center_changed = false;
                    switch(key)
                    {
                    case SDLK_UP:
                        center_y += 0.1 * getScale();
                        center_changed = true;
                        break;
                    case SDLK_DOWN:
                        center_y -= 0.1 * getScale();
                        center_changed = true;
                        break;
                    case SDLK_LEFT:
                        center_x -= 0.1 * getScale();
                        center_changed = true;
                        break;
                    case SDLK_RIGHT:
                        center_x += 0.1 * getScale();
                        center_changed = true;
                    }

                    if(center_changed)
                    {
                        for(int i = 0; i < thread_count; ++i)
                            threads[i]->setCenter(center_x, center_y);
                    }

                    if(key != SDLK_ESCAPE) // else will fall to next case:
                                           // label and quit
                        break;
                }
            case SDL_QUIT:
                for(int i = 0; i < thread_count; ++i)
                    delete threads[i];
                exit(0);
                break;
            }
        }
    }
}

/* This function should be called every frame for proper FPS counting. */
void renderInfo(SDL_PixelFormat *pixelFormat, const int screenWidth, double scale, vector<Uint32> &pixels)
{
    const int recount_threshold = 25;

    static Uint32 last_tick = 0;
    
    static int frame = 0;
    static string fps;

    ++frame;

    if(frame > recount_threshold)
    {
        Uint32 tick = SDL_GetTicks();

        float avg_fps = (float)frame * 1000.0f / (tick - last_tick);
        fps = (format("FPS: %1%") % (int)avg_fps).str();

        frame = 0;
        last_tick = tick;
    }
    string output = fps + (format("\nSCALE: %1$E") % scale).str();

    render_text(pixelFormat, screenWidth, output, pixels);
}

const double SPEED = 1.1;

/* Returns scale at current moment of time. */
double getScale()
{
    return 6.0 / pow(SPEED, (double)SDL_GetTicks() / 300);
}
