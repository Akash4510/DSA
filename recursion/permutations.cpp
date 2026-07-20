#include <iostream>
#include <vector>

using namespace std;

void generateAllPermutationsInOrder(int index, vector<int>& curr, vector<int>& nums, vector<vector<int>>& result) {
  if (index >= nums.size()) {
    result.push_back(curr);
    return;
  }

  // Pick condition
  curr.push_back(nums[index]);
  generateAllPermutationsInOrder(index + 1, curr, nums, result);
  curr.pop_back();

  // Don't pick condition
  generateAllPermutationsInOrder(index + 1, curr, nums, result);
}

void generatePermutations(int index, vector<int>& nums, vector<vector<int>>& result) {
  // 1. The Base Case: When do you know you've locked in a complete permutation?
  // (Hint: Look at your index compared to the array size)
  if (index >= nums.size()) {
    result.push_back(nums);
    return;
  }

  // 2. The Branching Loop: 
  // For the current 'index', try swapping it with every element from 'index' to the end of the array.
  for (int i = index; i < nums.size(); i++) {
    // Step A: Make a choice (Swap the element at 'index' with the element at 'i')
    swap(nums[i], nums[index]);

    // Step B: The Recursive Leap of Faith (Move to the next index)
    generatePermutations(index + 1, nums, result);

    // Step C: The Backtrack (Undo the swap so you don't mess up the array for the next loop iteration!)
    swap(nums[i], nums[index]);
  }
}

int main() {
  vector<int> nums = { 3, 1, 2 };
  vector<int> curr;
  vector<vector<int>> result;

  generateAllPermutationsInOrder(0, curr, nums, result);
  // generatePermutations(0, nums, result);

  cout << "Total Permutations: " << result.size() << "\n\n";
  for (const auto& perm : result) {
    cout << "[";
    for (int i = 0; i < perm.size(); i++) {
      cout << perm[i] << (i < perm.size() - 1 ? ", " : "");
    }
    cout << "]\n";
  }

  return 0;
}
