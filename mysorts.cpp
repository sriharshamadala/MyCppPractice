#include <iostream>
#include "mysorts.h"
#include <list>
#include <iterator>

using namespace std;

void selectSort(int* arr, int N)
{
	int minVal, minInd, count=0;
	for (int j=0; j<N; j++)
	{
		minVal = arr[j];
		for (int i=j; i<N; i++)
		{
			count++;
			if (arr[i]<=minVal)
			{
				minVal = arr[i];
				minInd = i;
			}
		}
		swapem(arr, minInd, j);	
	}
	cout << count << endl;
}

void bubbleSort(int* arr, int N)
{
	bool swapped=true;
	int count=0;
	while (swapped==true)
	{
		swapped=false;
		for (int i=0; i<N-1; i++)
		{
			count++;
			if (arr[i]>arr[i+1])
			{
				swapem(arr, i, i+1);
				swapped=true;
			}
		}
	}
	cout << count << endl;
}

void swapem(int* arr, int index1,int index2)
{
	int swapHolder = arr[index1];
	arr[index1]=arr[index2];
	arr[index2]=swapHolder;
}

int quickSortPartition(int* arr, int left, int right, int pivotIndex)
{
	int pivotValue = arr[pivotIndex];
	swapem(arr, pivotIndex, right);
	int storeIndex = left;
	for (int i=left; i<right; i++)
	{
		if (arr[i]<pivotValue)
		{
			swapem(arr, i, storeIndex);
			storeIndex++;
		}
	}
	swapem(arr, storeIndex, right);
	return storeIndex;
}

		
void quickSortInplace(int* arr, int left, int right)
{
	if ((right-left)<2)
		cout << "Already sorted\n";
	if (left < right)
	{
		int pivotIndex= (right-left+1)/2;
		int pivotNewIndex = quickSortPartition(arr, left, right, left+pivotIndex-1);
		if (pivotNewIndex-1 >=left+1)
			quickSortInplace(arr, left, pivotNewIndex-1);
		if (right >= pivotNewIndex+2 )
			quickSortInplace(arr, pivotNewIndex+1, right);
	}
}

list<int> mergeSort(list<int> data)
{
	if (data.size()<=1)
		return data;
	list<int> left, right;
	int mid=data.size()/2;
	list<int>::iterator pos=left.begin();
	list<int>::iterator first=data.begin();
	advance(first, mid);
	left.splice(pos, data, data.begin(), first);
	pos = right.begin();	
	right.splice(pos, data, first, data.end());
	left = mergeSort(left);
	right = mergeSort(right);
	return merge(left, right);
}

list<int> merge(list<int> left, list<int> right)
{
	list<int> result;
	list<int>::iterator posl=left.begin();
	list<int>::iterator posr=right.begin();
	while (left.size() > 0 || right.size() > 0)
	{
		if (left.size() > 0 && right.size() > 0)
		{
			if (*posl<=*posr)
			{
				cout << *posl << endl;
				result.push_back(*posl);
				posl = left.erase(posl);
				//posl++;
			}
			else
			{
				cout << *posr << endl;
				result.push_back(*posr);
				posr = right.erase(posr);
				//posr++;
			}
		}
		else if (left.size()>0)
			result.splice(result.end(), left);
		else if (right.size()>0)
			result.splice(result.end(), right);
	}
	return result;
}


