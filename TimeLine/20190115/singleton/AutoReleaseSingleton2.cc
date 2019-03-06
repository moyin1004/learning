/// @file    AutoReleaseSingleton2.cc
/// @data    2019-01-15 22:52:20
 
#include <cstdlib>
#include <iostream>
 
using std::cout;
using std::endl;
 
class Singleton {
public:
    static Singleton *getInstance() {
        //在多线程环境下，并不是线程安全的,
        if(nullptr == _pInstance) { 
            _pInstance =  new Singleton();
            ::atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy() {
        if(_pInstance)
            delete _pInstance;
    }

    void print() {  cout << "Singleton::print()" << endl;  }

private:
    static Singleton *_pInstance;
    Singleton() { cout << "Singleton()" << endl; };
    ~Singleton() {  cout << "~Singleton()" << endl;  };
};

Singleton *Singleton::_pInstance = nullptr;
//Singleton *Singleton::_pInstance = getInstance(); //饱汉模式，可以保证线程安全

int main() {
    Singleton *p = Singleton::getInstance();
    p->print();

    return 0;
}
