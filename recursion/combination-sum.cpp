#include <iostream>
#include <vector>

using namespace std;

void combinationSum(int index, int currentSum, int target, vector<int>& candidates, vector<int>& currentComb, vector<vector<int>>& result) {
  // 1. Success Base Case: If currentSum matches target, save currentComb and return!
  if (currentSum == target) {
    result.push_back(currentComb);
    return;
  }

  // 2. Failure Base Cases: If currentSum > target OR index goes out of bounds, prune the branch!
  if (index >= candidates.size() || currentSum > target) return;

  // 3. Timeline 1: Pick & Stay
  // Step A: Add candidates[index] to your currentComb
  currentComb.push_back(candidates[index]);
  // Step B: Make the recursive leap (Keep the index the SAME!)
  combinationSum(index, currentSum + candidates[index], target, candidates, currentComb, result);
  // Step C: Backtrack (Pop the number back off currentComb so Timeline 2 has a clean slate)
  currentComb.pop_back();

  // 4. Timeline 2: Don't Pick & Go
  // Make the recursive leap to index + 1 (Do not add anything to currentComb)
  combinationSum(index + 1, currentSum, target, candidates, currentComb, result);
}

int main() {
  vector<int> candidates = { 2, 3, 6, 7 };
  int target = 7;
  vector<vector<int>> result;
  vector<int> currentComb;

  combinationSum(0, 0, target, candidates, currentComb, result);

  cout << "Total Combinations: " << result.size() << "\n\n";
  for (const auto& comb : result) {
    cout << "[";
    for (int i = 0; i < comb.size(); i++) {
      cout << comb[i] << (i < comb.size() - 1 ? ", " : "");
    }
    cout << "]\n";
  }

  return 0;
}
