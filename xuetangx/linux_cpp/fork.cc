/// @file    fork.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-06 17:01:39
 
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <iostream>
 
using std::cout;
using std::endl;
 
sig_atomic_t child_exit_status;

void CleanUp(int sig_num) {
    int status;
    wait(&status);  //清理子进程
    child_exit_status = status; //存储子进程的状态
}

int main() {
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &CleanUp;

    cout << "the mian program process ID is " << (int)getpid() << endl;
    pid_t child_pid = fork();  //fork函数返回两个值
    if (child_pid == -1) return -1;
    if (child_pid != 0) { //主进程中运行
        cout << "this is parent process with id" << (int)getpid() << endl;
        cout << "the child's process ID is " << (int)child_pid << endl;
        sleep(1);
        cout << "child_exit_status: " << child_exit_status << endl;
        if (WIFEXITED(child_exit_status)) cout << "Exited normally with " << WEXITSTATUS(child_exit_status) << endl;
    }
    else { //子进程中运行
        //sleep(2);
        cout << "this is child's process with id" << (int)getpid() << endl;
        cout << "parent id = " << getppid() << endl;
        sigaction(SIGCHLD, &sa, NULL); //通知主线程执行处理操作
    }

    return 0;
}
