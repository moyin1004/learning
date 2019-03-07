/// @file    15_NumberOfOne.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-07 10:47:20
 
#include <iostream>
 
using std::cout;
using std::endl;
 
int NumberOf1(int n) {
    int count = 0;
    while (n) {
        ++count;
        n = (n - 1) & n;
    }
    return count;
}

int main() {
    int n = 0;
    cout << "1 of 0 = " << NumberOf1(n) << endl;
    n = 1;
    cout << "1 of 1 = " << NumberOf1(n) << endl;
    n = 0x80000000;
    cout << "1 of 0x80000000 = " << NumberOf1(n) << endl;
    n = 0xFFFFFFFF;
    cout << "1 of 0xFFFFFFFF = " << NumberOf1(n) << endl;
}
