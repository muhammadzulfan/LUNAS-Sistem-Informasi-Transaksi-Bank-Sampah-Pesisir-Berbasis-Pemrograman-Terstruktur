#include <iostream>
#include <cctype>
#include "nasabah.hpp"
#include "transaksi.hpp"

vector<Nasabah> databaseNasabah;

bool isTerdaftar(int idNasabah) {
    for (auto &n : databaseNasabah)
        if (n.idNasabah == idNasabah) return true;
    return false;
}

bool isTerdaftar(string nama, string alamat) {
    for (auto &n : databaseNasabah)
        if (n.nama == nama && n.alamat == alamat) return true;
    return false;
}

// dipanggil setelah isTerdaftar(id) bernilai true
Nasabah &cariNasabah(int idNasabah) {
    for (auto &n : databaseNasabah)
        if (n.idNasabah == idNasabah) return n;
    return databaseNasabah[0];
}

int buatIDNasabah() {
    return databaseNasabah.size() + 1;
}

void RegistrasiNasabah() {
    Nasabah n;
    cout << "\n=== Pendaftaran Nasabah ===\n";
    
    while (true) {
    cout << "Nama   : ";
        getline(cin, n.nama);
    
        bool valid = true;
        bool adahuruf = false;
    
        if (n.nama.empty() || n.nama.find_first_not_of(" \t") == string::npos) {
            valid = false;
        } else {
            for (char c : n.nama) {
                if (isalpha(static_cast<unsigned char>(c))) {
                    adahuruf = true;
                } else if (c == ' ' || c == '.') {
                    continue;
                } else {
                    valid = false;
                    break;
                }
            }
        }
        if (!valid || !adahuruf) {
            cout << "Inputan nama tidak valid!, Ulangi inputan\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Alamat : ";
        getline(cin, n.alamat);
        
        bool valid = true;
        bool adaAlfanumerik = false; // Harus ada minimal huruf atau angka

        if (n.alamat.empty() || n.alamat.find_first_not_of(" \t") == string::npos) {
            valid = false;
        } else {
            for (unsigned char c : n.alamat) {
                if (isalnum(c)) {
                    adaAlfanumerik = true; // Ketemu huruf atau angka
                } else if (c == ' ' || c == '.' || c == ',' || c == '/' || c == '-') {
                    // Karakter pendukung alamat yang diizinkan
                    continue;
                } else {
                    // Jika ada simbol lain yang terlalu aneh (misal: @, $, %, *, dll)
                    valid = false;
                    break;
                }
            }
        }

        if (!valid || !adaAlfanumerik) {
            cout << "Inputan alamat tidak valid! Ulangi inputan\n";
            continue;
        }
        break; // Lolos semua pengecekan
    }

    if (isTerdaftar(n.nama, n.alamat)) {
            cout << "Pendaftaran ditolak (data sudah ada)\n";
            return;
        }
    

    n.idNasabah = buatIDNasabah();
    n.saldo = 0;
    databaseNasabah.push_back(n);
    simpanKeFile("nasabah.txt");
    cout << "Pendaftaran berhasil. ID Nasabah Anda: " << n.idNasabah << endl;
}
