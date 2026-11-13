#include "sampah.hpp"

vector<Sampah> daftarSampah;

void inisialisasiSampah() {
    daftarSampah.push_back({1, "Plastik Botol PET", 3000});
    daftarSampah.push_back({2, "Plastik gelas/kemasan", 1500});
    daftarSampah.push_back({3, "Kertas", 1500});
    daftarSampah.push_back({4, "Logam", 8000});
    daftarSampah.push_back({5, "Kaca", 1000});
    daftarSampah.push_back({6, "Kardus", 2000});
    daftarSampah.push_back({7, "Tembaga", 6000});
    daftarSampah.push_back({8, "Aluminium", 12000});
    daftarSampah.push_back({9, "Elektronik", 5000});
    daftarSampah.push_back({10, "Tekstil", 1000});
    daftarSampah.push_back({11, "Minyak Jelantah", 4000});
}

bool isJenisValid(int kodeJenis) {
    for (auto &s : daftarSampah)
        if (s.kodeJenis == kodeJenis) return true;
    return false;
}

double cariHarga(int kodeJenis) {
    for (auto &s : daftarSampah)
        if (s.kodeJenis == kodeJenis) return s.hargaPerKg;
    return 0;
}
