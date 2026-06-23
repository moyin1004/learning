#include <iostream>

using namespace std;

class A {
public:
    A() { std::cout << "A" << std::endl; }
    virtual ~A() { std::cout << "~A" << std::endl; }
};

class B : public A {
public:
    B() { std::cout << "B" << std::endl; }
};

struct Simple {
    int data;
};

int main() {
    cout << sizeof(A) << endl;
    cout << sizeof(B) << endl;
    Simple a;
    Simple b;
    // cout << (a == b) << endl;
    return 0;
}
