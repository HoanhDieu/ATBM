#include <iostream>
#include <cmath>

using namespace std;

// Ham kiem tra tinh nguyen to?
bool isPrime(int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// H�m t�nh co so can nguy�n thuy (primitive root) cua mot so nguyen to
int calculatePrimitiveRoot(int q) {
    for (int r = 2; r < q; r++) {
        bool isPrimitiveRoot = true;
        for (int i = 1; i <= q - 2; i++) {
            if ((int)pow(r, i) % q == 1) {
                isPrimitiveRoot = false;
                break;
            }
        }
        if (isPrimitiveRoot)
            return r;
    }
    return -1;
}

// H�m t�nh kh�a c�ng khai
int calculatePublicKey(int base, int privateExponent, int modulus) {
    return static_cast<int>(pow(base, privateExponent)) % modulus;
}

// H�m t�nh kh�a b� mat
int calculatePrivateKey(int base, int privateExponent, int modulus) {
    return static_cast<int>(pow(base, privateExponent)) % modulus;
}

int main() {
    int q, base;
    int privateExponentSender, privateExponentReceiver;
    int publicKeySender, publicKeyReceiver;
    int privateKeySender, privateKeyReceiver;
    int sharedSecretKey;

    cout << "Diffie-Hellman Key Exchange" << endl;

    while (true) {
        cout << "--------------------------" << endl;
        cout << "Menu:" << endl;
        cout << "1. Nhap so nguyen to q v� tinh co so can nguyen thuy" << endl;
        cout << "2. Tinh khoa cong khai va khoa bi mat cho ben gui v� ben nhan" << endl;
        cout << "3. Hien thi khoa bi mat" << endl;
        cout << "4. Thoat" << endl;
        cout << "Chon chuc nang (1-4): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nh?p s? nguy�n t? q: ";
                cin >> q;
                if (!isPrime(q)) {
                    cout << "q kh�ng ph?i l� s? nguy�n t?. Vui l�ng nh?p l?i." << endl;
                    break;
                }
                base = calculatePrimitiveRoot(q);
                if (base == -1) {
                    cout << "Kh�ng t�m th?y co s? can nguy�n th?y c?a q." << endl;
                    break;
                }
                cout << "Co s? can nguy�n th?y c?a q l�: " << base << endl;
                break;
            case 2:
                cout << "Nh?p kh�a b� m?t c?a b�n g?i: ";
                cin >> privateExponentSender;
                cout << "Nh?p kh�a b� m?t c?a b�n nh?n: ";
                cin >> privateExponentReceiver;
                publicKeySender = calculatePublicKey(base, privateExponentSender, q);
                publicKeyReceiver = calculatePublicKey(base, privateExponentReceiver, q);
                privateKeySender = calculatePrivateKey(publicKeyReceiver, privateExponentSender, q);
                privateKeyReceiver = calculatePrivateKey(publicKeySender, privateExponentReceiver, q);
                cout << "Kh�a c�ng khai c?a b�n g?i: " << publicKeySender << endl;
                cout << "Kh�a c�ng khai c?a b�n nh?n: " << publicKeyReceiver << endl;
                break;
            case 3:
                sharedSecretKey = calculatePrivateKey(publicKeyReceiver, privateExponentSender, q);
                cout << "Kh�a b� m?t K: " << sharedSecretKey << endl;
                break;
            case 4:
                cout << "Tho�t kh?i chuong tr�nh." << endl;
                return 0;
            default:
                cout << "Ch?n ch?c nang kh�ng h?p l?. Vui l�ng ch?n l?i." << endl;
                break;
        }
    }

    return 0;
}

