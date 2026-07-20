#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPalindrome(const string& s, int left, int right) {
  if (left >= right) {
    return true;
  }

  while (left < right && !isalnum(s[left])) left++;
  while (right > left && !isalnum(s[right])) right--;

  if (tolower(s[left++]) != tolower(s[right--])) return false;
  return isPalindrome(s, left, right);
}

int main() {
  string test = "r ,./.ac e  car";

  string ans = isPalindrome(test, 0, test.size() - 1) ? "True" : "False";
  cout << ans << endl;

  return 0;
}
