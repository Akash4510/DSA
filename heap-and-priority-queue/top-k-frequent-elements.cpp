#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

// ==========================================
// Top K Frequent Elements (LeetCode 347)
// Optimal Solution: O(N log K) Time | O(N) Space
// ==========================================
std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
  // 1. O(N) Hash Map to count frequencies
  std::unordered_map<int, int> mp;
  for (int n : nums) {
    mp[n]++;
  }

  // 2. Create the Min-Heap of Pairs.
  // Stores pairs as: {frequency, number}
  std::priority_queue<std::pair<int, int>,
    std::vector<std::pair<int, int>>,
    std::greater<std::pair<int, int>>> minHeap;

  // 3. The Bouncer Method
  for (auto& it : mp) {
    // Push {frequency, number} into the club
    minHeap.push({ it.second, it.first });

    // If the club gets bigger than K, kick out the guy with the SMALLEST frequency
    if (minHeap.size() > k) {
      minHeap.pop();
    }
  }

  // 4. Extract the survivors (The K most frequent numbers)
  std::vector<int> ans;
  while (!minHeap.empty()) {
    ans.push_back(minHeap.top().second); // Grab the actual number, not the frequency
    minHeap.pop();
  }

  return ans;
}

// ==========================================
// Helper Function for Clean Console Output
// ==========================================
void printVector(const std::vector<int>& vec) {
  std::cout << "[";
  for (size_t i = 0; i < vec.size(); i++) {
    std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
  }
  std::cout << "]\n";
}

// ==========================================
// Main Function & Test Cases
// ==========================================
int main() {
  std::cout << "--- TOP K FREQUENT ELEMENTS TESTS ---\n\n";

  // Test Case 1: Standard Array (LeetCode Example 1)
  std::vector<int> nums1 = { 1, 1, 1, 2, 2, 3 };
  int k1 = 2;
  std::cout << "Test 1: Array [1, 1, 1, 2, 2, 3], K = 2\n";
  std::cout << "Expected: [2, 1] or [1, 2]\n";
  std::cout << "Result:   ";
  printVector(topKFrequent(nums1, k1));
  std::cout << "\n";

  // Test Case 2: Single Element (LeetCode Example 2)
  std::vector<int> nums2 = { 1 };
  int k2 = 1;
  std::cout << "Test 2: Array [1], K = 1\n";
  std::cout << "Expected: [1]\n";
  std::cout << "Result:   ";
  printVector(topKFrequent(nums2, k2));
  std::cout << "\n";

  // Test Case 3: All Unique Elements, K is the size of array
  std::vector<int> nums3 = { 7, 8, 9 };
  int k3 = 3;
  std::cout << "Test 3: Array [7, 8, 9], K = 3\n";
  std::cout << "Expected: [7, 8, 9] (in any order)\n";
  std::cout << "Result:   ";
  printVector(topKFrequent(nums3, k3));
  std::cout << "\n";

  return 0;
}
