#ifndef TRANSAKSI_HPP
#define TRANSAKSI_HPP
#include <string>
#include <vector>
using namespace std;

struct Transaksi {
    int idTransaksi, idNasabah;
    string namaJenis;
    string jenis;
    double berat, total;
    string tanggal;
};

extern vector<Transaksi> riwayatTransaksi;

void SetorSampah();
void TarikSaldo();
void CekSaldoRiwayat();
int buatIDTransaksi();
string ambilTanggal();
void simpanKeFile(string namaFile);
void muatDariFile(string namaFile);
#endif
