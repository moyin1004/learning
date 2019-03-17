/// @file    exec.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-17 13:05:10

#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

int spawn(char *program, char **args) {
    pid_t pid = fork();
    if (pid != 0) {
        return pid;
        //int status;
        //cout << "childpid exit status: " << status << endl;
    }
    else {
        sleep(1);
        execvp(program, args);
        std::cerr << "Error occurred when executing execvp.\n";
        abort();
    }
}

int main() {
    char s1[] = "ls";
    char s2[] = "-l";
    char s3[] = "/";
    char *args[] = {s1, s2, s3, NULL};
    int pid = spawn(s1, args);
    int status;
    wait(&status);
    cout << "child_pid: " << pid << endl;
    //判断进程是否正常退出
    if (WIFEXITED(status)) cout << "Exited normally with " << WEXITSTATUS(status) << endl;
    else cout << "nonormally" << endl;
    cout << "Done\n";
    return 0;
}
