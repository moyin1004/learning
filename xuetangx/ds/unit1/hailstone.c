/// @file    hailstone.c
/// @author  moyin(moyin1004@163.com)
/// @data    2019-11-27 23:09:50

#include <stdio.h>

int hailstone(int n) {
    int length = 1;
    while (n > 1) {
        (n%2) ? (n=n*3+1) : (n/=2);
        ++length;
    }
    return length;
}

int main() {
    int n = 0;

    while (scanf("%d", &n) != EOF) {
        printf("%d\n", hailstone(n));
    }
    return 0;
}
