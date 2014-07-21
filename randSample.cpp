#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int randSample(int* arr, int N, int* freq)
{
	vector<int> v;
	vector<int>::iterator it = v.begin();
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<freq[i]; j++)
			it = v.insert(it, arr[i]);
	}
	return v.at(rand() % v.size());
}

int main()
{
	
	int arr[4] = {10, 20, 30, 40};
	int freq[4] = {5, 1, 1, 1};
	for(int i=0; i<10; i++)
		cout << randSample(arr, 4, freq) << endl;
	return 0;
}
