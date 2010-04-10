/* Header file for text rendering. */
#ifndef TEXT_RENDERING_H
#define TEXT_RENDERING_H

#include <string>
#include <SDL.h>

void render_text(SDL_Surface *screen, const std::string &text);

#endif // TEXT_RENDERING_H
