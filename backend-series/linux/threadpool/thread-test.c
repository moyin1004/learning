#include <stdio.h>
#include <unistd.h>

#include "threadpool.h"

void task(void *arg) {
    struct NJOB *job = (struct NJOB *)arg;
    int num = *(int *)job->user_data;
    int ans = 0;
    for (int i = 0; i < num*num; ++i) {
        ans += i;
    }
    printf("threadid:%ld %d %d\n", pthread_self(), num, ans);
    free(job->user_data);
    free(job);
}

int main() {
    nThreadPool *pool = (nThreadPool *)malloc(sizeof(nThreadPool));
    nThreadPoolCreate(pool, 6);
    for (int i = 0; i < 100; ++i) {
        struct NJOB *job = malloc(sizeof(struct NJOB));
        memset(job, 0, sizeof(struct NJOB));
        job->func = task;
        int *num = malloc(sizeof(int));
        *num = i;
        job->user_data = num;
        nThreadPoolPushTask(pool, job);
    }
    sleep(1);
    nThreadPoolDestory(pool);
    free(pool);
}