#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> 

using namespace std;

int smallestSubarrayWithSum(const vector<int>& arr, int target) {
  int minLength = INT_MAX;
  int windowSum = 0;
  int left = 0;

  for (int right = 0; right < arr.size(); right++) {
    windowSum += arr[right];

    while (windowSum >= target) {
      minLength = min(minLength, right - left + 1);
      windowSum -= arr[left++];
    }
  }

  return minLength == INT_MAX ? 0 : minLength;
}

int main() {
  // 1. Standard Case
  vector<int> arr1 = { 2, 1, 5, 2, 3, 2 };
  int target1 = 7;
  cout << "Test 1 (Standard)        : " << smallestSubarrayWithSum(arr1, target1)
    << " | (Expected Output: 2 from [5, 2])\n";

  // 2. Impossible Case (Target too large)
  vector<int> arr2 = { 1, 1, 1, 1, 1, 1, 1, 1 };
  int target2 = 11;
  cout << "Test 2 (Impossible)      : " << smallestSubarrayWithSum(arr2, target2)
    << " | (Expected Output: 0)\n";

  // 3. Single Element Match
  vector<int> arr3 = { 1, 10, 2, 3 };
  int target3 = 8;
  cout << "Test 3 (Single Element)  : " << smallestSubarrayWithSum(arr3, target3)
    << " | (Expected Output: 1 from [10])\n";

  // 4. The Exact Fit
  vector<int> arr4 = { 2, 2, 2, 2 };
  int target4 = 8;
  cout << "Test 4 (Exact Fit)       : " << smallestSubarrayWithSum(arr4, target4)
    << " | (Expected Output: 4 from [2, 2, 2, 2])\n";

  // 5. The Late Bloomer (Massive element at the end)
  vector<int> arr5 = { 1, 1, 1, 1, 100 };
  int target5 = 100;
  cout << "Test 5 (Late Bloomer)    : " << smallestSubarrayWithSum(arr5, target5)
    << " | (Expected Output: 1 from [100])\n";

  // 6. Target Smaller Than Any Element
  vector<int> arr6 = { 10, 20, 30 };
  int target6 = 5;
  cout << "Test 6 (Target < Array)  : " << smallestSubarrayWithSum(arr6, target6)
    << " | (Expected Output: 1 from [10])\n";

  // 7. Match at the very end
  vector<int> arr7 = { 1, 2, 3, 4, 5 };
  int target7 = 9;
  cout << "Test 7 (Match at end)    : " << smallestSubarrayWithSum(arr7, target7)
    << " | (Expected Output: 2 from [4, 5])\n";

  return 0;
}
