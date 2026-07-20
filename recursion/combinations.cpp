#include <iostream>
#include <vector>

using namespace std;

void getCombinations(int n, int k, int curr, vector<int>& currComb, vector<vector<int>>& result) {
  if (currComb.size() == k) {
    result.push_back(currComb);
    return;
  }

  if (curr > n) return;

  for (int i = curr; i <= n; i++) {
    currComb.push_back(i);
    getCombinations(n, k, i + 1, currComb, result);
    currComb.pop_back();
  }
}

int main() {
  int n = 5;
  int k = 3;

  vector<vector<int>> result;
  vector<int> currentComb;

  getCombinations(n, k, 1, currentComb, result);

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
