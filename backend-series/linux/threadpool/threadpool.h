#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LL_ADD(item, list)                   \
    do {                                     \
        item->prev = NULL;                   \
        item->next = list;                   \
        if (list != NULL) list->prev = item; \
        list = item;                         \
    } while (0)

#define LL_REMOVE(item, list)                                  \
    do {                                                       \
        if (item->prev != NULL) item->prev->next = item->next; \
        if (item->next != NULL) item->next->prev = item->prev; \
        if (list == item) list = item->next;                   \
        item->prev = item->next = NULL;                        \
        F                                                      \
    } while (0)

struct NJOB {
    void (*func)(void *arg);
    void *user_data;

    struct NJOB *prev;
    struct NJOB *next;
};

struct NMANAGER;

struct NWORKER {
    pthread_t threadid;
    int terminate;
    struct NMANAGER *pool;
    struct NWORKER *prev;
    struct NWORKER *next;
};

typedef struct NMANAGER {
    pthread_mutex_t mtx;
    pthread_cond_t cond;

    struct NJOB *jobs;
    struct NWORKER *workers;
} nThreadPool;

void *thread_callback(void *arg) {
    struct NWORKER *worker = (struct NWORKER *)arg;
    return worker;
}

// api

int nThreadPoolCreate(nThreadPool *pool, int numWorkers) {
    if (numWorkers < 0) numWorkers = 1;
    memset(pool, 0, sizeof(nThreadPool));

    pthread_mutex_t blank_mutex = PTHREAD_MUTEX_INITIALIZER;
    memcpy(&pool->mtx, &blank_mutex, sizeof(pthread_mutex_t));

    pthread_cond_t blank_cond = PTHREAD_COND_INITIALIZER;
    memcpy(&pool->cond, &blank_cond, sizeof(pthread_cond_t));

    int i = 0;
    for (i = 0; i < numWorkers; ++i) {
        struct NWORKER *worker = (struct NWORKER *)malloc(sizeof(struct NWORKER));
        if (worker == NULL) {
            perror("malloc");
            return -1;
        }
        memset(worker, 0, sizeof(struct NWORKER));
        worker->pool = pool;
        int ret = pthread_create(&worker->threadid, NULL, thread_callback, worker);
        if (ret != 0) {
            return ret;
        }
        LL_ADD(worker, pool->workers);
    }
}

int nThreadPoolDestory(nThreadPool *pool) {}

int nThreadPoolPushTask(nThreadPool *pool, struct NJOB *task) {}