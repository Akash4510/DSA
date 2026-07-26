#include <iostream>
#include <vector>

using namespace std;

// --------------------- MY FIRST ATTEMPT O(LOG^2 N) SOLUTION ---------------------

// int binarySearch(vector<int>& arr, int target, int left, int right) {
//   if (left > right) return -1;
//   int mid = left + (right - left) / 2;

//   if (arr[mid] == target)
//     return mid;
//   else if (arr[mid] < target)
//     return binarySearch(arr, target, mid + 1, right);
//   else
//     return binarySearch(arr, target, left, mid - 1);
// }

// vector<int> searchRange(vector<int>& nums, int target) {
//   int left = 0, right = nums.size() - 1, mid;
//   int f, l;

//   while (left <= right) {
//     mid = left + (right - left) / 2;

//     if (nums[mid] == target) {
//       int tempMid = mid;

//       while (tempMid != -1) {
//         f = tempMid;
//         tempMid = binarySearch(nums, target, 0, tempMid - 1);
//       }

//       tempMid = mid;

//       while (tempMid != -1) {
//         l = tempMid;
//         tempMid = binarySearch(nums, target, tempMid + 1, nums.size() - 1);
//       }

//       return { f, l };
//     }

//     else if (nums[mid] > target) right = mid - 1;
//     else left = mid + 1;
//   }

//   return { -1, -1 };
// }


// --------------------- ACTUAL OPTIMAL APPROACH O(LOG N) SOLUTION ---------------------
int findBound(vector<int>& arr, int target, bool isFirst) {
  int left = 0, right = arr.size() - 1, mid;
  int bound = -1;

  while (left <= right) {
    mid = left + (right - left) / 2;

    if (arr[mid] == target) {
      bound = mid;

      if (isFirst) right = mid - 1;
      else left = mid + 1;
    }
    else if (arr[mid] > target) right = mid - 1;
    else left = mid + 1;
  }

  return bound;
}

vector<int> searchRange(vector<int>& nums, int target) {
  int first = findBound(nums, target, true);
  if (first == -1) return { -1, -1 }; // Element not there in the array

  int last = findBound(nums, target, false);

  return { first, last };
}

// Helper function to print the result cleanly
void printResult(const vector<int>& result) {
  cout << "[" << result[0] << ", " << result[1] << "]\n";
}

int main() {
  // Test Case 1: Target exists multiple times (Standard Case)
  vector<int> nums1 = { 5, 7, 7, 8, 8, 10 };
  int target1 = 8;
  cout << "Test Case 1 (Expected: [3, 4]): ";
  printResult(searchRange(nums1, target1));

  // Test Case 2: Target does not exist
  vector<int> nums2 = { 5, 7, 7, 8, 8, 10 };
  int target2 = 6;
  cout << "Test Case 2 (Expected: [-1, -1]): ";
  printResult(searchRange(nums2, target2));

  // Test Case 3: Empty array (Edge Case)
  vector<int> nums3 = {};
  int target3 = 0;
  cout << "Test Case 3 (Expected: [-1, -1]): ";
  printResult(searchRange(nums3, target3));

  // Test Case 4: Target exists only once
  vector<int> nums4 = { 1, 2, 3, 4, 5 };
  int target4 = 3;
  cout << "Test Case 4 (Expected: [2, 2]): ";
  printResult(searchRange(nums4, target4));

  // Test Case 5: Array contains ONLY the target (Edge Case)
  vector<int> nums5 = { 2, 2, 2, 2 };
  int target5 = 2;
  cout << "Test Case 5 (Expected: [0, 3]): ";
  printResult(searchRange(nums5, target5));

  return 0;
}
