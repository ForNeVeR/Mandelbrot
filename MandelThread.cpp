/* Main source file for MandelThread class. */
#include "MandelThread.h"
#include "drawing.h"

MandelThread::MandelThread()
{
    workMutex = new boost::mutex();
    workMutex->lock();
    freeMutex = new boost::mutex();
    
    thread = new boost::thread(work, this);
}

void MandelThread::start(SDL_Surface *screen, int from_y, int to_y,
    double scale)
{
    this->screen = screen;
    this->from_y = from_y;
    this->to_y = to_y;
    this->scale = scale;

    freeMutex->try_lock();
    workMutex->unlock();
}

void MandelThread::join()
{
    freeMutex->lock();
}

MandelThread::~MandelThread()
{
    thread->interrupt();
    workMutex->unlock();
    freeMutex->unlock();

    delete thread;
    delete workMutex;
    delete freeMutex;
}

void MandelThread::work(MandelThread *object)
{
    for(;;)
    {
        // Wait for mutex to be opened:
        object->workMutex->lock();
        
        // Do work:
        draw_part(object->screen, object->from_y, object->to_y, object->scale);

        object->freeMutex->unlock();
    }
}
