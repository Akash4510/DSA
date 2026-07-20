#include <iostream>
#include <cmath>

using namespace std;

long long reverseNum(int n) {
  long long ans = 0;

  while (n) {
    ans *= 10;
    ans += n % 10;
    n /= 10;
  }

  return ans;
}

int main() {
  int n = 124763;
  long long reverseOfN = reverseNum(n);

  cout << endl << "The reverse of " << n << " is: " << reverseOfN << endl << endl;

  return 0;
}
