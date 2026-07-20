#include <iostream>

using namespace std;

int countSetBit(int n) {
  int ans = 0;

  while (n) {
    n = n & (n - 1);
    ans++;
  }

  return ans;
}

int main() {
  int n = 11;

  cout << endl << "The number of set bit is: " << countSetBit(n) << endl << endl;

  return 0;
}
