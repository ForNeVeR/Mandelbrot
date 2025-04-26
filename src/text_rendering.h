/* Text rendering function. */
#ifndef TEXT_RENDERING_H
#define TEXT_RENDERING_H

#include <string>
#include <vector>

#include <SDL2/SDL.h>

struct SDL_Surface;

void render_text(
    SDL_PixelFormat *pixelFormat,
    const int screenWidth,
    const std::string &text,
    std::vector<Uint32> &pixels);

#endif // TEXT_RENDERING_H
