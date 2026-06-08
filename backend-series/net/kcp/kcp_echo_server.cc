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
    UKcpServer() {}
    ~UKcpServer() {}
    void Run() {
        while (1) {
            auto conn = m_acceptor.Accept();
            if (conn) {
                m_client_conns[conn->GetConv()] = conn;
            }
            for (auto& elem : m_client_conns) {
                auto data = elem.second->Recv();
                // cout << "UKcpServer run:" << data << endl;
                if (!data.empty()) {
                    cout << "UKcpServer recv conv " << elem.second->GetConv()
                         << " data: " << data.c_str() << endl;
                    elem.second->Send(data.c_str(), data.size());
                    elem.second->Update();
                }
            }
            m_acceptor.Update();
            this_thread::sleep_for(chrono::seconds(1));
        }
    }

private:
    UKcpAcceptor m_acceptor;
    std::unordered_map<int, std::shared_ptr<UKcp>> m_client_conns;
};

int main() {
    UKcpServer server;
    server.Run();
    return 0;
}