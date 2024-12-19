#include <iostream>
#include <thread>
#include <future>

using namespace std;

int doAsyncWord() {
    // std::promise<void> p;
    // p.get_future().wait();
    // return 1;
}

int main() {
    auto fut = std::async(doAsyncWord);
    std::thread th;
    auto tid = th.native_handle();
    return 0;
}