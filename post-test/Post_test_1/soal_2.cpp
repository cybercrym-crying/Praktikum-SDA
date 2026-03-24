// Akbar Rachim
// 2509106028
#include <iostream>
using namespace std;
struct Mhs {
  string nama;
  string NIM;
  float ipk;
  Mhs() = default;
  Mhs(string n, string N, float i) : nama(n), NIM(N), ipk(i) {}
  void display() {
    cout << "Nama : " << nama << endl;
    cout << "NIM  : " << NIM << endl;
    cout << "IPK  : " << ipk << endl;
  }
};

void greaterIPK(Mhs array[], int n) {
  Mhs max = array[0];
  for (int i = 0; i < n; i++) {
    if (array[i].ipk > max.ipk) {
      max = array[i];
    }
  }
  max.display();
}
int main() {
  int const n = 5;
  string nama, nim;
  float ipk;
  Mhs array[n];
  for (int i = 0; i < n; i++) {
    cin.ignore();
    cout << "Nama : ";
    getline(cin, nama);
    cout << "NIM  : ";
    cin >> nim;
    cout << "IPK  : ";
    cin >> ipk;
    cout << endl;
    array[i] = Mhs(nama, nim, ipk);
  }
  cout << "Mahasiswa IPK Tertinggi\n";
  greaterIPK(array, n);
  return 0;
}
