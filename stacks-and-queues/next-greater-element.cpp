#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
  vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
    //! O(N^2) brute force approach with nested loops
    // vector<int> ans(nums1.size(), -1); // Pre-fill with -1

    // for (int i = 0; i < nums1.size(); i++) {
    //   bool found = false;
    //   for (int j = 0; j < nums2.size(); j++) {
    //     if (nums2[j] == nums1[i]) found = true; // We found the number!
    //     if (found && nums2[j] > nums1[i]) {     // Look for the next greater
    //       ans[i] = nums2[j];
    //       break;
    //     }
    //   }
    // }

    // return ans;

    //! O(N) Monotonic Stack + Hash Map approach
    vector<int> ans(nums1.size(), -1);

    stack<int> st;
    unordered_map<int, int> mp;

    for (int& n : nums2) {
      while (!st.empty() && n > st.top()) {
        mp[st.top()] = n;
        st.pop();
      }

      st.push(n);
    }

    for (int i = 0; i < nums1.size(); i++) {
      int n = nums1[i];
      if (mp.find(n) != mp.end()) {
        ans[i] = mp[n];
      }
    }

    return ans;
  }
};

// --- Helper function to print vectors cleanly ---
void printVector(const vector<int>& vec) {
  cout << "[";
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
  }
  cout << "]\n";
}

int main() {
  Solution sol;

  // Test Case 1 (The standard example)
  vector<int> nums1_1 = { 4, 1, 2 };
  vector<int> nums2_1 = { 1, 3, 4, 2 };
  cout << "Test Case 1:\n";
  cout << "Expected: [-1, 3, -1]\n";
  cout << "Output:   ";
  printVector(sol.nextGreaterElement(nums1_1, nums2_1));
  cout << "-----------------------\n";

  // Test Case 2 (Strictly increasing array)
  vector<int> nums1_2 = { 2, 4 };
  vector<int> nums2_2 = { 1, 2, 3, 4 };
  cout << "Test Case 2:\n";
  cout << "Expected: [3, -1]\n";
  cout << "Output:   ";
  printVector(sol.nextGreaterElement(nums1_2, nums2_2));
  cout << "-----------------------\n";

  return 0;
}
