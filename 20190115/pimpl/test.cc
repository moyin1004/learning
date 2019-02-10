/// @file    test.cc
/// @data    2019-01-15 21:40:47
 
#include "Line.h"
#include <iostream>
 
using std::cout;
using std::endl;
    
int main() {
    Line l1(1, 2, 3, 4);
    Line l2; //调用默认构造函数

    l1.printLine();
    l2.printLine();

    return 0;
}
