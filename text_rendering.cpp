/* Source file for text rendering. */
#include "text_rendering.h"

#include <string>
#include <SDL.h>

using namespace std;

#include "font.h"

/* This function renders specified text in the top right corner of the
 * screen. */
void render_text(SDL_Surface *screen, const string &text)
{
    const int TOP_MARGIN = 5;
    const int RIGHT_MARGIN = 5;

    for(int i = 0; i < text.length(); ++i)
    {
        int x_pos = screen->w - RIGHT_MARGIN - 8 * (text.length() - i);

        const PixelArray &character = get_character(text[i]);
        for(int x = 0; x < 8; ++x)
        {
            for(int y = 0; y < 8; ++y)
            {
                if(character[y][x])
                {
                    Uint16 *p_pixel = (Uint16 *)screen->pixels +
                        (y + TOP_MARGIN) * screen->pitch / 2 + x_pos + x;
                    *p_pixel = SDL_MapRGB(screen->format, 0, 0, 0);
                }
                // Else let pixel as is ("transparent" color).
            }
        }
    }
}
