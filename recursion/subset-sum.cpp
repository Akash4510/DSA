#include <iostream>
#include <vector>

using namespace std;

bool hasSubsetSum(int index, int currentSum, int target, const vector<int>& nums) {
  // 1. Base Case 1: What is the immediate success condition? 
  // (If your currentSum matches the target, you can stop and return true!)
  if (currentSum == target) return true;

  // 2. Base Case 2: What is the failure condition? 
  // (If your index steps out of bounds, you've run out of numbers to check)
  if (index >= nums.size()) return false;

  // if the array doesn't have any negative integers then below is one more optimization -
  // if (currentSum > target) return;

  // 3. Timeline 1 (Pick): The recursive leap where you INCLUDE nums[index]
  bool pick = hasSubsetSum(index + 1, currentSum + nums[index], target, nums);

  // 4. Timeline 2 (Don't Pick): The recursive leap where you EXCLUDE nums[index]
  bool dontPick = hasSubsetSum(index + 1, currentSum, target, nums);

  // 5. The Return: How do you return true if EITHER timeline was successful?
  return pick || dontPick;
}

void getSubsetsWithSumK(int index, int currentSum, int target, vector<int>& currentCombination, const vector<int>& nums, vector<vector<int>>& result) {
  // OPTIMIZATION (Pruning): Only works if array has strictly positive integers
  // if (currentSum > target) return;

  // 1. The True Base Case: We ran out of numbers
  if (index >= nums.size()) {
    // Check if our final sum matches the target
    if (currentSum == target) {
      result.push_back(currentCombination);
    }

    return;
  }

  // if the array doesn't have any negative integers then below is one more optimization -
  // if (currentSum > target) return;

  currentCombination.push_back(nums[index]);
  getSubsetsWithSumK(index + 1, currentSum + nums[index], target, currentCombination, nums, result);
  currentCombination.pop_back();

  getSubsetsWithSumK(index + 1, currentSum, target, currentCombination, nums, result);
}

int main() {
  vector<int> nums = { 3, 34, 4, 12, 5, 2, -5 };
  int target = 7;

  vector<int> currComb;
  vector<vector<int>> result;

  // Start at index 0, with a current sum of 0
  if (hasSubsetSum(0, 0, target, nums)) {
    cout << "\nTrue! A subset exists that adds up to " << target << ".\n";
  }
  else {
    cout << "\nFalse. No such subset exists.\n";
  }

  getSubsetsWithSumK(0, 0, target, currComb, nums, result);

  cout << "\nTotal Combinations: " << result.size() << "\n\n";
  for (const auto& comb : result) {
    cout << "[";
    for (int i = 0; i < comb.size(); i++) {
      cout << comb[i] << (i < comb.size() - 1 ? ", " : "");
    }
    cout << "]\n";
  }

  return 0;
}
