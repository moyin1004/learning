/// @file    03_DuplicationlnArray.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-02 16:03:41
 
#include <iostream>
 
using namespace std;

void swap(int &x, int &y) {
    x ^= y;
    y ^= x;
    x ^= y;
}
 
bool duplicate(int numbers[], int length, int *duplication) {
    //边界判断
    if (numbers == nullptr || length <= 0) return false;
    for (int i = 0; i < length; ++i) {
        if (numbers[i] < 0 || numbers[i] > length - 1) return false;
    }

    for (int i = 0; i < length; ++i) {
        while (numbers[i] != i) {
            int temp = numbers[i];
            if (numbers[i] == numbers[temp]) {
                *duplication = numbers[i];
                return true;
            }
            swap(numbers[i], numbers[temp]);
        }
    }
    return false;
}

int main() {
    int num[7] = {2, 3, 6, 1, 0, 4, 5};
    int dumplication = 0;
    int *p = &dumplication;
    if (duplicate(num, 7, p)) cout << "*p = " << *p << endl;
    for (int i = 0; i < 7; ++i) cout << num[i] << endl;;
    return 0;
}
