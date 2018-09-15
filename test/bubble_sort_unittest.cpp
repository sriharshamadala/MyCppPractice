#include <gtest/gtest.h>
#include "bubble_sort.h"

using namespace std;

TEST(BubbleSortTest, testSimpleSort) {
  int arr[] = {12, 11, 13, 5, 6, 7};
  int n = sizeof(arr)/sizeof(arr[0]);

  bubbleSort<int> (arr, n);

  EXPECT_EQ(5, arr[0]);
  EXPECT_EQ(6, arr[1]);
  EXPECT_EQ(7, arr[2]);
  EXPECT_EQ(11, arr[3]);
  EXPECT_EQ(12, arr[4]);
  EXPECT_EQ(13, arr[5]);
}

TEST(BubbleSortTest, testAlreadySorted) {
  int arr[] = {5, 6, 7, 11, 12, 13};
  int n = sizeof(arr)/sizeof(arr[0]);

  bubbleSort<int> (arr, n);

  EXPECT_EQ(5, arr[0]);
  EXPECT_EQ(6, arr[1]);
  EXPECT_EQ(7, arr[2]);
  EXPECT_EQ(11, arr[3]);
  EXPECT_EQ(12, arr[4]);
  EXPECT_EQ(13, arr[5]);
}

TEST(BubbleSortTest, testWorstCase) {
  int arr[] = {13, 12, 11, 7, 6, 5};
  int n = sizeof(arr)/sizeof(arr[0]);

  bubbleSort<int> (arr, n);

  EXPECT_EQ(5, arr[0]);
  EXPECT_EQ(6, arr[1]);
  EXPECT_EQ(7, arr[2]);
  EXPECT_EQ(11, arr[3]);
  EXPECT_EQ(12, arr[4]);
  EXPECT_EQ(13, arr[5]);
}

TEST (BubbleSortTest, testOneElementSort) {
  int arr[] = {26};
  int n = sizeof(arr)/sizeof(arr[0]);

  bubbleSort<int> (arr, n);

  EXPECT_EQ(26, arr[0]);
}
