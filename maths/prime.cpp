#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int n) {
  if (n <= 1) return false;

  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

bool isPrime2(int n) {
  if (n <= 1) return false;

  vector<bool> primes(n + 1, true);
  primes[0] = false;
  primes[1] = false;

  for (int i = 2; i * i <= n; i++) {
    if (!primes[i]) continue;

    for (int j = i * i; j <= n; j += i) {
      primes[j] = false;
    }
  }

  return primes[n];
}

int main() {
  int n = 3;

  cout << "\n" << n << " is ";
  if (isPrime(n)) {
    cout << "a";
  }
  else {
    cout << "not a";
  }
  cout << " prime number.\n\n";

  return 0;
}
