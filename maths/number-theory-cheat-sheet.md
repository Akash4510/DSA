# 🧮 Number Theory & Math for DSA

## 🧠 Why Number Theory?

In DSA, problems often ask you to calculate massive numbers or count combinations that exceed standard memory limits. Number Theory provides the mathematical formulas to bypass $O(N)$ loops, prevent integer overflow, and compute answers in $O(\sqrt{N})$ or $O(\log N)$ time.

---

## 🔢 1. Primality Testing ($O(\sqrt{N})$)

`Note:` if `X` = `M x N`, then both `M` and `N` are the factors of `X`.

Therefore, you do not need to check all numbers from `1` to `N` to see if `N` is prime. Factors always come in pairs. E.g., the factors of `36` are:
`1 x 36`, `2 x 18`, `3 x 12`, `4 x 9`, `6 x 6`,
`9 x 4`, `12 x 3`, `18 x 2`, `36 x 1`.

If you notice the factors in the second half of the pair, they are just the reverse of the first half (for e.g, `4 x 9` in the first half is basically `9 x 4` in the second half). Which means, we got all the factors of `N` by just checking up to $\sqrt{N}$, which in this case is `6` ($\sqrt{36}$ = `6`).

The smallest factor in the pair will ALWAYS be $\le \sqrt{N}$.

```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    // Loop only up to the square root of n
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

---

## 🪢 2. Sieve of Eratosthenes ($O(N \log(\log N))$)

When you need to find **ALL** prime numbers up to `N` quickly.
**The Trick:** Assume all numbers are prime. Start at 2, and "cross out" every multiple of 2. Move to the next uncrossed number (3), and cross out all its multiples. Repeat.

```cpp
vector<bool> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        // If p is not changed, then it is a prime
        if (isPrime[p] == true) {
            // Update all multiples of p starting from p^2
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }
    return isPrime;
}
```

---

## ➗ 3. GCD and LCM (Euclidean Algorithm)

**GCD (Greatest Common Divisor):** The largest number that divides both `a` and `b`.
**LCM (Least Common Multiple):** The smallest number that both `a` and `b` divide into.

**Euclidean Algorithm:** The GCD of two numbers `a` and `b` is the same as the GCD of `b` and `a % b`. This is because if `d` divides both `a` and `b`, it must also divide `a - bq` for any integer `q`. Therefore, we can reduce the problem size by replacing the larger number with its remainder when divided by the smaller number.

For example, to find `gcd(48, 18)`:

1. `gcd(48, 18)` → `gcd(18, 48 % 18)` → `gcd(18, 12)`
2. `gcd(18, 12)` → `gcd(12, 18 % 12)`
3. `gcd(12, 6)` → `gcd(6, 12 % 6)` → `gcd(6, 0)` → `6`

**The LCM Formula:** `lcm(a, b) = (a * b) / gcd(a, b)`
Simply, the product of two numbers is equal to the product of their GCD and LCM. `a * b = gcd(a, b) * lcm(a, b)`

- **The C++ Shortcut:** C++ has a built-in function `__gcd(a, b)` inside `<algorithm>`.
- **The Manual Formula (Euclidean Algorithm $O(\log(\min(A, B)))$):**

```cpp
// Recursive GCD, we can also implement it iteratively.
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Formula for LCM (Always divide first to prevent integer overflow!)
long long lcm(int a, int b) {
    return (a / gcd(a, b)) * 1LL * b;
}
```

We can also use the Euclidean Algorithm to find GCD using subtraction, but it is slower than the modulo method. The subtraction method is only useful when you are not allowed to use the modulo operator.:

```cpp
// Implementing GCD using subtraction method (in an iterative way).
// The same can be done recursively as well.
int gcdSubtraction(int a, int b) {
    while (a != b) {
        if (a > b) a -= b;
        else b -= a;
    }
    return a; // or return b; both are same
}
```

---

## 🛡️ 4. Modular Arithmetic ($10^9 + 7$)

When an answer is too large to fit in memory, problems ask for the answer modulo `10^9 + 7` (or `1e9 + 7`).

- **Why $10^9 + 7$?** It is a prime number, and it is perfectly sized so that adding two modded numbers fits in a 32-bit `int`, and multiplying two modded numbers fits in a 64-bit `long long`.

**The Golden Rules (Apply at EVERY step, not just the end):**
Let $M = 1e9 + 7$.

- **Addition:**
  `ans = ((A % M) + (B % M)) % M;`
- **Multiplication (Must cast to long long!):**
  `ans = ((A % M) * 1LL * (B % M)) % M;`
- **Subtraction (The C++ Negative Trap):**
  _C++ modulo can return negative numbers. You MUST add M before the final modulo._
  `ans = ((A % M) - (B % M) + M) % M;`
- **Division (Fermat's Little Theorem):**
  You **CANNOT** use the `/` symbol in modular arithmetic. `(A / B) % M` is completely illegal.
  Instead, you must multiply by the **Modular Multiplicative Inverse**.

  **Fermat's Theorem:** If $M$ is a prime number, the inverse of $B$ is $B^{M-2} \pmod M$.
  - **The Code:** To calculate `(A / B) % M`, you use your Fast Exponentiation function!

  ```cpp
  // (A / B) % M
  long long inverse = fastExponent(B, mod - 2);
  long long answer = (A % mod * inverse) % mod;
  ```

  The **fastExponent** function is explained in the next section.
  The **Modular Multiplicative Inverse** is also used in combinatorics to calculate $\frac{n!}{r!(n-r)!} \pmod M$.

---

## 🚀 5. Fast Exponentiation ($O(\log N)$)

Calculating $A^B$ natively takes $O(B)$ time. If $B$ is 1 Billion, your program will crash (TLE).
**The Trick:** $A^{10} = (A^2)^5$. You can cut the exponent in half every step, dropping the time complexity to $O(\log N)$.

### 1. Recursive Fast Exponentiation (Handling Negatives)

This is the standard recursive approach.
**The Trap:** If a problem asks for exact floating-point calculation with negative exponents, you must invert the base and make the exponent positive. However, the minimum 32-bit integer is `-2,147,483,648`. If you try to make `INT_MIN` positive, it causes an integer overflow! You **must** cast the exponent to a `long long` first.

```cpp
double fastExponent(double x, long long n) {
    if (n == 0) return 1.0;

    // If the exponent is negative, invert the base and make exponent positive.
    // We use long long 'n' because turning INT_MIN to positive overflows a 32-bit int!
    // Because x^(-n) = 1 / (x ^ n)
    if (n < 0) return fastExponent(1.0 / x, -n);

    double half = fastExponent(x, n / 2);

    if (n % 2 == 0) {
        return half * half;
    } else {
        return x * half * half;
    }
}
```

### 2. Binary Exponentiation (The Iterative Standard)

This uses the exact same mathematical logic as above, but drops the Space Complexity to $O(1)$ by using a `while` loop and Bitwise Operators instead of the Call Stack.
**The Trick:** Think in binary! $13$ is `1101` in binary, meaning $13 = 8 + 4 + 1$. Therefore, $x^{13} = x^8 \cdot x^4 \cdot x^1$. We continuously square the base, but only multiply it into our result when the current right-most bit is `1`.

```cpp
double fastExponentBinary(double x, int n) {
    long long exp = n; // Cast to long long to prevent INT_MIN overflow

    // Handle negative exponents
    if (exp < 0) {
        x = 1.0 / x;
        exp = -exp;
    }

    double result = 1.0;
    while (exp > 0) {
        // If the right-most bit is 1 (meaning the exponent is odd)
        if (exp & 1) result *= x;

        // Square the base, roll the snowball! (x^1 -> x^2 -> x^4 -> x^8)
        x *= x;

        // Shift bits right by 1 (same as exp = exp / 2)
        exp >>= 1;
    }
    return result;
}
```

### 3. Modular Fast Exponentiation ($10^9 + 7$)

In competitive programming, you are often asked to find $A^B \pmod M$. You cannot use `double` here. Everything must be calculated using integers (`long long`), and the modulo must be applied at **every single multiplication step** to prevent integer overflow.

```cpp
long long modularExponentiation(long long base, long long exp) {
    long long mod = 1e9 + 7;
    long long result = 1;

    // Safety check: shrink base immediately just in case it starts larger than mod
    base = base % mod;

    while (exp > 0) {
        // If exponent is odd, multiply result by current base and modulo immediately
        if (exp % 2 != 0) {
            result = (result * base) % mod;
        }

        // Square the base and modulo immediately!
        base = (base * base) % mod;

        // Halve the exponent
        exp /= 2;
    }
    return result;
}
```
