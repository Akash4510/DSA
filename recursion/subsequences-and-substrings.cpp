#include <iostream>
#include <vector>

using namespace std;

void getSubsequences(string str, string curr, int i, vector<string>& result) {
  if (i >= str.size()) {
    result.push_back(curr);
    return;
  }

  getSubsequences(str, curr + str[i], i + 1, result);
  getSubsequences(str, curr, i + 1, result);
}

vector<string> getSubstrings(string str) {
  vector<string> result;

  for (int left = 0; left < str.size(); left++) {
    for (int right = left; right < str.size(); right++) {
      result.push_back(str.substr(left, right - left + 1));
    }
  }

  return result;
}

void getSubstringsRecursive(string str, int left, int right, vector<string>& result) {
  // RULE 1: The Ultimate Base Case (Outer Loop Finished)
      // If 'left' goes out of bounds, we have checked every single starting letter.
  if (left >= str.size()) {
    return;
  }

  // RULE 2: The Reset (Inner Loop Finished)
  // If 'right' hits the end of the string, we are done with the current 'left'.
  // We increment left by 1, and snap right back to equal left. 
  if (right >= str.size()) {
    getSubstringsRecursive(str, left + 1, left + 1, result);
    return; // CRITICAL: We return here so we don't accidentally run Rule 3!
  }

  // RULE 3: The Expansion (Inside the Inner Loop)
  // 1. Slice the string and save it.
  result.push_back(str.substr(left, right - left + 1));

  // 2. Expand our window to the right by 1.
  getSubstringsRecursive(str, left, right + 1, result);
}

int main() {
  string str = "abcd";
  vector<string> ans;

  getSubsequences(str, "", 0, ans);

  cout << "\nTotal number of subsequences: " << ans.size() << "\n";
  cout << "[";
  for (int i = 0; i < ans.size(); i++) {
    cout << ans[i] << (i < ans.size() - 1 ? ", " : "");
  }
  cout << "]\n";

  vector<string> substrings = getSubstrings(str);

  cout << "\nTotal number of substrings: " << substrings.size() << "\n";
  cout << "[";
  for (int i = 0; i < substrings.size(); i++) {
    cout << substrings[i] << (i < substrings.size() - 1 ? ", " : "");
  }
  cout << "]\n";

  vector<string> recursiveSubstrings;
  getSubstringsRecursive(str, 0, 0, recursiveSubstrings);

  cout << "\nTotal number of substrings using recursive strategy: " << recursiveSubstrings.size() << "\n";
  cout << "[";
  for (int i = 0; i < recursiveSubstrings.size(); i++) {
    cout << recursiveSubstrings[i] << (i < recursiveSubstrings.size() - 1 ? ", " : "");
  }
  cout << "]\n";

  return 0;
}
