# 📚 Heaps & Priority Queues Cheat Sheet

## 1. What is a Heap?

A **Heap** is the underlying engine that powers a **Priority Queue**.
Structurally, it is a Binary Tree that forces data to obey two unbreakable rules, allowing us to find the Maximum or Minimum element in **$O(1)$** time, while keeping insertions and deletions blazing fast at **$O(\log N)$**.

_Note: The Heap Data Structure has absolutely nothing to do with "Heap Memory" (RAM allocation). They just share a name._

---

## 2. The Two Golden Rules

To be a valid heap, the data structure MUST satisfy both of these rules simultaneously:

### Rule 1: The Shape Rule (Complete Tree)

A Heap must be a **Complete Binary Tree**.

- Every level of the tree must be completely filled before starting a new level.
- The bottom level must be filled strictly from **left to right**. No gaps allowed.

### Rule 2: The Order Rule (The Heap Property)

A Heap only cares about **Top vs. Bottom** (Parents vs. Children). It does _not_ care about Left vs. Right.

- **Max-Heap:** Every parent node must be $\ge$ both of its children. (The absolute largest element sits at the root).
- **Min-Heap:** Every parent node must be $\le$ both of its children. (The absolute smallest element sits at the root).

---

## 3. The Mathematical Architecture (No Pointers!)

Because of the strict "Complete Tree" Shape Rule, we do not need `left` and `right` pointers. We can map the entire tree into a flat, contiguous **Array** (or `std::vector`) using pure math.

If you are standing at index `i` in the array:

- **Left Child:** `(2 * i) + 1`
- **Right Child:** `(2 * i) + 2`
- **Parent:** `(i - 1) / 2` _(Rounded down via integer division)_

---

## 4. The Core Operations

### Insertion: "Push to Back & Bubble Up"

- **Time Complexity:** $O(\log N)$

1. Place the new element at the very end of the array (satisfies the Shape Rule).
2. Look at its parent using `(i - 1) / 2`.
3. If it violates the Order Rule (e.g., a child in a Min-Heap is smaller than its parent), swap them!
4. Continue "Bubbling Up" until the rule is satisfied or you hit the root (`index 0`).

### Deletion (Pop): "Swap, Chop, & Bubble Down"

- **Time Complexity:** $O(\log N)$
- _Note: Standard Heaps only allow you to remove the Root element._

1. **Swap:** Take the very last element in the array and overwrite the Root with it.
2. **Chop:** Remove the last element from the array (`pop_back()`).
3. **Bubble Down:** The new root is likely violating the Order Rule. Look at both of its children.
4. Swap the parent with the **most extreme** child (the smaller child for a Min-Heap, the larger child for a Max-Heap).
5. Repeat until the rule is satisfied.

---

## 5. Floyd's Heapify Algorithm ($O(N)$ Construction)

If you are given an unsorted array and need to turn it into a Heap, calling `.push()` on every element takes $O(N \log N)$ time. We can optimize this to **$O(N)$** using Floyd's Bottom-Up approach.

**The Logic:**

- The bottom half of any Complete Binary Tree consists entirely of leaf nodes.
- A single leaf node with no children is already mathematically a valid Heap.
- Therefore, we skip the entire bottom half of the array!
- We start at the **last non-leaf node** and work backward to index `0`, calling `Bubble Down` on each node.

**The Formula:**

- Start Index = `(size / 2) - 1`

```cpp
// O(N) Array Constructor
Heap(const std::vector<int>& inputArr) {
    arr = inputArr;
    // Start from the last non-leaf node and sink everything down
    for (int i = (size() / 2) - 1; i >= 0; i--) {
        heapDown(i);
    }
}
```

---

## 6. The C++ STL: `std::priority_queue`

When writing algorithms, rely on the highly optimized STL adapter.

**Max-Heap (The Default):**

```cpp
#include <queue>
std::priority_queue<int> maxHeap;
maxHeap.push(10);
maxHeap.pop();
int top = maxHeap.top();
```

**Min-Heap (The Ugly Syntax):**
Requires explicitly defining the container and the comparator.

```cpp
#include <queue>
#include <vector>
std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
```

**Custom Pairs (For Frequencies / Coordinates):**
By default, `std::priority_queue` sorts pairs based on the `.first` element. If tied, it looks at the `.second`.

```cpp
// Min-Heap holding Pairs
std::priority_queue<std::pair<int, int>,
                    std::vector<std::pair<int, int>>,
                    std::greater<std::pair<int, int>>> minHeap;

// Always push as {priority_value, actual_data}
minHeap.push({frequency, num});
```

---

## 7. When to Use a Priority Queue (The Interview Triggers)

A Priority Queue is terrible for searching and terrible for keeping things in arrival order. It is the undisputed king of **Dynamic Sorting**. Use it when:

1. **"Top K" or "K-th" Problems:** \* "Find the K-th largest element", "Top K most frequent words".
   - **THE SECRET TRICK:** \* To find the **$K$-th Largest**, use a **Min-Heap** of size $K$. (The Bouncer kicks out the smallest elements, leaving only the $K$ largest inside).
     - To find the **$K$-th Smallest**, use a **Max-Heap** of size $K$.
     - Complexity drops from $O(N \log N)$ sorting to **$O(N \log K)$**.
2. **Streaming Data:**
   - "Find the median from a data stream."
   - When data is constantly being added and removed, and you always need to know the Max/Min instantly without resorting the whole array.
3. **Merge K Sorted Arrays/Lists:**
   - Dump the heads into a Min-Heap. Pop the smallest, push the next item from that specific list.
4. **Greedy / Minimum Cost Algorithms:**
   - "Minimum cost to connect ropes", Dijkstra's Shortest Path Algorithm, CPU Task Scheduling.
