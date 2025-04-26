// SPDX-FileCopyrightText: 2010-2025 Friedrich von Never <friedrich@fornever.me>
//
// SPDX-License-Identifier: GPL-3.0-only

#include "MandelThread.h"

#include "MandelDrawer.h"
#include "MandelMap.h"

MandelThread::MandelThread(MandelMap *map, double center_x, double center_y,
    int from_y, int to_y)
{
    drawer = new MandelDrawer(map, center_x, center_y, from_y, to_y);
    
    workMutex = new boost::mutex();
    workMutex->lock();
    freeMutex = new boost::mutex();
    
    thread = new boost::thread(work, this);
}

void MandelThread::calculate(double scale)
{
    this->scale = scale;

    freeMutex->try_lock();
    workMutex->unlock();
}

void MandelThread::setCenter(double x, double y)
{
    drawer->setCenter(x, y);
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
    delete drawer;
}
