// Akbar Rachim
// 2509106028
#include <iostream>
using namespace std;

int findMin(int array[], int n) {
  int min = array[0];
  for (int i = 1; i < n; i++) {
    if (array[i] < min) {
      min = array[i];
    }
  }
  return min;
}
int main() {
  int const n = 8;
  int array[n] = {1, 1, 2, 3, 5, 8, 13, 21};
  int min = findMin(array, n);
  for (int i = 0; i < n; i++) {
    if (min == array[i]) {
      cout << "Indeks : " << i << endl;
      cout << "Min    : " << min << endl;
      break;
    }
  }

  return 0;
}

/*

PSEUDOCODE                                     Cost  Tmin   Tmax
procedure FindMin(A : array of n elements)     C1    O(1)   O(1)
min ← A[0]                                     C2    O(1)   O(1)
for i ← 1 to n - 1 do                          C3    O(n)   O(n)
if A[i] < min then                             C4    O(n-1) O(n-1)
min ← A[i]                                     C5    0      O(n-1)
end if                                         C6    O(n-1) O(n-1)
end for                                        C7    O(n)   O(n)
return min                                     C8    O(1)   O(1)
end procedure                                  C9    O(1)   O(1)

Jika dihitung maka Tmin
Best Case = C1 + C2 + C3n + C4n-C4 + 0 + C6n-C6 + C7n + C8 + C9
          = (C3 + C4 + C6 + C7)n + (C1 + C2 - C4 - C6 + C8 + C9)
          = (1 + 1 + 1 + 1)n + (1 + 1 - 1 - 1 + 1 + 1)
          = 4n + 2 (Abaikan konstanta)
          = O(n)


Worst Case =  C1 + C2 + C3n + C4n-C4 + C5n-C5 + C6n-C6 + C7n + C8 + C9
           = (C3 + C4 + C5 + C6 + C7)n + (C1 + C2 - C4 - C5 - C6 + C8 + C9)
           = (1 + 1  + 1 + 1 + 1)n + (1 + 1 - 1 - 1 - 1 + 1 + 1)
           = 5n + 1 (Abaikan konstanta)
           = O(n)

Best Case dan Worst Case tetap membentu Fungsi linier maka BIG-O => O(n)






  */
