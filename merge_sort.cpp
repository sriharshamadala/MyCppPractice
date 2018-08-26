#include <iostream>

using namespace std;

template <class T>
void printArray(const T *arr, int array_length) {
  for (int ii = 0; ii < array_length; ++ii) {
    cout << arr[ii] << " ";
  }
  cout << endl;
}

template <class T>
void merge (T *arr, int left_index, int mid_index, int right_index) {
  // merge operation using array data struct requires extra space. 
  // This can be avoided using linked list.
  int left_count = mid_index - left_index + 1;
  int right_count = right_index - mid_index; 
  int temp_left[left_count];
  int temp_right[right_count];
  for (int ii = left_index, temp_index = 0; ii <= mid_index; ++ii, ++temp_index) {
    temp_left[temp_index] = arr[ii];
  }
  for (int ii = mid_index + 1, temp_index = 0; ii <= right_index; ++ii, ++temp_index) {
    temp_right[temp_index] = arr[ii];
  }

  int curr_left_marker = 0;
  int curr_right_marker = 0;
  int curr_arr_marker = left_index;
  while ((curr_left_marker < left_count) && (curr_right_marker < right_count)) {
    if (temp_left[curr_left_marker] <= temp_right[curr_right_marker]) {
      arr[curr_arr_marker] = temp_left[curr_left_marker];
      curr_left_marker++;
      curr_arr_marker++;
    } else {
      arr[curr_arr_marker] = temp_right[curr_right_marker];
      curr_right_marker++;
      curr_arr_marker++;
    }
  } 

  while (curr_left_marker < left_count) {
    arr[curr_arr_marker] = temp_left[curr_left_marker];
    curr_left_marker++;
    curr_arr_marker++;
  }
  while (curr_right_marker < right_count) {
    arr[curr_arr_marker] = temp_right[curr_right_marker];
    curr_right_marker++;
    curr_arr_marker++;
  }
}

// Inclusive of both indices
template <class T>
void mergeSort (T *arr, int left_index, int right_index) {
  if (left_index == right_index) {
    return;
  } else {
    int mid_index = (left_index + right_index) / 2;
    mergeSort(arr, left_index, mid_index);
    mergeSort(arr, mid_index + 1, right_index);
    merge(arr, left_index, mid_index, right_index);
  }
}


// Driver program
int main()
{
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr)/sizeof(arr[0]);

  mergeSort<int> (arr, 0, n - 1);

  cout << "Sorted array is \n";
  printArray<int> (arr, n);
}
