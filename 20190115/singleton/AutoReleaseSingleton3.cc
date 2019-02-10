/// @file    AutoReleaseSingleton3.cc
/// @data    2019-01-15 23:11:05
 
#include <pthread.h>
#include <cstdlib>
#include <iostream>
 
using std::cout;
using std::endl;
 
class Singleton {
public:
    static Singleton *getInstance() {
        pthread_once(&_once, init);
        return _pInstance;
    }

    static void init() {
        _pInstance =  new Singleton();
        ::atexit(destroy);
    }

    static void destroy() {
        if(_pInstance)
            delete _pInstance;
    }

    void print() {  cout << "Singleton::print()" << endl;  }

private:
    static Singleton *_pInstance;
    static pthread_once_t _once;
    Singleton() { cout << "Singleton()" << endl; };
    ~Singleton() {  cout << "~Singleton()" << endl;  };
};

Singleton *Singleton::_pInstance = nullptr;
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main() {
    Singleton *p = Singleton::getInstance();
    p->print();

    return 0;
}
