/// @file    test.cc
/// @data    2019-01-23 22:59:02
 
#include "Vector.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
    Vector<int> number;
    cout << "capacity = " << number.capacity() << endl;
    cout << "size = " << number.size() << endl;
    for (size_t i = 1; i < 10; ++i)
        number.push_back(i);
    for (int i = 0; i < number.size(); ++i)
        cout << number[i] << endl;

    cout << "capacity = " << number.capacity() << endl;
    cout << "size = " << number.size() << endl;

    int size = number.size();
    for (int i = 0; i < size; ++i)
        number.pop_back();

    cout << "capacity = " << number.capacity() << endl;
    cout << "size = " << number.size() << endl;
    number.pop_back();

    return 0;
}
