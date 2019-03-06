/// @file    qsort.cc
/// @data    2019-01-21 20:21:05

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;
using std::swap;

int Partition(int A[], int left, int right) {  //以left位置数据的为主元
    int temp = A[left];
    while(left < right) {
        while(left < right && A[right] > temp) right--;
        A[left] = A[right]; //右侧小于主元的数据放到左边
        while(left < right && A[left] <= temp) left++;
        A[right] = A[left]; //左侧大于主元的数据放到右侧
    }
    A[left] = temp; //left == right
    return left;
}

//随机主元
int randPartition(int A[], int left, int right) {
    int p = (round(1.0*rand() / RAND_MAX*(right - left) + left));
    swap(A[p], A[left]);
    int temp = A[left];
    while(left < right) {
        while(left < right && A[right] > temp) right--;
        A[left] = A[right];
        while(left < right && A[left] <= temp) left++;
        A[right] = A[left];
    }
    A[left] = temp; //left == right
    return left;
}

void quickSort(int A[], int left, int right) {
    if(left < right) {
        int pos = randPartition(A, left, right);
        quickSort(A, left, pos - 1);  //排序left右边部分
        quickSort(A, pos + 1, right); //排序left左边部分
    }
}

int main() {
    int a[] = {1, 5, 11, 432, 44, 5, 431, 567, 55, 85};
    quickSort(a, 0, 9);
    for (auto &elem : a)
        cout << elem << endl;
    return 0;
}
