#pragma once

#include <initializer_list>

template <typename T>
class Vector {
public:
    // Vector();

    Vector(std::initializer_list<T> init) {
        msize = init.size();
        mdata = new T[msize];
        int i = 0;
        for (auto& elem : init) {
            mdata[i++] = elem;
        }
    }

    // there are 3 candidates 需要使用推导指引
    template <typename Iter>
    Vector(Iter begin, Iter end) {}
    struct Iterator {
        using difference_type = T*;
        using value_type = T;
        T* data;
        Iterator(T* data) : data(data) {}
        T& operator*() { return *data; }
        Iterator& operator++() {
            data++;
            return *this;
        }
        Iterator operator+(int n) {
            Iterator tmp(*this);
            for (int i = 0; i < n; i++) {
                tmp.data++;
            }
            return tmp;
        }
        bool operator!=(const Iterator& other) { return data != other.data; }
    };
    Iterator begin() { return {mdata}; }
    Iterator end() { return {mdata + msize}; }

    ~Vector() { delete[] mdata; }

private:
    int msize = 0;
    T* mdata;
};

// 使用推导指引 也可以使用concepts
template <typename Iter>
Vector(Iter begin, Iter end) -> Vector<typename Iter::value_type>;

void test_construct() {
    Vector v1 = {1, 2, 3};
    Vector v2(v1.begin(), v1.begin() + 2);
}
