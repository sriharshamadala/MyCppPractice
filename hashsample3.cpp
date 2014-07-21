#include <iostream>
#include "hash.h"
#include <string>
#include <fstream>

using namespace std;

int main()
{
	int N=1009;
	hashtable bucket[N];
	hashtable* transcient;
	transcient = new hashtable [1000];
	ifstream myfile;
	myfile.open("wordHash.txt");
	string word;
	int count=0;
	while (getline(myfile,word))
	{
		transcient[count].setValues(word, std::to_string(count));
		insertHashTable(bucket, transcient+count, N);
		count++;
	}	
	printHashTable(bucket,N);
}

