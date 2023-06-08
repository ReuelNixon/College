#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[]) {
    cout << "Enter the data stream: ";
    string data;
    cin >> data;
    int count = 0;
    for (int i = 0; i < data.length(); i++)
        if (data[i] == '1')
            count++;

    string evenParity = data, oddParity = data;
    if (count % 2 == 0) {
        evenParity += '0';
        oddParity += '1';
    } else {
        evenParity += '1';
        oddParity += '0';
    }

    cout << "Even Parity: " << evenParity << "\n";
    cout << "Odd Parity: " << oddParity << "\n";
    return 0;
}