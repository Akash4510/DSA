#include <iostream>
#include <cmath>

using namespace std;

bool isArmstrongNumber(int n) {
  if (n < 0) return false;

  int originalNum = n;
  int numberOfDigits = n == 0 ? 1 : static_cast<int>(log10(abs(n))) + 1;

  int sum = 0;
  while (n > 0) {
    sum += pow(n % 10, numberOfDigits);
    n /= 10;
  }

  return originalNum == sum;
}

int main() {
  int n = 153;

  cout << endl << n << " is " << (isArmstrongNumber(n) ? "a" : "not a") << " armstrong number" << endl << endl;

  return 0;
}
