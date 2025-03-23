#include <condition_variable>
#include <mutex>
#include <vector>
#include <list>


// 内存对齐到cacheline 效果并不明显
// 增加数组大小在压测时比较明显
template <typename T>
class alignas(64) LimitMutexQueue {
public:
    LimitMutexQueue(size_t size) : _datas(size) {}
    ~LimitMutexQueue() {}

    bool push(const T& value) {
        // 使用条件变量比外层使用循环慢
        {
            std::lock_guard lg(_m);
            if (_start == _end + 1 % _datas.size()) {
                return false;
            }
            _datas[_end] = value;
            _end = (_end + 1) % _datas.size();
        }
        _cond.notify_one();
        return true;
    }

    void pop(T& value) {
        std::unique_lock lk(_m);
        _cond.wait(lk, [this]() { return _start != _end; });
        value = _datas[_start];
        _start = (_start + 1) % _datas.size();
    }

private:
    std::mutex _m;
    std::condition_variable _cond;
    std::vector<T> _datas;
    int _start = 0;
    int _end = 0;
};

// 实测比内存连续的数组慢
template <typename T>
class MutexQueue {
public:
    MutexQueue(size_t size) : _datas(size) {}
    ~MutexQueue() {}

    void push(const T& value) {
        {
            std::lock_guard lg(_m);
            _datas.push_back(value);
        }
        _cond.notify_one();
    }

    void pop(T& value) {
        std::unique_lock lk(_m);
        _cond.wait(lk, [this]() { return !_datas.empty(); });
        value = _datas.front();
        _datas.pop_front();
    }

private:
    std::mutex _m;
    std::condition_variable _cond;
    std::list<T> _datas;
};