#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int>& arr) {
  int n = arr.size();

  cout << "\n[";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << (i < n - 1 ? ", " : "");
  }
  cout << "]\n";
}

int partition(vector<int>& arr, int left, int right) {
  int pivot = arr[right];

  // 1. Keep track of where the "smaller than pivot" section ends.
  // We start it at 'left' because we haven't found any small numbers yet.
  int smallSlot = left;

  // 2. Iterate through the array (The Explorer)
  for (int j = left; j < right; j++) {
    // 3. If we find an element smaller than the pivot...
    if (arr[j] < pivot) {
      // Swap it into our guaranteed "small section" 
      swap(arr[smallSlot], arr[j]);

      // Move the wall forward to make room for the next small number
      smallSlot++;
    }
  }

  // 4. Finally, swap the pivot into its correct spot right after the smaller elements
  swap(arr[smallSlot], arr[right]);

  // 5. Return that index
  return smallSlot;
}

// We can select whatever element as a pivot, and then just simply swap it at the right and the same logic will work, instead of left we can select any random element as the pivot as well.
int hidePivotTrickPartition(vector<int>& arr, int left, int right) {
  // We want the left element to be the pivot, so hide it at the end!
  swap(arr[left], arr[right]);

  // Now, arr[right] holds our chosen pivot. 
  // The rest of this is EXACTLY your working code:
  int pivot = arr[right];
  int smallSlot = left;

  for (int j = left; j < right; j++) {
    if (arr[j] < pivot) {
      swap(arr[smallSlot], arr[j]);
      smallSlot++;
    }
  }
  swap(arr[smallSlot], arr[right]);
  return smallSlot;
}

// In this we select the left element as the pivot, and adjust the loop
int actualLeftPivotPartition(vector<int>& arr, int left, int right) {
  int pivot = arr[left];

  // The wall starts one step AHEAD of the pivot
  int smallSlot = left + 1;

  // The explorer also starts one step AHEAD, and goes all the way to 'right'
  for (int j = left + 1; j <= right; j++) {
    if (arr[j] < pivot) {
      swap(arr[smallSlot], arr[j]);
      smallSlot++;
    }
  }

  // Swap the pivot (at left) into its final spot just behind the wall
  swap(arr[left], arr[smallSlot - 1]);
  return smallSlot - 1;
}

void quickSort(vector<int>& arr, int left, int right) {
  if (left >= right) return;

  // Get the index of the locked-in pivot
  int pivotIndex = partition(arr, left, right);

  // Recursively sort the left side (everything before the pivot)
  quickSort(arr, left, pivotIndex - 1);
  // Recursively sort the right side (everything after the pivot)
  quickSort(arr, pivotIndex + 1, right);
}

int main() {
  vector<int> arr = { 1,5,6,4,3,8,9,7,2 };
  cout << "\nBefore swapping:";
  printArray(arr);

  quickSort(arr, 0, arr.size() - 1);

  cout << "\nAfter swapping: ";
  printArray(arr);

  return 0;
}
