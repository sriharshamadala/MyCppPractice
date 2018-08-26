#include <iostream>

using namespace std;

// assuming the indices are within the range.
template <class T>
void swap (T *arr, int index1, int index2) {
  T temp = arr[index1];
  arr[index1] = arr[index2];
  arr[index2] = temp;
}

template <class T>
void selectSort (T *arr, int array_length) {
  int sorted_till_index = 0;
  while (sorted_till_index < array_length - 1) {
    int min_val = arr[sorted_till_index];
    int min_val_index = 0;
    for (int ii = sorted_till_index; ii < array_length; ++ii) {
      if (arr[ii] <= min_val) {
        min_val = arr[ii];
        min_val_index = ii;
      }
    }
    swap(arr, min_val_index, sorted_till_index);
    ++sorted_till_index;
  }
}

template <class T>
void printArray(const T *arr, int array_length) {
  for (int ii = 0; ii < array_length; ++ii) {
    cout << arr[ii] << " ";
  }
  cout << endl;
}

// Driver program
int main()
{
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr)/sizeof(arr[0]);

  selectSort<int> (arr, n);

  cout << "Sorted array is \n";
  printArray<int> (arr, n);
}
