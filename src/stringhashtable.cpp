#include <iostream>
#include <cstring>
#include <string>
#include <cmath>

using namespace std;

class hashtable
{
	string key;
	string value;
	public:
	hashtable *nextEl;
	hashtable();
	void setValues (string, string);
	void printTable(void);
	long hashit(void);
	string findit(string key);
	void operator= (const hashtable& param);
};

hashtable::hashtable()
{
	key="";
	value="";
	nextEl=0;
}

void hashtable::setValues(string a,string b)
{
	key=a;
	value=b;
	nextEl=0;
}

void hashtable::printTable(void)
{
	cout << "(" << key <<"," << value << ")\n";
}

long hashtable::hashit(void)
{
	const long p=16908799;
	long hashval=0;
	for (int i=0; i<key.length(); i++)
	{
		hashval = 127*hashval+key.at(i);
	}
	return (hashval % p);
}

void hashtable::operator= (const hashtable& param)
{
	key = param.key;
	value = param.value;
	nextEl = param.nextEl;
}
	
int main()
{
//Expected  No of entries
	int n=20;
//loading factor
//	float alpha=0.5;
//	int N=n*alpha;
	int N=41;
	hashtable input[N];
	hashtable transcient[n];
	std::string temp="start";
	int	count=0;
	long pos=0;
	std::string a,b;
	hashtable* temp1;
	while (temp.compare("end")!=0)
	{
		cout << "enter key\n";
		getline(cin,a);
		temp = a;
		cout << "enter value\n";
		getline(cin,b);
		transcient[count].setValues(a,b);
		pos = transcient[count].hashit();
		pos = pos % N;
		cout << pos << endl;
		temp1 = input[pos].nextEl;
		if (temp1==0)
			input[pos].nextEl= &transcient[count];
		else
		{
			while(temp1->nextEl !=0)
				temp1 = temp1->nextEl;
			temp1->nextEl = &transcient[count];
		}
		count++;
	}
	for (int i=0; i<N; i++)
	{
		temp1=input[i].nextEl;
		if (temp1 != 0)
			//	input[i].printTable();
		{
			cout <<"1\n";
			while(temp1 !=0)
			{
			//	cout << "   ";
				temp1->printTable();
				temp1 = temp1->nextEl;
			}
		}
	}
	return 0;
}

