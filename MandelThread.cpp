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
    // Request thread interruption and wait for it before deleting objects:
    thread->interrupt();
    workMutex->unlock();
    freeMutex->unlock();
    thread->join();

    delete thread;
    delete workMutex;
    delete freeMutex;
}

void MandelThread::work(MandelThread *this_mthread)
{
    for(;;)
    {
        // Wait for mutex to be opened:
        this_mthread->workMutex->lock();
        try
        {
            boost::this_thread::interruption_point();
        }
        catch(boost::thread_interrupted &)
        {
            this_mthread->workMutex->unlock();
            throw;
        }

        // Do work:
        draw_part(this_mthread->screen, this_mthread->from_y,
            this_mthread->to_y, this_mthread->scale);

        this_mthread->freeMutex->unlock();
    }
}
