# ➕ The Prefix Sum Pattern - Master Cheat Sheet

## 🧠 The Core Concept

The Prefix Sum pattern is a pre-calculation technique. Instead of repeatedly looping through an array to find the sum (or product) of a specific range, you do the heavy lifting exactly once in an $O(N)$ pass. You build an auxiliary array that stores the running total up to each index. Once built, finding the sum of _any_ contiguous subarray takes exactly $O(1)$ mathematical time.

---

## 🚦 Identifying the Signals (When to USE it)

Look for these specific clues in the problem description:

1. **Range Queries:** The problem asks you to calculate the sum, product, or XOR of elements between indices `i` and `j` multiple times.
2. **"Subarray Sum Equals K":** You need to find the number of contiguous subarrays that add up to a specific target, especially when the array contains **negative numbers**.
3. **Equilibrium/Balancing:** You are asked to find an index where the sum of elements on its left equals the sum of elements on its right (e.g., "Find Pivot Index").
4. **Excluding an Element:** You need an answer for an entire array _except_ the current element (e.g., "Product of Array Except Self").

## 🛑 When NOT to Use it

1. **Mutable Arrays:** If the problem involves frequently updating/changing individual elements in the array _between_ the queries, standard Prefix Sum becomes $O(N)$ per update. (You would need advanced structures like a Segment Tree or Fenwick Tree instead).
2. **Subsequences:** Just like Sliding Window, Prefix Sum only works for contiguous blocks of memory. If you are picking and choosing non-adjacent elements, it won't work.

---

## ⚙️ The 3 Main Variations & Templates

### Variation 1: Standard Range Query (The `N + 1` Trick)

**Setup:** Create a prefix array of size `N + 1` initialized to `0`. `prefix[i+1]` stores the sum of all elements up to `nums[i]`. This elegantly shifts the indices and prevents `out-of-bounds` crashes when querying from index 0.
**Common Uses:** Range Sum Query - Immutable, finding subset sums.

```cpp
// Template: N + 1 Prefix Sum Array
class PrefixSum {
private:
    vector<int> prefix;
public:
    PrefixSum(vector<int>& nums) {
        // Size is N + 1. prefix[0] stays 0.
        prefix.resize(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }

    int query(int left, int right) {
        // O(1) query. (right + 1) because of the shifted array!
        return prefix[right + 1] - prefix[left];
    }
};
```

### Variation 2: Prefix + Hash Map (The Negative Number Savior)

**Setup:** Sliding Window fails to find target sums when negative numbers exist. Instead, keep a running `prefixSum`. If `prefixSum - target` exists in a Hash Map, it means a valid subarray exists behind you!
**Common Uses:** Subarray Sum Equals K, Contiguous Array (Equal 0s and 1s).

```cpp
// Template: Prefix Sum + Hash Map (Subarray Sum Equals K)
int subarraySum(vector<int>& nums, int target) {
    unordered_map<int, int> prefixCounts;
    prefixCounts[0] = 1; // Base case: a sum of 0 happens 1 time initially

    int currentSum = 0;
    int count = 0;

    for (int num : nums) {
        currentSum += num;

        // If (currentSum - target) was seen before, we found valid subarrays!
        if (prefixCounts.count(currentSum - target)) {
            count += prefixCounts[currentSum - target];
        }

        // Add current sum to the map for future elements to use
        prefixCounts[currentSum]++;
    }
    return count;
}
```

### Variation 3: Prefix & Suffix Arrays (Bi-directional)

**Setup:** You build a running total from the left (Prefix) and a running total from the right (Suffix). Multiplying or adding them together gives you data surrounding an element without including the element itself.
**Common Uses:** Product of Array Except Self, Trapping Rain Water.

```cpp
// Template: In-Place Prefix & Suffix (Product of Array Except Self)
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> ans(n, 1);

    // 1. Build Prefix from Left to Right
    int leftProduct = 1;
    for (int i = 0; i < n; i++) {
        ans[i] = leftProduct;
        leftProduct *= nums[i];
    }

    // 2. Build Suffix from Right to Left, applying it directly
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        ans[i] *= rightProduct;
        rightProduct *= nums[i];
    }

    return ans;
}
```

---

## ⚠️ Tricky Situations & Interview "Gotchas"

1. **Integer Overflow (The Silent Killer):**
   When summing up large arrays of integers, the running total can quickly exceed the 32-bit `int` limit (`~2.14 billion`), causing a silent negative overflow.
   - ✅ **Fix:** Always consider using `vector<long long> prefix` or a `long long currentSum` if the problem constraints indicate large numbers.

2. **Forgetting the Base Case in Hash Map Variation:**
   When doing the Prefix + Hash Map variation, if the array is `[3, 4]` and target is `7`, `currentSum` at the end is `7`. We look for `7 - 7 = 0` in our map. If we didn't seed the map with `map[0] = 1`, we would miss this valid sub-array!
   - ✅ **Fix:** Always initialize your map with `prefixCounts[0] = 1;`

3. **The Index Match Trap:**
   When doing standard prefix sums matching the original array size (without the $N+1$ trick), querying the sum from index `i` to `j` is `prefix[j] - prefix[i - 1]`.
   - ❌ **BAD:** If `i = 0`, `prefix[0 - 1]` throws an Out Of Bounds Segfault!
   - ✅ **Fix:** You are forced to write `if (i == 0) return prefix[j];`. (This is exactly why the $N+1$ Template is vastly superior in production!).

## ⏱️ Complexity Expectations

- **Time Complexity:** \* **Build Phase:** **$O(N)$**. You only loop through the array once (or twice for suffix variations).
  - **Query Phase:** **$O(1)$**. Just a simple mathematical subtraction.
- **Space Complexity:** \* **$O(N)$** to store the auxiliary Prefix Array or Hash Map.
  - **$O(1)$** if the interviewer explicitly allows you to modify the input array in-place, or if you can build the prefix directly into the required output array (like in Product Except Self).
