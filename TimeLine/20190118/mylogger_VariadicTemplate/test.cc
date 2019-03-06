/// @file    test.cc
/// @data    2019-01-12 18:23:33
 
#include "mylogger.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace log;
 
int main() {
    int num = 100;
    const char *p = "hello";
    logError("this is an error. num = %d str = %s\n", num, p);
    logInfo("this is an info");
    logWarn("this is a warn");
    logDebug("this is a debug");
    cout << endl;
    logSetPriority(Mylogger::Priority::ERROR);
    cout << "setPriority(ERROR) :" << endl;
    logError("this is an error. num = %d str = %s\n", num, p);
    logInfo("this is an info");
    logWarn("this is a warn");
    logDebug("this is a debug");
    return 0;
}
