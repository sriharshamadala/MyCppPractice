#include <iostream>
#include <vector>
#include <list>

using namespace std;

void calculatePowerSets(int *arr, int right_index, list<vector<int>>& power_set) {
  if (right_index < 0) {
    // Push empty set.
    vector<int> temp;
    power_set.push_back(temp);
  } else {
    calculatePowerSets(arr, right_index - 1, power_set);
    for (auto iter = power_set.begin(); iter != power_set.end(); iter++) {
      // Copy the existing set.
      vector<int> temp((*iter));
      temp.push_back(arr[right_index]);
      // inserts before the iterator.
      power_set.insert(iter, temp);
    }
  }
}

int main () {
  int arr[5] = {1, 2, 3, 4, 5};
  // List because we insert new vectors for every vector that already exists.
  list<vector<int>> power_set;

  calculatePowerSets(arr, 4, power_set);

  cout << "All the subsets (" << power_set.size() << "): " << endl;
  for (auto vec : power_set) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }

  return 0;
}
