# 🧮 Number Theory & Math for DSA

## 🧠 Why Number Theory?

In DSA, problems often ask you to calculate massive numbers or count combinations that exceed standard memory limits. Number Theory provides the mathematical formulas to bypass $O(N)$ loops, prevent integer overflow, and compute answers in $O(\sqrt{N})$ or $O(\log N)$ time.

---

## 🔢 1. Primality Testing ($O(\sqrt{N})$)

You do not need to check all numbers from `1` to `N` to see if `N` is prime. Factors always come in pairs (e.g., for 36: $2 \times 18$, $3 \times 12$, $4 \times 9$, $6 \times 6$). The smallest factor in the pair will ALWAYS be $\le \sqrt{N}$.

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

- **The C++ Shortcut:** C++ has a built-in function `__gcd(a, b)` inside `<algorithm>`.
- **The Manual Formula (Euclidean Algorithm $O(\log(\min(A, B)))$):**

```cpp
// Recursive GCD
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Formula for LCM (Always divide first to prevent integer overflow!)
long long lcm(int a, int b) {
    return (a / gcd(a, b)) * 1LL * b;
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

---

## 🚀 5. Fast Exponentiation ($O(\log N)$)

Calculating $A^B \pmod M$ natively takes $O(B)$ time. If $B$ is 1 Billion, your program will crash (TLE).
**The Trick:** $A^{10} = (A^2)^5$. You can cut the exponent in half every step, calculating massive powers in ~30 CPU cycles.

```cpp
long long fastExponent(long long base, long long exp) {
    long long mod = 1e9 + 7;
    long long result = 1;

    // Safety check: shrink base
    base = base % mod;

    while (exp > 0) {
        // If exponent is odd, multiply result by current base
        if (exp % 2 != 0) {
            result = (result * base) % mod;
        }
        // Square the base, roll the snowball!
        base = (base * base) % mod;

        // Halve the exponent
        exp /= 2;
    }
    return result;
}
```

---

## 🧲 6. Modular Division & Fermat's Little Theorem

You **CANNOT** use the `/` symbol in modular arithmetic. `(A / B) % M` is completely illegal.
Instead, you must multiply by the **Modular Multiplicative Inverse**.

**Fermat's Theorem:** If $M$ is a prime number, the inverse of $B$ is $B^{M-2} \pmod M$.

- **The Code:** To calculate `(A / B) % M`, you use your Fast Exponentiation function!

```cpp
// (A / B) % M
long long inverse = fastExponent(B, mod - 2);
long long answer = (A % mod * inverse) % mod;
```
