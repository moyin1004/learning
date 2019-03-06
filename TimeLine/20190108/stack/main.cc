/// @file    main.cc
/// @data    2019-01-08 23:20:41
 

#include "stack.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
int main() {
    Stack s;
    s.push(10);
    s.push(12);
    s.push(14);
    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
//    s.pop();
//    s.pop();
//    s.pop();
//    s.pop();

    return 0;
}
