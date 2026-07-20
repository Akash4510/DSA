#include <iostream>
#include <vector>

using namespace std;

vector<int> mergeSortedArrays(const vector<int>& arr1, const vector<int>& arr2) {
  vector<int> merged;
  int ptr1 = 0;
  int ptr2 = 0;

  while (ptr1 < arr1.size() && ptr2 < arr2.size()) {
    if (arr1[ptr1] < arr2[ptr2]) {
      merged.push_back(arr1[ptr1++]);
    }
    else {
      merged.push_back(arr2[ptr2++]);
    }
  }

  while (ptr1 < arr1.size()) {
    merged.push_back(arr1[ptr1++]);
  }

  while (ptr2 < arr2.size()) {
    merged.push_back(arr2[ptr2++]);
  }

  return merged;
}

int main() {
  vector<int> arr1 = { 1, 3, 5, 7 };
  vector<int> arr2 = { 2, 4, 6, 8, 9, 10 };

  vector<int> result = mergeSortedArrays(arr1, arr2);

  cout << "Merged Array: ";
  for (int num : result) {
    cout << num << " ";
  }
  cout << "\n";

  // Expected Output: 1 2 3 4 5 6 7 8 9 10

  return 0;
}