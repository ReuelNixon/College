#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

using namespace std;

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
        cin.getline(sendline, 100);  // Read input from user
        write(sockfd, sendline, strlen(sendline) + 1);
        read(sockfd, recvline, 100);
        cout << recvline;
    }

    return 0;
}
