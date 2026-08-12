# 🧠 The Ultimate Recursion & Backtracking Cheat Sheet

## 1. The Core Mental Model: What is Recursion?

Recursion is an algorithmic engine where a function solves a problem by calling itself on a smaller subset of the same problem.

- **The Call Stack:** Every time a function calls itself, the CPU pauses the current function and stacks the new one on top. It follows **LIFO (Last-In, First-Out)** order. The answer isn't finalized until the stack collapses back down.
- **Dynamic Programming (DP) Pre-requisite:** Recursion is the foundation of DP. DP is simply recursion + a memory notepad (caching).

### The 3 Absolute Pillars of Recursion

1.  **The Base Case (The Anchor):** The condition where the function stops calling itself and returns a definitive answer. Without this -> **Stack Overflow**.
2.  **The Recursive Relation (The Leap of Faith):** The logic that breaks the problem down into a smaller piece (e.g., `n - 1`, `left + 1`, `right - 1`).
3.  **State Management:** What variables need to change as you move down the tree, and what variables need to be cleaned up as you move back up?

---

## 2. Pattern 1: Linear Recursion (Passing State Down / Answers Up)

**The Mental Model:** A straight line. The function calls itself exactly **once** per execution.

- **Passing State Down:** Carrying pointers or accumulators down the stack (e.g., Two Pointers `left` and `right`).
- **Building Answers Up:** Waiting for the base case to hit, then performing math/logic as the stack collapses (e.g., Factorial).

### 📝 Classic C++ Skeleton

```cpp
int linearRecursion(int n) {
    // 1. Base Case
    if (n <= 1) return 1;

    // 2. Recursive Leap (Building answer up)
    return n * linearRecursion(n - 1);
}
```

- **Time Complexity:** Generally $O(N)$
- **Space Complexity:** $O(N)$ due to the Call Stack.
- **When to use:** Simple mathematical sequences, Linked List traversals, simple array checks (like Valid Palindrome).

---

## 3. Pattern 2: Tree Branching (The "Pick or Don't Pick" Model)

**The Mental Model:** The straight line explodes into a Tree. The function calls itself **twice** (or more) per execution. The CPU follows **Depth-First Search (DFS)**, diving all the way down the left branch before exploring the right.

### The Subsequence / Subset Pattern

You look at exactly one element at a time (governed by an `index`).

- **Branch 1 (Include):** Add the element to your state, move to `index + 1`.
- **Branch 2 (Exclude):** Ignore the element, move to `index + 1`.

### 📝 Classic C++ Skeleton

```cpp
void generateSubsequences(int index, string current, const string& s, vector<string>& result) {
    // 1. Base Case: Reached the end of the string
    if (index >= s.size()) {
        result.push_back(current);
        return;
    }
    // 2. Timeline 1: INCLUDE the current character
    generateSubsequences(index + 1, current + s[index], s, result);

    // 3. Timeline 2: EXCLUDE the current character
    generateSubsequences(index + 1, current, s, result);
}
```

- **Time Complexity:** $O(2^n)$ because every element forces a split into two parallel realities.
- **When to use:** When the prompt asks for "All combinations", "All subsequences", or "Subsets".

---

## 4. Pattern 3: Backtracking (Constrained Branching & State Cleanup)

**The Mental Model:** Backtracking is Branching Recursion with a mop and bucket. Since you are passing a single shared data structure (like a `vector` passed by reference) through the parallel universes, you **must undo your choices** after a branch finishes so the next branch has a clean slate.

### The 3-Step Backtrack Loop

Inside a `for` loop, you:

1.  **Choose:** Add an item to the vector / Swap an element.
2.  **Explore:** Make the recursive leap.
3.  **Un-choose:** Pop the item off the vector / Swap it back.

### 📝 Classic C++ Skeleton (Permutations / Combinations)

```cpp
void backtrack(int index, vector<int>& currentComb, vector<int>& nums, vector<vector<int>>& result) {
    // 1. Base Case (e.g., target length reached)
    if (currentComb.size() == targetLength) {
        result.push_back(currentComb);
        return; // DO NOT clear currentComb here! Let pop_back handle it.
    }

    // 2. The Branching Loop
    for (int i = index; i < nums.size(); i++) {
        // Step A: Make a choice
        currentComb.push_back(nums[i]);

        // Step B: Recursive Leap
        // (Pass i + 1 if elements can't be reused. Pass i if they CAN be reused)
        backtrack(i + 1, currentComb, nums, result);

        // Step C: Undo the choice (The Backtrack)
        currentComb.pop_back();
    }
}
```

- **Time Complexity:** Can range from $O(2^n)$ to $O(N!)$ (for Permutations).
- **When to use:** Sudoku solvers, N-Queens, generating valid parentheses, combinations with unlimited reuse.

---

## 5. How to Recognize Which Pattern to Use

| Keyword in Problem Statement                     | The Pattern You Should Immediately Use                                       |
| :----------------------------------------------- | :--------------------------------------------------------------------------- |
| "Find **all** combinations/subsets/permutations" | Backtracking / Tree Branching                                                |
| "Return **all** possible valid..."               | Constrained Backtracking                                                     |
| "Can we partition this array into..."            | "Pick or Don't Pick" Subset logic                                            |
| "Check if a string/array is..."                  | Linear Recursion (or Iterative Two Pointers)                                 |
| Order matters (`[1,2]` != `[2,1]`)               | **Permutations:** Use a `for` loop from `0` to $N$, swap elements.           |
| Order does NOT matter (`[1,2]` == `[2,1]`)       | **Combinations:** Use `for` loop from `index` to $N$.                        |
| Elements can be reused infinitely                | **Unbounded Backtrack:** Recursive leap uses `index` instead of `index + 1`. |

---

## 6. Critical Edge Cases & "Gotchas" (The Interview Savers)

### 🚨 1. The Pass-by-Value Memory Trap

**The Error:** `void recurse(string s)` or `void recurse(vector<int> v)`
**Why it fails:** Passes the heavy object by value. Every recursive call copies the entire string/array. $O(2^n)$ time complexity turns into a Memory Limit Exceeded (MLE) crash.
**The Fix:** Always pass read-only state by constant reference: `const string& s` or `const vector<int>& nums`.

### 🚨 2. The "State Destroyer" Bug

**The Error:** Clearing an array inside the base case before returning: `currentComb.clear();` or `currentComb = {};`
**Why it fails:** You wipe out the state for the entire Call Stack. When the CPU steps back up to a previous branch, its data is completely gone.
**The Fix:** Simply `return;` inside the base case. Rely exclusively on `pop_back()` or manual swapping to clean up the state one level at a time.

### 🚨 3. The Index Out-of-Bounds Crash

**The Error:** `if (index > nums.size()) return;`
**Why it fails:** Arrays are 0-indexed. If `nums.size()` is 3, the valid indices are 0, 1, and 2. When index hits 3, `3 > 3` is false, so it tries to read `nums[3]` and causes a Segmentation Fault.
**The Fix:** Always use `>=` or `==`: `if (index >= nums.size()) return;`

### 🚨 4. The Early Return Trap (Missing Valid Paths)

**The Error:** Returning immediately when a sum hits a target in a Subset problem without checking the rest of the array.
**Why it fails:** If your array contains negative numbers or zeros (e.g., `[2, 3, 0]`, target = 5), stopping at `[2, 3]` means you completely miss the valid subset `[2, 3, 0]`.
**The Fix:** Let the `index` travel all the way to the end of the array, and _only_ evaluate success inside the boundary base case: `if (index >= nums.size()) { if (sum == target) ... }`.

### 🚨 5. Missing Pruning

**The Error:** Letting the recursion tree grow out of control when you already know the branch is invalid.
**The Fix:** Add failure base cases at the very top of your function. If finding a positive sum and `currentSum > target`, return immediately to kill that timeline.
