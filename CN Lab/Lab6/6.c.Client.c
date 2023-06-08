#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    int sockfd, n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1) {
        bzero(sendline, 100);
        bzero(recvline, 100);
        printf("Enter a number to find the factorial of: ");
        fgets(sendline, 100, stdin);
        write(sockfd, sendline, strlen(sendline) + 1);
        read(sockfd, recvline, 100);
        printf("Result: %s\n\n", recvline);
    }
}