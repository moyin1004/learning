/// @file    daemonSimulation.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-03-16 22:27:52

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <iostream>

using std::cout;
using std::endl;

int main() {
    pid_t pid = fork();
    if (pid == -1) return -1;
    else if (pid != 0) exit(EXIT_SUCCESS);
    if (setsid() == -1) return -2; //创建会话
    if (chdir("/") == -1) return -3; //设置工作目录
    umask(0); //重设文件掩码
    for (int i = 0; i < 3; ++i) close(i); //关闭文件描述符
    open("/dev/null", O_RDWR); //stdin
    dup(0); //两个文件描述符等位处理
    dup(0);

    cout << "daemon work" << endl;

    return 0;
}
