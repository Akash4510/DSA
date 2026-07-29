#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
  bool isSolution(vector<int>& piles, int h, int k) {
    long long currHours = 0; // Using long long to prevent integer overflow

    for (int i = 0; i < piles.size(); i++) {
      if (currHours > h) return false;

      // Performance trick -
      // Instead of:  currHours += (int) ceil((double)piles[i] / k);
      currHours += (piles[i] + k - 1) / k;

      // Why this works: If piles[i] is exactly divisible by k, adding k - 1 
      // isn't enough to push it over to the next multiple, so the integer division 
      // stays exactly where it should be. If there is a remainder, adding k - 1 
      // guarantees it rolls over to the next integer. It's a beautiful math trick!
    }

    return currHours <= h;
  }

public:
  int minEatingSpeed(vector<int>& piles, int h) {
    int ans = 0;
    int left = 1, right = *max_element(piles.begin(), piles.end()), mid;

    while (left <= right) {
      mid = left + (right - left) / 2;

      if (isSolution(piles, h, mid)) {
        ans = mid;
        right = mid - 1; // Try to find a slower (smaller) valid speed
      }
      else {
        left = mid + 1;  // Speed is too slow, we need to eat faster
      }
    }

    return ans;
  }
};

// Helper function to print vectors cleanly
void printVector(const vector<int>& v) {
  cout << "[";
  for (int i = 0; i < v.size(); i++) {
    cout << v[i] << (i == v.size() - 1 ? "" : ", ");
  }
  cout << "]";
}

// Helper function to run and format test cases
void runTestCase(int testNum, vector<int> piles, int h, int expected) {
  Solution sol;
  int result = sol.minEatingSpeed(piles, h);

  // Line 1: Test Case number and PASS/FAIL status
  cout << "Test Case " << testNum << ": ";
  if (result == expected) {
    cout << "[PASS]\n";
  }
  else {
    cout << "[FAIL]\n";
  }

  // Line 2: Input variables
  cout << "Input: piles = ";
  printVector(piles);
  cout << ", h = " << h << "\n";

  // Line 3: Expected Output
  cout << "Expected Output: " << expected << "\n";

  // Line 4: Actual Output
  cout << "Output: " << result << "\n\n"; // Double newline for the requested gap
}

int main() {
  cout << "--- Koko Eating Bananas (Binary Search on Answer) ---\n\n";

  // Test Case 1: Standard Example
  runTestCase(1, { 3, 6, 7, 11 }, 8, 4);

  // Test Case 2: Standard Example (h is exactly array size)
  runTestCase(2, { 30, 11, 23, 4, 20 }, 5, 30);

  // Test Case 3: Standard Example
  runTestCase(3, { 30, 11, 23, 4, 20 }, 6, 23);

  // Test Case 4: Minimum speed possible is 1
  runTestCase(4, { 1, 1, 1, 1 }, 10, 1);

  // Test Case 5: The Massive TLE Case
  // This tests if the integer overflow (long long) and math optimizations work.
  vector<int> massivePiles = {
      332484035, 524908576, 855865114, 632922376, 222257295,
      690155293, 112677673, 679580077, 337406589, 290818316,
      877337160, 901728858, 679284947, 688210097, 692137887,
      718203285, 629455728, 941802184
  };
  runTestCase(5, massivePiles, 823855818, 14);

  return 0;
}
