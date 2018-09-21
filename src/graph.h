#include <iostream>
#include <list>
#include <deque>      // For BFS
#include <utility>    // for std::make_pair

using namespace std;

template <typename T>
class Node {
  private:
    T key_;
    // Each edge has a destination and a weight.
    list<pair<Node<T>*, int>> children_;
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
    list<pair<Node<T>*, int>>& getChildren () {
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
        auto temp_pair_list = node->getChildren();
        for (auto temp_pair : temp_pair_list) {
          cout << (temp_pair.first)->getKey() << " ";
        }
        cout << endl;
      }
    }

    void printDFS (Node<T> *root) {
      cout << root->getKey() << endl;
      root->visited();
      auto temp_pair_list = root->getChildren();
      for (auto temp_pair : temp_pair_list) {
        if (!((temp_pair.first)->isVisited())) {
          printDFS(temp_pair.first);
        }
      }
    }

    void printBFS (Node<T> *root) {
      deque<Node<T>*> my_deque;
      my_deque.push_back(root);
      root->visited();

      while (!my_deque.empty()) {
        Node<T> * temp_node = my_deque.front();
        my_deque.pop_front();
        cout << temp_node->getKey() << endl;
        
        auto temp_pair_list = temp_node->getChildren();
        for (auto temp_pair : temp_pair_list) {
          if (!((temp_pair.first)->isVisited())) {
            my_deque.push_back(temp_pair.first);
            temp_pair.first->visited();
          }
        }
      }
    }
};
