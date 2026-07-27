#include <iostream>
#include <vector>

using namespace std;

int search(vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1, mid;

  while (left <= right) {
    mid = left + (right - left) / 2;
    if (nums[mid] == target) return mid;

    // Left half is sorted
    if (nums[left] <= nums[mid]) {
      if (nums[left] <= target && target < nums[mid])
        right = mid - 1;
      else left = mid + 1;
    }

    // Right half is sorted
    else {
      if (nums[right] >= target && target > nums[mid])
        left = mid + 1;
      else right = mid - 1;
    }
  }

  return -1;
}

int main() {
  vector<int> arr = { 34,45,46,48,56,78,79,82,1,3,5,8,9,25,28 };
  int target = 1;

  int idx = search(arr, target);

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
