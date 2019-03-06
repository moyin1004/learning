/// @file    singleton_template.cc
/// @data    2019-01-15 22:31:34
 
#include <iostream>
#include <string>
 
using std::cout;
using std::endl;
using std::string;
 
template<class T>
class Singleton {
public:
    template<class ...Args>
    static T *getInstance(Args... args) {
        if(nullptr == _pInstance) {
            _pInstance =  new T(args ...);
            ::atexit(destroy);
        }
        return _pInstance;
    }

    static void destroy() {  //这里要是静态，否则属于具体对象，无法直接调用
        if(_pInstance) {
            cout << "delete" << endl;
            delete _pInstance;
        }
    }

private:
    static T *_pInstance;
    Singleton() { cout << "Singleton()" << endl; };
    ~Singleton() {  cout << "~Singleton()" << endl;  };
};

template<class T>
T *Singleton<T>::_pInstance = nullptr;

class Computer {
public:
    Computer(string brand, int price) 
    : _brand(brand)
    , _price(price)
    {  cout << "Computer(String, int)" << endl;  }
    void print() {
        cout << "_brand = " << _brand  << endl;
        cout << "_price = " << _price << endl;
    }
private:
    string _brand;
    int _price;
};

class Point {
public:
    Point(int ix = 0, int iy = 0) 
    : _ix(ix)
    , _iy(iy)
    {  cout << "Point(int, int)" << endl;  }
    void print() {
        cout << "_ix = " << _ix  << endl;
        cout << "_iy = " << _iy  << endl;
    }
private:
    int _ix;
    int _iy;

};

int main() {
    Computer *p1 = Singleton<Computer>::getInstance("xiaomi", 6666);
    Computer *p2 = Singleton<Computer>::getInstance("huawei", 6666);
    cout << "Computer *p1 :" << endl;
    p1->print();
    cout << "Computer *p2 :" << endl;
    p2->print();
    Point *p3 = Singleton<Point>::getInstance(1, 2);
    Point *p4 = Singleton<Point>::getInstance(3, 4);
    cout << "Point *p3 :" << endl;
    p3->print();
    cout << "Point *p4 :" << endl;
    p4->print();
    return 0;
}
