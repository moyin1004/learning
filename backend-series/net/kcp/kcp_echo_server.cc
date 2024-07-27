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

class UKcpServer {
public:
    UKcpServer() {
        m_fd = socket(AF_INET, SOCK_DGRAM, 0);
        int flags = O_ASYNC | O_NONBLOCK;
        fcntl(m_fd, F_SETFL, flags);
        sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
        servaddr.sin_port = htons(8080);

        // Bind the socket with the server address
        int ret = bind(m_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        if (ret < 0) {
            close(m_fd);
            m_fd = 0;
            throw std::runtime_error("bind err:" + std::to_string(errno));
        }
        UUserData data;
        data.fd = m_fd;
        m_listenKcp = std::make_unique<UKcp>(0x1, data);
    }
    ~UKcpServer() {
        if (m_fd > 0) {
            close(m_fd);
        }
    }
    void Run() {
        while (1) {
            char buffer[MTU_SIZE] = {0};
            sockaddr_in clientaddr;
            memset(&clientaddr, 0, sizeof(clientaddr));
            socklen_t addrlen = sizeof(sockaddr_in);
            int len = recvfrom(m_fd, buffer, sizeof(buffer), 0, (sockaddr *)&clientaddr, &addrlen);
            if (len > 0) {
                sockaddr_storage addr;
                auto c = inet_ntop(AF_INET, &clientaddr, (char *)&addr, sizeof(addr));
                int port = ntohs(clientaddr.sin_port);
                printf("recv data %d, addr:%s, port:%d\n", len, c, port);
                std::string id(c);
                auto it = m_client_conns.find(id + std::to_string(port));
                if (it != m_client_conns.end()) {
                    it->second->Input(buffer, len);
                } else {
                    m_listenKcp->GetUUserData().addr = clientaddr;
                    m_listenKcp->Input(buffer, len);
                    m_listenKcp->Update();
                    std::string recv = m_listenKcp->Revc();
                    if (recv.find("handshake") != string::npos) {
                        m_fd = socket(AF_INET, SOCK_DGRAM, 0);
                        int flags = O_ASYNC | O_NONBLOCK;
                        fcntl(m_fd, F_SETFL, flags);
                        sockaddr_in servaddr;
                        memset(&servaddr, 0, sizeof(servaddr));

                        std::cout << recv << std::endl;
                        m_listenKcp->Send((char *)&cur_conv, sizeof(int));
                        UUserData data;
                        data.addr = clientaddr;
                        data.fd = m_fd;
                        m_client_conns.insert(
                            std::make_pair(reinterpret_cast<sockaddr *>(&clientaddr)->sa_data,
                                           std::make_unique<UKcp>(cur_conv++, data)));
                    }
                }
            } else if (errno == EAGAIN) {
            } else {
                printf("recvfrom ret:%d, err:%d\n", len, errno);
            }
            m_listenKcp->Update();
            for (auto &elem : m_client_conns) {
                elem.second->Update();
                auto data = elem.second->Revc();
                if (!data.empty()) {
                    printf("recv conv %d data: %s\n", ikcp_getconv(elem.second->GetIkcp()),
                           data.c_str());
                    elem.second->Send(data.c_str(), data.size());
                }
            }
        }
    }

private:
    int m_fd;
    int cur_conv = 0x2;
    std::unique_ptr<UKcp> m_listenKcp;
    std::unordered_map<std::string, std::unique_ptr<UKcp>> m_client_conns;
};

int main() {
    UKcpServer server;
    server.Run();
    return 0;
}