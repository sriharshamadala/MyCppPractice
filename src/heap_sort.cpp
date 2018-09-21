#include <iostream>
#include <cmath>

using namespace std;

// We use array to represent the heap.
// Each node at i has child nodes at 2i+1 and 2i+2.
template <class T>
class MaxHeap {
  private:
    T * arr;
    int arr_length;
    void swap (int index1, int index2);

  public:
    MaxHeap (T *data, int n) {
      arr = data;
      arr_length = n;
    }
    void maxHeapify (int node_index);
    
    T extractMax () {
      // Swap the max with end of heap element.
      swap(0, arr_length - 1);
      T result = arr[arr_length - 1];
      arr_length--;

      // Make sure the heap structure is preserved.
      maxHeapify(0);
      return result;
    }

    void printHeap ();
    void heapSort ();
    void printArray ();
};

template <class T>
void MaxHeap<T>::printHeap () {
  int heap_depth = floor(log2(arr_length)) + 1;
  int count = 0;
  for (int ii = 0; ii < heap_depth; ++ii) {
    string pattern (2 * (heap_depth - ii) - 1, ' ');
    int nf_nodes_curr_depth = (1 << ii);
    if ((count + nf_nodes_curr_depth) >= arr_length) {
      nf_nodes_curr_depth = arr_length - count;
    }
    cout << pattern;
    for (int jj = 0; jj < nf_nodes_curr_depth; ++jj) {
      cout << arr[count + jj] << pattern;
    }
    cout << endl;
    count += nf_nodes_curr_depth;
  }
  cout << string(50, '+') << endl;
}

template <class T>
void MaxHeap<T>::swap (int index1, int index2) {
  T temp_value = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp_value;
}

template <class T>
void MaxHeap<T>::maxHeapify (int node_index) {
  int left_index = 2 * node_index + 1;
  int right_index = 2 * node_index + 2;
  int largest_index = node_index;
  
  if ((left_index < arr_length) && (arr[left_index] > arr[largest_index])) {
    largest_index = left_index;
  }

  if ((right_index < arr_length) && (arr[right_index] > arr[largest_index])) {
    largest_index = right_index;
  }
  
  if (largest_index != node_index) {
    swap(node_index, largest_index);
    // further recursively heapify if the subtree is affected.
    maxHeapify(largest_index);
  }
}

template <class T>
void MaxHeap<T>::heapSort () {
  for (int ii = 0; ii < (arr_length / 2); ++ii) {
    maxHeapify(ii);
  }

  while (arr_length > 0) {
    cout << arr[0] << " ";
    extractMax();
  }
  cout << endl;
}

// Driver program
int main() {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr)/sizeof(arr[0]);

  MaxHeap<int> max_heap (arr, n);
  max_heap.heapSort();
  return 0;
}

