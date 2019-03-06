/// @file    virtualFunction.cc
/// @data    2019-01-29 20:14:11
 
#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    Base() 
    : _data(new int(0))
    {  cout << "Base::Base()" << endl;  }

    virtual ~Base() {  //析构函数定义为虚函数防止内存泄漏
        cout << "Base::~Base()" << endl;
        delete _data;
    }

    virtual void display() {
        cout << "Base::display : " << *_data << endl;
    }
private:
    int * _data;
};

class Middle
: public Base
{
public:
    Middle(int data)
    : _data(new int(data))
    {  cout << "Middle::Middle()" << endl;  }

    ~Middle() {
        cout << "Middle::~Middle()" << endl;
        delete _data;
    }

    virtual void display() {
        cout << "Middle::display : " << *_data << endl;
    }

private:
    int * _data;
};

class Derived
: public Middle
{
public:
    Derived(int data1, int data2)
    : Middle(data1)
    , _data(new int(data2))
    { cout << "Derived::Derived()" << endl;  }

    ~Derived() {
        cout << "Derived::~Derived()" << endl;
        delete _data;
    }

    virtual void display() {
        cout << "Derived::display : " << *_data << endl;
    }

private:
    int *_data;
};

void display(Base &base) {
    base.display();
}

void display(Base *base) {
    base->display();
}

int main() {
    Base base1;
    Middle middle(1);

    cout << endl;
    Base *pbase = &base1;
    display(pbase);
    cout << endl;
    pbase = &middle;
    display(pbase);
    cout << endl;

    pbase = new Derived(2, 3);
    display(pbase);
    delete pbase;
    cout << endl;

    Base &base = middle;
    display(base);
    cout << endl;

    return 0;
}
