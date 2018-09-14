#include "hash.h"

HashTable::HashTable(int nf_buckets) {
  nf_buckets_ = nf_buckets;
  hash_map_ = new list<struct node>[nf_buckets_];
}

HashTable::HashTable() {
  nf_buckets_ = 1001;
  hash_map_ = new list<struct node>[nf_buckets_];
}

HashTable::~HashTable() {
  for (int ii = 0; ii < nf_buckets_; ++ii) {
    // Clear the list.
    hash_map_[ii].clear();
  }
  delete [] hash_map_;
}

void HashTable::printHashTable() {
  for (int ii = 0; ii < nf_buckets_; ++ii) {
    for (auto node : hash_map_[ii]) {
      cout << "(" << node.key << ", " << node.value << ") ";
    }
    cout << endl;
  }
}

int HashTable::hashingFunction (string key) {
	long hashval = 0;
	for (int ii = 0; ii < key.length(); ii++) {
		hashval += key.at(ii);
	}
	return static_cast<int>(hashval % nf_buckets_);
}

void HashTable::insert (string key, string value) {
  int bucket_index = hashingFunction(key);
  struct node temp_node;
  temp_node.key = key;
  temp_node.value = value;
  // Doesn't matter if push front or back. Front saves computations.
  hash_map_[bucket_index].push_front(temp_node);
}

struct node * HashTable::findEntry(string key) {
  int bucket_index = hashingFunction(key);
  auto curr_list = hash_map_[bucket_index];
  for (auto it = curr_list.begin(); it != curr_list.end(); ++it) {
    if ((it->key).compare(key) == 0) {
      return &(*it);
    }
  }
  cout << "No entry found" << endl;
  return NULL;
}

void HashTable::removeEntry (string key) {
  int bucket_index = hashingFunction(key);
  auto curr_list = hash_map_[bucket_index];
  for (auto it = curr_list.begin(); it != curr_list.end(); ++it) {
    if ((it->key).compare(key) == 0) {
      curr_list.erase(it);
    }
  }
  cout << "No entry found to remove" << endl;
}
