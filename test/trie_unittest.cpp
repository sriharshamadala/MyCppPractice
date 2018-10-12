#include <gtest/gtest.h>
#include "trie.h"

TEST (TrieTest, InsertAndPrint) {
  Trie my_trie;
  my_trie.insert("man");
  my_trie.insert("many");

  // Since the word already exists.
  EXPECT_FALSE(my_trie.insert("man"));

  my_trie.printDFS(my_trie.getRoot());

  EXPECT_TRUE(my_trie.wordExists("man"));
  EXPECT_TRUE(my_trie.wordExists("many"));
  EXPECT_FALSE(my_trie.wordExists("ma"));
  EXPECT_FALSE(my_trie.wordExists("mandarin"));
  EXPECT_FALSE(my_trie.wordExists("manys"));
}
