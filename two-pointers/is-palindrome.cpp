#include <iostream>
#include <string>

using namespace std;

// The Challenge:
// Given a string s, return true if it is a palindrome, or false otherwise.
// The Catch : You must ignore spaces, punctuation, and cases.
// Example : "A man, a plan, a canal: Panama" should return true.

bool isPalindrome(string s) {
  int left = 0;
  int right = s.size() - 1;

  while (left < right) {
    while (!isalnum(s[left]) && left < right) left++;
    while (!isalnum(s[right]) && right > left) right--;

    if (tolower(s[left++]) != tolower(s[right--])) {
      return false;
    }
  }

  return true;
}

int main() {
  string test1 = "racecar";
  string test2 = "hello";
  string test3 = "level";
  string test4 = "A man, a plan, a canal: Panama";
  string test5 = "ab_A";

  cout << "Is '" << test1 << "' a palindrome? " << (isPalindrome(test1) ? "Yes" : "No") << "\n";
  cout << "Is '" << test2 << "' a palindrome? " << (isPalindrome(test2) ? "Yes" : "No") << "\n";
  cout << "Is '" << test3 << "' a palindrome? " << (isPalindrome(test3) ? "Yes" : "No") << "\n";
  cout << "Is '" << test4 << "' a palindrome? " << (isPalindrome(test4) ? "Yes" : "No") << "\n";
  cout << "Is '" << test5 << "' a palindrome? " << (isPalindrome(test5) ? "Yes" : "No") << "\n";

  return 0;
}
