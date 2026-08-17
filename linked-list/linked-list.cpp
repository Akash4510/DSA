#include <iostream>
#include "linked-list.h"

Node::Node(int val) : val(val), next(nullptr) {}

LinkedList::LinkedList() : head(nullptr), size(0) {}
LinkedList::LinkedList(int val) : head(new Node(val)), size(1) {}
LinkedList::LinkedList(std::vector<int>& arr) : head(nullptr), size(0) {
  for (int& n : arr) {
    push_back(n);
  }
}
LinkedList::~LinkedList() {
  while (!empty()) {
    pop_front();
  }
}

bool LinkedList::empty() const {
  return size == 0;
}

void LinkedList::print() const {
  std::cout << std::endl << std::endl;

  if (empty()) {
    std::cout << "List is empty!" << std::endl;
  };

  Node* curr = head;
  while (curr != nullptr) {
    std::cout << curr->val << " -> ";
    curr = curr->next;
  }
  std::cout << "NULL" << std::endl << std::endl;
}

int LinkedList::search(int x) const {
  if (empty()) return -1;

  int idx = 0;
  Node* curr = head;

  while (curr != nullptr && curr->val != x) {
    curr = curr->next;
    idx++;
  }

  return (curr == nullptr) ? -1 : idx;
}

void LinkedList::push_back(int val) {
  Node* newNode = new Node(val);
  if (head == nullptr) {
    head = newNode;
    size++;
    return;
  }

  Node* curr = head;

  while (curr->next != nullptr) {
    curr = curr->next;
  }

  curr->next = newNode;
  size++;
  return;
};

int LinkedList::pop_back() {
  Node* curr = head;

  if (empty()) return -1;

  if (head->next == nullptr) {
    int val = head->val;
    head = nullptr;

    delete curr;

    size--;
    return val;
  }

  while (curr->next->next != nullptr) {
    curr = curr->next;
  }

  Node* lastNode = curr->next;
  int val = lastNode->val;
  curr->next = nullptr;
  delete lastNode;

  size--;
  return val;
}

int LinkedList::pop_front() {
  if (empty()) return -1;

  Node* temp = head;
  int val = head->val;

  head = head->next;
  delete temp;

  size--;
  return val;
}

void LinkedList::reverse() {
  if (empty()) return;

  Node* prev = nullptr;
  Node* curr = head;
  Node* next = nullptr;

  while (curr != nullptr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  head = prev;
}

Node* LinkedList::reverseNode(Node* prev, Node* curr) {
  if (curr == nullptr) return prev;

  Node* next = curr->next;
  curr->next = prev;
  return reverseNode(curr, next);
}

void LinkedList::reverseRec() {
  head = reverseNode(nullptr, head);
}

void LinkedList::reverseSegment(int i, int j) {
  // 1. Corrected Boundary Checks (1-based indexing)
  if (i < 1 || i >= j || j > size) return;

  int c = 0;
  Node* curr = head;
  Node* prev = nullptr;

  // 2. Skip 'i-1' nodes to reach the start of the segment
  while (c < i - 1) {
    prev = curr;
    curr = curr->next;
    c++;
  }

  // 3. Anchor our boundaries
  Node* beforeNode = prev;
  Node* fromNode = curr;

  prev = nullptr;
  Node* next = nullptr;

  // 4. Standard Reversal for the segment length
  while (c < j) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
    c++;
  }

  // 5. The Rewire (With the Head Edge-Case Fix!)
  if (beforeNode != nullptr) {
    beforeNode->next = prev; // Connect left boundary
  }
  else {
    head = prev;             // If we reversed from the start, update the head!
  }

  fromNode->next = curr;     // Connect right boundary
}

// =================================================================
// HELPER 1: Reverses the first 'N' nodes starting from 'curr'
// =================================================================
Node* LinkedList::reverseFirstN(Node* curr, int n) {
  // Base Case: We reached the end of the segment we want to reverse.
  if (n == 1) {
    // Save the rest of the list so it isn't lost!
    successor = curr->next;
    // Return this node, as it is the brand new head of the reversed segment
    return curr;
  }

  // Recursively burrow down to the end of the segment
  Node* newHead = reverseFirstN(curr->next, n - 1);

  // Standard recursive reversal of the pointer
  curr->next->next = curr;

  // ATTACHMENT: Point the current node to the saved rest of the list.
  // As the call stack unwinds, this correctly leaves the final tail 
  // pointing to the un-reversed remainder of the list.
  curr->next = successor;

  return newHead;
}

// =================================================================
// HELPER 2: Burrows down to the starting point of the segment
// =================================================================
Node* LinkedList::reverseBetween(Node* curr, int m, int n) {
  // Base Case: We have reached the starting node of the segment!
  // Now, we just need to reverse the first 'n' elements from this point.
  if (m == 1) {
    return reverseFirstN(curr, n);
  }

  // We aren't at the start yet. Move forward by 1 node.
  // Because we moved forward, our target segment is now relatively 
  // 1 step closer, so we subtract 1 from both m and n.
  curr->next = reverseBetween(curr->next, m - 1, n - 1);

  return curr;
}

// =================================================================
// PUBLIC API: The method called by your main() function
// =================================================================
void LinkedList::reverseSegmentRec(int i, int j) {
  // Standard safety boundaries (1-based indexing)
  if (i < 1 || i >= j || j > size || head == nullptr) return;

  // Start the recursive chain at the head
  head = reverseBetween(head, i, j);
}
