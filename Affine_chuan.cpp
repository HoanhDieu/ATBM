#include <iostream>
#include <string>

using namespace std;

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if (((a % m) * (x % m)) % m == 1) {
            return x;
        }
    }
    return -1;
}

string encrypt(string plain_text, int a, int b) {
    string encrypted_text = "";
    for (int i = 0; i < plain_text.length(); i++) {
        if (isalpha(plain_text[i])) {
            char c = toupper(plain_text[i]);
            int x = c - 'A';
            int encrypted_x = (a * x + b) % 26;
            char encrypted_c = encrypted_x + 'A';
            encrypted_text += encrypted_c;
        } else {
            encrypted_text += plain_text[i];
        }
    }
    return encrypted_text;
}

string decrypt(string encrypted_text, int a, int b) {
    string decrypted_text = "";
    int a_inverse = mod_inverse(a, 26);
    for (int i = 0; i < encrypted_text.length(); i++) {
        if (isalpha(encrypted_text[i])) {
            char c = toupper(encrypted_text[i]);
            int y = c - 'A';
            int decrypted_y = (a_inverse * (y - b + 26)) % 26;
            char decrypted_c = decrypted_y + 'A';
            decrypted_text += decrypted_c;
        } else {
            decrypted_text += encrypted_text[i];
        }
    }
    return decrypted_text;
}

int main() {
    string plain_text;
    int a, b;
    cout << "Nhap thong diep can ma hoa: ";
    getline(cin, plain_text);
    cout << "Nhap khoa K (a, b): ";
    cin >> a >> b;

    
    if (gcd(a, 26) != 1) {
        cout << "Khoa K khong hop le. Vui long nhap lai." << endl;
        return 0;
    }

    string encrypted_text = encrypt(plain_text, a, b);
    string decrypted_text = decrypt(encrypted_text, a, b);

    cout << "Thong diep da ma hoa: " << encrypted_text << endl;
    cout << "Ban ro ban dau: " << decrypted_text << endl;

    return 0;
}

