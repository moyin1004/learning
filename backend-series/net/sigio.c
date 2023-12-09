#include <arpa/inet.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int sockfd = 0;

void do_sigio(int sigio) {
    printf("sig:%d\n", sigio);
    char buffer[256] = {0};
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    int len = recvfrom(sockfd, buffer, 256, 0, (struct sockaddr *)&cli_addr, &clilen);
    printf("recv, len:%d, msg:%s\n", len, buffer);
    len = sendto(sockfd, buffer, len, 0, (struct sockaddr *)&cli_addr, clilen);
    printf("sendto ret:%d\n", len);
}

int main() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    signal(SIGIO, do_sigio);
    struct sockaddr_in serv_addr;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);

    fcntl(sockfd, __F_SETOWN, getpid());
    int flags = fcntl(sockfd, F_GETFL, 0);
    flags |= O_ASYNC | O_NONBLOCK;
    fcntl(sockfd, F_SETFL, flags);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {
        sleep(1);
    }

    return 0;
}