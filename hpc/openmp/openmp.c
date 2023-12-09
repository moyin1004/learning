#include <omp.h>
#include <stdio.h>

#define MAXNTHREADS 1024

static long num_steps = 1000000000;
double step, single_time;

void single_test() {
    int i, actual_nthreads;
    double sum, start_time, run_time;
    step = 1.0 / (double)num_steps;
    double x;
    sum = 0.0;
    start_time = omp_get_wtime();
    for (i = 0; i < num_steps; ++i) {
        x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }
    double pi = step * sum;
    run_time = omp_get_wtime() - start_time;
    printf("pi = %lf, %lf secs\n", pi, run_time);
    single_time = run_time;
}

void test(int num_threads) {
    int actual_nthreads;
    double start_time, run_time;
    step = 1.0 / (double)num_steps;
    double sum[MAXNTHREADS] = {0.0};
    omp_set_num_threads(num_threads);
    start_time = omp_get_wtime();
#pragma omp parallel
    {
        double x;
        int i;
        int ID = omp_get_thread_num();
        int nthread = omp_get_num_threads();
        if (ID == 0) actual_nthreads = nthread;
        // for (i = ID; i < num_steps; i += nthread) {
        //     x = (i + 0.5) * step;
        //     sum[ID] += 4.0 / (1.0 + x * x);
        // }
        int istart = ID * num_steps / nthread;
        int iend = (ID + 1) * num_steps / nthread;
        for (i = istart; i < iend; ++i) {
            x = (i + 0.5) * step;
            sum[ID] += 4.0 / (1.0 + x * x);
        }
    }

    double res = 0.0;
    for (int i = 0; i < actual_nthreads; ++i) {
        res += sum[i];
    }
    res = res * step;
    run_time = omp_get_wtime() - start_time;
    printf("pi = %lf, %lf secs, s(p) = %lf , %d thrds\n", res, run_time,
           single_time / run_time, actual_nthreads);
}

int main() {
    single_test();
    test(12);
    // test(64);
    // test(128);
    // test(256);
    // test(256 + 128);
    // test(512);
    // test(512 + 128);
    // test(512 + 256);
    return 0;
}