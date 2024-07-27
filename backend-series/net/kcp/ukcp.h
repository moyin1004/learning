#ifndef __UKCP_H__
#define __UKCP_H__

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "ikcp.h"

constexpr int MTU_SIZE = 577;  // 576+1

struct UUserData {
    int fd = 0;
    sockaddr_in addr;
};

inline int output(const char *buf, int len, ikcpcb *kcp, void *user) {
    auto data = reinterpret_cast<UUserData *>(user);
    int sendlen = sendto(data->fd, buf, len, 0, (sockaddr *)&data->addr, sizeof(sockaddr_in));
    if (sendlen < 0) {
        printf("len:%d, sendlen:%d, errno:%d\n", len, sendlen, errno);
    }
    return 0;
}

class UKcp {
public:
    UKcp(int conv, const UUserData &data) : m_data(data) {
        m_ikcp = ikcp_create(conv, &m_data);
        ikcp_setoutput(m_ikcp, output);
    };
    ~UKcp() {}

    void Send(const char *buf, int len) {
        int ret = ikcp_send(m_ikcp, buf, len);
        if (ret < 0) {
            printf("ikcp_send ret:%d\n", ret);
        }
    }

    std::string Revc() {
        char real_buf[MTU_SIZE + 1] = {0};
        int ret = ikcp_recv(m_ikcp, real_buf, sizeof(real_buf));
        if (ret >= 0) {
            return std::string(real_buf, ret);
        }
        return "";
    }

    void RevcFrom() {
        char buffer[MTU_SIZE] = {0};
        sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        socklen_t addrlen = sizeof(sockaddr_in);
        int len = recvfrom(m_data.fd, buffer, sizeof(buffer), 0, (sockaddr *)&clientaddr, &addrlen);
        if (len > 0) {
            this->Input(buffer, len);
        } else if (errno == EAGAIN) {
        } else {
            printf("recvfrom fd:%d, ret:%d, err:%d\n", m_data.fd, len, errno);
        }
    }

    void Input(const char *buf, int len) {
        int ret = ikcp_input(m_ikcp, buf, len);
        if (ret < 0) {
            printf("ikcp_input ret:%d\n", ret);
        }
    }

    void Update() {
        IUINT32 now = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
        m_next = ikcp_check(m_ikcp, now);
        if (m_next == now) {
            ikcp_update(m_ikcp, now);
        } else {
            std::cout << "kcp next update time:" << m_next << std::endl;
        }
    }

    ikcpcb *GetIkcp() { return m_ikcp; }
    UUserData &GetUUserData() { return m_data; }

private:
private:
    ikcpcb *m_ikcp;
    UUserData m_data;
    IUINT32 m_next;
};

#endif