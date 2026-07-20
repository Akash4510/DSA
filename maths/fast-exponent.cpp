#include <iostream>

using namespace std;

long long fastExponent(int n, int p) {
  if (p == 0) return 1;
  if (p == 1) return n;

  long long half = fastExponent(n, p / 2);

  if (p % 2 == 0) {
    return half * half;
  }
  else {
    return n * half * half;
  }
}

long long fastExponentRecursiveMod(long long n, int p) {
  long long mod = 1e9 + 7;

  if (p == 0) return 1;

  // Safety first: shrink base
  if (p == 1) return n % mod;

  long long half = fastExponentRecursiveMod(n, p / 2);

  // Safely square the half and instantly shrink it back down!
  long long halfSquared = (half * half) % mod;

  if (p % 2 == 0) {
    return halfSquared;
  }
  else {
    // Because halfSquared is safely small, multiplying by n won't overflow
    return (n % mod * halfSquared) % mod;
  }
}

long long fastExponentIterative(int n, int p) {
  long long result = 1;

  while (p > 0) {
    if (p % 2 != 0) {
      result *= n;
    }

    n *= n;
    p /= 2;
  }

  return result;
}

long long fastExponentIterativeMod(long long n, int p) {
  long long mod = 1e9 + 7;
  long long result = 1;

  // Safety first: If 'n' starts larger than mod, shrink it immediately
  n = n % mod;

  while (p > 0) {
    // 1. Modulo the Result Box
    if (p % 2 != 0) {
      result = (result * n) % mod;
    }

    // 2. Modulo the Snowball
    n = (n * n) % mod;
    p /= 2;
  }

  return result;
}

int main() {
  int n = 54;
  int p = 4;

  long long result = fastExponentIterative(n, p);

  cout << "\n(" << n << ")^" << p << " = " << result << endl << endl;

  return 0;
}
