/// @file    AutoReleaseSingleton1.cc
/// @data    2019-01-15 22:31:34
 
#include <iostream>
 
using std::cout;
using std::endl;
 
class Singleton {
public:
    static Singleton *getInstance() {
        if(nullptr == _pInstance)
            _pInstance =  new Singleton();
        return _pInstance;
    }

    void print() {  cout << "Singleton::print()" << endl;  }

private:
    static Singleton *_pInstance;
    Singleton() { cout << "Singleton()" << endl; };
    ~Singleton() {  cout << "~Singleton()" << endl;  };
    class AutoRelease {
    public:
        ~AutoRelease() {
            cout << "delete" << endl;
            if(_pInstance)
                delete _pInstance;
        }
    };
    static AutoRelease _auto;
};

Singleton *Singleton::_pInstance = nullptr;
Singleton::AutoRelease Singleton::_auto;

int main() {
    Singleton *p = Singleton::getInstance();
    p->print();
    return 0;
}
