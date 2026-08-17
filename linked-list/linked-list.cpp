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

void LinkedList::reverseSegmentRec(int i, int j) {}
