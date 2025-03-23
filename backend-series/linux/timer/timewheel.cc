#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <thread>

using namespace std;

struct Timer {
    int id;
    int exec_time;
    using TimerCallback = function<bool()>;
    TimerCallback callback;
    bool cancel;
};

class TimeWheel {
public:
    TimeWheel(int tickMs) : _tick_ms(tickMs), _cur_times(128) {
        _timers.resize(2, std::vector<std::list<shared_ptr<Timer>>>(32));
    }
    ~TimeWheel() {
        if (_th) {
            _th->join();
            delete _th;
            _th = nullptr;
        }
    }

    void Start() { _th = new thread(bind(&TimeWheel::work, this)); }
    void Stop() { _stop_flag = true; }
    shared_ptr<Timer> AddTimer(int delay_ms, Timer::TimerCallback callback) {
        lock_guard lg(_m);
        auto timer = make_shared<Timer>();
        timer->callback = callback;
        timer->exec_time = _cur + delay_ms / _tick_ms;
        if (timer->exec_time <= 0) {
            callback();
        } else {
            this->addTimer(timer);
        }
        return timer;
    }

private:
    void addTimer(shared_ptr<Timer> &timer) {
        int num = _cur_times.size();
        int level_size = _timers[0].size();
        int diff = timer->exec_time - _cur;
        if (diff < num) {
            _cur_times[diff % num].push_back(timer);
        } else {
            diff /= num;
            int level = diff / level_size;
            int idx = diff % level_size;
            if (level >= static_cast<int>(_timers.size())) {
                throw runtime_error("exceed timer limit");
            }
            _timers[level][idx].push_back(timer);
        }
    }
    void work() {
        cout << "work" << endl;
        while (!_stop_flag) {
            lock_guard lg(_m);
            int num = _cur_times.size();
            // cout << "_cur:" << _cur << endl;
            auto &timers = _cur_times[this->_cur % num];
            for (auto it = timers.begin(); it != timers.end();) {
                if (!(*it)->cancel) {
                    (*it)->callback();
                }
                it = timers.erase(it);
            }
            ++this->_cur;
            if (this->_cur % num != 0) {
                this_thread::sleep_for(_tick_ms * 1ms);
                continue;
            }
            int level = this->_cur / num;
            int level_size = _timers[0].size();
            for (size_t i = 0; i < _timers.size() && level; ++i) {
                int idx = level % level_size;
                // 高层的第一层都是轮空的，数据已经在下一层了
                if (idx > 0) {
                    auto &timers = _timers[i][idx];
                    for (auto it = timers.begin(); it != timers.end();) {
                        this->addTimer(*it);
                        it = timers.erase(it);
                    }
                }
                level /= level_size;
            }
            this_thread::sleep_for(_tick_ms * 1ms);
        }
    }

    int _cur = 0;
    const int64_t _tick_ms;
    std::vector<std::list<shared_ptr<Timer>>> _cur_times;
    std::vector<std::vector<std::list<shared_ptr<Timer>>>> _timers;
    mutex _m;
    atomic<bool> _stop_flag;
    thread *_th;
};

// g++ timewheel.cc -std=c++20 -g  -Wall -O2

int64_t get_cur_ms() {
   return chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count();
}

int main() {
    cout << "hello world" << endl;
    TimeWheel th(10);
    th.AddTimer(2, [&]() {
        cout << "timer:" << "2" << "," << get_cur_ms() << endl;
        return true;
    });
    th.AddTimer(8, [&]() {
        cout << "timer:" << "8" << "," << get_cur_ms() << endl;
        return true;
    });
    th.AddTimer(15, [&]() {
        cout << "timer:" << "15" << "," << get_cur_ms() << endl;
        return true;
    });
    th.AddTimer(33*128*10, [&]() {
        cout << "timer:" << 33*128*10 << "," << get_cur_ms() << endl;
        return true;
    });
    th.Start();
    th.AddTimer(60, [&]() {
        cout << "timer:" << 60 << "," << get_cur_ms() << endl;
        return true;
    });
    this_thread::sleep_for(50s);
    try {
        th.AddTimer(128*32*32*10+20, [&]() {
            cout << "timer:" << 128*32*32*10+20 << "," << get_cur_ms() << endl;
            return true;
        });
    } catch (exception &ex) {
        cout << ex.what() << endl;
    }
    th.Stop();
    return 0;
}