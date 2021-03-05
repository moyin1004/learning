/// @file    test.c
/// @author  moyin(moyin1004@163.com)
/// @data    2019-11-18 22:17:50

#include <stdio.h>
#include <math.h>

int add(int n) { //连续和递归
    if (n == 1) return n;
    return n + add(n - 1);
}

int main() {
    printf("%d", add(100));
    return 0;
}
