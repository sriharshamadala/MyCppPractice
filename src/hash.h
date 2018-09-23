#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

struct node {
  string key;
  string value;
};

class HashTable {
  private:
    list<struct node> *hash_map_;
    int nf_buckets_;
	public:
    HashTable(int nf_buckets);
    HashTable();
    ~HashTable();
    void printHashTable();
    void insert (string key, string value);
    int hashingFunction (string key);
    struct node * findEntry(string key);
    void remove(string key);
};

#endif
