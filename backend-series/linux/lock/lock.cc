#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

int count = 0;
atomic<int> acount = 0;

mutex m;

// sudo perf stat -e cache-misses,context-switches ./a.out
/*
 上下文切换明显大于try_lock
 lock
 Performance counter stats for './a.out':

                 0      cache-misses
             10897      context-switches

       0.053451341 seconds time elapsed

       0.070899000 seconds user
       0.264028000 seconds sys
 
linux spinlock 总体时间和lock差不大 上下文切换远小于lock
 Performance counter stats for './a.out':

                 0      cache-misses
                45      context-switches

       0.078062290 seconds time elapsed

       0.568795000 seconds user
       0.002015000 seconds sys

 try_lock
 Performance counter stats for './a.out':

                 0      cache-misses
               187      context-switches

       0.335082337 seconds time elapsed

       2.545921000 seconds user
       0.003074000 seconds sys

 // 原子变量
 Performance counter stats for './a.out':

                 0      cache-misses
                26      context-switches

       0.019057565 seconds time elapsed

       0.124730000 seconds user
       0.000000000 seconds sys

*/


// mov dest, src at&t
// mov src, dest x86
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

void *func(void *arg) {
    cout << this_thread::get_id() << endl;
    int *pcount = (int *)arg;
    int i = 0;
    while (i++ < 100000) {
        {
            unique_lock<mutex> lg(m, try_to_lock);
            if (!lg) {
                i--;
                continue;
            }
            // unique_lock lg(m);
            // (*pcount)++;
            inc(pcount, 1);
            // acount++; // 比锁快2倍多
        }
        // this_thread::sleep_for(1us);
    }
    return nullptr;
}

int main() {
    auto start = chrono::system_clock::now();
    thread th[10];    
    for (int i = 0; i < 10; ++i) {
        th[i] = thread(func, &count);
    }
    for (int i = 0; i < 10; ++i) {
        th[i].join();
    }
    cout << count << " " << acount.load() << endl;
    auto end =  chrono::system_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end-start).count() << endl;
    return 0;
}