/// @file    mylogger.h
/// @data    2019-01-12 18:05:34
 
#ifndef __MYLOGGER_H__
#define __MYLOGGER_H__

#include <log4cpp/Category.hh>
#include <string>
#include <iostream>
using std::string;
using std::to_string;

namespace log {

class Mylogger {
public:
    enum Priority { 
        ERROR = 300,
        WARN,
        INFO,
        DEBUG
    };

    static Mylogger *getInstance();
    static void destroy();

    template<class... Args>
    void error(const char *p, Args ...args);
    template<class... Args>
    void info(const char *p, Args ...args);
    template<class... Args>
    void warn(const char *p, Args ...args);
    template<class... Args>
    void debug(const char *p, Args ...args);

//    void error(const char *msg);
//    void info(const char *msg);
//    void warn(const char *msg);
//    void debug(const char *msg);

    void setPriority(Priority p);
private:

    Mylogger();
    ~Mylogger();
    static Mylogger *_pInstance;
    log4cpp::Category &_mylog;
};

template<class... Args>
void Mylogger::error(const char *p, Args ...args) {
    _mylog.error(p, args...);
}

template<class... Args>
void Mylogger::info(const char *p, Args ...args) {
    _mylog.info(p, args...);
}
template<class... Args>
void Mylogger::warn(const char *p, Args ...args) {
    _mylog.warn(p, args...);
}
template<class... Args>
void Mylogger::debug(const char *p, Args ...args) {
    _mylog.debug(p, args...);
}

#define prefix(format) string("[")\
    .append(__FILE__).append(" , ")\
    .append(__func__).append(" , ")\
    .append(to_string(__LINE__)).append("] ")\
    .append(format).c_str()

#define logError(format, args...)Mylogger::getInstance()->error(prefix(format), ##args);
#define logInfo(format, args...) Mylogger::getInstance()->info(prefix(format), ##args);
#define logWarn(format, args...) Mylogger::getInstance()->warn(prefix(format), ##args);
#define logDebug(format, args...) Mylogger::getInstance()->debug(prefix(format), ##args);
#define logSetPriority(priority) Mylogger::getInstance()->setPriority(priority);
    
}

#endif
