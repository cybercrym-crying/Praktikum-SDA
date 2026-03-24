// Akbar Rachim
// 2509106028
#include <iostream>
using namespace std;
void SWAP(int *a, int *b) {
  int temp;
  cout << "Var a : " << *a << " \t| " << a << endl;
  cout << "Var b : " << *b << " \t| " << b << endl;
  temp = *a;
  *a = *b;
  *b = temp;
  cout << "Var a : " << *a << " \t| " << a << endl;
  cout << "Var b : " << *b << " \t| " << b << endl;
};
int main() {
  int a = 5, b = 2;
  SWAP(&a, &b);
  return 0;
}
