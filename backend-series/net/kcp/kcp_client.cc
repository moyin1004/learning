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
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(8080);
        m_data.fd = m_fd;
        m_data.addr = servaddr;
    }
    ~UKcpClient() {
        if (m_fd > 0) {
            close(m_fd);
        }
    }

    void Send() {
        while (1) {
            if (m_kcp) {
                std::string line;
                cin >> line;
                printf("client send conv %d data: %s\n", m_kcp->GetConv(), line.c_str());
                {
                    std::lock_guard<std::mutex> lock(m_mutex);
                    m_kcp->Send(line.c_str(), line.size());
                }
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    void Run() {
        UKcpOpcode op = UKcpOpcode::kHandshake;
        sendto(m_fd, &op, sizeof(op), 0, (sockaddr*)&m_data.addr, sizeof(m_data.addr));
        while (1) {
            socklen_t addrlen = sizeof(sockaddr_in);
            char buffer[1024] = {0};
            int len = recvfrom(m_fd, buffer, sizeof(buffer), 0, (sockaddr*)&m_data.addr, &addrlen);
            if (len > 0) {
                // printf("client recvfrom fd:%d, len:%d, buf:%d\n", m_fd, len, buffer[0]);
                if (buffer[0] == static_cast<char>(UKcpOpcode::kHandshakeRsp)) {
                    int conv = *((int*)&buffer[1]);
                    printf("client recv handshakersp conv:%d\n", conv);
                    if (!m_kcp) {
                        m_kcp = std::make_unique<UKcp>(conv, m_data);
                    }
                } else if (buffer[0] == static_cast<char>(UKcpOpcode::kData)) {
                    if (m_kcp) {
                        std::lock_guard<std::mutex> lock(m_mutex);
                        m_kcp->Input(buffer, len);
                        auto data = m_kcp->Recv();
                        if (!data.empty()) {
                            printf("client recv conv %d data: %s\n", m_kcp->GetConv(),
                                   data.c_str());
                        }
                    }
                }
            } else if (errno == EAGAIN) {
            } else {
                printf("client recvfrom fd:%d, ret:%d, err:%d\n", m_fd, len, errno);
            }
            if (m_kcp) {
                std::lock_guard<std::mutex> lock(m_mutex);
                m_kcp->Update();
            }
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

private:
    int m_fd;
    std::unique_ptr<UKcp> m_kcp;
    UUserData m_data;
    std::mutex m_mutex;
};

int main(int argc, char* argv[]) {
    UKcpClient client;
    std::thread t([&client]() { client.Run(); });
    client.Send();
    return 0;
}