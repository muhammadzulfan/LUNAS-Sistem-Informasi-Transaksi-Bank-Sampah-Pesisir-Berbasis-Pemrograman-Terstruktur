#include <iostream>
#include <sstream>
#include "antrean.hpp"

queue<Layanan> antrean;
int nomorAntreanTerakhir = 0;

// cari tiket nasabah yang masih menunggu, nullptr jika tidak ada
static bool sudahAntre(int idNasabah, Layanan &hasil) {
    queue<Layanan> salinan = antrean;
    while (!salinan.empty()) {
        if (salinan.front().idNasabah == idNasabah) {
            hasil = salinan.front();
            return true;
        }
        salinan.pop();
    }
    return false;
}

// nasabah ambil nomor, tiket (ID + jenis transaksi) masuk antrean
int generateAntrean(int idNasabah, string jenis) {
    nomorAntreanTerakhir++;
    antrean.push({idNasabah, jenis, nomorAntreanTerakhir});
    return nomorAntreanTerakhir;
}

// true jika tiket nasabah di urutan depan DAN jenisnya sesuai menu, lalu keluar dari antrean
bool panggilAntrean(int idNasabah, string jenis) {
    if (antrean.empty()) {
        cout << "Tidak ada nomor antrean, silakan ambil nomor dulu\n";
        return false;
    }
    if (antrean.front().idNasabah != idNasabah) {
        cout << "Belum giliran Anda, ID yang dipanggil: " << antrean.front().idNasabah << endl;
        return false;
    }
    if (antrean.front().jenis != jenis) {
        cout << "Nomor antrean Anda (" << antrean.front().nomor << ") untuk transaksi "
             << antrean.front().jenis << ", bukan " << jenis
             << ". Silakan pilih menu " << antrean.front().jenis << " di menu utama\n";
        return false;
    }
    cout << "\nMemanggil nomor antrean " << antrean.front().nomor
         << " (ID " << antrean.front().idNasabah << ", " << antrean.front().jenis << ")\n";
    antrean.pop();
    return true;
}

// true = boleh dilayani, false = kembali ke menu utama
bool KelolaAntrean(int idNasabah, string jenis) {
    int pilihAntrean;
    string baris;
    while (true) {
        cout << "\n--- Antrean " << jenis << " ---\n";
        cout << "1. Ambil nomor\n2. Panggil nomor\nPilih : ";
        getline(cin, baris);

        stringstream ss(baris);
        char sisa;

        if (ss >> pilihAntrean && !(ss >> sisa)) {
            if (pilihAntrean == 1 || pilihAntrean == 2) {
                break;
            }
        }
        cout << "Inputan tidak valid, masukkan angka (1-2)\n";
    }

    if (pilihAntrean == 1) {
        Layanan aktif;
        if (sudahAntre(idNasabah, aktif)) {
            cout << "Anda masih punya nomor antrean " << aktif.nomor
                 << " untuk transaksi " << aktif.jenis << " (menunggu dipanggil)\n";
            return false;
        }
        int nomor = generateAntrean(idNasabah, jenis);
        cout << "Nomor antrean Anda: " << nomor << " (menunggu dipanggil)\n";
        return false;
    }
    return panggilAntrean(idNasabah, jenis);
}
