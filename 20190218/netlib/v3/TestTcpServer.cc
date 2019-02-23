/// @file    TestTcpServer.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 16:53:43
 
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Threadpool.h"
#include <unistd.h>
#include <iostream> 
#include <memory>

using namespace wd;
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
using std::unique_ptr;
 
unique_ptr<Threadpool> threadpool(new Threadpool());

class MyTask {
public:
    MyTask(const string & request, shared_ptr<TcpConnection> conn)
    : _request(request)
    , _connection(conn)
    {}

    void process() {
        string response = doTask();
        _connection->sendInLoop(response);
    }

    string doTask() {
        return _request;
    }

private:
    string _request;
    shared_ptr<TcpConnection> _connection;
};

void onConnection(const shared_ptr<TcpConnection> &connection) {
    cout << ">> " << connection->toString() << " has connection!" << endl;
}

void onMessage(const shared_ptr<TcpConnection> &connection) {
    string msg = connection->receive();
    cout << ">> server receive: " << msg << endl;
    MyTask task(msg, connection);
    threadpool->addTask(std::bind(&MyTask::process, task));
}

void onClose(const shared_ptr<TcpConnection> & connection) {
    cout << ">> " << connection->toString() << " has closed!" << endl;
}

void test() {
    wd::TcpServer server("192.168.40.128", 8888);
    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.setCloseCallback(onClose);

    threadpool->start();
    server.start();

    threadpool->stop();
}

int main() {
    test();
    return 0;
}
