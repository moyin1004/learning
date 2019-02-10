/// @file    Vector.h
/// @data    2019-01-23 17:49:07
 
#ifndef __VECTOR_H__
#define __VECTOR_H__
    
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

template<typename T>
class Vector {
public:
    typedef T value_type;
    typedef T *iterator;

    Vector();
    ~Vector();

    void push_back(const T &);
    void pop_back();

    int size() const;
    int capacity() const;

    iterator begin() {  return _start;  }
    iterator end() {  return _finish;  }

    T &operator[](std::size_t idx); 

private:
    void reallocate();
    static std::allocator<T> _alloc;

    T *_start;
    T *_finish;
    T *_end_of_storage;
};

template <class T>
std::allocator<T> Vector<T>::_alloc;

template<typename T>
Vector<T>::Vector() 
: _start(nullptr)
, _finish(nullptr)
, _end_of_storage(nullptr)
{}

template<typename T>
Vector<T>::~Vector() {
    if (_start) {
        while (_finish != _start)
            _alloc.destroy(--_finish);   //删数据
        _alloc.deallocate(_start, capacity());  //释放空间
    }
//    delete []_start;
}

template<typename T>
void Vector<T>::push_back(const T &lhs) {
    if (capacity() == size())
        reallocate();
    _alloc.construct(_finish++, lhs);
    
//    *_finish++ = lhs;
}


template<typename T>
void Vector<T>::pop_back() {
    if (!size()) {
        cout << "Don't have data" << endl;
        return ;
    }
    _alloc.destroy(--_finish);

//    _finish--;
}

template<typename T>
void Vector<T>::reallocate() {
    int oldCapacity = capacity();
    int newCapacity = oldCapacity > 0 ? 2 * oldCapacity : 1;

    T *ptpm = _alloc.allocate(newCapacity);

    if (_start) {
        std::uninitialized_copy(_start, _finish, ptpm);
        while (_finish != _start) 
            _alloc.destroy(--_finish);
    }

    _start = ptpm;
    _finish = _start + oldCapacity;
    _end_of_storage = _start + newCapacity;

//    int cap = capacity();
//    T *start = new T[cap*2]();
//    T *finish = start;
//    _finish = _start;
//    while (_finish != _end_of_storage) {
//        *finish = *_finish;
//        ++_finish;
//        ++finish;
//    }
//    delete []_start;
//    _start = start;
//    _finish = finish;
//    _end_of_storage = _start + cap * 2;
}

template<typename T>
T &Vector<T>::operator[](std::size_t idx) {
    return _start[idx];
}

template<typename T>
int Vector<T>::size() const {
    return _finish - _start;
}

template<typename T>
int Vector<T>::capacity() const {
    return _end_of_storage - _start;
}

#endif
