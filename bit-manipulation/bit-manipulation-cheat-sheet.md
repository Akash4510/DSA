# 💻 Bit Manipulation: The Language of the CPU

## 🧠 Why Bit Manipulation?

When you write standard math like `a + b` or `a % 2`, the CPU has to decode those instructions into microcode. Bitwise operators bypass this completely. They are wired directly into the physical logic gates of the CPU's Arithmetic Logic Unit (ALU).
**A bitwise operation executes in exactly one CPU clock cycle.** It is the absolute fastest thing a computer can physically do.

---

## 🔤 1. The Core Operators (The Alphabet)

### AND (`&`)

Returns `1` only if **BOTH** bits are `1`.

- **Usage:** Masking, extracting specific bits, checking if a number is odd/even.
- **Example:** `5 & 3` (`0101 & 0011` = `0001` = `1`)

### OR (`|`)

Returns `1` if **EITHER** bit is `1`.

- **Usage:** Setting specific bits to `1`, combining flags.
- **Example:** `5 | 3` (`0101 | 0011` = `0111` = `7`)

### XOR (`^`) - _The Magic Operator_

Returns `1` if bits are **DIFFERENT**. Returns `0` if they are the SAME.

- **The Golden Rules of XOR:**
  1. `A ^ A = 0` (Any number XOR'd with itself destroys itself).
  2. `A ^ 0 = A` (Any number XOR'd with zero remains unchanged).
  3. Order doesn't matter: `A ^ B ^ C = C ^ A ^ B`.
- **Usage:** Finding missing numbers, finding single/lone elements in arrays.

### NOT (`~`)

Flips every `1` to `0`, and every `0` to `1`.

- **Note:** In C++, numbers are stored in **Two's Complement** form. Therefore, `~x` is mathematically equivalent to `-(x + 1)`.
- **Example:** `~5 = -6`.

### Left Shift (`<<`)

Shifts bits to the left, padding the right with `0`.

- **The Math:** Left shifting by `k` is the same as **Multiplying by $2^k$**.
- `N << 1` $\rightarrow N \times 2$
- `N << 2` $\rightarrow N \times 4$

### Right Shift (`>>`)

Shifts bits to the right, dropping the rightmost bit.

- **The Math:** Right shifting by `k` is the same as **Integer Division by $2^k$**.
- `N >> 1` $\rightarrow \lfloor N / 2 \rfloor$

---

## 🎯 2. The $O(1)$ Bitwise Cheat Sheet (Math Replacements)

Replace standard, slow math operations with these instant 1-clock-cycle bitwise equivalents:

| Goal                 | Standard Code (Slow)  | Bitwise Code (Fast $O(1)$) | Explanation                                |
| :------------------- | :-------------------- | :------------------------- | :----------------------------------------- |
| **Check Even / Odd** | `if (n % 2 == 0)`     | `if (!(n & 1))`            | The 0th bit of all even numbers is `0`.    |
| **Multiply by 2**    | `n = n * 2`           | `n = n << 1`               | Shifts everything left one place.          |
| **Divide by 2**      | `n = n / 2`           | `n = n >> 1`               | Shifts everything right one place.         |
| **Power of 2 Check** | `while` loop dividing | `if ((n & (n - 1)) == 0)`  | Powers of 2 only have exactly one `1` bit. |

---

## 🛠️ 3. Manipulating the $i$-th Bit (Zero-Indexed)

In many advanced problems, you will need to check or change a single specific bit at index `i`.
_(Note: `i` is counted from right to left, starting at 0)._

**The "Mask":** To target the $i$-th bit, we create a mask by taking the number `1` and left-shifting it `i` times: `(1 << i)`.

**1. Check if the $i$-th bit is SET (1):**

```cpp
bool isSet = (n & (1 << i)) != 0;
```

**2. SET the $i$-th bit to 1:**

```cpp
n = n | (1 << i);
```

**3. CLEAR the $i$-th bit to 0:**

```cpp
n = n & ~(1 << i);
```

_(Explanation: `~(1 << i)` creates a mask where EVERY bit is 1, except for the $i$-th bit which is 0. ANDing this with `n` leaves all other bits alone but forces the $i$-th bit to 0)._

**4. TOGGLE the $i$-th bit (Flip 0 to 1, or 1 to 0):**

```cpp
n = n ^ (1 << i);
```

---

## 🧙‍♂️ 4. Advanced Bit Magic Algorithms

### Brian Kernighan’s Algorithm (Drop the lowest set bit)

This mathematically instantly drops the rightmost `1` bit from a number.

```cpp
n = n & (n - 1);
```

- **Use Case:** Counting the number of `1` bits in $O(K)$ time (where $K$ is the number of set bits, rather than 32 loops).

### Isolate the Lowest Set Bit

This destroys all bits EXCEPT the right-most `1` bit.

```cpp
int lowestBit = n & -n;
```

- **Why it works:** Because of Two's Complement, `-n` is equal to `~n + 1`. This trick is the foundation of the advanced **Fenwick Tree / Binary Indexed Tree** data structure.

### Swap Two Numbers without a Temp Variable

```cpp
a ^= b;
b ^= a;
a ^= b;
```

---

## 📦 5. C++ Built-In Hardware Functions (GCC/Clang)

C++ has built-in functions that compile directly down to hardware-level CPU instructions for massive speed boosts.

- `__builtin_popcount(n)`: Returns the number of `1` bits in an `int`.
- `__builtin_popcountll(n)`: Returns the number of `1` bits in a `long long`.
- `__builtin_clz(n)`: Returns the number of **C**ount **L**eading **Z**eros.
- `__builtin_ctz(n)`: Returns the number of **C**ount **T**railing **Z**eros.

---

## 🧩 6. Bitmasking (Combinatorics & Subsets)

Bit manipulation isn't just for math; it is the ultimate way to represent **Combinations** and sets.
Since an integer in C++ has 32 bits, we can use an integer to represent a "Set" of 32 items.

- A `0` bit means the item is NOT in the subset.
- A `1` bit means the item IS in the subset.

**Generate all possible Subsets (Power Set) of an array of size $N$:**
Since there are $2^N$ possible subsets, we can loop from $0$ to $2^N - 1$. The binary representation of each number acts as a perfect blueprint for a subset!

```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    int totalSubsets = 1 << n; // 2^n
    vector<vector<int>> result;

    for (int mask = 0; mask < totalSubsets; mask++) {
        vector<int> currentSubset;
        for (int i = 0; i < n; i++) {
            // If the i-th bit of the mask is set, include nums[i]
            if (mask & (1 << i)) {
                currentSubset.push_back(nums[i]);
            }
        }
        result.push_back(currentSubset);
    }
    return result;
}
```

_This completely removes the need for complex backtracking recursion to find subsets!_
