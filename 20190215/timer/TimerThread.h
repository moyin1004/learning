/// @file    TimerThread.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 19:04:41
 
#ifndef __WD_TIMERTHREAD_H__
#define __WD_TIMERTHREAD_H__

#include "Timer.h"
#include "Thread.h"

namespace wd {

class TimerThread {
    using TimerCallback = std::function<void()>;
public:
    TimerThread(TimerCallback &&cb, int initialTime, int peoriodicTime);
    void start();
    void stop();

private:
    Timer _timer;
    Thread _thread;
};

} //end of namespace wd

#endif
