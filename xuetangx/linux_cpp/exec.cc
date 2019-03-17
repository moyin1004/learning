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
        sleep(1);
        cout << "wait child pid: " << wait(NULL) << endl;
    }
    else {
        execvp(program, args);
        std::cerr << "Error occurred when executing execvp.\n";
        abort();
    }
    cout << "child pid = " << pid << endl;
    return pid;
}

int main() {
    char s1[] = "ls";
    char s2[] = "-l";
    char s3[] = "/";
    char *args[] = {s1, s2, s3, NULL};
    spawn(s1, args);
    cout << "Done\n";
    return 0;
}
