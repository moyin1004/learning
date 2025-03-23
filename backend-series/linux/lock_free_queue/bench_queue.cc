#include <benchmark/benchmark.h>

#include <iostream>

#include "mutex_queue.h"
#include "spsc.h"

using namespace std;

static SPSCQueue<int, 1000> queue;
static void BM_QueueSPSC(benchmark::State& state) {
    const bool is_consumer = state.thread_index() % 2 == 0;  // 奇数线程生产，偶数线程消费

    for (auto _ : state) {
        if (is_consumer) {
            int value;
            while (!queue.Read(&value)) {
            }  // 忙等待
            benchmark::DoNotOptimize(value);
            state.counters["consume cnt"] += 1;
        } else {
            state.counters["produce cnt"] += 1;
            queue.Write(state.thread_index(), false);
            queue.Flush();
        }
    }

    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_QueueSPSC)->Threads(2)->UseRealTime();

static LimitMutexQueue<int> limit_mutex_queue(100000);
static void BM_LimitQueueMutex(benchmark::State& state) {
    const bool is_consumer = state.thread_index() % 2 == 0;  // 奇数线程生产，偶数线程消费

    for (auto _ : state) {
        if (is_consumer) {
            int value;
            limit_mutex_queue.pop(value);  // 阻塞
            benchmark::DoNotOptimize(value);
            state.counters["consume cnt"] += 1;
        } else {
            while (!limit_mutex_queue.push(state.thread_index())) {
                std::this_thread::sleep_for(1us);
            }
            state.counters["produce cnt"] += 1;
        }
    }

    state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_LimitQueueMutex)
    ->Threads(4)  // 4线程（2生产+2消费）
    ->UseRealTime();

static MutexQueue<int> mutex_queue(10000);
static void BM_QueueMutex(benchmark::State& state) {
    const bool is_consumer = state.thread_index() % 2 == 0;  // 奇数线程生产，偶数线程消费

    for (auto _ : state) {
        if (is_consumer) {
            int value;
            mutex_queue.pop(value);  // 阻塞
            benchmark::DoNotOptimize(value);
            state.counters["consume cnt"] += 1;
        } else {
            mutex_queue.push(state.thread_index());
            state.counters["produce cnt"] += 1;
        }
    }

    state.SetItemsProcessed(state.iterations());
}

// 线程数越多，性能越差
BENCHMARK(BM_QueueMutex)
    ->Threads(4)  // 4线程（2生产+2消费）
    ->UseRealTime();

BENCHMARK_MAIN();