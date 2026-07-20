# Time and Space Complexity: The Ultimate Interview Cheat Sheet

This cheat sheet covers the fundamental concepts of algorithmic analysis, from basic notation to advanced scaling behavior.

---

## 1. Asymptotic Notations: The Vocabulary of Scaling

These define how your algorithm performs as the input size $N$ approaches infinity.

- **Big O ($O$):** The **Upper Bound** (Worst Case). The maximum time an algorithm will take. _This is what interviewers care about._
- **Big Omega ($\Omega$):** The **Lower Bound** (Best Case). The minimum time an algorithm will take.
- **Big Theta ($\Theta$):** The **Tight Bound** (Average Case). The exact scaling behavior.

---

## 2. The Time Complexity Hierarchy

Ordered from fastest to slowest.

| Notation          | Name         | Meaning                                | Example                     |
| :---------------- | :----------- | :------------------------------------- | :-------------------------- |
| **$O(1)$**        | Constant     | Same time regardless of $N$.           | Accessing array index       |
| **$O(\log N)$**   | Logarithmic  | Search space halves/divides each step. | Binary Search               |
| **$O(N)$**        | Linear       | Time grows 1:1 with input.             | Single loop                 |
| **$O(N \log N)$** | Linearithmic | Logarithmic halving done $N$ times.    | Merge Sort / Quick Sort     |
| **$O(N^2)$**      | Quadratic    | Nested loops.                          | Bubble Sort / Pair checking |
| **$O(2^N)$**      | Exponential  | Operations double per input item.      | Brute-force subsets         |
| **$O(N!)$**       | Factorial    | Extremely high; avoids at all costs.   | Permutations                |

---

## 3. The Rules of Analysis

Follow these rules to calculate complexity without getting confused.

1.  **Drop Constants:** $O(2N)$ becomes $O(N)$. $O(1/2 \cdot N^2)$ becomes $O(N^2)$.
2.  **Keep Dominant Terms:** $O(N^2 + N)$ becomes $O(N^2)$ because $N^2$ dominates.
3.  **Use Independent Variables:** If you have two loops using different input arrays, use `O(A + B)` or `O(A * B)`, not `O(N)`.
4.  **Multiplication Rule:** If loops are **nested**, multiply the complexities. If they are **sequential**, add them.
5.  **Multiplication vs. Addition in loops:**
    - `i = i + 2`: Linear ($O(N)$).
    - `i = i * 2`: Logarithmic ($O(\log N)$).

---

## 4. Space Complexity: The "Auxiliary" Rule

Space Complexity measures the **extra memory** an algorithm needs (excluding the input itself).

- **Auxiliary Space:** Only count memory created _inside_ your function (variables, arrays, hash maps).
- **Recursive Trap:** Every recursive function call consumes $O(1)$ space on the **Call Stack**. If the function recurses $N$ times, the space complexity is $O(N)$.
- **In-Place:** If you modify the input without creating new data structures, your space is $O(1)$.

---

## 5. Advanced Examples & Math Tricks

### A. The Arithmetic Progression (Gauss Sum)

If an inner loop shrinks every iteration (e.g., `for i in 0..N: for j in 0..i`):

- Operations: $0 + 1 + 2 + ... + (N-1) = \frac{N(N-1)}{2}$
- Result: $O(N^2)$

### B. Square Root Complexity

If a loop condition is `i * i <= N`:

- The loop runs until $i = \sqrt{N}$.
- Result: $O(\sqrt{N})$

### C. Change of Base Formula

Proof that all Logarithms are the same in Big O:
$$\log_a N = \frac{\log_b N}{\log_b a}$$
Because $\frac{1}{\log_b a}$ is just a constant, it is dropped in Big O. Thus, $\log_2 N, \log_{10} N$, and $\log_e N$ are all simply $O(\log N)$.

---

## 6. Code Examples (C++)

### Example 1: The "Pair Maker" ($O(N^2)$ Time, $O(1)$ Space)

Demonstrates the Gauss Sum pattern. Inner loop runs $N-1, N-2, ...$ times.

```cpp
void pairMaker(vector<int>& arr) {
    int N = arr.size();
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << arr[i] << " " << arr[j] << endl;
        }
    }
}
```

### Example 2: The "Double Jetpack" ($O(\log^2 N)$ Time, $O(1)$ Space)

Both loops scale by multiplication. The outer runs $\log N$ times; for each, the inner runs $\log N$ times.

```cpp
void doubleJetpack(int N) {
    for (int i = 1; i < N; i *= 2) {
        for (int j = 1; j < N; j *= 2) {
            cout << i << " " << j << endl;
        }
    }
}
```

### Example 3: The "Square Root" ($O(\sqrt{N})$ Time, $O(1)$ Space)

The loop terminates when $i^2 > N$.

```cpp
void sqrtComplexity(int N) {
    for (int i = 1; i * i <= N; i++) {
        cout << i << endl;
    }
}
```

### Example 4: Invisible Memory ($O(N)$ Time, $O(N)$ Space)

Demonstrates the Recursive Trap. Each recursive call adds 1 frame to the call stack.

```cpp
void countdown(int N) {
    if (N <= 0) return; // Base case
    cout << N << endl;
    countdown(N - 1);
}
```

---

## 7. Interview "Gotchas"

- **Challenge:** `O(N + M^2)` is NOT `O(M^2)` if $N$ can be larger than $M^2$. Always report both independent variables!
- **Recursive Space:** Never forget that depth of recursion = space complexity.
- **Multiplication:** If a problem says "cut into 1/10th" or "cut in half," think Logarithmic. If it says "increment/decrement," think Linear.
