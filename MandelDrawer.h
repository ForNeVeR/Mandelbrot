/* Header file for class that performs drawing operations. */
#ifndef MANDELDRAWER_H
#define MANDELDRAWER_H

#include <SDL.h>

class MandelDrawer
{
public:
    MandelDrawer(SDL_Surface *screen, double center_x, double center_y,
        int start_y, int end_y);
    void setCenter(double x, double y);
    
    void draw(double scale);

private:
    SDL_Surface *screen;
    double center_x, center_y;
    int start_y, end_y;

    const static int MAX_ITERATION = 128;

    inline double scaleX(int x, double scale);
    inline double scaleY(int y, double scale);
};

#endif // MANDELDRAWER_H
