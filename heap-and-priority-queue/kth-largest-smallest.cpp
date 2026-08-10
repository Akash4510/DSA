#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

// ==========================================
// SCENARIO 1: Standard (Duplicates Counted)
// Example: [5, 5, 4, 3], K=2 -> Result: 5
// ==========================================
int findKthLargest(std::vector<int>& nums, int k) {
  std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
  for (int num : nums) {
    minHeap.push(num);
    if (minHeap.size() > k) minHeap.pop();
  }
  return minHeap.top();
}

int findKthSmallest(std::vector<int>& nums, int k) {
  std::priority_queue<int> maxHeap;
  for (int num : nums) {
    maxHeap.push(num);
    if (maxHeap.size() > k) maxHeap.pop();
  }
  return maxHeap.top();
}


// ==========================================
// SCENARIO 2: Distinct (Duplicates Ignored)
// Example: [5, 5, 4, 3], K=2 -> Result: 4
// ==========================================

/* * If the interviewer explicitly uses the keyword "DISTINCT",
 * we use a Hash Set to wipe out duplicates before building our Heap.
 */
int findKthDistinctLargest(std::vector<int>& nums, int k) {
  // 1. Wipe out all duplicates in O(N) time and O(N) space
  std::unordered_set<int> uniqueNums(nums.begin(), nums.end());

  // 2. If K is larger than our total unique numbers, it's impossible.
  if (uniqueNums.size() < k) return -1;

  // 3. Standard Min-Heap Logic on the cleaned data
  std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
  for (int num : uniqueNums) {
    minHeap.push(num);
    if (minHeap.size() > k) minHeap.pop();
  }

  return minHeap.top();
}

/* * The distinct variation for finding the K-th smallest element.
 */
int findKthDistinctSmallest(std::vector<int>& nums, int k) {
  // 1. Wipe out duplicates
  std::unordered_set<int> uniqueNums(nums.begin(), nums.end());

  // 2. Safety check
  if (uniqueNums.size() < k) return -1;

  // 3. Standard Max-Heap Logic on the cleaned data
  std::priority_queue<int> maxHeap;
  for (int num : uniqueNums) {
    maxHeap.push(num);
    if (maxHeap.size() > k) maxHeap.pop();
  }

  return maxHeap.top();
}


// ==========================================
// Main Function & Test Cases
// ==========================================
int main() {
  std::vector<int> nums = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };

  std::cout << "Target Array: [3, 2, 3, 1, 2, 4, 5, 5, 6]\n\n";

  // Test 1: Standard
  std::cout << "--- Standard Tests ---\n";
  std::cout << "2nd Largest (Standard): " << findKthLargest(nums, 2) << "\n";
  std::cout << "2nd Smallest (Standard): " << findKthSmallest(nums, 2) << "\n\n";

  // Test 2: Distinct
  std::cout << "--- Distinct Tests ---\n";
  std::cout << "2nd DISTINCT Largest: " << findKthDistinctLargest(nums, 2) << "\n";
  std::cout << "2nd DISTINCT Smallest: " << findKthDistinctSmallest(nums, 2) << "\n\n";

  return 0;
}
