/// @file    TimerThread.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 19:04:54
 
#include "TimerThread.h"
 
namespace wd {

TimerThread::TimerThread(TimerCallback &&cb, int initialTime, int peoriodicTime)
: _timer(std::move(cb), initialTime, peoriodicTime)
, _thread(std::bind(&Timer::start, &_timer))
{}

void TimerThread::start() {
    _thread.start();
}

void TimerThread::stop() {
    _timer.stop();
    _thread.join();
}

} //end of namespace wd
