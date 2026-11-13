#ifndef ANTREAN_HPP
#define ANTREAN_HPP
#include <queue>
#include <string>
using namespace std;

// satu layanan = ID nasabah + jenis transaksi yang diantrekan ("SETOR" / "TARIK")
struct Layanan {
    int idNasabah;
    string jenis;
    int nomor;
};

extern queue<Layanan> antrean;
extern int nomorAntreanTerakhir;

int generateAntrean(int idNasabah, string jenis);
bool panggilAntrean(int idNasabah, string jenis);
bool KelolaAntrean(int idNasabah, string jenis);
#endif
