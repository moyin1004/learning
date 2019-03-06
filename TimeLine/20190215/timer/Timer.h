/// @file    Timer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-17 22:06:38
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__
    
#include <functional>

namespace wd {

class Timer {
public:
    using TimerCallback = std::function<void()>;
    Timer(TimerCallback &&callback, int initialTime, int peoriodicTime);
    ~Timer();

    void start();
    void stop();
private:
    int creatTimerfd();
    void setTimerfd(int initialTime, int peoriodicTime);
    void handleRead();

private:
    int _fd;
    int _initialTime;
    int _periodicTime;
    TimerCallback _callback;
    bool _isStarted;
};

} //end of namespce wd

#endif
