#include <iostream>
#include <vector>

// Standard LeetCode Node Definition
struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
  // =================================================================
  // Problem 1: LeetCode 876 - Middle of the Linked List
  // =================================================================
  ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    return slow;
  }

  // =================================================================
  // Problem 2: LeetCode 141 - Linked List Cycle
  // =================================================================
  bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;

      if (fast == slow) return true;
    }

    return false;
  }

  // =================================================================
  // Problem 3: LeetCode 19 - Remove Nth Node From End of List
  // =================================================================
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    // 1. Create a dummy node to handle edge cases (like deleting the head)
    ListNode* dummy = new ListNode(0);
    dummy->next = head;

    // 2. Start BOTH pointers at the dummy
    ListNode* slow = dummy;
    ListNode* fast = dummy;

    // 3. Move fast forward 'n' steps to create the gap
    while (n > 0) {
      fast = fast->next;
      n--;
    }

    // 4. Move both until fast reaches the VERY LAST node
    while (fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next;
    }

    // 5. 'slow' is now sitting right before the node we want to delete
    ListNode* nodeToRemove = slow->next;
    slow->next = slow->next->next; // Bypass the target

    // 6. Clean up memory
    delete nodeToRemove;

    // 7. Capture the new head and delete our temporary dummy
    ListNode* newHead = dummy->next;
    delete dummy;

    return newHead;
  }
};

// --- Helper Functions for Testing ---
ListNode* createList(const std::vector<int>& arr) {
  if (arr.empty()) return nullptr;
  ListNode* head = new ListNode(arr[0]);
  ListNode* curr = head;
  for (size_t i = 1; i < arr.size(); i++) {
    curr->next = new ListNode(arr[i]);
    curr = curr->next;
  }
  return head;
}

void printList(ListNode* head) {
  while (head != nullptr) {
    std::cout << head->val << " -> ";
    head = head->next;
  }
  std::cout << "NULL\n";
}

int main() {
  Solution sol;
  std::cout << "--- Testing Fast & Slow Pointers ---\n\n";

  // TEST 1: Middle Node
  std::cout << "Test 1: Middle Node\n";
  ListNode* list1 = createList({ 1, 2, 3, 4, 5 });
  std::cout << "List: "; printList(list1);
  ListNode* mid = sol.middleNode(list1);
  if (mid) std::cout << "Your Middle Node: " << mid->val << " (Expected: 3)\n\n";
  else std::cout << "Your Middle Node: NULL (Expected: 3)\n\n";

  // TEST 2: Linked List Cycle
  std::cout << "Test 2: Cycle Detection\n";
  ListNode* list2 = createList({ 3, 2, 0, -4 });
  // Manually create a cycle: Point the tail (-4) back to the 2nd node (2)
  list2->next->next->next->next = list2->next;
  bool has_cycle = sol.hasCycle(list2);
  std::cout << "Does it have a cycle? " << (has_cycle ? "Yes" : "No") << " (Expected: Yes)\n\n";

  // TEST 3: Remove Nth From End
  std::cout << "Test 3: Remove Nth From End (n = 2)\n";
  ListNode* list3 = createList({ 1, 2, 3, 4, 5 });
  std::cout << "Original List: "; printList(list3);
  ListNode* updatedList = sol.removeNthFromEnd(list3, 2);
  std::cout << "Updated List:  "; printList(updatedList);
  std::cout << "Expected:      1 -> 2 -> 3 -> 5 -> NULL\n";

  return 0;
}
