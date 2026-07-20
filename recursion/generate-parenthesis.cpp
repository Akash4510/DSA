#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generateParens(int openCount, int closeCount, int n, string current, vector<string>& result) {
  // 1. The Base Case: When do you know you have a complete, valid string?
  // (Hint: What will the total length of the string be, or what will the counts equal?)
  if (current.size() == n * 2) {
    result.push_back(current);
    return;
  }

  // 2. Timeline 1: The recursive leap to add '('
  // Apply the rule: Only if openCount < n
  if (openCount < n) {
    generateParens(openCount + 1, closeCount, n, current + "(", result);
  }

  // 3. Timeline 2: The recursive leap to add ')'
  // Apply the rule: Only if closeCount < openCount
  if (closeCount < openCount) {
    generateParens(openCount, closeCount + 1, n, current + ")", result);
  }
}

int main() {
  int n = 3;
  vector<string> result;

  // Start with 0 open, 0 close, and an empty string
  generateParens(0, 0, n, "", result);

  cout << "Total Combinations: " << result.size() << "\n\n";
  for (const string& s : result) {
    cout << s << "\n";
  }

  return 0;
}