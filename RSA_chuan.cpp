#include <bits/stdc++.h>
#include <cmath>
using namespace std;

// Hàm tính uoc so chung lon nhat
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Hàm kiem tra tính nguyên to
bool isPrime(int num) {
    if (num <= 1)
        return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Hàm tao khóa bí mat và khóa công khai
void generateKeys(int p, int q, int& n, int& e, int& d) {
    // Tính n
    n = p * q;

    // Tính f(n)
    int phi = (p - 1) * (q - 1);

    // Tìm e (so nguyên to cùng nhau voi f(n))
    for (e = 2; e < phi; e++) {
        if (gcd(e, phi) == 1)
            break;
    }

    // Tìm d (nghich dao modulo cua e)
    d = 0;
    int k = 1;
    while (true) {
        d = (k * phi + 1) / e;
        if (d * e == k * phi + 1)
            break;
        k++;
    }
}

// Hàm mã hóa
int encrypt(int message, int e, int n) {
    int cipher = 1;
    for (int i = 0; i < e; i++) {
        cipher = (cipher * message) % n;
    }
    return cipher;
}

// Hàm giai mã
int decrypt(int cipher, int d, int n) {
    int message = 1;
    for (int i = 0; i < d; i++) {
        message = (message * cipher) % n;
    }
    return message;
}

int main() {
    int p, q, n, e, d;
    int choice, message, cipher, decrypted;

    cout << "RSA" << endl;

    do {
        cout << "\nMenu:\n";
        cout << "1. Nhap thong diep can ma hoa\n";
        cout << "2. Tao khoa bi mat và khoa cong khai\n";
        cout << "3. Tien hanh ma hoa thong diep da nhap\n";
        cout << "4. Tien hanh giai ma thong diep\n";
        cout << "5. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Nhap thong diep can ma hoa: ";
                cin >> message;
                break;
            case 2:
                cout << "Nhap hai so nguyên to p và q: ";
                cin >> p >> q;

                // Kiem tra tính nguyên to cua p và q
                if (!isPrime(p) || !isPrime(q)) {
                    cout << "p và q phai la so nguyen to. Vui long nhap lai.\n";
                    break;
                }

                // Tao khóa bí mat và khóa công khai
                generateKeys(p, q, n, e, d);
                cout << "Tao khoa thanh cong.\n";
                cout << "Khoa cong khai (e, n): (" << e << ", " << n << ")\n";
               
                cout << "Khoa bi mat (d, n): (" << d << ", " << n << ")\n";
                break;
            case 3:
                if (e == 0 || n == 0) {
                    cout << "Vui long tao khoa truoc khi ma hoa.\n";
                    break;
                }
                // Mã hóa thông diep
                cipher = encrypt(message, e, n);
                cout << "Thong diep da ma hoa: " << cipher << endl;
                break;
            case 4:
                if (d == 0 || n == 0) {
                    cout << "Vui long tao khoa truoc khi giai ma.\n";
                    break;
                }
                // Giai mã thông diep
                decrypted = decrypt(cipher, d, n);
                cout << "Thong diep da giai ma: " << decrypted << endl;
                break;
            case 5:
                cout << "Thoat khoi chuong trình.\n";
                break;
            default:
                cout << "Lua chon không hop le. Vui lòng chon lai.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}

