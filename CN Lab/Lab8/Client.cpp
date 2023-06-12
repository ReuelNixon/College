#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

using namespace std;

int main() {
    // create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify the server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    // connect to the server
    connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // send data to the server
    string IP;
    cout << "Enter IP address: ";
    cin >> IP;
    const char *message = IP.c_str();
    send(client_socket, message, strlen(message), 0);

    string subnets;
    cout << "Enter number of subnets: ";
    cin >> subnets;
    const char *message2 = subnets.c_str();
    send(client_socket, message2, strlen(message2), 0);

    // receive data from the server
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);
    cout << "Server message: " << buffer << endl
         << endl;

    // close the socket
    close(client_socket);
    return 0;
}