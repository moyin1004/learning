#define _GNU_SOURCE 1
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

    int epfd = epoll_create(1);
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

    // 足够大的发送数据 用于测试ET模式send
    int nsucc = 0;
    int sbuffer_len = 10240000;
    char *sbuffer = (char *)malloc(sbuffer_len * sizeof(char));
    memset(sbuffer, 'h', sbuffer_len * sizeof(char));

    struct epoll_event events[100];
    while (1) {
        int ret = epoll_wait(epfd, events, sizeof(events), 50);
        if (ret) {
            for (int i = 0; i < ret; ++i) {
                if (events[i].data.fd == sockfd) {
                    struct sockaddr_in client_addr;
                    socklen_t client_len = 0;
                    int clientfd = accept4(sockfd, (struct sockaddr *)&client_addr, &client_len,
                                           SOCK_NONBLOCK);
                    if (clientfd < 0) {
                        return clientfd;
                    }
                    // setsockopt(clientfd, SOL_SOCKET, SOCK_NONBLOCK, &opt, sizeof(int));
                    struct sockaddr_storage addr;
                    printf("add:%d, ip:%s\n", clientfd,
                           inet_ntop(AF_INET, &client_addr, (char *)&addr,
                                     sizeof(struct sockaddr_storage)));
                    struct epoll_event clent_ev;
                    clent_ev.events = EPOLLIN | EPOLLET;
                    clent_ev.data.fd = clientfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &clent_ev);
                } else if (events[i].events & EPOLLIN) {
                    char buffer[5] = {0};
                recv:
                    int len = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                    printf("revc, fd:%d, len:%d\n", events->data.fd, len);
                    if (len > 0) {
                        // https://man7.org/linux/man-pages/man7/epoll.7.html
                        // 基于数据流的文件描述符判断是否读完缓冲区 send时判断len < sizeof(buffer)
                        // if (len == sizeof(buffer)) {
                        //     goto recv;
                        // }
                        goto recv;
                    } else if (len == 0) {
                        printf("close:%d\n", events[i].data.fd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                        close(events[i].data.fd);
                    } else if (errno == EINTR) {
                        goto recv;
                    } else if (errno == EAGAIN) {
                        // 所有文件描述符判断是否读完缓冲区
                        printf("socket noblock, recv errno:%d\n", errno);
                    } else {
                        printf("recv error:%d\n", errno);
                        break;
                    }
                    nsucc = 0;
                    events[i].events = EPOLLIN | EPOLLET | EPOLLOUT;
                    epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &events[i]);
                } else if (events[i].events & EPOLLOUT) {
                send:
                    int slen = send(events[i].data.fd, sbuffer + nsucc, sbuffer_len - nsucc, 0);
                    if (slen >= 0) {
                        nsucc += slen;
                        printf("send, fd:%d, len:%d, nsucc:%d\n", events->data.fd, slen, nsucc);
                        if (nsucc < sbuffer_len) {
                            goto send;
                        } else {  // 发送完成
                            events[i].events = EPOLLIN | EPOLLET;
                            epoll_ctl(epfd, EPOLL_CTL_MOD, events[i].data.fd, &events[i]);
                        }
                    } else if (slen < 0 && errno == EAGAIN) {
                        // 所有文件描述符判断是否写完缓冲区
                        printf("socket noblock, send errno:%d\n", errno);
                    } else {
                        printf("send error:%d\n", errno);
                    }
                }
            }
            printf("\n");
        } else if (ret == 0) {
        } else {
            printf("error:%d\n", errno);
            break;
        }
    }
    close(sockfd);
    close(epfd);

    return 0;
}