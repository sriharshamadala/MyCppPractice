#include <iostream>

using namespace std;

template <class T>
void printArray(const T *arr, int array_length) {
  for (int ii = 0; ii < array_length; ++ii) {
    cout << arr[ii] << " ";
  }
  cout << endl;
}

// assuming the indices are within the range.
template <class T>
void swap (T *arr, int index1, int index2) {
  T temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

template <class T>
// Choosing median of low high and middle as the choice of pivot. 
// Return index of the pivot.
int ChoosePivot(T *arr, int left_index, int right_index) {
  int mid_index = (left_index + right_index) / 2;
  if (arr[left_index] > arr[mid_index]) {
    if (arr[left_index] < arr[right_index]) {
      return left_index;
    } else if (arr[mid_index] > arr[right_index]) {
      return mid_index;
    } else {
      return right_index;
    }
  } else {
    if (arr[left_index] > arr[right_index]) {
      return left_index;
    } else if (arr[mid_index] > arr[right_index]) {
      return right_index;
    } else {
      return mid_index;
    }
  }
  return left_index;
}

template <class T>
int Partition (T *arr, int left_index, int right_index, int pivot_index) {
  // Swap the pivot element with left_index.
  // With this step we are back to partitioning using well known pivot as last or first element.
  swap(arr, left_index, pivot_index);
  
  int lo = left_index + 1;
  int hi = right_index;
  int pivot_val = arr[left_index];
  while (lo < hi) {
    while (arr[lo] <= pivot_val) lo++;
    while (arr[hi] > pivot_val) hi--;
    if (lo < hi) {
      swap(arr, lo, hi);
      lo++;
      hi--;
    }
  }
  // put the pivot element back where it belongs.
  swap(arr, hi, left_index);
  return hi;
}

// Inclusive of both indices.
template<class T>
void QuickSort(T *arr, int left_index, int right_index) {
  if (left_index >= right_index) {
    return;
  } else {
    int pivot_index = ChoosePivot(arr, left_index, right_index);
    int partition_index = Partition(arr, left_index, right_index, pivot_index);

    QuickSort(arr, left_index, partition_index - 1);
    QuickSort(arr, partition_index + 1, right_index);
  }
}

// Driver program
int main()
{
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr)/sizeof(arr[0]);

  QuickSort<int> (arr, 0, n - 1);

  cout << "Sorted array is \n";
  printArray<int> (arr, n);
}
