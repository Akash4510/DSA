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

// A variant of a selection sort, but it's quite inefficient, it's more like bubble sort but opposite.
void exchangeSort(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j])  swap(arr[i], arr[j]);
    }
  }
}

void selectionSort(vector<int>& arr) {
  int n = arr.size();
  if (n <= 1) return;

  for (int i = 0; i < n - 1; i++) {
    int minIndex = i;

    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) minIndex = j;
    }

    swap(arr[i], arr[minIndex]);
  }
}

int main() {
  vector<int> arr = { 1,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  selectionSort(arr);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
