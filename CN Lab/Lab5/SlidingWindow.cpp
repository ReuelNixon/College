#include <bits/stdc++.h>

using namespace std;

void sender(int n, int sf, int sn) {
    int r = pow(2, n);
    cout << endl
         << "No. of frames transmitted: " << r << endl;

    int ack;
    char response = 'y';
    while (tolower(response) == 'y') {
        cout << endl
             << "Acknowledgement Recieved: ACK";
        cin >> ack;
        int framesTransmitted;
        cout << "Enter the no.of new frames transmitted: ";
        cin >> framesTransmitted;

        sf = ack;
        sn = (sn + framesTransmitted) % r;

        cout << endl
             << "Updated Sf = " << sf << endl;
        cout << "Updated Sn = " << sn << endl;

        int last = (sf - 1) % r;
        cout << "Updated window: frame " << sf << " to " << last << endl;
        cout << endl
             << "Do you want to continue (y/n): ";
        cin >> response;
    }
}

int main(int argc, const char* argv[]) {
    int n;
    cout << "Enter the no. of bits required for frame no.: ";
    cin >> n;

    int sf;
    int sn;
    cout << "Value of Sf = ";
    cin >> sf;
    cout << "Value of Sn = ";
    cin >> sn;

    sender(n, sf, sn);
}