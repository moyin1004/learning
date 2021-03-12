/// @file    server.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2021-03-10 10:58:45

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <cstring>
#include <iostream>
#include <string>
#include <functional>
#include <deque>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

#define SERVER_PORT     10800
#define SERVER_IP       "127.0.0.1"
#define MAX_BUFFER      128
#define MAX_EPOLLSIZE   100000
#define MAX_THREAD      8
#define MAX_PORT        100

#define TIME_SUB_MS(tv1, tv2)  ((tv1.tv_sec - tv2.tv_sec) * 1000 + (tv1.tv_usec - tv2.tv_usec) / 1000)
#define ERROR_EXIT(msg) do{\
        cerr << msg << endl;\
        exit(EXIT_FAILURE);\
} while(0)

class ThreadPool {
public:
    using TaskFunc = function<void()>;
    // 禁止拷贝与赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool &operator=(const ThreadPool&) = delete;
    ThreadPool(uint32_t num = 4)
        :_threadNum(num),
        _isExit(false)
    {
        init();
    }

    ~ThreadPool() {
        while (!_taskQue.empty()) {
            usleep(100);
        }
        _isExit = true;
        // 唤醒所有线程并回收资源
        _notnull.notify_all();
        for (auto &t : _threadPool) {
            cout << "thread id:" << t->get_id() << endl;
            t.get()->join();
        }
    }

    // 添加任务
    void addTask(TaskFunc &&task) {
        // 自动加解锁
        std::lock_guard<mutex> guard(_taskMutex);
        _taskQue.push_back(std::move(task));
        _notnull.notify_one();
    }

private:
    static void threadFunc(void *);
    void init() {
        for (uint32_t i = 0; i < _threadNum; ++i) {
            unique_ptr<thread> up(new thread(std::bind(ThreadPool::threadFunc, this)));
            _threadPool.push_back(std::move(up));
        }
    }
    void run() {
        while (!_isExit) {
            std::unique_lock<mutex> guard(_taskMutex); // 配合条件变量使用
            while (_taskQue.empty() && !_isExit) {
                _notnull.wait(guard);
            }
            if (_isExit) break;
            TaskFunc &task = _taskQue.front();
            task();
            _taskQue.pop_front();
        }
    }
    uint32_t _threadNum;
    bool _isExit;
    vector <unique_ptr<thread>> _threadPool;
    deque<TaskFunc> _taskQue;
    mutex _taskMutex;
    condition_variable _notnull;
    int thread_id;
};

void ThreadPool::threadFunc(void *arg) {
    ThreadPool *p = reinterpret_cast<ThreadPool*>(arg);
    p->run();
}

// 设置非阻塞
static int ntySetNonblock(int fd) {
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return flags;
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) return -1;
    return 0;
}

static int ntySetReUseAddr(int fd) {
    int reuse = 1;
    return setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
}

static int curfds = 1;
static int nRun = 0;

void client_data_process(int clientfd, int epoll_fd) {
    char buffer[MAX_BUFFER];
    bzero(buffer, MAX_BUFFER);
    int ret = recv(clientfd, buffer, MAX_BUFFER, 0);
    if (ret > 0) {	
        if (nRun) {
            printf("TcpRecv --> curfds : %d, buffer: %s\n", curfds, buffer);
            send(clientfd, "quit", 4, 0);
        }
        else send(clientfd, buffer, strlen(buffer), 0);
    } else if (ret == 0 || ret == ENOTCONN) {
        epoll_event ev;
        ev.events = EPOLLIN;
        ev.data.fd = clientfd;
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, clientfd, &ev);
        printf("disconnect %d\n", clientfd);
        close(clientfd);
        --curfds;
    }
}

int listenfd(int fd, int *fds) {
    for (int i = 0; i < MAX_PORT; ++i) {
        if (fd == *(fds+i)) return *(fds+i);
    }
    return 0;
}

int main() {
    int sockfds[MAX_PORT] = {0};
    int epoll_fd = epoll_create(MAX_EPOLLSIZE);
    for (int i = 0; i < MAX_PORT; ++i) {
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            ERROR_EXIT("socket");
        }

        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(struct sockaddr_in));
        addr.sin_family = AF_INET;
        addr.sin_port = htons(SERVER_PORT+i);
        addr.sin_addr.s_addr = INADDR_ANY;
        if (bind(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0) {
            ERROR_EXIT("bind");
        }
        if (listen(sockfd, 5) < 0) {
            ERROR_EXIT("listen");
        }
        sockfds[i] = sockfd;
        cout << "C1000k Server Listen on Port:" << SERVER_PORT+i << endl;

        struct epoll_event ev;
        ev.events = EPOLLIN | EPOLLET;
        ev.data.fd = sockfd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sockfd, &ev);
    }

    struct timeval tv_begin;
    gettimeofday(&tv_begin, NULL);
    struct epoll_event events[MAX_EPOLLSIZE];
    ThreadPool *p_tp = new ThreadPool(MAX_THREAD);
    while (1) {
        int nfds = epoll_wait(epoll_fd, events, curfds, -1);
        if (nfds == 0) break;
        if (nfds == -1) {
            cerr << "epoll_wait" << endl;
            break;
        }
        for (int i = 0;i < nfds; ++i) {
            int sockfd = listenfd(events[i].data.fd, sockfds);
            struct epoll_event ev;
            if (sockfd) {
                struct sockaddr_in client_addr;
                memset(&client_addr, 0, sizeof(struct sockaddr_in));
                socklen_t client_len = sizeof(client_addr);

                int clientfd = ::accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
                if (clientfd < 0) {
                    return clientfd;
                }

                ev.events = EPOLLIN;
                ev.data.fd = clientfd;

                if (curfds++ > 1000 * 1008) {
                    nRun = 1;
                }
                if (curfds % 1000 == 999) {
                    struct timeval tv_cur;
                    memcpy(&tv_cur, &tv_begin, sizeof(struct timeval));
                    gettimeofday(&tv_begin, NULL);
                    int time_used = TIME_SUB_MS(tv_begin, tv_cur);
                    printf("connections: %d, sockfd:%d, time_used:%d\n", curfds, clientfd, time_used);
                }

                ntySetNonblock(clientfd);
                ntySetReUseAddr(clientfd);

                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, clientfd, &ev);
            } else {
                int clientfd = events[i].data.fd;
                if (nRun) {
                    printf("New Data is Comming: ");
                    client_data_process(clientfd, epoll_fd);
                } else {
                    p_tp->addTask(std::bind(client_data_process, clientfd, epoll_fd));
                }
            }
        } // end for
    } // end while

    close(epoll_fd);
    delete p_tp;
    return 0;
}
