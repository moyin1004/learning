#include <atomic>
#include <functional>
#include <thread>

// zmq方案
template <typename T, int N>
class YQueue {
public:
    YQueue() : _begin_pos(0), _back_pos(0), _end_pos(0) {
        _begin_chunk = (Chunk *)malloc(sizeof(Chunk));
        if (_begin_chunk == nullptr) [[unlikely]] {
            throw std::bad_alloc();
        }
        _back_chunk = nullptr;
        _end_chunk = _begin_chunk;
    }
    ~YQueue() {
        while (true) {
            if (_begin_chunk == _end_chunk) {
                free(_begin_chunk);
                break;
            }
            Chunk *o = _begin_chunk;
            _begin_chunk = _begin_chunk->next;
            free(o);
        }
        Chunk *sc = _spare_chunk.exchange(nullptr);
        if (sc != nullptr) {
            free(sc);
        }
    }
    void push() {
        _back_chunk = _end_chunk;
        _back_pos = _end_pos;
        if (++_end_pos != N) {
            return;
        }
        Chunk *sc = _spare_chunk.exchange(nullptr);
        if (sc) {
            _end_chunk->next = sc;
            sc->prev = _end_chunk;
        } else {
            _end_chunk->next = (Chunk *)malloc(sizeof(Chunk));
            if (_begin_chunk == nullptr) [[unlikely]] {
                throw std::bad_alloc();
            }
            _end_chunk->next->prev = _end_chunk;
        }
        _end_chunk = _end_chunk->next;
        _end_pos = 0;
    }

    void pop() {
        if (++_begin_pos != N) {
            return;
        }
        Chunk *bc = _begin_chunk;
        _begin_chunk = _begin_chunk->next;
        _begin_chunk->prev = nullptr;
        _begin_pos = 0;
        // 由于局部性原理，总是保存最新的空闲块而释放先前的空闲块
        Chunk *sc = _spare_chunk.exchange(bc);
        free(sc);
    }

    T &front() { return _begin_chunk->values[_begin_pos]; }

    T &back() { return _back_chunk->values[_back_pos]; }

private:
    YQueue(const YQueue &) = delete;
    YQueue &operator=(const YQueue &) = delete;

    struct Chunk {
        T values[N];  // 每个chunk_t可以容纳N个T类型的元素，以后就以一个chunk_t为单位申请内存
        Chunk *prev;
        Chunk *next;
    };
    Chunk *_begin_chunk;
    int _begin_pos;
    Chunk *_back_chunk;
    int _back_pos;
    Chunk *_end_chunk;
    int _end_pos;
    std::atomic<Chunk *> _spare_chunk;
};

template <typename T, int N>
class SPSCQueue {
public:
    SPSCQueue() {
        _queue.push();
        _r = _w = _f = &_queue.back();
        _c.store(&_queue.back());
    }
    ~SPSCQueue() {}

    void Write(const T &value, bool incomplete) {
        _queue.back() = value;
        _queue.push();
        if (!incomplete) {
            _f = &_queue.back();
        }
    }

    void Write(T &&value, bool incomplete) {
        _queue.back() = std::move(value);
        _queue.push();
        if (!incomplete) {
            _f = &_queue.back();
        }
    }

    // 刷新写入 不再撤回
    bool Flush() {
        if (_w == _f) {
            return true;
        }
        if (!_c.compare_exchange_strong(_w, _f)) {
            _c.store(_f);
            _w = _f;
            return false;
        }
        _w = _f;
        return true;
    }

    bool CheckRead() {
        if (&_queue.front() != _r && _r) {
            return true;
        }
        _r = &_queue.front();
        bool succ = _c.compare_exchange_strong(_r, nullptr);
        // 成功交换说明没有可读的元素
        if (succ || !_r) {
            return false;
        }
        return true;
    }

    bool Read(T *value) {
        if (!CheckRead()) {
            return false;
        }
        *value = std::move(_queue.front());
        _queue.pop();
        return true;
    }

private:
    YQueue<T, N> _queue;
    T *_w;
    T *_r;
    T *_f;
    std::atomic<T *> _c; // 用于读写位置交换
    SPSCQueue(const SPSCQueue &) = delete;
    SPSCQueue &operator=(const SPSCQueue &) = delete;
};
