#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int>& arr) {
  int n = arr.size();

  cout << "\n[";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << (i < n - 1 ? ", " : "");
  }
  cout << "]\n";
}

void insertionSort(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  for (int i = 1; i < n; i++) {
    int curr = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > curr) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = curr;
  }
}

int main() {
  vector<int> arr = { 1,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  insertionSort(arr);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
