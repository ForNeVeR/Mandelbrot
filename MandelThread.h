/* Header file for MandelThread class. */
#ifndef MANDELTHREAD_H
#define MANDELTHREAD_H

#include <boost/thread/thread.hpp>
#include <SDL.h>

class MandelThread
{
public:
    MandelThread();
    void start(SDL_Surface *screen, int from_y, int to_y, double scale);
    void join();
    ~MandelThread();

private:
    boost::thread *thread;
    boost::mutex *workMutex;
    boost::mutex *freeMutex;

    SDL_Surface *screen;
    int from_y, to_y;
    double scale;
    
    static void work(MandelThread *this_mthread);
};

#endif // MANDELTHREAD_H
