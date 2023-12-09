#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

using namespace std;

int main() {
    int sfd[10];
    int sfd_len = 0;
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    addrinfo *res, *rp;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    int ret = getaddrinfo(nullptr, "9090", &hints, &res);
    if (ret != 0) {
        cout << "getaddrinfo err:" << ret << endl;
        return ret;
    }
    for (rp = res; rp != NULL; rp = rp->ai_next) {
        sockaddr_storage ss;
        printf("%s %d, %d %d %d\n", inet_ntop(rp->ai_family, rp->ai_addr, (char *)&ss, sizeof(ss)),
               rp->ai_addrlen, rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        int fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd <= 0) {
            cout << "socket err:" << errno << endl;
            return fd;
        }
        int opt = 1;
        ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt));
        ret = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (const char *)&opt, sizeof(opt));
        if (ret != 0) {
            cout << "setsockopt err:" << errno << endl;
            return ret;
        }
        sfd[sfd_len++] = fd;
        ret = bind(fd, rp->ai_addr, rp->ai_addrlen);
        if (ret != 0) {
            cout << "bind err:" << errno << endl;
            return ret;
        }
    }
    freeaddrinfo(res);
    int use_fd = sfd[1];
    ret = listen(use_fd, 0);
    if (ret != 0) {
        cout << "listen err:" << errno << endl;
        return ret;
    }
    ret = listen(sfd[0], 0);
    if (ret != 0) {
        cout << "listen err:" << errno << endl;
        return ret;
    }
    for (;;) {
        int fd = accept(use_fd, nullptr, nullptr);
        if (fd < 0) {
            cout << "accept err:" << errno << endl;
            return fd;
        }
        char buf[256] = {};
        ssize_t nread = recv(fd, buf, sizeof(buf), 0);
        if (nread > 0) {
            send(fd, buf, nread, 0);
        } else if (errno != ENOTSOCK) {
            cout << nread << " err:" << errno << endl;
        }
    }
    return 0;
}