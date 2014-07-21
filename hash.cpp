#include <iostream>
#include "hash.h"
#include <string>

using namespace std;

hashtable::hashtable()
{
	key="";
	value="";
	nextEl=0;
}

/*hashtable::~hashtable()
{
	delete [] key;
	delete [] value;
	
}*/

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

void hashtable::operator= (const hashtable& param)
{
	key = param.key;
	value = param.value;
	nextEl = param.nextEl;
}

bool hashtable::keyMatch(string s)
{
	if (key.compare(s)==0)
		return true;
	else
		return false;
}	

long hashtable::hashit()
{
	const long p=16908799;
	long hashval=0;
	for (int i=0; i<key.length(); i++)
	{
		hashval = 127*hashval+key.at(i);
	}
	return (hashval % p);
}

long findHashValue(string key)
{
	const long p=16908799;
	long hashval=0;
	for (int i=0; i<key.length(); i++)
	{
		hashval = 127*hashval+key.at(i);
	}
	return (hashval % p);
}


void insertHashTable(hashtable* head, hashtable* transcient, int N)
{
		long pos = transcient->hashit();
		pos = pos % N;
//		cout << pos << endl;
		hashtable* temp1;
		temp1 = (head+pos)->nextEl;
		if (temp1==0)
			(head+pos)->nextEl= transcient;
		else
		{
			while(temp1->nextEl !=0)
				temp1 = temp1->nextEl;
			temp1->nextEl = transcient;
		}
}

void findEntry(hashtable* head, string s, int N)
{
	long pos = findHashValue(s);
	pos = pos % N;
  hashtable* temp1=(head+pos);
	while (temp1->nextEl !=0)
	{
		temp1 = temp1->nextEl;
		if (temp1->keyMatch(s))
		{
			temp1->printTable();
			return;
		}
	}
	cout << "No entry found\n";
}

void removeEntry(hashtable* head, string s, int N)
{
	long pos = findHashValue(s);
	pos = pos % N;
  hashtable* temp1=(head+pos);
  hashtable* prevtemp1;
	while (temp1->nextEl !=0)
	{
		prevtemp1 = temp1;
		temp1 = temp1->nextEl;
		if (temp1->keyMatch(s))
		{
			prevtemp1->nextEl = temp1->nextEl;
			//delete the object using destructor
			temp1->~hashtable();
			return;
		}
	}
	cout << "No entry found to delete\n";
}


void printHashTable(hashtable* head, int N)
{
	hashtable* temp1;
	for (int i=0; i<N; i++)
	{
		cout << "1\n";
		temp1=(head+i)->nextEl;
		while(temp1 !=0)
		{
			temp1->printTable();
			temp1 = temp1->nextEl;
		}
	}
}
	
