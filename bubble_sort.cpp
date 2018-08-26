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
void bubbleSort(T* arr, int array_length) {
  bool swapped = false;
	do {
    swapped = false;
		for (int ii = 0; ii < array_length - 1; ++ii) {
			if (arr[ii] > arr[ii + 1]) {
				swap(arr, ii, ii + 1);
        swapped = true;
			}
		}
	} while (swapped);
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

  bubbleSort<int> (arr, n);

  cout << "Sorted array is \n";
  printArray<int> (arr, n);
}
