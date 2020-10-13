#include "sort.h"
#include <cmath>

void InsertSort(int A[], int n) {
    for (int i = 1; i < n; ++i) {
        if (A[i] >= A[i-1]) continue;
        for (int j = i - 1; j >= 0 && A[j] > A[j+1]; --j) swap(A[j], A[j+1]);
    }
}

// 插入升级
void ShellSort(int A[], int n) {
    int d = n / 2, i, j;
    int temp;
    for (d = n/2; d > 0; d /= 2) {     //步长变化
        for (int i = d; i < n; ++i) {
            if (A[i] >= A[i-d]) continue;
            temp = A[i];
            for (j = i-d; j >= 0 && A[j] > A[j+d]; j -= d) swap(A[j+d], A[j]);
        }
    }
}

void BubbleSort(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = n-1; j > 0; --j) {
            if (A[j] < A[j-1]) {
                swap(A[j], A[j-1]);
                flag = true;
            }
        }
        if (!flag) return ;
    }
}

void DBubbleSort(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = n-1; j > i; --j) {
            if (A[j] < A[j-1]) {
                swap(A[j], A[j-1]);
                flag = true;
            }
        }
        if (!flag) return ;
    }
}

void QSort(int A[], int l, int r) {
    if (l >= r) return ;
    int bound = A[l];
    int i = l, j = r;
    while (i <= j) {
        while (A[i] < bound) ++i;
        while (bound < A[j]) --j;
        if (i <= j) swap(A[i++], A[j--]);
    }
    QSort(A, l, j);
    QSort(A, i, r);
}

int Partition(int A[], int low, int high) {
    int pivot = A[low];
    while (low < high) {
        while (low < high && A[high] >= pivot) --high;
        A[low] = A[high];
        while (low < high && A[low] <= pivot) ++low;
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}
void QuickSort(int A[], int low, int high) {
    if (low >= high) return ;
    int pivotpos = Partition(A, low, high);
    QuickSort(A, low, pivotpos-1);
    QuickSort(A, pivotpos+1, high);
}

void SelectSort(int A[], int n) {
    for (int i = 0; i < n-1; ++i) {
        int minx = i;
        for (int j = i+1; j < n; ++j) {
            if (A[j] < A[minx]) minx = j;
        }
        if (minx != i) swap(A[i], A[minx]);
    }
}

void ListSelectSort(LinkList L) {
    LNode *rear = L->next;
    while (rear) {
        LNode *min_p = rear;
        LNode *q = rear->next;
        while (q) {
            min_p = min_p->data < q->data ? min_p : q;
            q = q->next;
        }
        swap(min_p->data, rear->data);
        rear = rear->next;
    }
}

void PercDown(ElemType A[], int p, int N) {
  /* 改编代码4.24的PercDown( MaxHeap H, int p )    */
  /* 将N个元素的数组中以A[p]为根的子堆调整为最大堆 */
    int Parent, Child;
    ElemType X;
 
    X = A[p]; /* 取出根结点存放的值 */
    for (Parent = p; (Parent*2+1) < N; Parent = Child) {
        Child = Parent * 2 + 1;
        if ((Child != N-1) && (A[Child] < A[Child+1]))
            Child++;  /* Child指向左右子结点的较大者 */
        if (X >= A[Child]) break; /* 找到了合适位置 */
        else  /* 下滤X */
            A[Parent] = A[Child];
    }
    A[Parent] = X;
}

void MinHeap(ElemType A[], int p, int n) {
    int parent, child;
    ElemType x;
    x = A[p];

    for (parent = p; parent * 2 + 1 < n; parent = child) {
        child = parent*2+1;
        if (child != n-1 && A[child] > A[child+1]) ++child;
        if (x <= A[child]) break;
        else A[parent] = A[child];
    }
    A[parent] = x;
}

void HeapInsert(ElemType A[], int n, ElemType x) {
    A[n] = x;
    int parent;
    for (int i = n; ceil(i/2) + 1 >= 0; i = parent) {
        parent = ceil(i/2) + 1;
        if (A[i] < A[parent]) swap(A[i], A[parent]);
    }
}

void HeapDelete(ElemType A[], int n, int i) {
    A[i] = A[n-1];
    MinHeap(A, n-1, i);
}

void HeapSort(ElemType A[], int N) { /* 堆排序 */
     int i;
     for (i = N/2-1; i >= 0; --i)/* 建立最大堆 */
         PercDown(A, i, N);

     for (i = N-1; i > 0; --i) {
         /* 删除最大堆顶 */
         swap(A[0], A[i]);
         PercDown(A, 0, i);
     }
}

void Merge(ElemType A[], int l, int r) {
    int mid = l + (r-l) / 2;
    int i = l, j = mid;
    ElemType temp[r-l+1];
    int pos = 0;;
    while (i < mid && j < r) {
        if (A[i] < A[j]) temp[pos++] = A[i++];
        else  temp[pos++] = A[j++];
    }
    while (i < mid) temp[pos++] = A[i++];
    while (j < r) temp[pos++] = A[j++];
    for (int k = 0; k < pos; ++k) {
        A[l+k] = temp[k];
    }
}

void MergeSort(ElemType A[], int l, int r) {
    if (l >= r-1) return ;
    int mid = l + (r-l) / 2;
    MergeSort(A, l, mid);
    MergeSort(A, mid, r);
    Merge(A, l, r);
}