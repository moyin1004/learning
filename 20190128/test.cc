/// @file    test.cc
/// @data    2019-01-28 20:05:01
 
#include "Circle.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
void test() {
    Cylinder cylinder(6, 6);
    cylinder.show();
    cylinder.showVolume();
}

int main() {
    test();

    return 0;
}
