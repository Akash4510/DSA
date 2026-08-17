#include <vector>

class Node {
public:
  int val;
  Node* next;

  Node(int val);
};

class LinkedList {
private:
  Node* head;
  int size;

  Node* reverseNode(Node*, Node*);
  Node* reverseFirstN(Node* curr, int n);
  Node* successor = nullptr;
  Node* reverseBetween(Node* curr, int m, int n);

public:
  LinkedList();
  LinkedList(int);
  LinkedList(std::vector<int>&);
  ~LinkedList();

  void print() const;
  bool empty() const;
  int search(int) const;
  void push_back(int);
  int pop_back();
  int pop_front();
  void reverse();
  void reverseRec();
  void reverseSegment(int, int);
  void reverseSegmentRec(int, int);
};
