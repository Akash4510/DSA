#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& arr, int target) {
  int left = 0, right = arr.size() - 1, mid;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] == target) return mid;
    else if (arr[mid] > target) right = mid - 1;
    else left = mid + 1;
  }

  return -1;
}

int binarySearchRecursive(vector<int>& arr, int target, int left, int right) {
  if (left > right) return -1;

  int mid = left + (right - left) / 2;
  if (arr[mid] == target) return mid;

  else if (arr[mid] > target) return binarySearchRecursive(arr, target, left, mid - 1);
  else return binarySearchRecursive(arr, target, mid + 1, right);
}

int main() {
  vector<int> arr = { 1,3,5,8,9,25,28,34,45,46,48,56,78,79,82 };
  int target = 34;

  // int idx = binarySearch(arr, target);
  int idx = binarySearchRecursive(arr, target, 0, arr.size() - 1);

  cout << endl << target;
  if (idx != -1) {
    cout << " is present in index: " << idx;
  }
  else {
    cout << " is not present in the array";
  }
  cout << endl << endl;

  return 0;
}
