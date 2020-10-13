#include <iomanip>
#include "util.h"

void Print(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        cout << setw(3) << A[i] << " ";
    }
    cout << endl;
}

void Copy(int a[], int b[], int n) {
    for (int i = 0; i < n; ++i) {
        b[i] = a[i];
    }
}

void PrintFunction(const char *s) {
    cout << "======" << s << "=======" << endl;
}