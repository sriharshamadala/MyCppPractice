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
    int shortest_path_;    // For Dijkstra
    Node<T>* prev_node_;   // For Dijkstra
  
  public:
    Node (T key) {
      key_ = key;
      is_visited_ = false;
      prev_node_ = NULL;
      shortest_path_ = 0;
    }
    T getKey () {
      return key_;
    }
    int getShortestPath () {
      return shortest_path_;
    }
    void setShortestPath (int distance) {
      shortest_path_ = distance;
    }
    Node<T>* getPrevNode () {
      return prev_node_;
    }
    void setPrevNode (Node<T> *prev_node) {
      prev_node_ = prev_node;
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

// Needed for Dijkstra
template <typename T>
class MyCompare {
  public:
    bool operator() (Node<T> *node_l, Node<T> *node_r) {
      return (node_l->getShortestPath() > node_r->getShortestPath());
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
    
    void printEachNodeDistanceFromSource (Node<T> *source) {
      for (auto node : adjacency_list_) {
        cout << "Shortest distance from " << source->getKey() << " to " << node->getKey() << " is " << node->getShortestPath() << " via ";
        if (node->getPrevNode()) {
          cout << (node->getPrevNode())->getKey() << endl;
        } else {
          cout << endl;
        }
      }
    }

    // Prints the path and the total weight if path exists.
    void shortestPath (Node<T> *source, Node<T> *destination) {
      // Initialize all distances to infinity except the source.
      for (auto node : adjacency_list_) {
        if (node->getKey() == source->getKey()) {
          node->setShortestPath(0);
        } else {
          node->setShortestPath(INT_MAX);
        }
      }
     
      list<Node<T>*> remaining_list(adjacency_list_);

      while (!remaining_list.empty()) {
        // Since the distances changed, refresh the priority queue.
        // XXX There seems to be an efficient way to only push the node whose distance is updated and check for up-to-date distance when popping. Need to understand it.
        priority_queue<Node<T>*, vector<Node<T>*>, MyCompare<T>> remaining_pq(remaining_list.begin(), remaining_list.end());
        Node<T> *temp_node = remaining_pq.top();
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
      
      printEachNodeDistanceFromSource(source);
      cout << "Distance to destination: " << destination->getShortestPath() << endl;
      cout << "Path :" << endl;
      cout << destination->getKey() << " <- ";
      Node<T> *curr_node = destination;
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
};

#endif
