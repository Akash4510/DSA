#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generateSubsequences(int index, string current, const string& s, vector<string>& result) {
  // 1. The Base Case: What happens when your index steps out of bounds of the string?
  if (index >= s.size()) {
    result.push_back(current);
    return;
  }

  // 2. Timeline 1: The recursive leap where you INCLUDE the current character
  generateSubsequences(index + 1, current + s[index], s, result);

  // 3. Timeline 2: The recursive leap where you EXCLUDE the current character
  generateSubsequences(index + 1, current, s, result);
}

int main() {
  string s = "abcdefghi";
  vector<string> result;

  // Start at index 0, with an empty growing string
  generateSubsequences(0, "", s, result);

  cout << "Total subsequences: " << result.size() << "\n\n";
  for (const string& sub : result) {
    cout << "[" << sub << "]\n";
  }

  return 0;
}
