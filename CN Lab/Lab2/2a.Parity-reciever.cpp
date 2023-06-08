#include <bits/stdc++.h>

using namespace std;

int noOfOnes(string data) {
    int count = 0;
    for (int i = 0; i < data.length(); i++)
        if (data[i] == '1')
            count++;
    return count;
}

int main(int argc, const char* argv[]) {
    cout << "Enter the data stream: ";
    string data;
    cin >> data;
    string scheme;
    cout << "Scheme: (Even(e)/ Odd(o)) " << scheme;
    cin >> scheme;
    int count = noOfOnes(data);
    if (scheme == "E" || scheme == "e") {
        if (count % 2 == 0)
            cout << "No error detected" << endl;
        else
            cout << "Error detected" << endl;
    } else if (scheme == "O" || scheme == "o") {
        if (count % 2 == 0)
            cout << "Error detected" << endl;
        else
            cout << "No error detected" << endl;
    } else {
        cout << "Invalid scheme" << endl;
    }
    return 0;
}