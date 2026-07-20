#include <iostream>
#include <cmath>

using namespace std;

int countDigits(int n) {
  if (n == 0) return 1;
  int ans = 0;
  while (n) {
    ans++;
    n /= 10;
  }
  return ans;
}

int countDigitsOptimal(int n) {
  if (n == 0) return 1;
  return static_cast<int>(log10(abs(n))) + 1; // abs() handles negatives too!
}

int main() {
  int n = 0;
  int digitsCount = countDigits(n);

  cout << endl << "The number of digits in " << n << " is: " << digitsCount << endl << endl;

  return 0;
}
