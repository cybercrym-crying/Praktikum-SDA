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
    cout << "Harga Pesanan        : Rp. " << hargaPesanan << endl;
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

struct NodePesanan {
  Pesanan *data;
  NodePesanan *next;
  NodePesanan(Pesanan *p) : data(p), next(nullptr) {}
};
Akun dataAkun[10];
Kereta dataKereta[MAX];

int jumlahKereta = 0, jumlahAkun = 1;
NodePesanan *front = nullptr, *rear = nullptr, *top = nullptr;
int queueMax = 0;

void SWAP(Kereta *a, Kereta *b);
void buatAkun();
Akun *loginAkun();
void tambahData();
void tampilkanList(Kereta *listKereta);
void linierSearch(Kereta *listKereta);
int jumpSearch();
void selectionSort();
void merger(Kereta arr[], int kiri, int tengah, int kanan);
void mergerSort(Kereta arr[], int kiri, int kanan);
bool cekInput(string input);
int cekNomorKereta(string x);
void pushRiwayat(Pesanan *p);
void popRiwayat();
void tampilRiwayat();
void tampilAntrian();
void peek();
void enqueuePesanan(Akun *user);
void dequeuePesanan();
bool cekAdmin(Akun *akun);

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
    cout << " 2.  Tambah Jadwal Kereta [Admin]\n";
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
      enqueuePesanan(akunUser);
      break;
    case 8:
      tampilAntrian();
      break;
    case 9:
      if (cekAdmin(akunUser) == false)
        break;
      dequeuePesanan();
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
      peek();
      break;
    default:
      cout << "Tidak Ada Dalam Pilihan\n";
      continue;
    }
  }
  return 0;
}

void SWAP(Kereta *a, Kereta *b) {
  Kereta temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

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
    if (dataAkun[i].nama == nama && dataAkun[i].pass == pass) {
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
}

void pushRiwayat(Pesanan *p) {
  NodePesanan *node = new NodePesanan(p);
  node->next = top;
  top = node;
}

void popRiwayat() {
  if (top == nullptr) {
    cout << "Tidak ada data Riwayat transaksi\n";
  } else {
    NodePesanan *temp = top;
    cout << "Transaksi dibatalkan\n";
    cout << "Nama Pelanggan : " << temp->data->akunUser->nama << endl;
    cout << "Nomor Kereta   : " << temp->data->tiketPesanan->nomorKereta
         << endl;
    top = top->next;
    delete temp->data;
    delete temp;
  }
}
void tampilRiwayat() {
  if (top == nullptr) {
    cout << "Tidak Ada Riwayat Transaksi\n";
  } else {
    NodePesanan *sekarang = top;
    int i = 1;
    while (sekarang != nullptr) {
      cout << i++ << " " << sekarang->data->akunUser->nama << " | "
           << sekarang->data->tiketPesanan->nomorKereta << endl;
      sekarang = sekarang->next;
    }
  }
}
void tampilAntrian() {
  if (front == nullptr) {
    cout << "Antrian Kosong\n";
  } else {
    NodePesanan *sekarang = front;
    int i = 1;
    cout << "Antrian Pesanan :\n";
    while (sekarang != nullptr) {

      cout << i++ << " | " << sekarang->data->akunUser->nama << " | "
           << sekarang->data->tiketPesanan->nomorKereta << endl;
      sekarang = sekarang->next;
    }
  }
}
void peek() {
  if (front == nullptr) {
    cout << "Antrian kosong.\n";
  } else {
    cout << "  Nama Pelanggan : " << front->data->akunUser->nama << "\n";
    cout << "  Nomor Kereta   : " << front->data->tiketPesanan->nomorKereta
         << "\n";
  }

  cout << "\n";

  if (top == nullptr) {
    cout << "[Riwayat] Riwayat transaksi kosong\n";
  } else {
    cout << "[Riwayat - Terakhir]\n";
    cout << "  Nama Pelanggan : " << top->data->akunUser->nama << "\n";
    cout << "  Nomor Kereta   : " << top->data->tiketPesanan->nomorKereta
         << "\n";
  }
}

void enqueuePesanan(Akun *user) {
  tampilkanList(dataKereta);
  cout << "Input Nomor Kereta Yang Dibeli : ";
  string inputUser;
  cin >> inputUser;

  int nomorKeretaPesanan = cekNomorKereta(inputUser);
  if (nomorKeretaPesanan == -1) {
    cout << "Pilihan Tidak Tersedia\n";

    return;
  }
  Pesanan *p = new Pesanan();
  p->akunUser = user;
  p->tiketPesanan = &dataKereta[nomorKeretaPesanan];

  NodePesanan *node = new NodePesanan(p);
  if (rear == nullptr) {
    rear = node;
    front = rear;
  } else {
    rear->next = node;
    rear = node;
  }
  queueMax++;
  cout << "Berhasil Memesan Tiket : " << p->tiketPesanan->nomorKereta << endl;
}
void dequeuePesanan() {
  while (front != nullptr) {

    NodePesanan *temp = front;
    cout << "Nama Pelanggan : " << temp->data->akunUser->nama << endl;
    cout << "Nomor Kereta   : " << temp->data->tiketPesanan->nomorKereta
         << endl;
    pushRiwayat(temp->data);
    front = front->next;
    delete temp;
    queueMax--;
  }

  rear = nullptr;
}
