#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int ftoa(float f, int d, char* c)
{
	int num = (int) f*pow(10,d);
	int temp = num;
	int temp2;
	int count=0;
	while( temp>0 )
	{
		temp = temp/10;
		count++;
	}
	*(c+count-d+1)='.';
	temp = num;
	for(int i=0; i<count+1; i++)
	{
		if (i!=count-d+1)
		{
			temp2 = temp-10*(temp/10);
			temp = temp/10;
			*(c+count+1-i) = char((int)'0' + temp2);
		}
	}
	return count;
}

int main()
{
	float f=100.0073;
	int d=3;
	char str[20];
	int count = ftoa(f,d,str);
	for(int i=0; i<count+1; i++)
		cout << str[i];
	cout << endl;
	return 0;
}
		

