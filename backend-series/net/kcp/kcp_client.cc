#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "ikcp.h"
#include "ukcp.h"

using namespace std;

class UKcpClient {
public:
    UKcpClient() {
        m_fd = socket(AF_INET, SOCK_DGRAM, 0);
        int flags = O_ASYNC | O_NONBLOCK;
        fcntl(m_fd, F_SETFL, flags);
        sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(8080);
        UUserData data;
        data.fd = m_fd;
        data.addr = servaddr;
        m_listenKcp = std::make_unique<UKcp>(0x1, data);
        m_listenKcp->Send("handshake", 10);
    }
    ~UKcpClient() {
        if (m_fd > 0) {
            close(m_fd);
        }
    }
    void Run() {
        bool trans = true;
        while (1) {
            m_listenKcp->Update();
            char buffer[MTU_SIZE] = {0};
            sockaddr_in clientaddr;
            memset(&clientaddr, 0, sizeof(clientaddr));
            socklen_t addrlen = sizeof(sockaddr_in);
            int len = recvfrom(m_fd, buffer, sizeof(buffer), 0, (sockaddr *)&clientaddr, &addrlen);
            if (len > 0) {
                sockaddr_storage addr;
                printf("recv data %d, addr:%s\n", len,
                       inet_ntop(AF_INET, &clientaddr, (char *)&addr, sizeof(addr)));
                if (m_kcp) {
                    m_kcp->Input(buffer, len);
                    auto read = m_kcp->Revc();
                    if (!read.empty()) {
                        printf("ret data:%s\n", read.c_str());
                    } else {
                        std::string data;
                        std::cin >> data;
                        m_kcp->Send(data.c_str(), data.size());
                    }
                } else {
                    m_listenKcp->Input(buffer, len);
                    std::string recv = m_listenKcp->Revc();
                    if (recv.size() == 4) {
                        int conv = *reinterpret_cast<int *>(recv.data());
                        UUserData data;
                        data.addr = clientaddr;
                        data.fd = m_fd;
                        printf("conn conv:%d\n", conv);
                        m_kcp = std::make_unique<UKcp>(conv, data);
                    }
                }
            } else if (errno == EAGAIN) {
            } else {
                printf("recvfrom ret:%d, err:%d\n", len, errno);
            }
            if (m_kcp) {
                m_kcp->Update();
            }
        }
    }

private:
    int m_fd;
    int cur_conv = 0x2;
    std::unique_ptr<UKcp> m_listenKcp;
    std::unique_ptr<UKcp> m_kcp;
};

int main(int argc, char *argv[]) {
    UKcpClient client;
    client.Run();
    return 0;
}