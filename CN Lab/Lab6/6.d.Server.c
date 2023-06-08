#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 22000

int evaluate(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b != 0) {
                return a / b;

            } else {
                printf("Error: Division by zero\n");
                exit(EXIT_FAILURE);
            }
        default:
            printf("Error: Invalid operation\n");
            exit(EXIT_FAILURE);
    }
}

int main() {
    char str[100];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 10);
    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1) {
        bzero(str, 100);
        read(comm_fd, str, 100);
        int a, b;
        char op;
        sscanf(str, "%d %c %d", &a, &op, &b);
        int result = evaluate(a, b, op);
        char result_str[100];
        printf("Recieved data:\n");
        printf("\tOperand 1: %d\n", a);
        printf("\tOperation: %c\n", op);
        printf("\tOperand 2: %d\n", b);
        snprintf(result_str, sizeof(result_str), "%d", result);
        printf("Result sent successfully...\n\n");
        write(comm_fd, result_str, strlen(result_str) + 1);
    }
    return 0;
}