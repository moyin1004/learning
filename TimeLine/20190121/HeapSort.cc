/// @file    HeapSort.cc
/// @data    2019-01-21 20:21:45
 
#include <iostream>
#include <cmath>
 
using std::cout;
using std::endl;
using std::ostream;

template <typename T, typename Compare = std::less<T> >
class HeapSort {
public:
    HeapSort(T *arr, int size) 
    : _data(arr)
    , _size(size)
    {}

    void heapAdjust(int low, int high) {  //从右至左，从下之上，依次调整
        Compare c;
        int i = low;
        int j = i*2 + 1;
        T temp = _data[i];
        while (j <= high) {
            if (j + 1 < high && c(_data[j], _data[j+1])) //比较左右儿子
                ++j;
            if (c(temp, _data[j])) { //比较父节点与较大的儿子
                _data[i] = _data[j];
                i = j;
                j = 2*i + 1;
            }
            else
                break;
        }
        _data[i] = temp;
    }

    void sort() {
        T temp;
        for (int i = _size/2 - 1; i >= 0; --i)
            heapAdjust(i, _size);
        for (int i = _size - 1; i >= 1; --i) {
            temp = _data[0];
            _data[0] = _data[i];
            _data[i] = temp;
            heapAdjust(0, i - 1); //升序排序时每次循环 依次把当前最大值放到从数组后往前放
        }
    }

private:
    T *_data;
    int _size;
};

class Point {
public:
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    {}

    friend bool operator<(const Point &lhs,const Point &rhs);
    friend ostream &operator<<(ostream &os, const Point &p);
private:
    int _ix;
    int _iy;
};

bool operator<(const Point &lhs, const Point &rhs) {
    return (hypot(lhs._ix, lhs._iy) < hypot(rhs._ix, rhs._iy));
}

ostream &operator<<(ostream &os, const Point &p) {
    cout << "(" << p._ix << "," << p._iy << ")";
    return os;
}

void test1() {
    int a[] = {1, 32, 31, 4, 8, 9, 1232, 43, 47};
    HeapSort<int, std::greater<int>> hs(a, 9);
    hs.sort();
    for (auto &elem : a)
        cout << elem << endl;
}
 
void test2() {
    Point a[] = {Point(), Point(-1, -1), Point(3, 4), Point(0, 1)};
    HeapSort<Point> hs(a, 4);
    hs.sort();
    for (auto &elem : a) {
       cout << elem << endl;
    }
}

int main() {
    cout << "int sort :" << endl;
    test1();
    cout << "Point sort :" << endl;
    test2();

    return 0;
}
