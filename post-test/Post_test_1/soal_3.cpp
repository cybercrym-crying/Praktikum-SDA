// Akbar Rachim
// 2509106028
#include <iostream>
using namespace std;

void reverseArray(int *array, int n) {
  int temp;
  for (int i = 0; i < n / 2; i++) {
    temp = *(array + i);
    *(array + i) = *(array + (n - i - 1));
    *(array + (n - 1 - i)) = temp;
  }
}
int main() {
  int const n = 7;
  int array[n] = {2, 3, 5, 7, 11, 13, 17};
  cout << "Normal \n";
  for (int i = 0; i < n; i++) {
    cout << array[i] << " \t| " << array + i << endl;
  }
  cout << endl << "Reverse\n";
  reverseArray(array, n);
  for (int i = 0; i < n; i++) {
    cout << array[i] << " \t| " << array + i << endl;
  }

  return 0;
}
