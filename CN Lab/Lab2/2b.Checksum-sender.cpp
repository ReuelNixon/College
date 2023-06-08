#include <bits/stdc++.h>

using namespace std;

string binAdd(string s1, string s2) {
    string result = "";
    string carry = "0";
    for (int i = s1.length() - 1; i >= 0; i--) {
        if (s1[i] == '0' && s2[i] == '0') {
            if (carry == "0") {
                result = "0" + result;
                carry = "0";
            } else {
                result = "1" + result;
                carry = "0";
            }
        } else if (s1[i] == '0' && s2[i] == '1') {
            if (carry == "0") {
                result = "1" + result;
                carry = "0";
            } else {
                result = "0" + result;
                carry = "1";
            }
        } else if (s1[i] == '1' && s2[i] == '0') {
            if (carry == "0") {
                result = "1" + result;
                carry = "0";
            } else {
                result = "0" + result;
                carry = "1";
            }
        } else if (s1[i] == '1' && s2[i] == '1') {
            if (carry == "0") {
                result = "0" + result;
                carry = "1";
            } else {
                result = "1" + result;
                carry = "1";
            }
        }
    }
    if (carry == "1") {
        string temp = "";
        for (int i = 0; i < result.length() - 1; i++) temp += '0';
        temp += '1';
        return binAdd(temp, result);
    }
    return result;
}

int main(int argc, const char* argv[]) {
    cout << "Enter number of data blocks: ";
    int n;
    cin >> n;
    vector<string> data;
    for (int i = 0; i < n; i++) {
        string temp;
        cout << "Enter the data block no." << i + 1 << ": ";
        cin >>
            temp;
        data.push_back(temp);
    }

    // binary addition
    string checksum = data[0];
    for (int i = 1; i < n; i++) {
        checksum = binAdd(checksum, data[i]);
    }

    // 1's complement
    for (int i = 0; i < checksum.length(); i++)
        if (checksum[i] == '0')
            checksum[i] = '1';
        else
            checksum[i] = '0';

    cout << "Checksum: " << checksum << "\n";
    return 0;
}