/// @file    SharedPtr.cc
/// @author  moyin(moyin1004@163.com)
/// @date    2025-03-07 13:28:15

#include <atomic>
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr {
public:
    WeakPtr() {}
    template <typename U>
    WeakPtr(const SharedPtr<U>& sp) noexcept : _ptr(sp._ptr), _cntrl(sp._cntrl) {}
    template <typename U>
    WeakPtr& operator=(const SharedPtr<U>& sp) noexcept {
        WeakPtr(sp).swap(*this);
        return *this;
    }
    ~WeakPtr() {
        _ptr = nullptr;
        _cntrl = nullptr;
    };
    SharedPtr<T> Lock() const noexcept {
        SharedPtr<T> p;
        if (_cntrl) {
            int cur = _cntrl->load();
            while (cur != 0) {
                if (_cntrl->compare_exchange_strong(cur, cur + 1)) {
                    p._cntrl = _cntrl;
                    break;
                }
            }
        }
        if (p._cntrl) {
            p._ptr = _ptr;
        }
        return p;
    }
    bool Expired() const { return _cntrl == nullptr || _cntrl->load() == 0; }

private:
    void swap(WeakPtr& sp) {
        std::swap(_ptr, sp._ptr);
        std::swap(_cntrl, sp._cntrl);
    }

    T* _ptr;
    atomic<int>* _cntrl;
};

template <typename T>
class EnableSharedFromThis {
public:
    SharedPtr<T> SharedFromThis() { return SharedPtr<T>(_weak_this); }
    SharedPtr<const T> SharedFromThis() const {
        // const变量调用此函数
        return SharedPtr<const T>(_weak_this);
    }

protected:
    EnableSharedFromThis() noexcept {}
    // 构造函数
    EnableSharedFromThis(const EnableSharedFromThis&) noexcept {}
    // 拷贝构造函数
    EnableSharedFromThis& operator=(const EnableSharedFromThis&) noexcept { return *this; }
    ~EnableSharedFromThis() {}

private:
    mutable WeakPtr<T> _weak_this;

    template <typename U>
    friend class SharedPtr;
};

template <typename T>
class SharedPtr {
public:
    SharedPtr() noexcept : _ptr(nullptr), _cntrl(nullptr) {}
    SharedPtr(T* p) : _ptr(p) {
        unique_ptr<T> hold(p);
        _cntrl = new atomic<int>(1);
        hold.release();
        __enable_weak_this(p, p);
    }
    SharedPtr(const WeakPtr<T>& sp) : SharedPtr(std::move(sp.Lock())) {
        if (_cntrl == nullptr) {
            throw std::runtime_error("bad_weak_ptr");
        }
    }

    SharedPtr(const SharedPtr& sp) noexcept : _ptr(sp._ptr), _cntrl(sp._cntrl) {
        if (_cntrl) {
            _cntrl->fetch_add(1);
        }
    }
    SharedPtr(SharedPtr&& sp) noexcept : _ptr(sp._ptr), _cntrl(sp._cntrl) {
        sp._ptr = nullptr;
        sp._cntrl = nullptr;
    }

    template <typename Y>
    SharedPtr(const SharedPtr<Y>& sp, T* p) noexcept : _ptr(p), _cntrl(sp._cntrl) {
        if (_cntrl) _cntrl->fetch_add(1);
    }

    SharedPtr& operator=(const SharedPtr& sp) noexcept {
        // 建立一个栈变量 相当于使用了构造函数和析构函数 不用额外定义一个引用计数加减的函数
        SharedPtr(sp).swap(*this);
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& sp) noexcept {
        SharedPtr(std::move(sp)).swap(*this);
        return *this;
    }
    T* operator->() const noexcept { return _ptr; }
    ~SharedPtr() {
        if (_cntrl) {
            if (_cntrl->fetch_sub(1) == 1) {
                cout << "---~SharedPtr delete _ptr" << endl;
                delete _ptr;
                delete _cntrl;
                _ptr = nullptr;
                _cntrl = nullptr;
            }
        }
    }
    void Print() { cout << "---count:" << _cntrl->load() << endl; }

private:
    T* _ptr;
    atomic<int>* _cntrl;

private:
    void swap(SharedPtr& sp) {
        std::swap(_ptr, sp._ptr);
        std::swap(_cntrl, sp._cntrl);
    }

    // 模板重载 如果继承了EnableSharedFromThis 实例化这个
    template <class _Yp, class _OrigPtr>
    typename enable_if<is_convertible<_OrigPtr*, const EnableSharedFromThis<_Yp>*>::value,
                       void>::type
    __enable_weak_this(const EnableSharedFromThis<_Yp>* __e, _OrigPtr* __ptr) noexcept {
        typedef typename remove_cv<_Yp>::type _RawYp;
        if (__e && __e->_weak_this.Expired()) {
            __e->_weak_this =
                SharedPtr<_RawYp>(*this, const_cast<_RawYp*>(static_cast<const _Yp*>(__ptr)));
        }
    }

    // 模板重载 没继承EnableSharedFromThis 实例化这个
    void __enable_weak_this(...) noexcept { cout << "---__enable_weak_this no op" << endl; }

    // 友元
    template <typename U>
    friend class SharedPtr;
    template <typename U>
    friend class WeakPtr;
};

class Data {
public:
    Data(int data) : _data(data) { cout << "---Data()" << endl; }
    ~Data() { cout << "---~Data()" << endl; }

private:
    int _data;
    string _str;
};

class SharedFromThisData : public EnableSharedFromThis<SharedFromThisData> {
public:
    SharedFromThisData(int data) : _data(data) { cout << "---SharedFromThisData()" << endl; }
    ~SharedFromThisData() { cout << "---~SharedFromThisData()" << endl; }

    void Process(vector<SharedPtr<SharedFromThisData>>& vec) {
        vec.emplace_back(this->SharedFromThis());
    }
    void Print() { cout << "---_data:" << _data << endl; }

private:
    int _data;
    string _str;
};

// g++ SharedPtr.cc -g -Wall
int main() {
    SharedPtr<Data> sp1(new Data(1));
    SharedPtr<Data> sp2(sp1);
    SharedPtr<Data> sp3 = sp2;
    SharedPtr<Data> sp4 = std::move(sp3);
    WeakPtr<Data> wp1(sp4);
    sp1.Print();  // 引用计数应该是3

    cout << endl;
    cout << "--------------------------" << endl;
    vector<SharedPtr<SharedFromThisData>> vec;
    // 会初始化内部的_weak_this
    SharedPtr<SharedFromThisData> ssp1(new SharedFromThisData(1));
    ssp1->Process(vec);
    SharedPtr<SharedFromThisData> ssp2(new SharedFromThisData(2));
    ssp2->Process(vec);
    for (auto& sp : vec) {
        sp->Print();
    }

    try {
        auto p = new SharedFromThisData(3);
        p->Process(vec); // throw 因为内部的weak_ptr是无效的
    } catch (std::exception &ex) {
        cout << "catch exception " << ex.what() << endl;
    }

    return 0;
}