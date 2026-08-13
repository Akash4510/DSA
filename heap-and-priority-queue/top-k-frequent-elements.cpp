#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

//! O(N) solution - (THIS DOESN'T USES HEAP, BUT INSTEAD IT USES BUCKET SORT)
// This solution takes advantages of the fact that the array indices are always sorted
// And the maximum frequency of an element can be N.
// So we basically create 2d array (array of frequency buckets),
// Where array[i] denotes the bucket of elements having frequency i
std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
  int n = nums.size();
  std::unordered_map<int, int> freqMap;

  // Step 1: Count the frequencies O(N)
  for (int num : nums) {
    freqMap[num]++;
  }

  // Step 2: Create buckets. Size is n+1 because max frequency is n.
  // The index is the frequency, the vector holds the numbers.
  std::vector<std::vector<int>> buckets(n + 1);
  for (auto it : freqMap) {
    int num = it.first;
    int freq = it.second;
    buckets[freq].push_back(num); // Place number in its frequency bucket
  }

  // Step 3: Traverse buckets from right to left (highest frequency to lowest) O(N)
  std::vector<int> result;
  for (int i = n; i >= 0; i--) {
    for (int num : buckets[i]) {
      result.push_back(num);
      if (result.size() == k) {
        return result; // We found our top K elements!
      }
    }
  }

  return result;
}

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
