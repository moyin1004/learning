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

enum class UKcpOpcode : int8_t {
    kHandshake = 0x1,
    kHandshakeRsp = 0x2,
    kData = 0x3,
};

class UKcp {
public:
    UKcp(int conv, const UUserData& data) : m_data(data) {
        m_ikcp = ikcp_create(conv, this);
        ikcp_setoutput(m_ikcp, [](const char* buf, int len, ikcpcb* kcp, void* user) {
            auto ukcp_obj = static_cast<UKcp*>(user);
            char real_buf[MTU_SIZE + 1] = {0};
            real_buf[0] = static_cast<char>(UKcpOpcode::kData);
            memcpy(&real_buf[1], buf, len);
            printf("ikcp output conv:%d, fd:%d, len:%d\n", ukcp_obj->GetConv(), ukcp_obj->m_data.fd,
                   len);
            int sendlen = sendto(ukcp_obj->m_data.fd, real_buf, len + 1, 0,
                                 (sockaddr*)&ukcp_obj->m_data.addr, sizeof(sockaddr_in));
            int conv = ukcp_obj->GetConv();
            if (sendlen < 0) {
                printf("ikcp output conv:%d, fd:%d, len:%d, sendlen:%d, errno:%d, msg:%s\n", conv,
                       ukcp_obj->m_data.fd, len, sendlen, errno, strerror(errno));
            }
            return 0;
        });
    };
    ~UKcp() { ikcp_release(m_ikcp); }

    void Send(const char* buf, int len) {
        int ret = ikcp_send(m_ikcp, buf, len);
        if (ret < 0) {
            printf("ikcp_send conv:%d, fd:%d, ret:%d\n", GetConv(), m_data.fd, ret);
        }
    }

    std::string Recv() {
        char real_buf[MTU_SIZE + 1] = {0};
        int ret = ikcp_recv(m_ikcp, real_buf, sizeof(real_buf));
        if (ret > 0) {
            return std::string(real_buf, ret);
        } else if (errno == EAGAIN) {
        } else {
            printf("ikcp_recv conv:%d, fd:%d, ret:%d, err:%d\n", GetConv(), m_data.fd, ret, errno);
        }
        return "";
    }

    void Update() {
        IUINT32 now = std::chrono::duration_cast<std::chrono::milliseconds>(
                          std::chrono::system_clock::now().time_since_epoch())
                          .count();
        m_next = ikcp_check(m_ikcp, now);
        if (m_next == now) {
            ikcp_update(m_ikcp, now);
        }
    }

    int GetConv() { return ikcp_getconv(m_ikcp); }
    UUserData& GetUUserData() { return m_data; }
    void Input(const char* buf, int len) {
        if (buf[0] == static_cast<char>(UKcpOpcode::kData) && len > 1) {
            int ret = ikcp_input(m_ikcp, &buf[1], len - 1);
            if (ret < 0) {
                printf("ikcp_input conv:%d, fd:%d, ret:%d\n", GetConv(), m_data.fd, ret);
            }
        }
    }

private:
private:
    ikcpcb* m_ikcp;
    UUserData m_data;
    IUINT32 m_next;
};

class UKcpAcceptor {
public:
    UKcpAcceptor() {
        m_fd = socket(AF_INET, SOCK_DGRAM, 0);
        int flags = O_ASYNC | O_NONBLOCK;
        fcntl(m_fd, F_SETFL, flags);
        sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(8080);

        // Bind the socket with the server address
        int ret = bind(m_fd, (const struct sockaddr*)&servaddr, sizeof(servaddr));
        if (ret < 0) {
            close(m_fd);
            m_fd = 0;
            throw std::runtime_error("bind err:" + std::to_string(errno));
        }
    }

    std::shared_ptr<UKcp> Accept() {
        char buffer[MTU_SIZE] = {0};
        sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        socklen_t addrlen = sizeof(sockaddr_in);
        int len = recvfrom(m_fd, buffer, sizeof(buffer), 0, (sockaddr*)&clientaddr, &addrlen);
        if (len > 0) {
            auto conn_it = m_client_conns.find(reinterpret_cast<sockaddr*>(&clientaddr)->sa_data);
            printf("acceptor recv opcode:%d\n", buffer[0]);
            switch (UKcpOpcode(buffer[0])) {
                case UKcpOpcode::kHandshake: {
                    // int newfd = socket(AF_INET, SOCK_DGRAM, 0);
                    // int flags = O_ASYNC | O_NONBLOCK;
                    // fcntl(newfd, F_SETFL, flags);
                    char rsp[MTU_SIZE] = {0};
                    rsp[0] = static_cast<char>(UKcpOpcode::kHandshakeRsp);
                    memcpy(&rsp[1], &cur_conv, sizeof(int));
                    sendto(m_fd, rsp, strlen(rsp), 0, (sockaddr*)&clientaddr, sizeof(sockaddr_in));
                    UUserData data;
                    data.addr = clientaddr;
                    data.fd = m_fd;
                    // int ret =
                    //     connect(m_fd, (const struct sockaddr*)&clientaddr, sizeof(clientaddr));
                    // if (ret != 0) {
                    //     close(newfd);
                    //     newfd = 0;
                    //     throw std::runtime_error("connect err:" + std::to_string(errno));
                    // }
                    printf("acceptor accept conv:%d\n", cur_conv);
                    if (conn_it == m_client_conns.end()) {
                        conn_it = m_client_conns
                                      .insert(std::make_pair(
                                          reinterpret_cast<sockaddr*>(&clientaddr)->sa_data,
                                          std::make_shared<UKcp>(cur_conv++, data)))
                                      .first;
                    }
                    return conn_it->second;
                }
                case UKcpOpcode::kData: {
                    if (conn_it == m_client_conns.end()) {
                        printf("acceptor error no conn conv:%d\n", buffer[1]);
                        break;
                    }
                    conn_it->second->Input(buffer, len);
                    conn_it->second->Update();
                    break;
                }
                default:
                    printf("acceptor error opcode:%d\n", buffer[0]);
                    break;
            }
        } else if (errno == EAGAIN) {
        } else {
            printf("acceptor recvfrom fd:%d, ret:%d, err:%d\n", m_fd, len, errno);
        }
        return nullptr;
    }
    union {
        UKcpOpcode op;
        int conv;
    };

    void Update() {
        for (auto& elem : m_client_conns) {
            elem.second->Update();
        }
    }

private:
    int m_fd;
    int cur_conv = 0x2;
    std::unordered_map<std::string, std::shared_ptr<UKcp>> m_client_conns;
};

#endif