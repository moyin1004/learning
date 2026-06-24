#define _GNU_SOURCE 1
#include "threadpool.h"

#include <assert.h>
#include <pthread.h>
#include <sched.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

struct threadpool* threadpool_init(int thread_num, int queue_max_num) {
    struct threadpool* pool = NULL;
    do {
        pool = malloc(sizeof(struct threadpool));
        if (NULL == pool) {
            printf("failed to malloc threadpool!\n");
            break;
        }
        pool->thread_num = thread_num;
        pool->queue_max_num = queue_max_num;
        pool->queue_cur_num = 0;
        pool->head = NULL;
        pool->tail = NULL;
        if (pthread_mutex_init(&(pool->mutex), NULL)) {
            printf("failed to init mutex!\n");
            break;
        }
        if (pthread_cond_init(&(pool->queue_empty), NULL)) {
            printf("failed to init queue_empty!\n");
            break;
        }
        if (pthread_cond_init(&(pool->queue_not_empty), NULL)) {
            printf("failed to init queue_not_empty!\n");
            break;
        }
        if (pthread_cond_init(&(pool->queue_not_full), NULL)) {
            printf("failed to init queue_not_full!\n");
            break;
        }
        pool->pthreads = malloc(sizeof(pthread_t) * thread_num);
        if (NULL == pool->pthreads) {
            printf("failed to malloc pthreads!\n");
            break;
        }
        pool->queue_close = 0;
        pool->pool_close = 0;
        int i;
        for (i = 0; i < pool->thread_num; ++i) {
            pthread_create(&(pool->pthreads[i]), NULL, threadpool_function, (void*)pool);
        }

        return pool;
    } while (0);

    return NULL;
}

int threadpool_add_job(struct threadpool* pool, void* (*callback_function)(void* arg), void* arg) {
    assert(pool != NULL);
    assert(callback_function != NULL);
    assert(arg != NULL);

    pthread_mutex_lock(&(pool->mutex));
    while ((pool->queue_cur_num == pool->queue_max_num) &&
           !(pool->queue_close || pool->pool_close)) {
        pthread_cond_wait(&(pool->queue_not_full), &(pool->mutex));  // 队列满的时候就等待
    }
    if (pool->queue_close || pool->pool_close)  // 队列关闭或者线程池关闭就退出
    {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }
    struct job* pjob = (struct job*)malloc(sizeof(struct job));
    if (NULL == pjob) {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }
    pjob->callback_function = callback_function;
    pjob->arg = arg;
    pjob->next = NULL;
    if (pool->head == NULL) {
        pool->head = pool->tail = pjob;
        pthread_cond_broadcast(
            &(pool->queue_not_empty));  // 队列空的时候，有任务来时就通知线程池中的线程：队列非空
    } else {
        pool->tail->next = pjob;
        pool->tail = pjob;
    }
    pool->queue_cur_num++;
    pthread_mutex_unlock(&(pool->mutex));
    return 0;
}

static uint64_t get_tick_count() {
    struct timeval tval;
    uint64_t ret_tick;

    gettimeofday(&tval, NULL);

    ret_tick = tval.tv_sec * 1000L + tval.tv_usec / 1000L;
    return ret_tick;
}

int s_cup_num = 1;
int s_used_cpu_bind = 0;
void* threadpool_function(void* arg) {
    struct threadpool* pool = (struct threadpool*)arg;
    struct job* pjob = NULL;

    if (s_used_cpu_bind) {
        printf("use cpu bind\n");
        cpu_set_t mask;

        CPU_ZERO(&mask);
        pthread_mutex_lock(&(pool->mutex));
        CPU_SET(s_cup_num++, &mask);
        pthread_mutex_unlock(&(pool->mutex));
        if (pthread_setaffinity_np(pthread_self(), sizeof(mask), &mask) < 0) {
            perror("pthread_setaffinity_np");
        }
    }

    uint64_t start_time = get_tick_count();
    uint64_t end_time = get_tick_count();
    while (1)  // 死循环
    {
        pthread_mutex_lock(&(pool->mutex));
        while ((pool->queue_cur_num == 0) && !pool->pool_close)  // 队列为空时，就等待队列非空
        {
            end_time = get_tick_count();
            pthread_cond_wait(&(pool->queue_not_empty), &(pool->mutex));
        }
        if (pool->pool_close)  // 线程池关闭，线程就退出
        {
            printf("threadpool need time:%lums\n", end_time - start_time);
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }
        pool->queue_cur_num--;
        pjob = pool->head;
        if (pool->queue_cur_num == 0) {
            pool->head = pool->tail = NULL;
        } else {
            pool->head = pjob->next;
        }
        if (pool->queue_cur_num == 0) {
            pthread_cond_signal(
                &(pool->queue_empty));  // 队列为空，就可以通知threadpool_destroy函数，销毁线程函数
        }
        if (pool->queue_cur_num == pool->queue_max_num - 1) {
            pthread_cond_broadcast(
                &(pool->queue_not_full));  // 队列非满，就可以通知threadpool_add_job函数，添加新任务
        }
        pthread_mutex_unlock(&(pool->mutex));

        (*(pjob->callback_function))(pjob->arg);  // 线程真正要做的工作，回调函数的调用
        free(pjob);
        pjob = NULL;
    }
}
int threadpool_destroy(struct threadpool* pool) {
    assert(pool != NULL);
    pthread_mutex_lock(&(pool->mutex));
    if (pool->queue_close || pool->pool_close)  // 线程池已经退出了，就直接返回
    {
        pthread_mutex_unlock(&(pool->mutex));
        return -1;
    }

    pool->queue_close = 1;  // 置队列关闭标志
    while (pool->queue_cur_num != 0) {
        pthread_cond_wait(&(pool->queue_empty), &(pool->mutex));  // 等待队列为空
    }

    pool->pool_close = 1;  // 置线程池关闭标志
    pthread_mutex_unlock(&(pool->mutex));
    pthread_cond_broadcast(&(pool->queue_not_empty));  // 唤醒线程池中正在阻塞的线程
    pthread_cond_broadcast(&(pool->queue_not_full));  // 唤醒添加任务的threadpool_add_job函数
    int i;
    for (i = 0; i < pool->thread_num; ++i) {
        pthread_join(pool->pthreads[i], NULL);  // 等待线程池的所有线程执行完毕
    }

    pthread_mutex_destroy(&(pool->mutex));  // 清理资源
    pthread_cond_destroy(&(pool->queue_empty));
    pthread_cond_destroy(&(pool->queue_not_empty));
    pthread_cond_destroy(&(pool->queue_not_full));
    free(pool->pthreads);
    struct job* p;
    while (pool->head != NULL) {
        p = pool->head;
        pool->head = p->next;
        free(p);
    }
    free(pool);
    return 0;
}

#define FOR_COUNT 1000
#define TASK_NUMBER 1000000
void do_for_test(int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        sum += i;
    }
}

void* work(void* arg) {
    char* p = (char*)arg;
    do_for_test(FOR_COUNT);
}
// gcc -o threadpool threadpool.c -D_GUN_SOURCE -lpthread
// main函数加入任务，线程池处理任务
int main(int argc, char* argv[]) {
    int thread_num = 1;  // 默认使用1个线程
    if (argc != 1) {
        thread_num = atoi(argv[1]);
    }
    if (argc == 3) {
        s_used_cpu_bind = atoi(argv[2]);
    }
    printf("thread_num = %d\n", thread_num);
    struct threadpool* pool = threadpool_init(thread_num, TASK_NUMBER);  // 线程池处理任务
    while (1)                                                            // main 任务生产
    {
        for (int i = 0; i < TASK_NUMBER; i++) {
            threadpool_add_job(pool, work, "1");
        }
        printf("生产%d任务\n", TASK_NUMBER);
        usleep(1000 * 1000);  // 休息一小会
        // usleep(100);
    }

    sleep(2);
    threadpool_destroy(pool);

    return 0;
}