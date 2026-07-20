# 🪟 The Sliding Window Pattern - Master Cheat Sheet

## 🧠 The Core Concept

The Sliding Window pattern is a specialized variation of the "Same Direction" Two-Pointer technique. Instead of evaluating individual elements, you evaluate a **contiguous block (window)** of elements. As the window "slides" forward, you optimize the math: instead of recalculating the entire block from scratch ($O(N \times K)$ time), you simply **subtract the element falling out of the left side**, and **add the new element entering the right side**, dropping the time complexity to a highly efficient $O(N)$.

---

## 🚦 Identifying the Signals (When to USE it)

Look for these specific combinations of keywords in the problem description:

1. **The Structure:** The problem explicitly asks for a **"contiguous subarray," "substring,"** or **"consecutive elements."**
2. **The Metric:** You need to find the **"Maximum," "Minimum," "Longest," "Shortest,"** or **"Target Sum"** of that contiguous block.
3. **Data Type:** You are iterating over Arrays, Strings, or Linked Lists.

## 🛑 When NOT to Use it

1. **Subsequences:** If the problem asks for a "subsequence" (elements do NOT need to be contiguous or next to each other), Sliding Window is useless. You usually need Dynamic Programming or Backtracking.
2. **Dynamic Windows with Negative Numbers:** If the problem asks for the shortest subarray with a target sum, but the array contains **negative numbers**, the dynamic Sliding Window breaks. (Expanding the window rightward usually increases the sum, but a negative number shrinks it, destroying the strict "expand-and-shrink" logic). You will need a **Prefix Sum + Hash Map** instead.

---

## ⚙️ The 2 Main Variations & Templates

### Variation 1: Fixed Sliding Window

**Setup:** The size of the window (`k`) is explicitly given. Both pointers move forward at the exact same time, maintaining a constant distance.
**Common Uses:** Maximum sum of a subarray of size `k`, finding averages of subarrays, Permutation in String.

```cpp
// Template: Fixed Sliding Window
int fixedSlidingWindow(const vector<int>& arr, int k) {
    if (arr.size() < k) return 0; // Edge case

    int windowSum = 0, maxSum = 0;

    // 1. Initialize the very first window
    for (int i = 0; i < k; i++) {
        windowSum += arr[i];
    }
    maxSum = windowSum;

    // 2. Slide the window across the rest of the array
    for (int i = k; i < arr.size(); i++) {
        // Add the new element entering the window (i)
        windowSum += arr[i];

        // Subtract the old element falling out (i - k)
        windowSum -= arr[i - k];

        // Update the metric
        maxSum = max(maxSum, windowSum);
    }

    return maxSum;
}
```

### Variation 2: Dynamic Sliding Window (The Caterpillar)

**Setup:** The window size changes. The `right` pointer (head) expands the window until a condition is met. Once met, the `left` pointer (tail) drags forward to shrink the window until the condition breaks.
**Common Uses:** Longest substring without repeating characters, shortest subarray with sum $\ge$ target, max consecutive ones.

```cpp
// Template: Dynamic Sliding Window (Shrinkable)
int dynamicSlidingWindow(const vector<int>& arr, int target) {
    int minLength = INT_MAX;
    int windowSum = 0;
    int left = 0; // The Tail

    // 'right' is the Head expanding the window
    for (int right = 0; right < arr.size(); right++) {
        windowSum += arr[right]; // Add new element

        // WHILE the condition is valid, shrink the window from the left
        while (windowSum >= target) {
            // Update metric (add +1 because indices are inclusive!)
            minLength = min(minLength, right - left + 1);

            // Subtract the left element and shrink
            windowSum -= arr[left];
            left++;
        }
    }

    return minLength == INT_MAX ? 0 : minLength;
}
```

---

## ⚠️ Tricky Situations & Interview "Gotchas"

1. **The "Off-By-One" Length Bug:**
   When calculating the length of your current window using indices, remember that indices are inclusive.
   - ❌ **BAD:** `length = right - left;` (If left is 0 and right is 1, length is 1, but there are actually 2 elements!)
   - ✅ **GOOD:** `length = right - left + 1;`

2. **The `if` vs `while` Trap (Dynamic Window):**
   When shrinking a dynamic window, beginners often use an `if (condition)` statement. This is a fatal flaw because a single element entering the right side might require the left side to shrink _multiple times_ to become valid again.
   - ❌ **BAD:** `if (windowSum >= target) { shrink(); }`
   - ✅ **GOOD:** `while (windowSum >= target) { shrink(); }`

3. **Fixed Window Index Math (`i` vs `i - k`):**
   When sliding a fixed window in your second loop (starting at `i = k`), getting the indices wrong will cause a Segfault.
   - **The new element entering:** is exactly at index `i`.
   - **The old element leaving:** is exactly at index `i - k`. (Do not use `i - 1`, that subtracts an element still inside your window!)

4. **Character Frequency Windows (Strings):**
   When doing Sliding Windows on strings (like "Longest Substring Without Repeating Characters"), you almost always combine the window with an Auxiliary Data Structure—specifically a Frequency Array `vector<int> freq(26, 0)` or a `std::unordered_map<char, int>`. The map tracks what is currently _inside_ the window.

## ⏱️ Complexity Expectations

- **Time Complexity:** **$O(N)$**. Even in the dynamic version with a nested `while` loop, the `left` pointer and `right` pointer only ever move forward. Every element is processed at most twice (once entering, once leaving). It is strictly linear.
- **Space Complexity:** **$O(1)$** if you only use integer variables for sums/lengths. If you use a Hash Map or Frequency Array for characters, it is technically **$O(K)$** where K is the alphabet size (e.g., $O(26)$ which simplifies to $O(1)$).
