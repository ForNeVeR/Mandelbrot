/* Header file for drawing routines. */

#ifndef DRAWING_H
#define DRAWING_H

#include <SDL.h>

void draw_part(SDL_Surface *screen, int start_y, int end_y, double scale);
double getScale();

#endif // DRAWING_H
