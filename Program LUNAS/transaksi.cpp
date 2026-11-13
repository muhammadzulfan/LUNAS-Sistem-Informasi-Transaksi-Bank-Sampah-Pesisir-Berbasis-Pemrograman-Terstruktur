#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include "transaksi.hpp"
#include "nasabah.hpp"
#include "sampah.hpp"
#include "antrean.hpp"

vector<Transaksi> riwayatTransaksi;

int buatIDTransaksi() {
    return 5000 + riwayatTransaksi.size() + 1;
}

string ambilTanggal() {
    time_t t = time(0);
    string s = ctime(&t);
    s.pop_back();   // hapus karakter newline
    return s;
}

void SetorSampah() {
    int idNasabah, kodeJenis;
    double berat;
    string namaJenis;
    string baris;
    while (true) {
        cout << "\n=== Setor Sampah ===\nInput ID Nasabah: ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
    
        // cek apakah murni angka dan tidak ada karakter anomali di belakang
        if (ss >> idNasabah && !(ss >> sisa)) {
            break;
        }
        cout << "ID Nasabah tidak valid! Masukkan angka saja\n";
    }

    if (!isTerdaftar(idNasabah)) {
        cout << "ID belum terdaftar, Lakukan pendaftaran\n";
        return;
    }
    if (!KelolaAntrean(idNasabah, "SETOR")) return;

    Nasabah &nasabah = cariNasabah(idNasabah);

    cout << "Jenis sampah:\n";
    for (auto &s : daftarSampah)
        cout << s.kodeJenis << ". " << s.namaJenis << " (Rp" << s.hargaPerKg << "/kg)\n";

    // input diulang sampai valid
    while (true) {
        cout << "Input kode jenis sampah : ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
        if (baris.empty() || baris.find_first_not_of(" ") == string::npos || !(ss >> kodeJenis) || (ss >> sisa) || !isJenisValid(kodeJenis)) {
            cout << "Kode jenis sampah tidak valid\n";
            continue;
        }
        break;
    }
    while (true) {
        cout << "Input berat sampah (kg) : ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
        if (baris.empty() || baris.find_first_not_of(" \t") == string::npos || !(ss >> berat) || (ss >> sisa) || berat <= 0) {
            cout << "Berat sampah tidak valid\n";
            continue;
        }
        break;
    }
    for (auto &s : daftarSampah) {
        if (s.kodeJenis == kodeJenis) {
            namaJenis = s.namaJenis;
            break;
        }
    }

    double hargaPerKg = cariHarga(kodeJenis);
    double total = berat * hargaPerKg;
    nasabah.saldo += total;

    Transaksi tx = {buatIDTransaksi(), idNasabah, namaJenis, "SETOR", berat, total, ambilTanggal()};
    riwayatTransaksi.push_back(tx);
    simpanKeFile("nasabah.txt");
    simpanKeFile("transaksi.txt");

    cout << fixed << setprecision(0);
    cout << "\n--- Bukti Penyetoran ---\n";
    cout << "Nasabah    : " << nasabah.nama << endl;
    cout << "Jenis      : " << namaJenis << endl;
    cout << "Berat      : " << berat << " kg x Rp" << hargaPerKg << endl;
    cout << "Total      : Rp" << total << endl;
    cout << "Saldo baru : Rp" << nasabah.saldo << endl;
}

void TarikSaldo() {
    int idNasabah;
    double jumlahTarik;
    string namaJenis;
    string baris;
    while (true) {
        cout << "\n=== Tarik Saldo ===\nInput ID Nasabah: ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
    
        // cek apakah murni angka dan tidak ada karakter anomali di belakang
        if (ss >> idNasabah && !(ss >> sisa)) {
            break;
        }
        cout << "ID Nasabah tidak valid! Masukkan angka saja\n";
    }


    if (!isTerdaftar(idNasabah)) {
        cout << "ID belum terdaftar, Lakukan pendaftaran\n";
        return;
    }
    if (!KelolaAntrean(idNasabah, "TARIK")) return;

    Nasabah &nasabah = cariNasabah(idNasabah);
    cout << "Saldo Anda: Rp" << nasabah.saldo;  
    while (true) {
        cout << "\nInput jumlah tarik: ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
    
        // cek apakah murni angka dan tidak ada karakter anomali di belakang
        if (ss >> jumlahTarik && !(ss >> sisa) && jumlahTarik > 0 && jumlahTarik <= nasabah.saldo) {
            break;
        }
        cout << "Transaksi Gagal (saldo tidak cukup atau nominal tidak valid)\n";
    }


    nasabah.saldo -= jumlahTarik;
    Transaksi tx = {buatIDTransaksi(), idNasabah, "-", "TARIK", 0, jumlahTarik, ambilTanggal()};
    riwayatTransaksi.push_back(tx);
    simpanKeFile("nasabah.txt");
    simpanKeFile("transaksi.txt");

    cout << fixed << setprecision(0);
    cout << "\n--- Bukti Penarikan ---\n";
    cout << "Petugas menyerahkan uang tunai sebesar Rp" << jumlahTarik << endl;
    cout << "Saldo baru : Rp" << nasabah.saldo << endl;
}

void CekSaldoRiwayat() {
    int idNasabah;
    string baris;   
    while (true) {
        cout << "\n=== Cek Saldo & Riwayat ===\nInput ID Nasabah: ";
        getline(cin, baris);
        stringstream ss(baris);
        char sisa;
    
        // cek apakah murni angka dan tidak ada karakter anomali di belakang
        if (ss >> idNasabah && !(ss >> sisa)) {
            break;
        }
        cout << "ID Nasabah tidak valid! Masukkan angka saja\n";
    }

    if (!isTerdaftar(idNasabah)) {
        cout << "ID belum terdaftar, Lakukan pendaftaran\n";
        return;
    }

    Nasabah &nasabah = cariNasabah(idNasabah);
    cout << "Nama  : " << nasabah.nama << "\nSaldo : Rp" << nasabah.saldo << "\n\nRiwayat:\n";

    bool ada = false;
    cout << fixed << setprecision(0);
    cout << left 
         << setw(6)  << "No" << " | "
         << setw(12) << "Jenis" << " | " 
         << left << setw(15) << "Jumlah"  << " | "
         << "   " << left << setw(12) << "Tanggal" << endl;
    cout << string(50, '-') << endl;

    for (auto &tx : riwayatTransaksi) {
        if (tx.idNasabah == idNasabah) {
            cout << left 
                 << setw(6)  << ("#" + to_string(tx.idTransaksi)) << " | "
                 << setw(12) << tx.jenis << " | "
                 << left << setw(15) << tx.total << " | "
                 << "   " << left << setw(12) << tx.tanggal << endl;
            ada = true;
        }
    }
    
    if (!ada) {
        cout << "(Belum ada riwayat transaksi)\n";
    }
    cout << string(50, '-') << endl;
}


// Penyimpanan data, satu data per baris, dipisahkan dengan '|'
void simpanKeFile(string namaFile) {
    ofstream file(namaFile);
    if (!file) return;

    file << fixed << setprecision(0);

    if (namaFile == "nasabah.txt") {
        // Simpan murni datanya saja tanpa setw dan garis pembatas
        for (auto &n : databaseNasabah) {
            file << n.idNasabah << "|" 
                 << n.nama << "|" 
                 << n.alamat << "|" 
                 << n.saldo << "\n";
        }
    } else {
        for (auto &t : riwayatTransaksi) {
            file << t.idTransaksi << "|" 
                 << t.idNasabah << "|" 
                 << t.namaJenis << "|" 
                 << t.jenis << "|" 
                 << t.berat << "|" 
                 << t.total << "|" 
                 << t.tanggal << "\n";
        }
    }
}

void muatDariFile(string namaFile) {
    ifstream file(namaFile);
    if (!file) return;   // file belum ada (pertama kali dijalankan)
    string a, b, c, d, e, f, g;

    if (namaFile == "nasabah.txt") {
        while (getline(file, a, '|')) {
            getline(file, b, '|');
            getline(file, c, '|');
            getline(file, d);
            databaseNasabah.push_back({stoi(a), b, c, stod(d)});
        }
    } else {
        while (getline(file, a, '|')) {
            getline(file, b, '|');
            getline(file, c, '|');
            getline(file, d, '|');
            getline(file, e, '|');
            getline(file, f, '|');
            getline(file, g);
            riwayatTransaksi.push_back({stoi(a), stoi(b), c, d, stod(e), stod(f), g});
        }
    }
}
