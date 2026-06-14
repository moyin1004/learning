#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

/*
 * Demonstrates why atomic_thread_fence is necessary.
 *
 * Example 1: Producer-consumer with non-atomic payload
 *   Without fence: consumer may read stale data (ARM/PowerPC).
 *   With release/acquire fences: ordering guaranteed, no data race.
 *
 * Example 2: Store->load reordering (seq_cst fence)
 *   Two threads each write their own atomic, then read the other's.
 *   Without seq_cst fence: CPU store-buffer can cause BOTH r1 AND r2
 *   to be 0 -- store->load reordering lets each load pass its own store.
 *   With seq_cst fence: r1 && r2 == 0 is impossible (SC holds).
 *   Release-store + acquire-load on the atomics CANNOT fix this:
 *   release only orders prior writes, acquire only orders subsequent
 *   reads -- neither prevents a load from passing a prior store.
 *
 * Example 3: Multiple non-atomic payloads published via a fence
 *   The fence provides a standalone release/acquire point without
 *   needing to attach ordering to any one atomic operation.
 */

// ============================================================
// Example 1: Producer-Consumer (relaxed atomics + fences)
// ============================================================

void example1_fixed(int iterations) {
    int data = 0;
    atomic<bool> ready{false};
    int failures = 0;

    for (int i = 0; i < iterations; ++i) {
        data = 0;
        ready.store(false, memory_order_relaxed);
        atomic_thread_fence(memory_order_seq_cst);

        thread writer([&] {
            data = 42;
            atomic_thread_fence(memory_order_release);
            ready.store(true, memory_order_relaxed);
        });

        thread reader([&] {
            while (!ready.load(memory_order_relaxed));
            atomic_thread_fence(memory_order_acquire);
            if (data != 42) ++failures;
        });

        writer.join();
        reader.join();
    }

    cout << "[Example 1 - FIXED]  " << failures << " / " << iterations
         << " stale reads (should be 0)\n";
}

void example1_broken(int iterations) {
    int data = 0;
    atomic<bool> ready{false};
    int failures = 0;

    for (int i = 0; i < iterations; ++i) {
        data = 0;
        ready.store(false, memory_order_relaxed);
        atomic_thread_fence(memory_order_seq_cst);

        thread writer([&] {
            data = 42;
            ready.store(true, memory_order_relaxed);  // no ordering
        });

        thread reader([&] {
            while (!ready.load(memory_order_relaxed));
            if (data != 42) ++failures;  // data race
        });

        writer.join();
        reader.join();
    }

    cout << "[Example 1 - BROKEN] " << failures << " / " << iterations
         << " stale reads (would fail on ARM; TSAN detects it)\n";
}

// ============================================================
// Example 2: Store->load reordering
//
// T0: x = 1;  r0 = y;
// T1: y = 1;  r1 = x;
//
// The key question: can r0 == 0 AND r1 == 0 ?
//   Without seq_cst fence: YES  (store->load reordering)
//   With seq_cst fence:    NO   (SC total order enforced)
// ============================================================

void example2_fixed(int iterations) {
    atomic<int> x{0}, y{0};
    int both_zero = 0;

    for (int i = 0; i < iterations; ++i) {
        x.store(0, memory_order_relaxed);
        y.store(0, memory_order_relaxed);
        atomic_thread_fence(memory_order_seq_cst);

        atomic<bool> go{false};
        int r0 = -1, r1 = -1;

        thread t0([&] {
            while (!go.load(memory_order_relaxed));
            x.store(1, memory_order_relaxed);
            atomic_thread_fence(memory_order_seq_cst);  // ★
            r0 = y.load(memory_order_relaxed);
        });

        thread t1([&] {
            while (!go.load(memory_order_relaxed));
            y.store(1, memory_order_relaxed);
            atomic_thread_fence(memory_order_seq_cst);  // ★
            r1 = x.load(memory_order_relaxed);
        });

        go.store(true, memory_order_relaxed);
        t0.join();
        t1.join();

        if (r0 == 0 && r1 == 0) ++both_zero;
    }

    cout << "[Example 2 - FIXED]  r0==0 && r1==0: " << both_zero << " / " << iterations;
    if (both_zero > 0)
        cout << "  ← UNEXPECTED (fence should prevent this)\n";
    else
        cout << "  ← Correct: SC holds\n";
}

void example2_broken(int iterations) {
    atomic<int> x{0}, y{0};
    int both_zero = 0;

    for (int i = 0; i < iterations; ++i) {
        x.store(0, memory_order_relaxed);
        y.store(0, memory_order_relaxed);
        atomic_thread_fence(memory_order_seq_cst);

        atomic<bool> go{false};
        int r0 = -1, r1 = -1;

        thread t0([&] {
            while (!go.load(memory_order_relaxed));
            x.store(1, memory_order_relaxed);
            // NO fence — load of y may be reordered before store of x
            r0 = y.load(memory_order_relaxed);
        });

        thread t1([&] {
            while (!go.load(memory_order_relaxed));
            y.store(1, memory_order_relaxed);
            // NO fence
            r1 = x.load(memory_order_relaxed);
        });

        go.store(true, memory_order_relaxed);
        t0.join();
        t1.join();

        if (r0 == 0 && r1 == 0) ++both_zero;
    }

    cout << "[Example 2 - BROKEN] r0==0 && r1==0: " << both_zero << " / " << iterations;
    if (both_zero > 0)
        cout << "  ← store->load reordering DETECTED!\n";
    else
        cout << "  (not observed on this run — try more iterations)\n";
}

// ============================================================
// Example 3: Multiple non-atomic payloads + fence
// ============================================================

void example3_multiple_payloads() {
    int a = 0, b = 0, c = 0;
    atomic<bool> done{false};

    thread writer([&] {
        a = 100;
        b = 200;
        c = 300;
        // atomic_thread_fence(memory_order_release);
        done.store(true, memory_order_relaxed);
        // while (done.load(memory_order_relaxed));
        // a = b = c = 400;
    });

    thread reader([&] {
        while (!done.load(memory_order_relaxed));
        // atomic_thread_fence(memory_order_acquire);
        if (a != 100 || b != 200 || c != 300)
            cout << "[Example 3] FAILED: a=" << a << " b=" << b << " c=" << c << "\n";
        // else
        //     cout << "[Example 3] PASSED: all payloads visible\n";
        // cout << "a=" << a << " b=" << b << " c=" << c << "\n";
        // done.store(false, memory_order_relaxed);
    });

    writer.join();
    reader.join();
}

// ============================================================

int main() {
    const int N1 = 1000;   // producer-consumer (slow: creates N1*2 threads)
    const int N2 = 50000;  // store-load test    (fast: creates N2*2 threads)

    cout << "=== Example 1: Producer-Consumer (release/acquire fences) ===\n";
    example1_fixed(N1);
    example1_broken(N1);

    cout << "\n=== Example 2: Store->Load ordering (seq_cst fence) ===\n";
    example2_fixed(N2);
    example2_broken(N2);

    cout << "\n=== Example 3: Multiple non-atomic payloads ===\n";
    example3_multiple_payloads();

    return 0;
}
