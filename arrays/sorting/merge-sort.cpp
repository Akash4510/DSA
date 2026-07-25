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

void merge(vector<int>& arr, int left, int mid, int right) {
  int n = right - left + 1;
  vector<int> temp(n);

  int i = left, j = mid + 1, k = 0;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j])  temp[k++] = arr[i++];
    else temp[k++] = arr[j++];
  }

  while (i <= mid) temp[k++] = arr[i++];
  while (j <= right) temp[k++] = arr[j++];

  k = 0;
  for (int i = left; i <= right; i++) {
    arr[i] = temp[k++];
  }
}

void mergeSort(vector<int>& arr, int left, int right) {
  if (left >= right) return;

  int mid = left + (right - left) / 2;

  mergeSort(arr, left, mid);
  mergeSort(arr, mid + 1, right);

  merge(arr, left, mid, right);
}

int main() {
  vector<int> arr = { 1,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  mergeSort(arr, 0, arr.size() - 1);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
