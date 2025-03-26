#include <stdio.h>
#include <setjmp.h>

jmp_buf env;

void sub_func(int idx) {
    printf("sub_func --> idx :%d\n", idx);
    longjmp(env, idx);
}

int main() {
    int idx = 0;
    int count = 0;
    count = setjmp(env);
    if (count == 0) { // try
        printf("count: %d\n", count);
        sub_func(++idx);
    } else if (count == 1) { // catch 1
        printf("count: %d\n", count);
        sub_func(++idx);
    } else if (count == 2) { // catch 2
        printf("count: %d\n", count);
        sub_func(++idx);
    }
    { // finally
        printf("other count: %d\n", count);
    }

    return 0;
}