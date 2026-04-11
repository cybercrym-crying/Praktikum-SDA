#include <iostream>
#include <math.h>
#include <string>
#define MAX 100
using namespace std;

struct Kereta {
  string nomorKereta;
  string namaKereta;
  string jadwalBerangkat;
  string jadwalTiba;
  string lokasiKeberangkatan;
  string lokasiTujuan;
  string hargaPesanan;
  Kereta() = default;
  Kereta(string nok, string nm, string jb, string jt, string lk, string lt,
         string ht)
      : nomorKereta(nok), namaKereta(nm), jadwalBerangkat(jb), jadwalTiba(jt),
        lokasiKeberangkatan(lk), lokasiTujuan(lt), hargaPesanan(ht) {}
  void tampilkan() {
    cout << "Nomor Kereta         : " << nomorKereta << endl;
    cout << "Nama Kereta          : " << namaKereta << endl;
    cout << "Jadwal Berangkat     : " << jadwalBerangkat << endl;
    cout << "Jadwal Tiba          : " << jadwalTiba << endl;
    cout << "Lokasi Keberangkatan : " << lokasiKeberangkatan << endl;
    cout << "Lokasi Tujuan        : " << lokasiTujuan << endl;
    cout << "Harga Pesanan          : Rp. " << hargaPesanan << endl;
  }
};

struct Akun {
  string nama;
  string pass;
  string hakAkun;
  Akun() = default;
  Akun(string n, string p, string ha) : nama(n), pass(p), hakAkun(ha) {}
};

struct Pesanan {
  Akun *akunUser = nullptr;
  Kereta *tiketPesanan = nullptr;
};
Akun dataAkun[10];
Kereta dataKereta[MAX];
Pesanan *dataPesanan[MAX];
Pesanan *dataRiwayat[MAX];
int jumlahKereta = 0, jumlahAkun = 1;
int front = 0, rear = -1, top = -1;
void SWAP(Kereta *a, Kereta *b) {
  Kereta temp;
  temp = *a;
  *a = *b;
  *b = temp;
};

void buatAkun() {
  string nama, pass;
  cin.ignore(1000, '\n');
  cout << "Masukan Nama : ";
  getline(cin, nama);
  cout << "Masukan Pass : ";
  getline(cin, pass);
  if (nama.empty() || pass.empty()) {
    cout << "Nama atau Pass tidak boleh kosong\n";
    return;
  }
  for (int i = 0; i < jumlahAkun; i++) {
    if (dataAkun[i].nama == nama) {
      cout << "Nama Telah Digunakan\n";
      return;
    }
  }
  if (jumlahAkun >= 10) {
    cout << "Akun Sudah Penuh\n";
  } else {
    dataAkun[jumlahAkun] = Akun(nama, pass, "User");
    jumlahAkun++;
    cout << "Akun berhasil dibuat!\n";
  }
}
Akun *loginAkun() {
  string nama, pass;
  cin.ignore(1000, '\n');
  cout << "Masukan Nama : ";
  getline(cin, nama);
  cout << "Masukan Pass : ";
  getline(cin, pass);
  for (int i = 0; i < jumlahAkun; i++) {
    if (dataAkun[i].nama == nama and dataAkun[i].pass == pass) {
      cout << "Berhasil Login\n";
      return &dataAkun[i];
    }
  }
  return nullptr;
}
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
  cout << "Harga Pesanan : ";
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
      if (stoi(dataKereta[j].hargaPesanan) <
          stoi(dataKereta[min_index].hargaPesanan)) {
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
  if (input.empty())
    return false;
  for (char c : input) {
    if (!isdigit(c))
      return false;
  }
  return true;
}
int cekNomorKereta(string x) {
  for (int i = 0; i < jumlahKereta; i++) {
    if (dataKereta[i].nomorKereta == x) {
      return i;
    }
  }
  return -1;
  ;
}
void pushRiwayat(Pesanan *p) {
  if (top >= MAX - 1) {
    cout << "Riwayat penuh, tidak bisa menyimpan transaksi baru lagi\n";
    return;
  }
  dataRiwayat[++top] = p;
}

void popRiwayat() {
  if (top == -1) {
    cout << "Tidak ada data Riwayat transaksi\n";
    return;
  }
  cout << "Transaksi dibatalkan\n";
  cout << "Nama Pelanggan : " << dataRiwayat[top]->akunUser->nama << endl;
  cout << "Nomor Kereta   : " << dataRiwayat[top]->tiketPesanan->nomorKereta
       << endl;

  delete dataRiwayat[top];
  dataRiwayat[top] = nullptr;
  top--;
}

void tampilRiwayat() {
  if (top == -1) {
    cout << "Tidak Ada  Riwayat Transaksi/n";
    return;
  }
  cout << "Riwayat Transaksi terbaru ke terlama\n";
  for (Pesanan **ptr = dataRiwayat + top; ptr >= dataRiwayat; ptr--) {
    int idx = ptr - dataRiwayat;
    cout << "[" << top - idx + 1 << "] " << (*ptr)->akunUser->nama << " | "
         << (*ptr)->tiketPesanan->nomorKereta << " "
         << ")\n";
  }
}
void tampilAntrian(Pesanan *(&antrian)[MAX]) {
  if (rear == -1 || front > rear) {
    cout << "Antrian Kosong\n";
    return;
  }
  cout << "Antrian Pesanan :\n";
  for (Pesanan **ptr = antrian + front; ptr <= antrian + rear; ptr++) {
    int urutan = ptr - (antrian + front) + 1;
    cout << "[" << urutan << "] " << (*ptr)->akunUser->nama << " |  "
         << (*ptr)->tiketPesanan->nomorKereta << " "
         << ")\n";
  }
}

void peek(Pesanan *(&antrian)[MAX]) {
  if (rear == -1 || front > rear) {
    cout << "Antrian kosong.\n";
  } else {
    cout << "  Nama Pelanggan : " << antrian[front]->akunUser->nama << "\n";
    cout << "  Nomor Kereta   : " << antrian[front]->tiketPesanan->nomorKereta
         << "\n";
  }

  cout << "\n";

  if (top == -1) {
    cout << "[Riwayat] Riwayat transaksi kosong\n";
  } else {
    cout << "[Riwayat - Terakhir]\n";
    cout << "  Nama Pelanggan : " << dataRiwayat[top]->akunUser->nama << "\n";
    cout << "  Nomor Kereta   : " << dataRiwayat[top]->tiketPesanan->nomorKereta
         << "\n";
  }
}
void enqueuePesanan(Pesanan *(&antrian)[MAX], Akun *user) {
  if (rear >= MAX - 1) {
    cout << "Antrian Penuh\n";
    return;
  }
  tampilkanList(dataKereta);
  cout << "Input Nomor Kereta Yang Dibeli : ";
  string inputUser;
  cin >> inputUser;

  int nomorKeretaPesanan = cekNomorKereta(inputUser);
  if (nomorKeretaPesanan == -1) {
    cout << "Pilihan Tidak Tersedia\n";
  } else {
    rear++;
    antrian[rear] = new Pesanan();
    antrian[rear]->akunUser = user;
    antrian[rear]->tiketPesanan = &dataKereta[nomorKeretaPesanan];
    cout << "Berhasil memesan tiket " << antrian[rear]->tiketPesanan->namaKereta
         << "!\n";
    cout << "Posisi Antrian Anda Saat Ini : " << rear - front + 1 << "\n";
  }
}
void dequeuePesanan(Pesanan *(&antrian)[MAX]) {
  if (rear == -1) {
    cout << "Tidak Ada Antrian Pesanan\n";
  } else {
    cout << "Memproses Pesanan Tiket....\n";
    while (front <= rear) {
      cout << "Nama Pelanggan : " << antrian[front]->akunUser->nama << endl;
      cout << "Nomor Tiket    : " << antrian[front]->tiketPesanan->nomorKereta
           << endl;
      pushRiwayat(antrian[front]);
      front++;
    }
    front = 0;
    rear = -1;
  }
}

bool cekAdmin(Akun *akun) {
  if (akun->hakAkun != "Admin") {
    cout << "Akses ditolak. Hanya Admin yang bisa mengakses fitur ini\n";
    return false;
  }
  return true;
}

int main() {
  string inputUser;
  int hasil;
  Akun *akunUser = nullptr;

  dataAkun[0] = Akun("Akbar", "028", "Admin");

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

  while (akunUser == nullptr) {
    cout << "1. Buat Akun\n";
    cout << "2. Login Akun\n";
    cout << "Pilihan : ";
    cin >> inputUser;
    if (cekInput(inputUser) == false) {
      continue;
    } else if (inputUser == "3") {
      cout << "Selamat Tinggal\n";
      return 0;
    }
    switch (stoi(inputUser)) {
    case 1:
      buatAkun();
      break;
    case 2:
      akunUser = loginAkun();
      break;
    default:
      continue;
    }
  }
  while (true) {
    cout << "------------------------------------------\n";
    cout << " 1.  Tampilkan Jadwal Kereta\n";
    cout << " 2.  Tambah Jadwal Kereta\n [Admin]";
    cout << " 3.  Cari Rute & Tujuan\n";
    cout << " 4.  Cari Nomor Kereta\n";
    cout << " 5.  Urutkan Nama Kereta (A-Z)\n";
    cout << " 6.  Urutkan Harga Kereta (Termurah)\n";
    cout << " 7.  Pesan Tiket (Enqueue)\n";
    cout << " 8.  Tampilkan Antrian Pesanan\n";
    cout << " 9.  Proses Pesanan (Dequeue) [Admin]\n";
    cout << " 10. Tampilkan Riwayat Transaksi\n";
    cout << " 11. Batalkan Transaksi Terakhir (Pop) [Admin]\n";
    cout << " 12. Peek Antrian & Riwayat\n";
    cout << " 13. Exit\n";
    cout << "Pilihan : ";
    cin >> inputUser;
    cout << "\n";
    if (cekInput(inputUser) == false) {
      continue;
    } else if (inputUser == "13") {
      cout << "Selamat Tinggal";
      break;
    }
    switch (stoi(inputUser)) {
    case 1:
      tampilkanList(dataKereta);
      break;
    case 2:
      if (cekAdmin(akunUser) == false)
        break;
      cin.ignore(1000, '\n');
      tambahData();
      break;
    case 3:
      linierSearch(dataKereta);
      break;
    case 4:
      cout << "Masukan Nomor Kereta : ";
      hasil = jumpSearch();
      if (hasil != -1) {
        cout << "\nKereta Ditemukan\n";
        dataKereta[hasil].tampilkan();
      } else {
        cout << "Kereta Tidak Ditemukan\n";
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
    case 7:
      enqueuePesanan(dataPesanan, akunUser);
      break;
    case 8:
      tampilAntrian(dataPesanan);
      break;
    case 9:
      if (cekAdmin(akunUser) == false)
        break;
      dequeuePesanan(dataPesanan);
      break;
    case 10:
      tampilRiwayat();
      break;
    case 11:
      if (cekAdmin(akunUser) == false)
        break;
      popRiwayat();
      break;
    case 12:
      peek(dataPesanan);
      break;
    default:
      cout << "Tidak Ada Dalam Pilihan\n";
      continue;
    }
  }
  return 0;
}
