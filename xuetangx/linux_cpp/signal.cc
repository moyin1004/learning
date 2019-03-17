/// @file    signal.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-17 12:36:13

#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

sig_atomic_t sigusr1_count = 0;

extern "C" {
    void OnSigUsr1(int signal_number) {
        ++sigusr1_count;
    }
}

int main() {
    cout << "pid" << (int)getpid() << endl;
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &OnSigUsr1;
    sigaction(SIGUSR1, &sa, NULL);
    sleep(100); //终端输入kill -s SIGUSR1 pid
    cout << "SIGUSR1 conuts: " << sigusr1_count << endl;
    return 0;
}
