//// @file    websocket.c
/// @author  moyin(moyin1004@163.com)
/// @date    2023-12-12 22:30:39

// gcc -Wall -g websocket.c `pkg-config openssl --libs`
#include <arpa/inet.h>
#include <bits/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <malloc.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

enum WS_STATUS {
    WS_INIT,
    WS_HANDSHAKE,
    WS_DATARASFROM,
    WS_DATAEND,
};

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
    int nrecvsucc;

    int wsstatus;
};

int handle_cb(int fd, int event, void *arg);

int accept_cb(int sockfd, int event, void *arg) {
    // struct sockitem *data = (struct sockitem *)arg;
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
    memset(si, 0, sizeof(struct sockitem));
    si->fd = clientfd;
    si->wsstatus = WS_HANDSHAKE;
    si->callback = handle_cb;
    clent_ev.data.ptr = si;
    epoll_ctl(event_loop->epfd, EPOLL_CTL_ADD, clientfd, &clent_ev);
    return 0;
}

int base64_encode(char *in_str, int in_len, char *out_str) {
    BIO *b64, *bio;
    BUF_MEM *bptr = NULL;
    size_t size = 0;

    if (in_str == NULL || out_str == NULL) return -1;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_write(bio, in_str, in_len);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bptr);
    memcpy(out_str, bptr->data, bptr->length);
    out_str[bptr->length - 1] = '\0';
    size = bptr->length;

    BIO_free_all(bio);
    return size;
}

void umask(char *data, int len, char *mask) {
    int i;
    for (i = 0; i < len; i++) *(data + i) ^= *(mask + (i % 4));
}

char *decode_packet(char *stream, char *mask, int length, int *ret);
int encode_packet(char *buffer, char *mask, char *stream, int length);

struct _nty_ophdr {
    unsigned char opcode : 4, rsv3 : 1, rsv2 : 1, rsv1 : 1, fin : 1;
    unsigned char payload_length : 7, mask : 1;

} __attribute__((packed));

struct _nty_websocket_head_126 {
    unsigned short payload_length;
    char mask_key[4];
    unsigned char data[8];
} __attribute__((packed));

struct _nty_websocket_head_127 {
    unsigned long long payload_length;
    char mask_key[4];

    unsigned char data[8];

} __attribute__((packed));

typedef struct _nty_websocket_head_127 nty_websocket_head_127;
typedef struct _nty_websocket_head_126 nty_websocket_head_126;
typedef struct _nty_ophdr nty_ophdr;

char *decode_packet(char *stream, char *mask, int length, int *ret) {
    nty_ophdr *hdr = (nty_ophdr *)stream;
    unsigned char *data = (unsigned char *)stream + sizeof(nty_ophdr);
    int size = 0;
    int start = 0;
    // char mask[4] = {0};
    int i = 0;

    // if (hdr->fin == 1) return NULL;

    if ((hdr->mask & 0x7F) == 126) {
        nty_websocket_head_126 *hdr126 = (nty_websocket_head_126 *)data;
        size = hdr126->payload_length;

        for (i = 0; i < 4; i++) {
            mask[i] = hdr126->mask_key[i];
        }

        start = 8;

    } else if ((hdr->mask & 0x7F) == 127) {
        nty_websocket_head_127 *hdr127 = (nty_websocket_head_127 *)data;
        size = hdr127->payload_length;

        for (i = 0; i < 4; i++) {
            mask[i] = hdr127->mask_key[i];
        }

        start = 14;

    } else {
        size = hdr->payload_length;

        memcpy(mask, data, 4);
        start = 6;
    }

    *ret = size;
    umask(stream + start, size, mask);

    return stream + start;
}

int encode_packet(char *buffer, char *mask, char *stream, int length) {
    nty_ophdr head = {0};
    head.fin = 1;
    head.opcode = 1;

    if (length < 126) {
        head.payload_length = length;
        memcpy(buffer, &head, sizeof(nty_ophdr));
    } else if (length < 0xffff) {
        nty_websocket_head_126 hdr = {0};
        hdr.payload_length = length;
        memcpy(hdr.mask_key, mask, 4);

        memcpy(buffer, &head, sizeof(nty_ophdr));
        memcpy(buffer + sizeof(nty_ophdr), &hdr, sizeof(nty_websocket_head_126));

    } else {
        nty_websocket_head_127 hdr = {0};
        hdr.payload_length = length;
        memcpy(hdr.mask_key, mask, 4);

        memcpy(buffer, &head, sizeof(nty_ophdr));
        memcpy(buffer + sizeof(nty_ophdr), &hdr, sizeof(nty_websocket_head_127));
    }

    memcpy(buffer + 2, stream, length);

    return length + 2;
}

int handle_ws_handshake(struct sockitem *data) {
    if (data->recvbuffer == NULL || data->nrecvsucc <= 4 ||
        strncmp(&data->recvbuffer[data->nrecvsucc - 4], "\r\n\r\n", 4) != 0) {
        return 0;
    }
    char wskey[] = "Sec-WebSocket-Key";
    char *pos = strstr(data->recvbuffer, "\r\n") + 2;
    while (pos + 2 < data->recvbuffer + data->nrecvsucc) {
        char key[512] = {0};
        int keylen = 0;
        char value[512] = {0};
        int vlen = 0;
        while (pos < data->recvbuffer + data->nrecvsucc && *pos != ':') {
            key[keylen++] = *pos;
            ++pos;
        }
        pos += 2;
        while (pos < data->recvbuffer + data->nrecvsucc && *pos != '\r') {
            value[vlen++] = *pos;
            ++pos;
        }

        // printf("%s, %s\n", key, value);
        pos += 2;
        if (strncmp(key, wskey, sizeof(wskey)) == 0) {
            char sha1_data[SHA_DIGEST_LENGTH + 1] = {0};
            strcat(value, "258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
            SHA1((unsigned char *)value, strlen(value), (unsigned char *)&sha1_data);
            char sec_accept[32];
            base64_encode(sha1_data, strlen(sha1_data), sec_accept);
            sprintf(data->sendbuffer,
                    "HTTP/1.1 101 Switching Protocols\r\n"
                    "Upgrade: websocket\r\n"
                    "Connection: Upgrade\r\n"
                    "Sec-WebSocket-Accept: %s\r\n\r\n",
                    sec_accept);
        };
    }
    return 1;
}

int handle_cb(int fd, int event, void *arg) {
    struct sockitem *data = (struct sockitem *)arg;
    struct epoll_event ev;
    if (event & EPOLLIN) {
        int len = recv(fd, data->recvbuffer + data->nrecvsucc,
                       sizeof(data->recvbuffer) - data->nrecvsucc, 0);
        printf("revc, fd:%d, len:%d\n", fd, len);
        if (len > 0) {
            // printf("%s\n", data->recvbuffer);
            data->nrecvsucc += len;
            if (data->wsstatus == WS_HANDSHAKE) {
                if (!handle_ws_handshake(data)) {
                    return len;
                }
            } else if (data->wsstatus == WS_DATARASFROM) {
                int ret = 0;
                char mask[4] = {0};
                char *pos = decode_packet(data->recvbuffer, mask, data->nrecvsucc, &ret);
                printf("data : %s, length : %d\n", pos, ret);
                ret = encode_packet(data->sendbuffer, mask, pos, ret);
            }
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
        memset(data->recvbuffer, 0, sizeof(data->recvbuffer));
        data->nsendsucc = data->nrecvsucc = 0;
        data->wsstatus = WS_DATARASFROM;
        ev.data.ptr = data;
        ev.events = EPOLLOUT;
        epoll_ctl(event_loop->epfd, EPOLL_CTL_MOD, fd, &ev);
    } else if (event & EPOLLOUT) {
        int sendlen = strlen(data->sendbuffer);
        int slen = send(fd, data->sendbuffer + data->nsendsucc, sendlen - data->nsendsucc, 0);
        if (slen >= 0) {
            data->nsendsucc += slen;
            printf("send, fd:%d, len:%d, nsucc:%d\n", fd, slen, data->nsendsucc);
            if (data->nsendsucc == sendlen) {
                data->nsendsucc = 0;
                memset(data->sendbuffer, 0, sizeof(data->sendbuffer));
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
    memset(si, 0, sizeof(struct sockitem));
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