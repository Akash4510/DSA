# 🗺️ The Two Pointers Pattern - Master Cheat Sheet

## 🧠 The Core Concept

The Two-Pointer pattern involves using two integer variables (or actual pointers) that represent indices in an iterable data structure (Array, String, Linked List). By traversing the data with two observers simultaneously, you can usually optimize a brute-force $O(N^2)$ nested loop down to an $O(N)$ single pass, keeping memory at a highly efficient $O(1)$.

---

## 🚦 Identifying the Signals (When to USE it)

Look for these specific clues in the problem description:

1. **Sorted Data:** The array is already sorted, or sorting it first makes logical sense. (e.g., "Find two numbers that add up to...")
2. **Contiguous Data:** You are working with Arrays or Strings.
3. **In-Place Manipulation:** The question asks you to reverse a string, remove duplicates, or partition an array _without_ allocating extra memory space.
4. **Comparing Two Lists:** You are given two separate arrays/strings to compare or merge.
5. **Linked Lists:** You need to find a cycle, the middle element, or the _k-th_ element from the end (specifically the Fast/Slow variation).

## 🛑 When NOT to Use it

1. **Unsorted Data (where order matters):** If the array is unsorted and the problem requires you to maintain the original indices (e.g., original "Two Sum" returning original indices requires a Hash Map, not Two Pointers).
2. **Finding ALL Combinations/Subsets:** Two pointers are for finding _optimal_ pairs/subarrays. If you need _every single_ combination, you need Backtracking/Recursion.
3. **Singly Linked Lists (Opposite Ends):** You cannot use the "Opposite Ends" pattern on a singly linked list because you cannot traverse backwards from the tail.

---

## ⚙️ The 3 Main Variations & Templates

### Variation 1: Opposite Ends (Meet in the Middle)

**Setup:** Pointers start at index `0` and `n-1`. They move towards each other based on logical conditions until they meet or cross.
**Common Uses:** Reversing arrays, checking palindromes, finding pairs in sorted arrays (Two Sum II), Container With Most Water.

```cpp
// Template: Opposite Ends (e.g., Valid Palindrome)
bool isPalindrome(string s) {
    int left = 0;
    int right = s.size() - 1;

    while (left < right) { // Use < instead of <= if comparing pairs
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
```

### Variation 2: Same Direction (Fast & Slow / Leapfrog)

**Setup:** Both pointers start at index `0` (or `slow=0, fast=1`). The `fast` pointer iterates through every element, while the `slow` pointer acts as an anchor, only moving when a specific condition is met.
**Common Uses:** Removing duplicates in-place, moving zeroes, detecting cycles in Linked Lists.

```cpp
// Template: Same Direction (e.g., Move Zeroes)
void moveZeroes(vector<int>& nums) {
    int slow = 0; // The Anchor (where the next valid element goes)

    // 'fast' is 'i', scanning the array
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            swap(nums[slow], nums[fast]);
            slow++;
        }
    }
}
```

### Variation 3: Two Arrays (Parallel Traversal)

**Setup:** Pointer A traverses Array 1, Pointer B traverses Array 2. You compare elements at both pointers to decide which one moves forward.
**Common Uses:** Merging sorted arrays, finding common elements (intersections), comparing strings.

```cpp
// Template: Two Arrays (e.g., Merge Sorted Arrays)
vector<int> mergeArrays(vector<int>& arr1, vector<int>& arr2) {
    vector<int> merged;
    int p1 = 0, p2 = 0;

    // Traverse while BOTH pointers are valid
    while (p1 < arr1.size() && p2 < arr2.size()) {
        if (arr1[p1] < arr2[p2]) {
            merged.push_back(arr1[p1++]);
        } else {
            merged.push_back(arr2[p2++]);
        }
    }

    // Handle Exhaustion (One array finished before the other)
    while (p1 < arr1.size()) merged.push_back(arr1[p1++]);
    while (p2 < arr2.size()) merged.push_back(arr2[p2++]);

    return merged;
}
```

---

## ⚠️ Tricky Situations & Interview "Gotchas"

1. **The Segfault Trap (Order of Operations):**
   When combining boundary checks with element checks, ALWAYS put the boundary check on the left side of the `&&`. C++ evaluates left-to-right.
   - ❌ **BAD:** `while (nums[left] == 0 && left < right)` -> If `left` goes out of bounds, `nums[left]` crashes the program _before_ checking the boundary.
   - ✅ **GOOD:** `while (left < right && nums[left] == 0)`

2. **The `<` vs `<=` Dilemma:**
   - Use `while (left < right)` when finding pairs or swapping. If `left == right`, you are pointing at the exact same element, and swapping a number with itself or pairing a number with itself is usually wrong.
   - Use `while (left <= right)` when checking every single element (like binary search, or specific partition algorithms where the middle element must be processed).

3. **Empty Arrays (Out of Bounds):**
   Always check if the array is empty before setting `right = arr.size() - 1`. If `arr.size()` is `0`, then `0 - 1` becomes `-1`. In C++, `size_t` is unsigned, so `-1` underflows into a massive positive number (e.g., `18446744073709551615`), causing an instant memory crash when accessed.
   - ✅ **Fix:** `if (arr.empty()) return;`

4. **Infinite Loops (Stuck Pointers):**
   If you are using nested `while` loops (e.g., moving `left` to skip spaces), ensure you are _actually incrementing_ the pointers inside the loop. If the condition is met but the pointer doesn't move, the CPU spins forever.

## ⏱️ Complexity Expectations

- **Time Complexity:** Always aim for **$O(N)$**. Both pointers only move forward (or inward), meaning every element is visited at most twice.
- **Space Complexity:** Always aim for **$O(1)$**. You are only creating 2 integer variables regardless of the array size.
