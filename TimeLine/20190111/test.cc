/// @file    test.cc
/// @data    2019-01-12 18:23:33
 
#include "mylogger.h"
#include <iostream>

using std::cout;
using std::endl;
using namespace log;
 
int main() {
    logError("this is an error");
    logInfo("this is an info");
    logWarn("this is a warn");
    logDebug("this is a debug");
    Mylogger::destroy();
    return 0;
}
