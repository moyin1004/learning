#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct sockaddr_in6 addr;
    memset(&addr, 0, sizeof(struct sockaddr_in6));
    addr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, ":::2", &addr.sin6_addr);

    int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }
    addr.sin6_port = htons(9090);
    if (connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in6)) < 0) {
        perror("connect");
        return -1;
    }

    char buffer[] = {"hello world!"};
    send(sockfd, buffer, strlen(buffer), 0);
    sleep(10);
    char res[256] = {};
    recv(sockfd, res, sizeof(res), 0);
    close(sockfd);
    printf("%s\n", res);
    return 0;
}
