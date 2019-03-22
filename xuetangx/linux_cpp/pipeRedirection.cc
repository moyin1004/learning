/// @file    pipeRedirection.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-22 14:02:05

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

const int buf_size = 4096;

int main() {
    int fds[2];
    pipe(fds);
    pid_t pid = fork();
    if (pid == 0) {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO); //将标准输出流重定向到管道
        char str1[] = "ls";
        char *args[] = {str1, NULL};
        execvp(args[0], args);
    }
    else if (pid > 0){
        close(fds[1]);
        char buf[buf_size];
        FILE *stream = fdopen(fds[0], "r");
        fprintf(stdout, "Data received:\n");
        while (!feof(stream) && !ferror(stream) && fgets(buf, sizeof(buf), stream) != NULL ) {
            fputs(buf, stdout);
        }
        close(fds[0]);
        waitpid(pid, NULL, 0);
    }
    else {
        cout << "fork error!" << endl;
    }
    return 0;
}
