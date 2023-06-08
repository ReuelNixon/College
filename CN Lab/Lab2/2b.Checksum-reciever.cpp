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
    cout << "Enter data blocks: ";
    for (int i = 0; i < n; i++) {
        string temp;
        cin >> temp;
        data.push_back(temp);
    }
    string checksum;
    cout << "Enter checksum: ";
    cin >> checksum;

    // binary addition
    for (int i = 0; i < n; i++) {
        checksum = binAdd(checksum, data[i]);
    }

    // 1's complement
    for (int i = 0; i < checksum.length(); i++)
        if (checksum[i] == '0')
            checksum[i] = '1';
        else
            checksum[i] = '0';

    // Check
    for (int i = 0; i < checksum.length(); i++)
        if (checksum[i] == '1') {
            cout << "Error detected" << endl;
            return 0;
        }
    cout << "No error detected" << endl;
    return 0;
}