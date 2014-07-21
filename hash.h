#ifndef HASH_H
#define HASH_H
#include <string>

//using namespace std;

class hashtable
{
	std::string key;
	std::string value;
	public:
	hashtable *nextEl;
	hashtable();
//	~hashtable();
	void setValues (std::string, std::string);
	void printTable(void);
	long hashit(void);
	bool keyMatch(std::string);
	void operator= (const hashtable& param);
};

void printHashTable(hashtable*, int);
void findEntry(hashtable*, std::string, int);
void removeEntry(hashtable*, std::string, int);
void insertHashTable(hashtable*, hashtable*, int);
long findHashValue(std::string);

#endif
