// print numbers in ascending order which have only the factors 2,3 and 5

#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	int i=0,j=0,k=1;
	int N=1000;
	int temp=0;
	while(temp < N)
	{
		while (temp < 2*3*(pow(5,k+1)))
		{
			j++;
			while (temp < 2*pow(3,j+1)*pow(5,k))	
			{
				i++;
				temp = pow(2,i)*pow(3,j)*pow(5,k);
				cout << temp << endl;
			}
			i=0;
		}
		k++;
		i=0;
		j=0;
	}
	return 0;
}
