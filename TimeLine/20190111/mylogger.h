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
    void warn(const char *msg);
    void error(const char *msg);
    void debug(const char *msg);
    void info(const char *msg);

    void setPriority(Priority p);
private:
//    class AutoRelease {
//    public:
//        ~AutoRelease();
//    };
//    static AutoRelease _auto;

    Mylogger();
    ~Mylogger();
    static Mylogger *_pInstance;
    log4cpp::Category &_mylog;
    //log4cpp::Category &getMylog();
};

#define prefix(msg) string("[")\
    .append(__FILE__).append(" , ")\
    .append(__func__).append(" , ")\
    .append(to_string(__LINE__)).append("] ")\
    .append(msg).c_str()

#define logError(msg) Mylogger::getInstance()->error(prefix(msg));
#define logInfo(msg) Mylogger::getInstance()->info(prefix(msg));
#define logWarn(msg) Mylogger::getInstance()->warn(prefix(msg));
#define logDebug(msg) Mylogger::getInstance()->debug(prefix(msg));
    
}

#endif
