#include <iostream>

using namespace std;

int fibonacci(int n) {
  // 1. The Base Case(s): What happens when n reaches the bottom of the sequence (0 or 1)?
  if (n < 0) return 0;
  if (n == 0 || n == 1) return n;

  // 2. The Recursive Relation (Branching Leap): How do you calculate 'n' using the two previous positions?
  return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  int n = 7;

  // The sequence:
  // Pos: 0  1  2  3  4  5  6
  // Val: 0  1  1  2  3  5  8

  cout << "The Fibonacci number at position " << n << " is: " << fibonacci(n) << "\n";

  return 0;
}
