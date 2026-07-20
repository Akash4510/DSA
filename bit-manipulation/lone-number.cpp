#include <iostream>
#include <vector>

using namespace std;

int findLonelyNumber(vector<int>& arr) {
  int ans = 0;
  for (int i = 0; i < arr.size(); i++) {
    ans ^= arr[i];
  }
  return ans;
}

int main() {
  vector<int> arr = { 1, 2, 3, 3, 1, 2, 4, 5, 5, 6, 6, 7, 7 };

  cout << endl << "The lonely number is: " << findLonelyNumber(arr) << endl << endl;

  return 0;
}
