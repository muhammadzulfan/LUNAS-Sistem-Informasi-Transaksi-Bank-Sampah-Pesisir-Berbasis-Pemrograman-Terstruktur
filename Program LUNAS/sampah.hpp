#ifndef SAMPAH_HPP
#define SAMPAH_HPP
#include <string>
#include <vector>
using namespace std;

struct Sampah {
    int kodeJenis;
    string namaJenis;
    double hargaPerKg;
};

extern vector<Sampah> daftarSampah;

void inisialisasiSampah();
bool isJenisValid(int kodeJenis);
double cariHarga(int kodeJenis);
#endif
