#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>  
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 22000

int countWordsInFile(const char* filename) {
    char ch;
    FILE* file;
    int count = 0;
    
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening the file.\n");
        return -1; 
    }

    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n')
            count++;
    }

    fclose(file);

    return count;
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
        char filename[100];
        sscanf(str, "%s", filename);
        printf("Reading the file...\n");
        int wordCount = countWordsInFile(filename);
        char result_str[10];
        snprintf(result_str, sizeof(result_str), "%d", wordCount);
        printf("Result sent successfully...\n\n");
        write(comm_fd, result_str, strlen(result_str) + 1);
    }
    return 0;
}