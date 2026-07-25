#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printArray(const vector<int>& arr) {
  int n = arr.size();

  cout << "\n[";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << (i < n - 1 ? ", " : "");
  }
  cout << "]\n";
}

void countingSort(vector<int>& arr) {
  if (arr.empty()) return;

  int maxElement = *max_element(arr.begin(), arr.end());
  vector<int> counts(maxElement + 1, 0);

  for (int a : arr) counts[a]++;

  int k = 0;
  for (int i = 0; i < counts.size(); i++) {
    for (int j = 0; j < counts[i]; j++) {
      arr[k++] = i;
    }
  }
}

int main() {
  vector<int> arr = { 1,2,4,5,5,7,9,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  countingSort(arr);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
