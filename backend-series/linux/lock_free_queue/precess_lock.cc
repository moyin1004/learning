#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int inc(int *value, int add) {
    int old;
    __asm__ volatile (
        "lock; xaddl %2, %1;" // lock锁总线 %2加到%1上
        : "=a" (old)          // 将结果从eax寄存器输出到变量old。
        : "m" (*value), "a" (add)
        : "cc", "memory"      // 内存屏障
    );
    return old;
}
/*
多进程 原子操作
 Performance counter stats for './a.out':

                 0      cache-misses
                18      context-switches

       0.019309623 seconds time elapsed

       0.112884000 seconds user
       0.007870000 seconds sys
*/


void *func(void *arg) {
    int *pcount = (int *)arg;
    int i = 0;
    while (i++ < 100000) {
        // (*pcount)++;
        inc(pcount, 1);
        // this_thread::sleep_for(1us);
    }
    return nullptr;
}

int main() {
    auto start = chrono::system_clock::now();
    int *pcount =
        (int *)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    pid_t pid[10] = {0};
    pid_t cur_pid = 0;
    for (int i = 0; i < 10; ++i) {
        cur_pid = pid[i] = fork();
        if (pid[i] <= 0) {
            break;
        }
    }
    if (cur_pid > 0) {
        for (int i = 0; i < 10; ++i) {
            waitpid(pid[i], NULL, 0);
        }
        cout << *pcount << endl;
        auto end = chrono::system_clock::now();
        cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    } else {
        func(pcount);
    }

    return 0;
}