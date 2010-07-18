/* MandelThread is clas for multi-threaded calculation of Mandelbrot set
 * points. */
#ifndef MANDELTHREAD_H
#define MANDELTHREAD_H

#include <boost/thread/thread.hpp>

class MandelDrawer;
class MandelMap;

class MandelThread
{
public:
    MandelThread(MandelMap *map, double center_x, double center_y, int from_y,
        int to_y);
    void calculate(double scale);
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
