/* Header file for MandelThread class. */
#ifndef MANDELTHREAD_H
#define MANDELTHREAD_H

#include <boost/thread/thread.hpp>
#include <SDL.h>

#include "MandelDrawer.h"

class MandelThread
{
public:
    MandelThread(SDL_Surface *screen, double center_x, double center_y,
        int from_y, int to_y);
    void draw(double scale);
    void setCenter(double x, double y);
    void join();
    ~MandelThread();

private:
    boost::thread *thread;
    boost::mutex *workMutex;
    boost::mutex *freeMutex;

    MandelDrawer *drawer;
    double scale;
    
    static void work(MandelThread *this_mthread);
};

#endif // MANDELTHREAD_H
