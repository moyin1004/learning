#include <unistd.h>
#include <stdio.h>

void fun() {
    while(1) {
        printf("Hello, I'm fun\n");
        sleep(1);
    }
}

int main() {
    int a[5] = {0}; //传说中的溢出攻击
    a[5] = (int)fun;
    a[6] = (int)fun;
    a[7] = (int)fun;
    return 0;
}
