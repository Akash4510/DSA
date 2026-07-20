#include <iostream>
#include <vector>

using namespace std;

// The Challenge: Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number. Return their values.

vector<int> twoSum(vector<int>& numbers, int target) {
  vector<int> ans;

  int left = 0;
  int right = numbers.size() - 1;

  while (left < right) {
    int sum = numbers[left] + numbers[right];
    if (sum == target) {
      ans.push_back(numbers[left]);
      ans.push_back(numbers[right]);
      break;
    }
    else if (sum > target) {
      right--;
    }
    else {
      left++;
    }
  }

  return ans;
}

int main() {
  vector<int> numbers = { 2, 7, 11, 15 };
  int target = 9;

  vector<int> result = twoSum(numbers, target);

  if (result.size() == 2) {
    cout << "Found pair: " << result[0] << " and " << result[1] << "\n";
  }
  else {
    cout << "No pair found.\n";
  }

  return 0;
}
