/// @file    mylogger.cc
/// @data    2019-01-12 18:13:32

#include "mylogger.h"
#include <iostream>
#include <string>
#include <log4cpp/Category.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

using std::cout;
using std::endl;
using std::string;

namespace log {

//Mylogger::AutoRelease Mylogger::_auto;
Mylogger *Mylogger::_pInstance = getInstance();

Mylogger *Mylogger::getInstance() {
    if (nullptr == _pInstance)
       _pInstance =  new Mylogger();
    return _pInstance;
}

void Mylogger::destroy() {
    if(_pInstance)
        delete _pInstance;
}

Mylogger::Mylogger() 
: _mylog(log4cpp::Category::getRoot().getInstance("mylog"))
{
    //控制日志输出格式
    using namespace log4cpp;
    PatternLayout * patternLayout1 = new PatternLayout();
    patternLayout1->setConversionPattern("%d %c [%p] %m%n");
    PatternLayout * patternLayout2 = new PatternLayout();
    patternLayout2->setConversionPattern("%d %c [%p] %m%n");
    //指定日志输出目的地
    OstreamAppender *ostreamAppender = new OstreamAppender("console", &cout);
    ostreamAppender->setLayout(patternLayout1);

    RollingFileAppender *rollingFileAppender = 
        new RollingFileAppender("rollingFileAppender", "my.log", 5*1024, 2);
    rollingFileAppender->setLayout(patternLayout2);

    //日志记录器
    _mylog.setAppender(ostreamAppender);
    _mylog.addAppender(rollingFileAppender);
    _mylog.setPriority(log4cpp::Priority::DEBUG);

}

Mylogger::~Mylogger() {
    log4cpp::Category::shutdown();
}

//Mylogger::AutoRelease::~AutoRelease() {
//    if(_pInstance)
//        delete _pInstance;
//}

void Mylogger::error(const char *msg) {
    _mylog.error(msg);
}

void Mylogger::warn(const char *msg) {
    _mylog.warn(msg);
}

void Mylogger::debug(const char *msg) {
    _mylog.debug(msg);
}

void Mylogger::info(const char *msg) {
    _mylog.info(msg);
}

void Mylogger::setPriority(Priority p) {
    switch(p) {
    case WARN:
        _mylog.setPriority(log4cpp::Priority::WARN);
        break;
    case ERROR:
        _mylog.setPriority(log4cpp::Priority::ERROR);
        break;
    case INFO:
        _mylog.setPriority(log4cpp::Priority::INFO);
        break;
    case DEBUG:
        _mylog.setPriority(log4cpp::Priority::DEBUG);
        break;
    }
}

}
