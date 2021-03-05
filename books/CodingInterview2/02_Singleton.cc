/// @file    2.Singleton.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-02 12:37:09

//按需创建 平台相关 Linux的posix线程库
#include <pthread.h> 
#include <stdlib.h>
class Singleton {
public:
    static Singleton *getInstace() {
        pthread_once(&_once, init);
        return _pInstance;
    }

    static void init() {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton();
            atexit(destroy);
        } 
    }

    static void destroy() {
        if (_pInstance)
            delete _pInstance;
    }
private:
    Singleton() {};
    ~Singleton() {};
    static Singleton *_pInstance;
    static pthread_once_t _once;
};

Singleton *Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

/*
//atexit Autorelease 线程安全 跨平台
#include <stdlib.h>
class Singleton {
public:
    static Singleton *getInstace() {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton();
            atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy() {
        if (_pInstance)
            delete _pInstance;
    }
private:
    Singleton() {};
    ~Singleton() {};
    static Singleton *_pInstance;
};

Singleton *Singleton::_pInstance = getInstace();
*/

/*
//Autorelease 线程安全 跨平台
class Singleton {
public:
    static Singleton *getInstace() {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton();
        }
        return _pInstance;
    }

private:
    Singleton() {};
    ~Singleton() {};
    class Autorelease {
    public:
        ~Autorelease() {
        if (_pInstance)
            delete _pInstance;
        }
    };
    static Autorelease _auto;
    static Singleton *_pInstance;
};

Singleton *Singleton::_pInstance = getInstace();
Singleton::Autorelease Singleton::_auto;
*/
