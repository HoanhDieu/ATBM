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

// Hàm tính co so can nguyên thuy (primitive root) cua mot so nguyen to
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

// Hàm tính khóa công khai
int calculatePublicKey(int base, int privateExponent, int modulus) {
    return static_cast<int>(pow(base, privateExponent)) % modulus;
}

// Hàm tính khóa bí mat
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
        cout << "1. Nhap so nguyen to q và tinh co so can nguyen thuy" << endl;
        cout << "2. Tinh khoa cong khai va khoa bi mat cho ben gui và ben nhan" << endl;
        cout << "3. Hien thi khoa bi mat" << endl;
        cout << "4. Thoat" << endl;
        cout << "Chon chuc nang (1-4): ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nh?p s? nguyên t? q: ";
                cin >> q;
                if (!isPrime(q)) {
                    cout << "q không ph?i là s? nguyên t?. Vui lòng nh?p l?i." << endl;
                    break;
                }
                base = calculatePrimitiveRoot(q);
                if (base == -1) {
                    cout << "Không tìm th?y co s? can nguyên th?y c?a q." << endl;
                    break;
                }
                cout << "Co s? can nguyên th?y c?a q là: " << base << endl;
                break;
            case 2:
                cout << "Nh?p khóa bí m?t c?a bên g?i: ";
                cin >> privateExponentSender;
                cout << "Nh?p khóa bí m?t c?a bên nh?n: ";
                cin >> privateExponentReceiver;
                publicKeySender = calculatePublicKey(base, privateExponentSender, q);
                publicKeyReceiver = calculatePublicKey(base, privateExponentReceiver, q);
                privateKeySender = calculatePrivateKey(publicKeyReceiver, privateExponentSender, q);
                privateKeyReceiver = calculatePrivateKey(publicKeySender, privateExponentReceiver, q);
                cout << "Khóa công khai c?a bên g?i: " << publicKeySender << endl;
                cout << "Khóa công khai c?a bên nh?n: " << publicKeyReceiver << endl;
                break;
            case 3:
                sharedSecretKey = calculatePrivateKey(publicKeyReceiver, privateExponentSender, q);
                cout << "Khóa bí m?t K: " << sharedSecretKey << endl;
                break;
            case 4:
                cout << "Thoát kh?i chuong trình." << endl;
                return 0;
            default:
                cout << "Ch?n ch?c nang không h?p l?. Vui lòng ch?n l?i." << endl;
                break;
        }
    }

    return 0;
}

