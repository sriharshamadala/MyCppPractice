#include "hash.h"
#include <string>

using namespace std;

int main()
{
  HashTable hash_table(7);
  hash_table.insert("walter white", "breaking bad");
  hash_table.insert("hal", "malcolm in the middle");
  hash_table.insert("fez", "that 70's show");
  hash_table.insert("monica", "friends");
  hash_table.insert("greg house", "house md");
  hash_table.insert("frasier", "frasier");
  hash_table.printHashTable();
  return 0;
}

