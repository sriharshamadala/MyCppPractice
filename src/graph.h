#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <deque>      // For BFS
#include <utility>    // for std::make_pair
#include <climits>    // For INT_MAX
#include <queue>      // For priority_queue
#include <vector>     // For dijkstra
#include <functional> // for std::function<>

using namespace std;

template <typename T>
class Node {
  private:
    T key_;
    // Each edge has a destination and a weight.
    list<pair<Node<T>*, int>> children_;
    
    // Augments
    bool is_visited_;      // Needed for graph traversal
  
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
class DijkstraNode : public Node<T> {
  private:
    T key_;
    // Each edge has a destination and a weight.
    list<pair<DijkstraNode<T>*, int>> children_;

    // Augments
    int shortest_path_;
    DijkstraNode<T>* prev_node_;

  public:
    DijkstraNode (T key) : Node<T>(key) {
      prev_node_ = NULL;
      shortest_path_ = 0;
    }
    int getShortestPath () {
      return shortest_path_;
    }
    void setShortestPath (int distance) {
      shortest_path_ = distance;
    }
    DijkstraNode<T>* getPrevNode () {
      return prev_node_;
    }
    void setPrevNode (DijkstraNode<T> *prev_node) {
      prev_node_ = prev_node;
    }
    list<pair<DijkstraNode<T>*, int>>& getChildren () {
      return children_;
    }
};

template <typename T>
class Graph {
  private:
    list<T*> adjacency_list_;
  
  public:
    Graph (list<T*>& adjacency_list) {
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

    void printDFS (T *root) {
      cout << root->getKey() << endl;
      root->visited();
      auto temp_pair_list = root->getChildren();
      for (auto temp_pair : temp_pair_list) {
        if (!((temp_pair.first)->isVisited())) {
          printDFS(temp_pair.first);
        }
      }
    }

    void printBFS (T *root) {
      deque<T*> my_deque;
      my_deque.push_back(root);
      root->visited();

      while (!my_deque.empty()) {
        T * temp_node = my_deque.front();
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

// Needed for Dijkstra
template <typename T>
class MyCompare {
  public:
    bool operator() (T *node_l, T *node_r) {
      return (node_l->getShortestPath() > node_r->getShortestPath());
    }
};

template<typename T>
void printEachNodeDistanceFromSource (DijkstraNode<T> *source, list<DijkstraNode<T>*>& adjacency_list) {
  for (auto node : adjacency_list) {
    cout << "Shortest distance from " << source->getKey() << " to " << node->getKey() << " is " << node->getShortestPath() << " via ";
    if (node->getPrevNode()) {
      cout << (node->getPrevNode())->getKey() << endl;
    } else {
      cout << endl;
    }
  }
}

template<typename T>
// Prints the path and the total weight if path exists.
void shortestPath (DijkstraNode<T> *source, DijkstraNode<T> *destination, list<DijkstraNode<T>*>adjacency_list) {
  // Initialize all distances to infinity except the source.
  for (auto node : adjacency_list) {
    if (node->getKey() == source->getKey()) {
      node->setShortestPath(0);
    } else {
      node->setShortestPath(INT_MAX);
    }
  }
 
  list<DijkstraNode<T>*> remaining_list(adjacency_list);

  while (!remaining_list.empty()) {
    // Since the distances changed, refresh the priority queue.
    // XXX There seems to be an efficient way to only push the node whose distance is updated and check for up-to-date distance when popping. Need to understand it.
    priority_queue<DijkstraNode<T>*, vector<DijkstraNode<T>*>, MyCompare<DijkstraNode<T>>> remaining_pq(remaining_list.begin(), remaining_list.end());
    DijkstraNode<T> *temp_node = remaining_pq.top();
    remaining_pq.pop();
    remaining_list.remove(temp_node);
    // Update distance to all the children.
    for (auto temp_pair : temp_node->getChildren()) {
      auto child_node = temp_pair.first;
      int curr_shortest_path = child_node->getShortestPath();
      int possible_shortest_path = temp_pair.second + temp_node->getShortestPath();
      if (curr_shortest_path > possible_shortest_path) {
        child_node->setShortestPath(possible_shortest_path);
        child_node->setPrevNode(temp_node);
      }
    }
  }
  
  printEachNodeDistanceFromSource(source, adjacency_list);
  cout << "Distance to destination: " << destination->getShortestPath() << endl;
  cout << "Path :" << endl;
  cout << destination->getKey() << " <- ";
  DijkstraNode<T> *curr_node = destination;
  do {
    auto temp_node = curr_node->getPrevNode();
    if (temp_node) {
      cout << temp_node->getKey() << " <- ";
      curr_node = temp_node;
    } else {
      break;
    }
  } while (curr_node != source);
  cout << endl;
}
#endif
