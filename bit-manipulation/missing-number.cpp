#include <iostream>
#include <vector>

using namespace std;

int findMissingNumber(const vector<int>& arr, int n) {
  int ans = 0;

  for (int i = 1; i <= n; i++) {
    ans ^= i;
  }

  for (int i = 0; i < arr.size(); i++) {
    ans ^= arr[i];
  }

  return ans;
}

int main() {
  vector<int> arr = { 1, 2, 4, 5 };
  int n = 5;

  int missingNumber = findMissingNumber(arr, n);

  cout << "\nThe missing number is: " << missingNumber << endl << endl;

  return 0;
}
