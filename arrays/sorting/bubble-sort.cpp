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

void bubbleSort(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
      }
    }
  }
}

void bubbleSortOptimized(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  for (int i = 0; i < n - 1; i++) {
    int isSorted = true;

    for (int j = 0; j < n - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(arr[j], arr[j + 1]);
        isSorted = false;
      }
    }

    // If in an entire inner loop we didn't swap, it means the array is already sorted
    if (isSorted) return;
  }
}

int main() {
  vector<int> arr = { 1,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  bubbleSort(arr);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
