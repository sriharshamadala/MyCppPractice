#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	string mystring;
	cout << "Enter the string\n";
	getline(cin,mystring);
	std::string str(mystring);
	int s = str.length();
	if (s==0 || s==1) 
	{
		cout << "Empty or 1 character string. valid palindrome\n";
		return 0;
	}
	else
	{
		int equivArr[100];
		int count=0;
		for (int i=0; i<s; i++)
		{
			int c=mystring[i];
			if ((c>=65 && c<=90) || (c>=97 && c<=122))
			{
				equivArr[count]=c;
				//cout << equivArr[count] << "\t";
				count++;
			}
		}
		int comp;
		for (int j=0; j<count; j++)
		{
			comp = equivArr[j]-equivArr[count-1-j];
			if (comp==0 || comp==32 || comp==-32)
			{
				continue;
				cout << "1\n";
			}
			else
			{
				cout << "Not a valid palindrome\n";
			//	cout << "2\n";
				return 0;
			}
		}
	}
	cout << "\nKudos! A valid palindrome\n";
	return 0;
}
