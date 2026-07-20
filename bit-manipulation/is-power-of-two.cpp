#include <iostream>

using namespace std;

bool isPowerOfTwo(int n) {
  if (n <= 0) return false;
  return (n & (n - 1)) == 0;
}

int main() {
  int n = 16;
  cout << endl << n << (isPowerOfTwo(n) ? " is a" : " is not a") << " power of two" << endl;
  return 0;
}
