#ifndef MYSORTS_H
#define MYSORTS_H
#include <list>

void selectSort(int*, int);
void bubbleSort(int*, int );
void quickSortInplace(int*, int, int);
int quickSortPartition(int*, int, int, int);
void swapem(int*, int, int);
std::list<int> mergeSort(std::list<int> );
std::list<int> merge(std::list<int>, std::list<int>);

#endif

