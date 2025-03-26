#include <pthread.h>
#include <setjmp.h>
#include <stdio.h>
typedef struct _Exception {
    jmp_buf env;
    int exceptype;
} Exception;

Exception *header;

#define Try(excep) if ((excep.exceptype = setjmp(excep.env)) == 0)
#define Catch(excep, ExceptionType) else if (excep.exceptype == ExceptionType)
#define Throw(excep, ExceptionType) longjmp(excep.env, ExceptionType)
#define Finally

void throw_func(Exception excep, int idx) {
    printf("throw_func --> idx :%d\n", idx);
    Throw(excep, idx);
}

int main() {
    Exception excep;
    excep.exceptype = 0;

    Try(excep) {
        printf("count: %d\n", excep.exceptype);
        throw_func(excep, 2);
    }
    Catch(excep, 1) { printf("count: %d\n", excep.exceptype); }
    Catch(excep, 2) {
        printf("count: %d\n", excep.exceptype);
        throw_func(excep, 1);
    }
    Finally { printf("Finally\n"); }

    return 0;
}