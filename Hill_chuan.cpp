#include <iostream>
#include <string>
#include <vector>

using namespace std;

int getInt(char a) {
    if (isupper(a)) return a - 65;
    return a - 97;
}

char getChar(int a) {
    return a + 65;
}

int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

int modND(int a, int b) {
    if (GCD(a, b) != 1) {
        cout << a << " mod " << b << " không ton tai modulo nghich dao\n";
        return -1;
    }

    int i = 0;
    vector<int> r, q, S, t;
    r.push_back(b);
    r.push_back(a);
    q.push_back(0);

    while (r[r.size() - 1] != 0) {
        q.push_back(r[i] / r[i + 1]);
        r.push_back(r[i] % r[i + 1]);
        if (i == 0) {
            S.push_back(1);
            t.push_back(0);
        } else if (i == 1) {
            S.push_back(0);
            t.push_back(1);
        } else {
            S.push_back(S[i - 2] - q[i - 1] * S[i - 1]);
            t.push_back(t[i - 2] - q[i - 1] * t[i - 1]);
        }
        i++;
    }
    S.push_back(S[i - 2] - q[i - 1] * S[i - 1]);
    t.push_back(t[i - 2] - q[i - 1] * t[i - 1]);

    int rs = t[t.size() - 1];
    if (rs < 0) rs += 26;
    return rs;
}

string encryp_Hill(string text, int k[]) {
    char rs[text.length()];
    int j = 0; //follow text;
    while (j < text.length()) {
        rs[j] = getChar((getInt(text[j]) * k[0] + getInt(text[j + 1]) * k[2]) % 26);
        rs[j + 1] = getChar((getInt(text[j]) * k[1] + getInt(text[j + 1]) * k[3]) % 26);
        j = j + 2;
    }
    return rs;
}
string decryp_Hill(string text, int k[]) {
    int detk = k[0] * k[3] - k[1] * k[2];
    int detk_nd = modND(detk, 26);
    int Pk[4];
    Pk[0] = k[3];
    Pk[3] = k[0];
    Pk[2] = -k[2];
    Pk[1] = -k[1];

    int Kgm[4], i = 0;
    while (i < 4) {
        int temp = detk_nd * Pk[i];
        while (temp < 0) temp += 26;
        Kgm[i] = temp % 26;
        i++;
    }

    char rs[text.length()];
        int j = 0; //follow text;
    while (j < text.length()) {
        rs[j] = getChar((getInt(text[j]) * Kgm[0] + getInt(text[j + 1]) * Kgm[2]) % 26);
        rs[j + 1] = getChar((getInt(text[j]) * Kgm[1] + getInt(text[j + 1]) * Kgm[3]) % 26);
        j = j + 2;
    }
    return rs;
}

int main() {
    int k[4];
    cout << "Nhap ma tran k:\n";
    for (int i = 0; i < 4; i++) {
        cout << "Nhap gia tri cho k[" << i << "]: ";
        cin >> k[i];
    }

    cin.ignore(); // Clear the input buffer
    string text;
    cout << "Nhap van ban: ";
    getline(cin, text);

    cout << "Van ban da ma hoa: " << encryp_Hill(text, k) << endl;
    cout << "Van ban da giai ma: " << decryp_Hill(encryp_Hill(text, k), k) << endl;

    return 0;
}
	

