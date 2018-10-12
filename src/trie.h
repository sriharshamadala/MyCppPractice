#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include "graph.h"
#include <string>

using namespace std;

struct TrieReturnValidity {
  UnweightedNode<char>* node;
  bool flag;
  TrieReturnValidity () {
    node = NULL;
    flag = false;
  }
};

/*
 * XXX Special nodes:
 *     1. Root node: key = ' '
 *     2. Terminal node: key = '*'
 */
class Trie : public UnweightedGraph<char> {
  private:
    UnweightedNode<char>* root_;
  
  public:
    Trie () {
      root_ = new UnweightedNode<char>(' ');
    }
    UnweightedNode<char>* getRoot () {
      return root_;
    }

    /*
     * Attempts to insert to 
     * 
     * @param[in] word Word to be inserted.
     * @return Whether the insert operation is successful. This oper fails when the word to be inserted is already present in the trie.
     */
    bool insert (string word) {
      bool is_success = true;
      size_t index = 0;
      UnweightedNode<char>* curr_node = root_;

      while (index < word.length()) {
        // Find the prefix that already exists in the Trie.
        auto children = curr_node->getChildren();
        bool found = false;
        for (auto child : children) {
          if (child->getKey() == word[index]) {
            found = true;
            curr_node = child;
            break;
          }
        }

        if (found) {
          index++;
        } else {
          // Prefix search done. Break.
          break;
        }
      }
      
      if (index >= word.length()) {
        // Already found the whole word.
        is_success = false;
      } else {
        // Insert the rest of the word here.
        while (index < word.length()) {
          UnweightedNode<char> * new_node = new UnweightedNode<char>(word[index]);
          curr_node->getChildren().push_back(new_node);
          index++;
          curr_node = new_node;
        }

        // Now insert the terminal node.
        UnweightedNode<char> * new_node = new UnweightedNode<char>('*');
        curr_node->getChildren().push_back(new_node);
      }

      return is_success;
    }

    bool wordExists (string word) {
      TrieReturnValidity ret_val = prefixExists(word);
      if (ret_val.flag) {
        // Need to find the terminal node as well. Else the word only exists as a prefix.
        auto children = (ret_val.node)->getChildren();
        for (auto child : children) {
          if (child->getKey() == '*') {
            // Found terminal node, hence the word exists.
            return true;
          }
        }
        // Did not find the terminal node.
        return false;
      } else {
        return false;
      }
    }

    /*
     * If prefix exists, return true and also the last node.
     * The last node is necessary for other algorithms.
     */
    TrieReturnValidity prefixExists (string prefix) {
      size_t index = 0;
      UnweightedNode<char>* curr_node = root_;
      TrieReturnValidity ret_val;

      while (index < prefix.length()) {
        // Find the prefix that already exists in the Trie.
        auto children = curr_node->getChildren();
        bool found = false;
        for (auto child : children) {
          if (child->getKey() == prefix[index]) {
            found = true;
            curr_node = child;
            break;
          }
        }
        if (found) {
          index++;
        } else {
          ret_val.flag = false;
          return ret_val;
        }
      }
      ret_val.flag = true;
      ret_val.node = curr_node;
      return ret_val;
    }
};

#endif
