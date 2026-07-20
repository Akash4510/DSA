#include <iostream>
#include <vector>
#include <algorithm> // For std::max

using namespace std;

int maxSumSubarray(const vector<int>& arr, int k) {
  // Edge case: If the array is smaller than the window size, return 0
  if (arr.size() < k) return 0;

  int maxSum = 0;
  int windowSum = 0;

  for (int i = 0; i < k; i++) {
    windowSum += arr[i];
  }

  maxSum = windowSum;

  for (int i = k; i < arr.size(); i++) {
    windowSum -= arr[i - k];
    windowSum += arr[i];

    maxSum = max(maxSum, windowSum);
  }

  return maxSum;
}

int main() {
  vector<int> arr1 = { 2, 1, 5, 1, 3, 2, 2 };
  int k1 = 3;

  vector<int> arr2 = { 1, 9, -1, -2, 7, 3, -1, 2 };
  int k2 = 4;

  cout << "Max sum of arr1 (k=" << k1 << "): " << maxSumSubarray(arr1, k1) << "\n";
  // Expected Output: 9 (from subarray [5, 1, 3])

  cout << "Max sum of arr2 (k=" << k2 << "): " << maxSumSubarray(arr2, k2) << "\n";
  // Expected Output: 13 (from subarray [9, -1, -2, 7])

  return 0;
}
