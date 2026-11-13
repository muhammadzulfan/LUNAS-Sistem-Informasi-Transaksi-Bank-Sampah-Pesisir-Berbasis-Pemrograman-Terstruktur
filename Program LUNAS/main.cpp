#include <iostream>
#include <sstream>
#include "nasabah.hpp"
#include "sampah.hpp"
#include "transaksi.hpp"
#include "antrean.hpp"

int main() {
    inisialisasiSampah(); 
    muatDariFile("nasabah.txt");
    muatDariFile("transaksi.txt");

    int pilihan;
    string baris;
    do {
        cout << "\n=== BANK SAMPAH PESISIR (LUNAS) ===\n";
        cout << "1. Pendaftaran Nasabah\n2. Setor Sampah\n3. Tarik Saldo\n";
        cout << "4. Cek Saldo dan Riwayat\n5. Keluar\nPilih: ";
        getline(cin, baris);
        stringstream ss(baris);
        
        char sisa;
        if (baris.find_first_not_of(" \t") == string::npos || !(ss >> pilihan) || (ss >> sisa)) {
            cout << "Inputan tidak valid, Pilih (1-5)\n";
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
            case 1: RegistrasiNasabah(); break;
            case 2: SetorSampah(); break;
            case 3: TarikSaldo(); break;
            case 4: CekSaldoRiwayat(); break;
            case 5:
                simpanKeFile("nasabah.txt");
                simpanKeFile("transaksi.txt");
                cout << "Data tersimpan. Terima kasih.\n";
                break;
            default: cout << "Inputan tidak valid, Pilih (1-5)\n";
        }
    } while (pilihan != 5);

    return 0;
}