#include <arpa/inet.h>
#include <math.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

string addDots(string IP) {
    string temp = "";
    for (int i = 0; i < IP.size(); i++) {
        if (i % 8 == 0 && i != 0) {
            temp += ".";
        }
        temp += IP[i];
    }
    return temp;
}

string binaryToDecimalIP(string binaryIP) {
    string IP = "";
    string temp = "";
    for (int i = 0; i < binaryIP.size(); i++) {
        if (binaryIP[i] == '.') {
            IP += to_string(stoi(temp, 0, 2)) + ".";
            temp = "";
        } else {
            temp += binaryIP[i];
        }
    }
    IP += to_string(stoi(temp, 0, 2));
    return IP;
}

string networkIP(string binaryIPwithoutDots, int CIDR) {
    string networkIP = "";
    for (int i = 0; i < binaryIPwithoutDots.size(); i++) {
        if (i < CIDR) {
            networkIP += binaryIPwithoutDots[i];
        } else {
            networkIP += "0";
        }
    }
    string temp = addDots(networkIP);
    return binaryToDecimalIP(temp);
}

string broadcastIP(string binaryIPwithoutDots, int CIDR) {
    string broadcastIP = "";
    for (int i = 0; i < binaryIPwithoutDots.size(); i++) {
        if (i < CIDR) {
            broadcastIP += binaryIPwithoutDots[i];
        } else {
            broadcastIP += "1";
        }
    }
    string temp = addDots(broadcastIP);
    return binaryToDecimalIP(temp);
}

vector<string> subnetIP(string binaryIPwithoutDots, int CIDR, int subnets) {
    vector<string> subnetIPs;
    int subnetBits = ceil(log2(subnets));
    int newCIDR = CIDR + subnetBits;
    int remainingBits = 32 - newCIDR;
    string IPtillCIDR = "";
    for (int i = 0; i < CIDR; i++) {
        IPtillCIDR += binaryIPwithoutDots[i];
    }

    for (int i = 0; i < subnets; i++) {
        string binary = bitset<2>(i).to_string();
        for (int i = 0; i < remainingBits; i++) {
            binary += "0";
        }
        string subnetIP = IPtillCIDR + binary;
        string temp = addDots(subnetIP);
        subnetIPs.push_back(binaryToDecimalIP(temp));
    }
    return subnetIPs;
}

void evaluate(string IPwithCIDR, int subnets) {
    string IP = IPwithCIDR.substr(0, IPwithCIDR.find('/'));
    int CIDR = stoi(IPwithCIDR.substr(IPwithCIDR.find('/') + 1));

    vector<string> numbers;
    string temp = "";
    for (int i = 0; i < IP.size(); i++) {
        if (IP[i] == '.') {
            numbers.push_back(temp);
            temp = "";
        } else {
            temp += IP[i];
        }
    }
    numbers.push_back(temp);

    string binaryString = "";
    for (int i = 0; i < numbers.size(); i++) {
        int num = stoi(numbers[i]);
        if (num > 255) {
            cout << "Invalid IP Address" << endl;
            return;
        }
        binaryString += bitset<8>(num).to_string();
    }

    cout << "IP: " << IP << endl;
    cout << "CIDR: " << CIDR << endl;
    cout << "IP in Binary: " << addDots(binaryString) << endl;
    cout << "Network Address: " << networkIP(binaryString, CIDR) << endl;
    cout << "Broadcast Address: " << broadcastIP(binaryString, CIDR) << endl;
    vector<string> subnetIPs = subnetIP(binaryString, CIDR, subnets);
    for (int i = 0; i < subnetIPs.size(); i++) {
        cout << "Subnet" << i + 1 << ": " << subnetIPs[i] << endl;
    }
}

int main() {
    // create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify the server address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(8080);

    // bind the socket to the server address and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // listen for incoming connections
    listen(server_socket, 3);

    // accept incoming connections
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t addrlen = sizeof(client_address);
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &addrlen);

    // receive data from the client
    char buffer[1024] = {0};
    char buffer2[1024] = {0};
    read(client_socket, buffer, 1024);
    read(client_socket, buffer2, 1024);
    string IP = buffer;
    int subnets = stoi(buffer2);

    evaluate(IP, subnets);
    cout << endl;
    // send data to the client
    const char *message = "Successfully processed!";
    send(client_socket, message, strlen(message), 0);

    // close the socket
    close(server_socket);
    return 0;
}