#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Heap {
protected:
  vector<int> arr;
  bool isMinHeap;

  void checkBound(int i) {
    if (i >= size()) {
      throw out_of_range("Index: " + to_string(i) + " is out of range!");
    }
  }

  int getParentNodeIdx(int i) {
    return (i - 1) / 2;
  }

  int getLeftNodeIdx(int i) {
    return (2 * i) + 1;
  }

  int getRightNodeIdx(int i) {
    return (2 * i) + 2;
  }

  bool isValid(int idx, int parentIdx) {
    if (isMinHeap) {
      return arr[parentIdx] < arr[idx];
    }
    else {
      return arr[parentIdx] > arr[idx];
    }
  }

public:
  Heap(bool isMin) : isMinHeap(isMin) {}

  // O(N LogN) Array Constructor
  // Heap(bool isMin, vector<int>& inputArr) : isMinHeap(isMin) {
  //   for (int& n : inputArr) {
  //     push(n);
  //   }
  // }

  // O(N) Array Constructor
  Heap(bool isMin, const vector<int>& inputArr) : isMinHeap(isMin) {
    arr = inputArr; // Copy the array as-is

    // Start from the last non-leaf node and sink everything down
    for (int i = (size() / 2) - 1; i >= 0; i--) {
      heapDown(i); // This is why we added 'int currIdx = 0' as a parameter to heap down!
    }
  }

  virtual ~Heap() = default;

  int size() const {
    return static_cast<int>(arr.size());
  }

  bool empty() const {
    return arr.empty();
  }

  int root() const {
    if (empty()) {
      throw out_of_range("Heap is empty!");
    }

    return arr.front();
  }

  void print() const {
    cout << "\n{";
    for (int i = 0; i < arr.size(); i++) {
      cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    cout << "}\n";
  }

  void push(int x) {
    arr.push_back(x);
    heapUp();
  }

  int pop() {
    int n = root();
    arr[0] = arr[size() - 1];
    arr.pop_back();
    heapDown();
    return n;
  }

  void heapUp() {
    int currIdx = size() - 1;
    int parentIdx = getParentNodeIdx(currIdx);

    while (currIdx > 0 && !isValid(currIdx, parentIdx)) {
      swap(arr[currIdx], arr[parentIdx]);
      currIdx = parentIdx;
      parentIdx = getParentNodeIdx(currIdx);
    }
  }

  void heapDown(int currIdx = 0) { // Default parameter added for the O(N) build trick below
    while (true) {
      int leftIdx = getLeftNodeIdx(currIdx);
      int rightIdx = getRightNodeIdx(currIdx);
      int extremeIdx = currIdx; // Start by assuming the parent is the correct one

      // Check if left child is more extreme than the parent
      if (leftIdx < size() && !isValid(leftIdx, extremeIdx)) {
        extremeIdx = leftIdx;
      }
      // Check if right child is more extreme than whoever is currently the most extreme
      if (rightIdx < size() && !isValid(rightIdx, extremeIdx)) {
        extremeIdx = rightIdx;
      }

      // If the parent is no longer the most extreme, swap and continue
      if (extremeIdx != currIdx) {
        swap(arr[currIdx], arr[extremeIdx]);
        currIdx = extremeIdx;
      }
      else {
        break; // The heap property is satisfied
      }
    }
  }
};

class MinHeap : public Heap {
public:
  MinHeap() : Heap(true) {}
  MinHeap(const vector<int>& inputArr) : Heap(true, inputArr) {}
};

class MaxHeap : public Heap {
public:
  MaxHeap() : Heap(false) {}
  MaxHeap(const vector<int>& inputArr) : Heap(false, inputArr) {}
};

int main() {
  vector<int> arr = { 15, 10, 30, 5, 20 };

  cout << endl << "--- MIN HEAP TESTS ---\n";
  MinHeap minHeap(arr);

  // Test 1: Insert multiple elements
  cout << endl << "Operation: Insert 15, 10, 30, 5, 20\nExpected Array: {5, 10, 30, 15, 20}";
  minHeap.print();

  // Test 2: Pop the root (5)
  minHeap.pop();
  cout << endl << "Operation: pop\nExpected Array: {10, 15, 30, 20}";
  minHeap.print();

  // Test 3: Push a new element that needs to bubble up (8)
  minHeap.push(8);
  cout << endl << "Operation: push(8)\nExpected Array: {8, 10, 30, 20, 15}";
  minHeap.print();

  // Test 4: Pop the root again (8)
  minHeap.pop();
  cout << endl << "Operation: pop\nExpected Array: {10, 15, 30, 20}";
  minHeap.print();

  // Test 5: Push an element that only bubbles up one level (12)
  minHeap.push(12);
  cout << endl << "Operation: push(12)\nExpected Array: {10, 12, 30, 20, 15}";
  minHeap.print();

  cout << endl << "\n";

  cout << "--- MAX HEAP TESTS ---\n";
  MaxHeap maxHeap(arr);

  // Test 1: Insert multiple elements
  cout << "\nOperation: Insert 15, 10, 30, 5, 20\nExpected Array: {30, 20, 15, 5, 10}";
  maxHeap.print();

  // Test 2: Pop the root (30)
  maxHeap.pop();
  cout << "\nOperation: pop\nExpected Array: {20, 10, 15, 5}";
  maxHeap.print();

  // Test 3: Push a new element that becomes the new root (25)
  maxHeap.push(25);
  cout << "\nOperation: push(25)\nExpected Array: {25, 20, 15, 5, 10}";
  maxHeap.print();

  // Test 4: Pop the root again (25)
  maxHeap.pop();
  cout << "\nOperation: pop\nExpected Array: {20, 10, 15, 5}";
  maxHeap.print();

  // Test 5: Push an element that bubbles up to the middle (18)
  maxHeap.push(18);
  cout << "\nOperation: push(18)\nExpected Array: {20, 18, 15, 5, 10}";
  maxHeap.print();

  cout << endl << "\n";

  return 0;
}
