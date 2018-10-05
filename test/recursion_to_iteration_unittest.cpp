#include <gtest/gtest.h>
#include "recursion_to_iteration.h"
#include "graph.h"

using namespace std;

class RecursionToIterationTest : public ::testing::Test {
  protected:
    list<Node<int>*> adjacency_list_1_;
    
    void SetUp () override {
      // Simple graph.
      // create nodes
      Node<int> *node0 = new Node<int>(0);
      Node<int> *node1 = new Node<int>(1);
      Node<int> *node2 = new Node<int>(2);
      Node<int> *node3 = new Node<int>(3);
      Node<int> *node4 = new Node<int>(4);
      Node<int> *node5 = new Node<int>(5);
      Node<int> *node6 = new Node<int>(6);

      // add links
      node0->getChildren().push_front(make_pair(node1, 1));
      node0->getChildren().push_front(make_pair(node3, 1));
      node1->getChildren().push_front(make_pair(node2, 1));
      node2->getChildren().push_front(make_pair(node3, 1));
      node4->getChildren().push_front(make_pair(node6, 1));
      node5->getChildren().push_front(make_pair(node4, 1));

      // populate the adjacency list
      adjacency_list_1_.push_back(node0);
      adjacency_list_1_.push_back(node1);
      adjacency_list_1_.push_back(node2);
      adjacency_list_1_.push_back(node3);
      adjacency_list_1_.push_back(node4);
      adjacency_list_1_.push_back(node5);
      adjacency_list_1_.push_back(node6);
    }

    void TearDown () override {
      for (auto node : adjacency_list_1_) {
        delete node;
      }
    }
};

TEST_F (RecursionToIterationTest, calculateDepth) {
  Graph<Node<int>> my_graph;
  printAdjacencyList<Node<int>>(adjacency_list_1_);
  Recursion<Node<int>*> maxDepth;
  EXPECT_EQ(3, maxDepth(adjacency_list_1_.front()));
}
