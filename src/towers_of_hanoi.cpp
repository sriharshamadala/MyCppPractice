#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void displayTowers (stack<int>* towers, int nf_towers) {
  int sizes[nf_towers];
  int max_size = 0;
  stack<int> temp_stack[nf_towers];
  for (int ii = 0; ii < nf_towers; ++ii) {
    // Making a copy since individual element access is not possible
    // in stack without popping.
    temp_stack[ii] = towers[ii];
    sizes[ii] = towers[ii].size();
    if (sizes[ii] > max_size) {
      max_size = sizes[ii];
    }
  }
  
  // Print each tower horizontally.
  for (int ii = max_size; ii > 0; --ii) {
    for (int jj = 0; jj < nf_towers; ++jj) {
      if (temp_stack[jj].size() == ii) {
        cout << temp_stack[jj].top() << "   ";
        temp_stack[jj].pop();
      } else {
        cout << "    ";
      }
    }
    cout << endl;
  }
  cout << string(20, '-') << endl;
}

void moveDisks (int size, stack<int>* towers, int nf_towers, int source, int destination, int buffer) {
  if (size > 0) {
    moveDisks(size - 1, towers, nf_towers, source, buffer, destination);
    towers[destination].push(towers[source].top());
    towers[source].pop();
    displayTowers(towers, nf_towers);
    moveDisks(size - 1, towers, nf_towers, buffer, destination, source);
  }
}

int main () {
  int nf_disks = 6;
  int nf_towers = 3;
  stack<int> towers[nf_towers];

  // Initial state
  for (int ii = nf_disks; ii > 0; --ii) {
    towers[0].push(ii);
  }

  displayTowers(towers, nf_towers);
  moveDisks(nf_disks, towers, nf_towers, 0, 2, 1);
  displayTowers(towers, nf_towers);

  return 0;
}
