#include "text_rendering.h"

#include "font.h"

using namespace std;

/* This function renders specified text in the top right corner of the
 * screen. */
void render_text(SDL_PixelFormat *pixelFormat, const int screenWidth, const string &text, vector<Uint32> &pixels)
{
    const int TOP_MARGIN = 5;
    const int RIGHT_MARGIN = 5;
    int y0 = TOP_MARGIN;

    for(int i = 0; i < text.length(); ++i)
    {
        int x_pos = screenWidth - RIGHT_MARGIN - 8 *
            ((text.find('\n', i) == string::npos ? text.length() :
            text.find('\n', i)) - i);

        if(text[i] == '\n')
        {
            y0 += 10;
        }
        else
        {
            const PixelArray &character = get_character(text[i]);
            for(int x = 0; x < 8; ++x)
            {
                for(int y = 0; y < 8; ++y)
                {
                    if (character[y][x])
                    {
                        auto color = SDL_MapRGB(pixelFormat, 0, 0, 0);
                        pixels[(y0 + y) * screenWidth + x_pos + x] = color;
                    }
                    // Else let pixel as is ("transparent" color).
                }
            }
        }
    }
}
