#include <iostream>
#include <list>
#include <deque>

using namespace std;

template <typename T>
class Node {
  private:
    T key_;
    list<Node<T>*> children_;
    // Needed for graph traversal algorithms
    bool is_visited_;
  
  public:
    Node (T key) {
      key_ = key;
      is_visited_ = false;
    }
    T getKey () {
      return key_;
    }
    list<Node<T>*>& getChildren () {
      return children_;
    }
    bool isVisited () {
      return is_visited_;
    }
    void visited () {
      is_visited_ = true;
    }
};

template <typename T>
class Graph {
  private:
    list<Node<T>*> adjacency_list_;
  
  public:
    Graph (list<Node<T>*>& adjacency_list) {
      adjacency_list_ = adjacency_list;
    }
    
    void printAdjacencyList () {
      for (auto node : adjacency_list_) {
        cout << node->getKey() << ": ";
        auto children = node->getChildren();
        for (auto child : children) {
          cout << child->getKey() << " ";
        }
        cout << endl;
      }
    }

    void printDFS (Node<T> *root) {
      cout << root->getKey() << endl;
      root->visited();
      for (auto node : root->getChildren()) {
        if (!node->isVisited()) {
          printDFS(node);
        }
      }
    }

    void printBFS (Node<T> *root) {
      deque<Node<T>*> my_deque;
      my_deque.push_back(root);

      while (!my_deque.empty()) {
        Node<T> * temp_node = my_deque.front();
        my_deque.pop_front();
        if (!temp_node->isVisited()) {
          cout << temp_node->getKey() << endl;
          temp_node->visited();
        }
        for (auto node : temp_node->getChildren()) {
          if (!node->isVisited()) {
            my_deque.push_back(node);
          }
        }
      }
    }
};
