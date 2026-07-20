#include <iostream>
#include <vector>

using namespace std;

// The Challenge: Given an integer array nums, move all 0s to the end of it while maintaining the relative order of the non-zero elements. You must do this in-place without making a copy of the array.

void moveZeroes(vector<int>& nums) {
  int insertPos = 0; // This is our slow pointer (Anchor)

  // 'i' is our fast pointer scanning the array
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0) {
      // Swap the non-zero element to the correct position
      int temp = nums[insertPos];
      nums[insertPos] = nums[i];
      nums[i] = temp;

      // Move the anchor forward
      insertPos++;
    }
  }
}

int main() {
  vector<int> nums = { 0, 1, 0, 3, 12 };

  moveZeroes(nums);

  cout << "Array after moving zeroes: ";
  for (int num : nums) {
    cout << num << " ";
  }
  cout << "\n";

  return 0;
}
