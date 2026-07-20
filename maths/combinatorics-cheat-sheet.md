# 🧮 Combinatorics & Counting for DSA

## 🧠 Why Combinatorics?

Combinatorics is essential for:

1. **Algorithm Analysis:** Calculating how many recursive calls an algorithm makes.
2. **Dynamic Programming:** Determining the number of unique paths or states in a grid.
3. **Probability & Cryptography:** Solving problems involving sub-groups, arrangements, and expected values.

---

## 🏗️ 1. The Core Building Blocks

### Permutations ($P$) - Order Matters

Used when the arrangement matters (e.g., passwords, race positions).

- **Formula:** $P(n, r) = \frac{n!}{(n-r)!}$
- **Example:** Arranging 3 people out of 10 in specific seats.

### Combinations ($C$) - Order Does NOT Matter

Used when you are selecting a subset (e.g., picking a team of 3 from 10).

- **Formula:** $C(n, r) = \binom{n}{r} = \frac{n!}{r!(n-r)!}$
- **The "Choose" Function:** You will often see this as `nCr`.

---

## 🤖 2. Grid Traversal Math

If you need to move from `(0,0)` to `(M,N)` using only `Right` and `Down` moves, the total number of moves is fixed at `(M + N)`.

To find the number of unique paths, you choose which of those total steps are `Down` moves (or `Right` moves).

- **Formula:** $\binom{M+N}{M}$

```cpp
// Calculating nCr efficiently (prevents overflow by dividing early)
long long nCr(int n, int r) {
    if (r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (r > n / 2) r = n - r; // Symmetry property

    long long res = 1;
    for (int i = 1; i <= r; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}
```

---

## 🐦 3. The Pigeonhole Principle

**Rule:** If you have $N$ boxes and $N+1$ items, at least one box must contain more than one item.

- **DSA Application:** If you are given an array of size $N$ with elements ranging from $1$ to $N-1$, it is mathematically guaranteed (via Pigeonhole) that there must be at least one duplicate.

---

## 🧱 4. Catalan Numbers

Used for counting structures like:

- Valid parentheses combinations.
- Binary Search Trees (BSTs) with $N$ nodes.
- Polygon triangulations.

- **Formula:** $C_n = \frac{1}{n+1} \binom{2n}{n}$
- **Sequence:** $1, 1, 2, 5, 14, 42, 132, 429, \dots$

---

## ⚡ 5. Important Implementation Tricks

### Preventing Integer Overflow in Combinatorics

When calculating $\frac{n!}{r!(n-r)!}$, **never** calculate the factorial first. It will overflow instantly.
**The Trick:** Multiply and divide iteratively inside the loop.

```cpp
// Efficient iteration for nCr
long long nCr_Modulo(int n, int r, int mod) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;

    // Use modular inverse for division if a modulo is required
    // Otherwise, use: res = res * (n - i + 1) / i;
}
```

### Pascal's Triangle (For $nCr$ Precomputation)

If you need to calculate many combinations quickly in a DP problem, precompute them using Pascal's Triangle in $O(N^2)$.

```cpp
// Pascal's Triangle: C[n][r] = C[n-1][r-1] + C[n-1][r]
long long C[N][N];
for (int i = 0; i < N; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= i; j++) {
        C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
    }
}
```
