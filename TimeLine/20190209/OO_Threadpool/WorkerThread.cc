/// @file    WorkerThread.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 20:32:08
 
#include "WorkerThread.h"
#include "Threadpool.h"

namespace wd {

WorkerThread::WorkerThread(Threadpool &threadpool)
: _threadpool(threadpool)
{}

void WorkerThread::run()
{
    _threadpool.threadFunc();
}

} //end of namespace wd
