#include <bits/stdc++.h>

using namespace std;

string alterOneBit(string data) {
    vector<int> valids;

    for (int i = 0; i < data.length(); i++) {
        if (pow(2, i) != i + 1) {
            valids.push_back(i);
        }
    }

    int randomIndex = rand() % valids.size();
    int randomPosition = valids[randomIndex];
    data[randomPosition] = data[randomPosition] == '0' ? '1' : '0';
    return data;
}

int checkBits(int n) {
    int r = 0;
    while (pow(2, r) < n + r + 1) {
        r++;
    }
    return r;
}

bool isPowerOfTwo(int n) {
    return (n & (n - 1)) == 0;
}

int xorSum(vector<int> arr) {
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        sum ^= arr[i];
    }
    return sum;
}

vector<vector<int>> findGroups(int n, int r) {
    vector<string> binaries;
    for (int i = 1; i < n + r + 1; i++) {
        string binary = bitset<4>(i).to_string();
        binaries.push_back(binary);
    }

    vector<vector<int>> groups;
    for (int i = 0; i < r; i++) {
        vector<int> group;
        for (int j = 0; j < n + r; j++) {
            if (binaries[j][i] == '1') {
                group.push_back(j + 1);
            }
        }
        groups.push_back(group);
    }
    reverse(groups.begin(), groups.end());
    return groups;
}

string hammingCode(string data, int n, int r) {
    vector<int> dataBits(n + r);
    int j = 0, k = 0;
    for (int i = n + r; i >= 1; i--) {
        if (isPowerOfTwo(i))
            dataBits[k++] = 0;
        else
            dataBits[k++] = data[j++] - '0';
    }

    vector<vector<int>> groups = findGroups(n, r);
    reverse(dataBits.begin(), dataBits.end());

    vector<vector<int>> bitsGroups;
    int i = 1;
    for (auto group : groups) {
        cout << "Group" << i++ << ": ";
        vector<int> bitsGroup;
        for (auto bit : group) {
            bitsGroup.push_back(dataBits[bit - 1]);
            cout << bit << ": " << dataBits[bit - 1] << "\t";
        }
        cout << endl;
        bitsGroups.push_back(bitsGroup);
    }
    cout << endl;

    // Finding R1, R2, R3, R4
    i = 0;
    for (auto it : bitsGroups) {
        dataBits[pow(2, i) - 1] = xorSum(it);
        cout << "R" << pow(2, i++) << ": " << xorSum(it) << endl;
    }
    cout << endl;

    reverse(dataBits.begin(), dataBits.end());

    vector<char> res;
    for (auto it : dataBits) {
        res.push_back(it + '0');
    }
    string dataBitsJoined(res.begin(), res.end());
    return dataBitsJoined;
}

int errorCheck(string data) {
    int n = data.length();
    int r = checkBits(n);
    vector<vector<int>> groups = findGroups(n, r);
    vector<int> dataBits;
    for (auto it : data) {
        dataBits.push_back(it - '0');
    }
    reverse(dataBits.begin(), dataBits.end());
    vector<vector<int>> bitsGroups;
    int i = 1;
    for (auto group : groups) {
        vector<int> bitsGroup;
        for (auto bit : group) {
            bitsGroup.push_back(dataBits[bit - 1]);
        }
        bitsGroups.push_back(bitsGroup);
    }

    // Finding C1, C2, C3, C4
    vector<char> errorChecks;
    i = 0;
    for (auto it : bitsGroups) {
        cout << "C" << i++ << ": " << xorSum(it) << endl;
        errorChecks.push_back(xorSum(it) + '0');
    }
    string errorChecksJoined(errorChecks.begin(), errorChecks.end());
    cout << "Error bits: " << errorChecksJoined << endl;

    // Binary to decimal
    int position = 0;
    for (int i = 0; i < errorChecksJoined.length(); i++) {
        position += (errorChecksJoined[i] - '0') * pow(2, i);
    }

    return position;
}

int main(int argc, const char* argv[]) {
    int n;
    cout << "Enter the number of bits in the data: ";
    cin >> n;
    int r = checkBits(n);
    cout << "Number of redundant bits required: " << r << endl;
    string data;
    cout << "Enter the data stream: ";
    cin >> data;
    cout << endl;

    string hamming = hammingCode(data, n, r);
    cout << "Hamming code: " << hamming << endl;
    cout << endl
         << endl;

    cout << "-----------------------------------------------------------------------";
    cout << "Error Detection: ";
    cout << endl
         << endl;

    data = alterOneBit(hamming);
    cout << "Data stream recieved: " << data << endl;
    int error = errorCheck(data);
    if (error == 0) {
        cout << "No error detected." << endl;
    } else {
        cout << "Error detected at bit " << error << "." << endl;
    }

    return 0;
}