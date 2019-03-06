/// @file    Timer.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-24 18:36:20
 
#include "Timer.h"
#include <unistd.h>
#include <errno.h>
#include <poll.h>
#include <sys/timerfd.h>
#include <iostream>
 
using std::cout;
using std::endl;
 
namespace wd {

Timer::Timer(TimerCallback && callback, int initialTime, int peoriodicTime)
: _fd(creatTimerfd())
, _initialTime(initialTime)
, _periodicTime(peoriodicTime)
, _callback(std::move(callback))
, _isStarted(false)
{}

Timer::~Timer() {
    if (_isStarted) {
        stop();
    }
}

void Timer::start() {
    struct pollfd pfd;
    pfd.fd = _fd;
    pfd.events = POLLIN;

    _isStarted = true;
    setTimerfd(_initialTime, _periodicTime);

    while (_isStarted) {
        int ready = ::poll(&pfd, 1, 6000);
        if (ready == -1 && errno == EINTR) continue;
        else if (ready == -1) cout << "";
        else if (ready == 0) {
            cout << ">> poll timeout!" << endl;
        }
        else {
            if (pfd.fd == _fd && (pfd.revents & POLLIN)) {
                handleRead();
                if (_callback) _callback();
            }
        }
    }
}

void Timer::stop() {
    if (_isStarted) {
        _isStarted = false;
        setTimerfd(0, 0);
    }
}

int Timer::creatTimerfd() {
    int ret = timerfd_create(CLOCK_REALTIME, 0);
    if (ret == -1) cout << "error" << endl;
    return ret;
}

void Timer::setTimerfd(int initialTime, int peoriodicTime) {
    struct itimerspec value;
    value.it_value.tv_sec = initialTime;
    value.it_value.tv_nsec = 1;
    value.it_interval.tv_sec = peoriodicTime;
    value.it_interval.tv_nsec = 0;

    int ret = ::timerfd_settime(_fd, 0, &value, nullptr);
    if (ret == -1) cout << "error" << endl;
}

void Timer::handleRead() {
    uint64_t num = 0;
    int ret = ::read(_fd, &num, sizeof(uint64_t));
    if (ret != sizeof(num)) cout << "error" << endl;
}

} //end of namespace wd
