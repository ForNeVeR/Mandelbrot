/* MandelMap is a class for storing results of MandelThreads work. It stores
 * count of iterations for every pixel of the screen. */
#ifndef MANDELMAP_H
#define MANDELMAP_H

#include <SDL.h>

class MandelMap
{
public:
    MandelMap(int width, int height);
    ~MandelMap();

    int getWidth() const;
    int getHeight() const;

    void set(int x, int y, int value);
    void draw(SDL_Surface *screen);

private:
    int width, height;
    int *data;
    
    bool minMaxCached;
    int min, max;

    int get(int x, int y) const;    
    
    int getMin();
    int getMax();

    void cacheMinMax();
};

#endif // MANDELMAP_H
