#include <iostream>

using namespace std;

int rodcutRecursive(int* arr, int N)
{
	int maxval=0, temp;
	if (N==1)
		return arr[0];
	else
	{
		for (int i=0; i<N; i++)
		{
			temp = arr[i] + rodcutRecursive(arr, N-i-1);
			if (temp > maxval)
				maxval = temp;
		}
	}
	return maxval;
}

int main()
{
	int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
	int size = sizeof(arr)/sizeof(arr[0]);
	int price = rodcutRecursive(arr, size);
	cout << price << endl;
}
