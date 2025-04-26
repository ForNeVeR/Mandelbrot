// SPDX-FileCopyrightText: 2010-2025 Mandelbrot contributors <https://github.com/ForNeVeR/Mandelbrot>
//
// SPDX-License-Identifier: GPL-3.0-only

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
        catch(const boost::thread_interrupted &)
        {
            this_mthread->workMutex->unlock();
            throw;
        }

        // Do work:
        this_mthread->drawer->calculate(this_mthread->scale);

        this_mthread->freeMutex->unlock();
    }
}
