#include <gtest/gtest.h>
#include "graph.h"

using namespace std;

class GraphTest : public ::testing::Test {
  protected:
    list<Node<int>*> adjacency_list_;
    
    void SetUp () override {
      // create nodes
      Node<int> *node0 = new Node<int>(0);
      Node<int> *node1 = new Node<int>(1);
      Node<int> *node2 = new Node<int>(2);
      Node<int> *node3 = new Node<int>(3);
      Node<int> *node4 = new Node<int>(4);
      Node<int> *node5 = new Node<int>(5);
      Node<int> *node6 = new Node<int>(6);

      // add links
      node0->getChildren().push_front(node1);
      node0->getChildren().push_front(node3);
      node1->getChildren().push_front(node2);
      node2->getChildren().push_front(node0);
      node2->getChildren().push_front(node3);
      node3->getChildren().push_front(node2);
      node4->getChildren().push_front(node6);
      node5->getChildren().push_front(node4);
      node6->getChildren().push_front(node5);

      // populate the adjacency list
      adjacency_list_.push_back(node0);
      adjacency_list_.push_back(node1);
      adjacency_list_.push_back(node2);
      adjacency_list_.push_back(node3);
      adjacency_list_.push_back(node4);
      adjacency_list_.push_back(node5);
      adjacency_list_.push_back(node6);
    }

    void TearDown () override {
      for (auto node : adjacency_list_) {
        delete node;
      }
    }
};

TEST_F (GraphTest, printAdjacencyList) {
  Graph<int> my_graph(adjacency_list_);
  my_graph.printAdjacencyList();
}

TEST_F (GraphTest, printDFS) {
  Graph<int> my_graph(adjacency_list_);
  my_graph.printDFS(adjacency_list_.front());
}

TEST_F (GraphTest, printBFS) {
  Graph<int> my_graph(adjacency_list_);
  my_graph.printBFS(adjacency_list_.front());
}
