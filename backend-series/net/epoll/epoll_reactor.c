#include <arpa/inet.h>
#include <bits/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// 设置非阻塞
static int ntySetNonblock(int fd) {
    int flags;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return flags;
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) return -1;
    return 0;
}

// mainloop / eventloop
struct reactor {
    int epfd;
    struct epoll_event events[1024];
};

struct reactor *event_loop;

struct sockitem {
    int fd;
    int (*callback)(int fd, int event, void *arg);
    char recvbuffer[1024];
    char sendbuffer[1024];
    int nsendsucc;
};

int handle_cb(int fd, int event, void *arg);

int accept_cb(int sockfd, int event, void *arg) {
    struct sockitem *data = (struct sockitem *)arg;
    struct sockaddr_in client_addr;
    socklen_t client_len = 0;
    int clientfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if (clientfd < 0) {
        return clientfd;
    }
    ntySetNonblock(clientfd);
    struct sockaddr_storage addr;
    printf("add:%d, ip:%s\n", clientfd,
           inet_ntop(AF_INET, &client_addr, (char *)&addr, sizeof(struct sockaddr_storage)));
    struct epoll_event clent_ev;
    clent_ev.events = EPOLLIN;
    struct sockitem *si = (struct sockitem *)malloc(sizeof(struct sockitem));
    memset(data->sendbuffer, 'h', sizeof(data->sendbuffer));
    data->nsendsucc = 0;
    si->fd = clientfd;
    si->callback = handle_cb;
    clent_ev.data.ptr = si;
    epoll_ctl(event_loop->epfd, EPOLL_CTL_ADD, clientfd, &clent_ev);
    return 0;
}

int handle_cb(int fd, int event, void *arg) {
    struct sockitem *data = (struct sockitem *)arg;
    struct epoll_event ev;
    if (event & EPOLLIN) {
        int len = recv(fd, data->recvbuffer, sizeof(data->recvbuffer), 0);
        printf("revc, fd:%d, len:%d\n", fd, len);
        if (len > 0) {
        } else if (len == 0) {
            printf("close:%d\n", fd);
            epoll_ctl(event_loop->epfd, EPOLL_CTL_DEL, fd, NULL);
            close(fd);
            free(data);
            return 0;
        } else if (errno == EINTR || errno == EAGAIN) {
            printf("socket noblock, recv errno:%d\n", errno);
        } else {
            printf("recv error:%d\n", errno);
            return len;
        }
        data->nsendsucc = 0;
        ev.data.ptr = data;
        ev.events = EPOLLIN | EPOLLOUT;
        epoll_ctl(event_loop->epfd, EPOLL_CTL_MOD, fd, &ev);
    } else if (event & EPOLLOUT) {
        int slen = send(fd, data->sendbuffer + data->nsendsucc,
                        sizeof(data->sendbuffer) - data->nsendsucc, 0);
        if (slen >= 0) {
            data->nsendsucc += slen;
            printf("send, fd:%d, len:%d, nsucc:%d\n", fd, slen, data->nsendsucc);
            if (data->nsendsucc == sizeof(data->sendbuffer)) {
                // 发送完成 取消EPOLLOUT
                ev.events = EPOLLIN;
                ev.data.ptr = data;
                epoll_ctl(event_loop->epfd, EPOLL_CTL_MOD, fd, &ev);
            }
        } else if (errno == EINTR || errno == EAGAIN) {
            printf("socket noblock, send errno:%d\n", errno);
        } else {
            printf("send error:%d\n", errno);
            return slen;
        }
    }
    return 0;
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in))) {
        return -2;
    }

    if (listen(sockfd, 5) < 0) {
        return -3;
    }
    event_loop = (struct reactor *)malloc(sizeof(struct reactor));

    event_loop->epfd = epoll_create(1);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    struct sockitem *si = (struct sockitem *)malloc(sizeof(struct sockitem));
    si->fd = sockfd;
    si->callback = accept_cb;
    ev.data.ptr = si;
    epoll_ctl(event_loop->epfd, EPOLL_CTL_ADD, sockfd, &ev);

    while (1) {
        int ret = epoll_wait(event_loop->epfd, event_loop->events, sizeof(event_loop->events), 50);
        if (ret) {
            for (int i = 0; i < ret; ++i) {
                struct sockitem *data = (struct sockitem *)event_loop->events[i].data.ptr;
                data->callback(data->fd, event_loop->events[i].events, data);
            }
            printf("\n");
        } else if (ret == 0) {
        } else {
            printf("error:%d\n", errno);
            break;
        }
    }
    close(sockfd);
    close(event_loop->epfd);
    free(si);
    free(event_loop);

    return 0;
}