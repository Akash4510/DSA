#include <iostream>
#include <vector>

using namespace std;

class RangeQuery {
private:
  vector<int> prefix;

public:
  // Step 1: Build the Prefix Sum Array
  RangeQuery(const vector<int>& nums) {
    // TODO: Initialize the 'prefix' array.
    // Hint: If you make prefix size nums.size() + 1, you can set prefix[0] = 0.
    // Then prefix[1] stores nums[0], prefix[2] stores nums[0]+nums[1], etc.

    // resize() actively creates the elements and initializes them to 0
    prefix.resize(nums.size() + 1, 0);
    prefix[0] = 0;

    for (int i = 0; i < nums.size(); i++) {
      prefix[i + 1] = prefix[i] + nums[i];
    }
  }

  // Step 2: Query the Sum in O(1) Time
  int query(int left, int right) {
    // TODO: Calculate the sum of elements from nums[left] to nums[right].
    // Remember to adjust your indices if you used the n + 1 trick!
    return prefix[right + 1] - prefix[left];
  }
};

int main() {
  vector<int> nums = { 3, 1, 4, 1, 5, 9, 2, 6 };

  // This calls your constructor ONCE
  RangeQuery rq(nums);

  // These should all return instantly
  cout << "Sum of index 0 to 2: " << rq.query(0, 2) << " | (Expected: 8 from 3+1+4)\n";
  cout << "Sum of index 2 to 5: " << rq.query(2, 5) << " | (Expected: 19 from 4+1+5+9)\n";
  cout << "Sum of index 0 to 7: " << rq.query(0, 7) << " | (Expected: 31)\n";
  cout << "Sum of index 4 to 4: " << rq.query(4, 4) << " | (Expected: 5)\n";

  return 0;
}
