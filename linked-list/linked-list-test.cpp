#include <iostream>
#include <vector>
#include "linked-list.h"

int main() {
  std::cout << "=========================================\n";
  std::cout << "   LINKED LIST REVERSAL TEST SUITE       \n";
  std::cout << "=========================================\n\n";

  // ---------------------------------------------------------
  // TEST 1: Full Reverse (Iterative)
  // ---------------------------------------------------------
  std::cout << "Test 1: Full Reverse (Iterative)\n";
  LinkedList list1;
  for (int i = 1; i <= 5; i++) list1.push_back(i);

  std::cout << "Original: ";
  list1.print();
  list1.reverse();
  std::cout << "Reversed: ";
  list1.print();
  std::cout << "Expected: 5  4  3  2  1\n\n";

  // ---------------------------------------------------------
  // TEST 2: Full Reverse (Recursive)
  // ---------------------------------------------------------
  std::cout << "Test 2: Full Reverse (Recursive)\n";
  LinkedList list2;
  for (int i = 1; i <= 5; i++) list2.push_back(i);

  std::cout << "Original: ";
  list2.print();
  list2.reverseRec();
  std::cout << "Reversed: ";
  list2.print();
  std::cout << "Expected: 5  4  3  2  1\n\n";

  // // ---------------------------------------------------------
  // // TEST 3: Reverse Segment (Iterative)
  // // ---------------------------------------------------------
  // // LeetCode standard uses 1-based indexing. pos=2 to pos=4
  // std::cout << "Test 3: Reverse Segment Iterative (pos 2 to 4)\n";
  // LinkedList list3;
  // for (int i = 10; i <= 60; i += 10) list3.push_back(i); // 10, 20, 30, 40, 50, 60

  // std::cout << "Original: ";
  // list3.print();
  // list3.reverseSegment(2, 4); // Reverses 20, 30, 40 -> 40, 30, 20
  // std::cout << "Reversed: ";
  // list3.print();
  // std::cout << "Expected: 10  40  30  20  50  60\n\n";

  // // ---------------------------------------------------------
  // // TEST 4: Reverse Segment (Recursive)
  // // ---------------------------------------------------------
  // std::cout << "Test 4: Reverse Segment Recursive (pos 2 to 4)\n";
  // LinkedList list4;
  // for (int i = 10; i <= 60; i += 10) list4.push_back(i);

  // std::cout << "Original: ";
  // list4.print();
  // list4.reverseSegmentRecursive(2, 4);
  // std::cout << "Reversed: ";
  // list4.print();
  // std::cout << "Expected: 10  40  30  20  50  60\n\n";

  // // ---------------------------------------------------------
  // // TEST 5: Edge Case - Segment involves the Head!
  // // ---------------------------------------------------------
  // // This is where most algorithms fail because the class's 'head' 
  // // pointer itself must be updated.
  // std::cout << "Test 5: Edge Case - Segment at Head (pos 1 to 3)\n";
  // LinkedList list5;
  // for (int i = 1; i <= 4; i++) list5.push_back(i);

  // std::cout << "Original: ";
  // list5.print();
  // list5.reverseSegment(1, 3); // Reverses 1, 2, 3 -> 3, 2, 1
  // std::cout << "Reversed: ";
  // list5.print();
  // std::cout << "Expected: 3  2  1  4\n\n";

  // std::cout << "=========================================\n";
  // std::cout << "   TESTING COMPLETE                      \n";
  // std::cout << "=========================================\n";

  return 0;
}