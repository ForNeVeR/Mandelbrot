/* Text rendering function. */
#ifndef TEXT_RENDERING_H
#define TEXT_RENDERING_H

#include <string>

struct SDL_Surface;

void render_text(SDL_Surface *screen, const std::string &text);

#endif // TEXT_RENDERING_H
