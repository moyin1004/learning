/// @file    MutexLock.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 19:49:12
 
#include "MutexLock.h"
#include <iostream>
 
using std::cerr;
using std::endl;

namespace wd {

MutexLock::MutexLock() {
    if (pthread_mutex_init(&_mutex, NULL))
        cerr << "pthread_mutex_init" << endl;
}

void MutexLock::lock() {
    if (pthread_mutex_lock(&_mutex))
        cerr << "pthread_mutex_lock" << endl;
}

void MutexLock::unlock() {
    if (pthread_mutex_unlock(&_mutex))
        cerr << "pthread_mutex_unlock" << endl;
}

MutexLock::~MutexLock() {
    if (pthread_mutex_destroy(&_mutex))
        cerr << "pthread_mutex_destroy" << endl;
}

} //end of namespace wd
