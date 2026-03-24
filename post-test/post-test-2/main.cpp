#include <iostream>
#include <math.h>
#include <string>
using namespace std;

struct Kereta {
  string nomorKereta;
  string namaKereta;
  string jadwalBerangkat;
  string jadwalTiba;
  string lokasiKeberangkatan;
  string lokasiTujuan;
  string hargaTiket;
  Kereta() = default;
  Kereta(string nok, string nm, string jb, string jt, string lk, string lt,
         string ht)
      : nomorKereta(nok), namaKereta(nm), jadwalBerangkat(jb), jadwalTiba(jt),
        lokasiKeberangkatan(lk), lokasiTujuan(lt), hargaTiket(ht) {}
  void tampilkan() {
    cout << "Nomor Kereta         : " << nomorKereta << endl;
    cout << "Nama Kereta          : " << namaKereta << endl;
    cout << "Jadwal Berangkat     : " << jadwalBerangkat << endl;
    cout << "Jadwal Tiba          : " << jadwalTiba << endl;
    cout << "Lokasi Keberangkatan : " << lokasiKeberangkatan << endl;
    cout << "Lokasi Tujuan        : " << lokasiTujuan << endl;
    cout << "Harga Tiket          : Rp. " << hargaTiket << endl;
  }
};

const int MAX = 100;
Kereta dataKereta[MAX];
int jumlahKereta = 0;

void SWAP(Kereta *a, Kereta *b) {
  Kereta temp;
  temp = *a;
  *a = *b;
  *b = temp;
};

void tambahData() {
  string nomor, nama, harga, jadwalB, jadwalT, lokasiK, lokasiT;
  cout << "Kode Kereta : ";
  getline(cin, nomor);
  cout << "Nama Kereta : ";
  getline(cin, nama);
  cout << "Jadwal Berangkat (dd-mm-yyyy hh:mm) : ";
  getline(cin, jadwalB);
  cout << "Jadwal Tiba (dd-mm-yyyy hh:mm) : ";
  getline(cin, jadwalT);
  cout << "Lokasi Keberangkatan : ";
  getline(cin, lokasiK);
  cout << "Lokasi Tiba : ";
  getline(cin, lokasiT);
  cout << "Harga Tiket : ";
  getline(cin, harga);
  dataKereta[jumlahKereta] =
      Kereta(nomor, nama, jadwalB, jadwalT, lokasiK, lokasiT, harga);
  jumlahKereta++;
}

void tampilkanList(Kereta *listKereta) {
  for (int i = 0; i < jumlahKereta; i++) {
    (listKereta + i)->tampilkan();
    cout << endl;
  }
}

void linierSearch(Kereta *listKereta) {
  bool ditemukan = false;
  string asal, tujuan;
  cin >> asal >> tujuan;

  // Iterasi dimulai dari elemen pertama (i=0) hingga elemen terakhir
  // (i=jumlahKereta-1)
  for (int i = 0; i < jumlahKereta; i++) {

    // Tiap iterasi: periksa apakah elemen ke-i cocok dengan asal DAN tujuan
    // yang dicari
    if ((listKereta + i)->lokasiKeberangkatan == asal &&
        (listKereta + i)->lokasiTujuan == tujuan) {

      // Kedua kondisi terpenuhi: tampilkan data dan tandai bahwa data ditemukan
      (listKereta + i)->tampilkan();
      ditemukan = true;

      // Tidak ada break di sini: iterasi tetap berlanjut ke elemen berikutnya
      // karena bisa saja ada lebih dari satu kereta dengan rute yang sama
    }

    // Kondisi tidak terpenuhi: i++ otomatis, lanjut periksa elemen berikutnya
  }

  // Setelah seluruh data diperiksa, tampilkan pesan jika tidak ada yang cocok
  if (ditemukan == false) {
    cout << "Tidak ada rute yang dicari\n";
  }
}
int jumpSearch() {
  string target;
  int n = jumlahKereta;
  int lompat = sqrt(n), sebelum = 0;
  cin >> target;
  while (dataKereta[min(lompat, n) - 1].nomorKereta < target) {
    sebelum = lompat;
    lompat += sqrt(n);
    if (sebelum >= n) {
      return -1;
    }
  }
  while (dataKereta[sebelum].nomorKereta < target) {
    sebelum++;
    if (sebelum == min(lompat, n)) {
      return -1;
    }
  }

  if (dataKereta[sebelum].nomorKereta == target) {
    return sebelum;
  }
  return -1;
}

void selectionSort() {
  int min_index;
  for (int i = 0; i < jumlahKereta - 1; i++) {
    min_index = i;
    for (int j = i + 1; j < jumlahKereta; j++) {
      if (stoi(dataKereta[j].hargaTiket) <
          stoi(dataKereta[min_index].hargaTiket)) {
        min_index = j;
      }
    }
    if (min_index != i) {
      SWAP(&dataKereta[i], &dataKereta[min_index]);
    }
  }
}

void merger(Kereta arr[], int kiri, int tengah, int kanan) {
  int n1 = tengah - kiri + 1;
  int n2 = kanan - tengah;

  Kereta L[MAX], R[MAX];

  for (int i = 0; i < n1; i++)
    L[i] = arr[kiri + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[tengah + 1 + j];

  int i = 0, j = 0, k = kiri;
  while (i < n1 && j < n2) {
    if (L[i].namaKereta <= R[j].namaKereta)
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }
  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}

void mergerSort(Kereta arr[], int kiri, int kanan) {
  if (kiri < kanan) {
    int tengah = kiri + (kanan - kiri) / 2;
    mergerSort(arr, kiri, tengah);
    mergerSort(arr, tengah + 1, kanan);
    merger(arr, kiri, tengah, kanan);
  }
}

bool cekInput(string input) {
  for (char c : input) {
    if (!(isdigit(c))) {
      return false;
    }
  }
  return true;
}

int main() {
  string inputUser;
  int hasil;

  dataKereta[0] = Kereta("KA001", "Argo Bromo Anggrek", "01-01-2025 08:00",
                         "01-01-2025 16:00", "Jakarta", "Surabaya", "350000");
  dataKereta[1] = Kereta("KA002", "Bima", "01-01-2025 17:00",
                         "02-01-2025 05:00", "Jakarta", "Surabaya", "280000");
  dataKereta[2] = Kereta("KA003", "Gajayana", "01-01-2025 18:00",
                         "02-01-2025 07:00", "Boyolali", "Malang", "320000");
  dataKereta[3] = Kereta("KA004", "Lodaya", "01-01-2025 09:00",
                         "01-01-2025 17:00", "Jakarta", "Bandung", "150000");
  dataKereta[4] = Kereta("KA005", "Argo Wilis", "01-01-2025 07:00",
                         "01-01-2025 19:00", "Malang", "Bandung", "420000");
  jumlahKereta = 5;

  if (jumlahKereta == 0) {
    cout << "Tidak Ada List Kereta";
    return 0;
  }
  while (true) {
    cout << "1. Tampilkan Jadwal Kereta\n";
    cout << "2. Tambah Jadwal Kereta\n";
    cout << "3. Cari Rute &  Tujuan\n";
    cout << "4. Cari Nomor Kereta\n";
    cout << "5. Urutkan Berdasarkan Nama Kereta A-Z\n";
    cout << "6. Urutkan Berdasarkan Harga Kereta Termursah\n";
    cout << "7. Exit\n";
    cout << "Pilihan : ";
    cin >> inputUser;
    cout << endl;
    cout << inputUser;
    if (cekInput(inputUser) == false) {
      continue;
    } else if (inputUser == "7") {
      cout << "Selamat Tinggal";
      return 0;
    }
    switch (stoi(inputUser)) {
    case 1:
      tampilkanList(dataKereta);
      break;
    case 2:
      cin.ignore(1000, '\n');
      tambahData();
      break;
    case 3:
      linierSearch(dataKereta);
      break;
    case 4:
      hasil = jumpSearch();
      if (hasil != -1) {
        cout << "\nKereta Ditemukan\n";
        dataKereta[hasil].tampilkan();
      } else {
        cout << "Kereta Tidak Ditemukan Dengan Nomor Tersebut\n";
      }
      break;
    case 5:
      mergerSort(dataKereta, 0, jumlahKereta - 1);
      tampilkanList(dataKereta);
      break;
    case 6:
      selectionSort();
      tampilkanList(dataKereta);
      break;
    default:
      cout << "Tidak Ada Dalam Pilihan\n";
      continue;
    }
  }
  return 0;
}
