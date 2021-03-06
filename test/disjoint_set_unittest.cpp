#include "disjoint_set.h"
#include <gtest/gtest.h>

using namespace std;

TEST (DisjointSetTest, simpleIntegerSets) {
  char arr[] = {'0', '1', '2', '3'};

  DisjointSet<char> disjoint_set(arr, 4);
  EXPECT_EQ('0', *disjoint_set.find(&arr[0]));
  EXPECT_EQ('1', *disjoint_set.find(&arr[1]));
  EXPECT_EQ('2', *disjoint_set.find(&arr[2]));
  EXPECT_EQ('3', *disjoint_set.find(&arr[3]));
  EXPECT_EQ(4, disjoint_set.numberOfDisjointSets());

  disjoint_set.Union(&arr[0], &arr[1]);
  EXPECT_EQ('1', *disjoint_set.find(&arr[0]));
  EXPECT_EQ('1', *disjoint_set.find(&arr[1]));
  EXPECT_EQ(3, disjoint_set.numberOfDisjointSets());

  disjoint_set.Union(&arr[1], &arr[2]);
  EXPECT_EQ('1', *disjoint_set.find(&arr[0]));
  EXPECT_EQ('1', *disjoint_set.find(&arr[1]));
  EXPECT_EQ('1', *disjoint_set.find(&arr[2]));
  EXPECT_EQ(2, disjoint_set.numberOfDisjointSets());
}

TEST (DisjointSetTest, templateSpecializationInt) {
  
  DisjointSet<int> disjoint_set(5);
  EXPECT_EQ(0, disjoint_set.find(0));
  EXPECT_EQ(1, disjoint_set.find(1));
  EXPECT_EQ(2, disjoint_set.find(2));
  EXPECT_EQ(3, disjoint_set.find(3));
  EXPECT_EQ(4, disjoint_set.find(4));
  EXPECT_EQ(5, disjoint_set.numberOfDisjointSets());

  disjoint_set.Union(0, 1);
  EXPECT_EQ(1, disjoint_set.find(0));
  EXPECT_EQ(1, disjoint_set.find(1));
  EXPECT_EQ(4, disjoint_set.numberOfDisjointSets());

  disjoint_set.Union(1, 2);
  EXPECT_EQ(1, disjoint_set.find(0));
  EXPECT_EQ(1, disjoint_set.find(1));
  EXPECT_EQ(1, disjoint_set.find(2));
  EXPECT_EQ(3, disjoint_set.numberOfDisjointSets());
}
