/// @file    set_num_threads.c
/// @author  moyin(moyin1004@163.com)
/// @date    2023-11-04 22:39:26

// gcc openmp.c -fopenmp
#include <omp.h>
#include <stdio.h>

void pooh(int ID, double *A) { A[ID] = ID; }

int main() {
    double A[100] = {0};
    omp_set_num_threads(4);
#pragma omp parallel
    {
        int ID = omp_get_thread_num();
        pooh(ID, A);
        printf("A of ID(%d) = %lf\n", ID, A[ID]);
    }
    return 0;
}