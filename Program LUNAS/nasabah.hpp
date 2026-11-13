#ifndef NASABAH_HPP
#define NASABAH_HPP
#include <string>
#include <vector>
using namespace std;

struct Nasabah {
    int idNasabah;
    string nama;
    string alamat;
    double saldo;
};

extern vector<Nasabah> databaseNasabah;

void RegistrasiNasabah();
bool isTerdaftar(int idNasabah);
bool isTerdaftar(string nama, string alamat);
Nasabah &cariNasabah(int idNasabah);
int buatIDNasabah();
#endif
