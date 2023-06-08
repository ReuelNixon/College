#include <bits/stdc++.h>

using namespace std;

string alterOneBit(string data) {
    vector<int> valids;

    for (int i = 0; i < data.length(); i++) {
        valids.push_back(i);
    }

    int randomIndex = rand() % valids.size();
    int randomPosition = valids[randomIndex];
    data[randomPosition] = data[randomPosition] == '0' ? '1' : '0';
    return data;
}

string findCoefficients(string polynomial, string delimiter, string variable) {
    vector<string> terms;
    size_t pos = 0;
    string term;
    while ((pos = polynomial.find("+")) != string::npos) {
        term = polynomial.substr(0, pos);
        terms.push_back(term);
        polynomial.erase(0, pos + 1);
    }
    terms.push_back(polynomial);

    vector<int> coefficients;
    vector<int> powers;
    for (auto it : terms) {
        size_t pos = 0;
        string coefficient;
        pos = it.find(variable);

        // constant
        if (pos > it.length()) {
            coefficient = it;
            powers.push_back(0);
            continue;
        }

        // coefficient
        coefficient = it.substr(0, pos);

        // x
        if (coefficient == "") {
            coefficients.push_back(1);
        } else {
            coefficients.push_back(stoi(coefficient));
        }

        // power
        pos = it.find(delimiter);

        // x^1
        if (pos > it.length()) {
            powers.push_back(1);
            continue;
        }

        // x^power
        string power = it.substr(pos + 1);
        powers.push_back(stoi(power));
    }
    string res = "";
    int j = 0;
    res += to_string(coefficients[0]);
    for (int i = powers[0] - 1; i >= 0; i--) {
        if (find(powers.begin(), powers.end(), i) == powers.end()) {
            res += "0";
        } else {
            res += to_string(coefficients[j]);
            j++;
        }
    }
    return res;
}

string exor(string a, string b) {
    string res;
    for (int i = 0; i < a.length(); i++) {
        res += (a[i] == b[i]) ? '0' : '1';
    }
    return res;
}

string crc(string dividend, string divisor, string sOrR) {
    int dividendLen = dividend.length();
    int divisorLen = divisor.length();

    // append 0s to data
    if (sOrR == "S") {
        for (int i = 0; i < divisorLen - 1; i++) {
            dividend += '0';
        }
    }

    int len = dividendLen + divisorLen - 1;

    string temp;
    string rem = dividend.substr(0, divisorLen);

    for (int j = divisorLen; j < len; j++) {
        temp = rem;
        if (rem[0] == '0') {
            rem = temp.substr(1);
        } else {
            rem = exor(temp.substr(1), divisor);
        }
        rem += dividend[j];
    }

    // left strip 0s
    int i = 0;
    while (rem[i] == '0') {
        i++;
    }
    rem = rem.substr(i);

    return rem;
}

int main(int argc, const char* argv[]) {
    string data;
    cout << "Enter the data: ";
    cin >> data;

    string polynomial;
    cout << "Enter the polynomial: ";
    cin >> polynomial;

    string delimiter;
    cout << "Enter the delimiter (Symbol used for power): ";
    cin >> delimiter;

    string variable;
    cout << "Enter the variable use in the polynomial: ";
    cin >> variable;

    string key = findCoefficients(polynomial, "^", "x");
    string dataToTransmit = data + crc(data, key, "S");
    cout << endl
         << endl;

    // sender
    cout << "SENDER SIDE" << endl;
    cout << "Divisor: " << key << endl;
    cout << "Check Bits: " << crc(data, key, "S") << endl;
    cout << "Data to transmit: " << dataToTransmit << endl
         << endl
         << endl;

    // receiver
    cout << "RECEIVER SIDE" << endl;
    string receivedData = alterOneBit(dataToTransmit);
    cout << "Received data: " << receivedData << endl;
    string remainder = crc(receivedData, key, "R");
    cout << "Remainder: " << (remainder == "" ? "0" : remainder) << endl;
    if (remainder == "") {
        cout << "No error is detected" << endl;
    } else {
        cout << "Error is detected" << endl;
    }

    return 0;
}