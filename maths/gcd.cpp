#include <iostream>

using namespace std;

int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}

int gcdIterative(int a, int b) {
  while (b > 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}

long long lcm(int a, int b) {
  if (a == 0 || b == 0) return 0;
  return (static_cast<long long>(a) / gcdIterative(a, b)) * b;
}

int main() {
  int a = 48;
  int b = 18;

  cout << "\nThe GCD of " << a << " and " << b << " is: " << gcdIterative(a, b) << endl << endl;

  return 0;
}
