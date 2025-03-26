#include <pthread.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define EXCEPTION_MESSAGE_LENTH 512

typedef struct _ExceptionType {
    const char *name;
    const char *what;
} ExceptionType;

typedef struct _Exception {
    jmp_buf env;
    ExceptionType *exceptype;
    struct _Exception *next;
    char msg[EXCEPTION_MESSAGE_LENTH];
} Exception;

pthread_key_t ExceptionStack;

#define ExceptionPopStack \
    pthread_setspecific(ExceptionStack, ((Exception *)pthread_getspecific(ExceptionStack))->next);

enum { ExceptionEntered = 0, ExceptionThrown, ExceptionHandled, ExceptionFinalized };
#define Try                                                            \
    do {                                                               \
        Exception excep;                                               \
        volatile int Exception_flag;                                   \
        excep.next = (Exception *)pthread_getspecific(ExceptionStack); \
        excep.msg[0] = 0;                                              \
        pthread_setspecific(ExceptionStack, &excep);                   \
        Exception_flag = setjmp(excep.env);                            \
        if (Exception_flag == ExceptionEntered) {
#define Catch(e)                                               \
    if (Exception_flag == ExceptionEntered) ExceptionPopStack; \
    }                                                          \
    else if (excep.exceptype == &(e)) {                        \
        Exception_flag = ExceptionHandled;

#define EndTry                                                 \
    }                                                          \
    if (Exception_flag == ExceptionEntered) ExceptionPopStack; \
    }                                                          \
    while (0)

void ExceptionThrow(ExceptionType *excep_type, const char *func, const char *file, int line,
                    const char *cause, ...) {
    Exception *excep = pthread_getspecific(ExceptionStack);
    if (excep) {
        pthread_setspecific(ExceptionStack, excep->next);
        excep->exceptype = excep_type;
        int len = sprintf(excep->msg, "%s:%d [%s] ", file, line, func);
        if (cause) {
            va_list ap;
            va_start(ap, cause);
            vsnprintf(excep->msg + len, EXCEPTION_MESSAGE_LENTH - len, cause, ap);
            va_end(ap);
        }
        excep_type->what = excep->msg;

        longjmp(excep->env, ExceptionThrown);
    }
}

#define Throw(e, cause, ...) \
    ExceptionThrow(&(e), __func__, __FILE__, __LINE__, cause, ##__VA_ARGS__, NULL)

ExceptionType A = {"AException"};
ExceptionType B = {"BException"};
ExceptionType C = {"CException"};
ExceptionType D = {"DException"};

void *thread(void *args) {
    pthread_t selfid = pthread_self();

    Try { Throw(A, "A"); }
    Catch(A) { printf("catch A : %ld\n", selfid); }
    EndTry;

    Try { Throw(B, "B"); }
    Catch(B) { printf("catch B : %ld\n", selfid); }
    EndTry;

    Try { Throw(C, "C"); }
    Catch(C) { printf("catch C : %ld\n", selfid); }
    EndTry;

    Try { Throw(D, "D"); }
    Catch(D) { printf("catch D : %ld\n", selfid); }
    EndTry;

    Try {
        Throw(A, "A Again");
        Throw(B, "B Again");
        Throw(C, "C Again");
        Throw(D, "D Again");
    }
    Catch(A) { printf("catch A again : %ld\n", selfid); }
    Catch(B) { printf("catch B again : %ld\n", selfid); }
    Catch(C) { printf("catch C again : %ld\n", selfid); }
    Catch(D) { printf("catch B again : %ld\n", selfid); }
    EndTry;

    return NULL;
}

#define THREADS 50

int main(void) {
    pthread_key_create(&ExceptionStack, NULL);

    Throw(D, NULL);

    Throw(C, "null C");

    printf("=> Test1: Try-Catch\n");
    int tmp;

    Try {
        printf("try A\n");
        Try {
            printf("try B\n");
            Throw(B, "recall B");
        }
        Catch(B) {
            (void)tmp;
            printf("Catch B:%s\n", B.what);
        }
        EndTry;

        Throw(A, NULL);
    }
    Catch(A) {
        (void)tmp;
        printf("Catch A:%s\n", A.what);
    }
    EndTry;

    printf("=> Test1: Ok\n\n");

    printf("=> Test2: Test Thread-safeness\n");
#if 1
    int i = 0;
    pthread_t threads[THREADS];

    for (i = 0; i < THREADS; i++) {
        pthread_create(&threads[i], NULL, thread, NULL);
    }

    for (i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
#endif
    printf("=> Test2: Ok\n\n");
}