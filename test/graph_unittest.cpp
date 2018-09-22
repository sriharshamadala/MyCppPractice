#include <gtest/gtest.h>
#include "graph.h"

using namespace std;

class GraphTest : public ::testing::Test {
  protected:
    list<Node<int>*> adjacency_list__1_;
    list<Node<char>*> adjacency_list__2_;
    
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
      node2->getChildren().push_front(make_pair(node0, 1));
      node2->getChildren().push_front(make_pair(node3, 1));
      node3->getChildren().push_front(make_pair(node2, 1));
      node4->getChildren().push_front(make_pair(node6, 1));
      node5->getChildren().push_front(make_pair(node4, 1));
      node6->getChildren().push_front(make_pair(node5, 1));

      // populate the adjacency list
      adjacency_list__1_.push_back(node0);
      adjacency_list__1_.push_back(node1);
      adjacency_list__1_.push_back(node2);
      adjacency_list__1_.push_back(node3);
      adjacency_list__1_.push_back(node4);
      adjacency_list__1_.push_back(node5);
      adjacency_list__1_.push_back(node6);

      // Bigger graph
      // create nodes
      Node<char> *nodea = new Node<char>('a');
      Node<char> *nodeb = new Node<char>('b');
      Node<char> *nodec = new Node<char>('c');
      Node<char> *noded = new Node<char>('d');
      Node<char> *nodee = new Node<char>('e');
      Node<char> *nodef = new Node<char>('f');
      Node<char> *nodeg = new Node<char>('g');
      Node<char> *nodeh = new Node<char>('h');
      Node<char> *nodei = new Node<char>('i');

      // add links
      nodea->getChildren().push_front(make_pair(nodeb, 5));
      nodea->getChildren().push_front(make_pair(nodec, 3));
      nodea->getChildren().push_front(make_pair(nodee, 2));
      nodeb->getChildren().push_front(make_pair(noded, 2));
      nodec->getChildren().push_front(make_pair(nodeb, 1));
      nodec->getChildren().push_front(make_pair(noded, 1));
      noded->getChildren().push_front(make_pair(nodea, 1));
      noded->getChildren().push_front(make_pair(nodeg, 2));
      noded->getChildren().push_front(make_pair(nodeh, 1));
      nodee->getChildren().push_front(make_pair(nodea, 1));
      nodee->getChildren().push_front(make_pair(nodeh, 4));
      nodee->getChildren().push_front(make_pair(nodei, 7));
      nodef->getChildren().push_front(make_pair(nodeb, 3));
      nodef->getChildren().push_front(make_pair(nodeg, 1));
      nodeg->getChildren().push_front(make_pair(nodec, 3));
      nodeg->getChildren().push_front(make_pair(nodei, 2));
      nodeh->getChildren().push_front(make_pair(nodeg, 2));
      nodeh->getChildren().push_front(make_pair(nodef, 2));
      nodeh->getChildren().push_front(make_pair(nodec, 2));
      
      // populate the adjacency list
      adjacency_list__2_.push_back(nodea);
      adjacency_list__2_.push_back(nodeb);
      adjacency_list__2_.push_back(nodec);
      adjacency_list__2_.push_back(noded);
      adjacency_list__2_.push_back(nodee);
      adjacency_list__2_.push_back(nodef);
      adjacency_list__2_.push_back(nodeg);
      adjacency_list__2_.push_back(nodeh);
      adjacency_list__2_.push_back(nodei);
    }

    void TearDown () override {
      for (auto node : adjacency_list__1_) {
        delete node;
      }
      for (auto node : adjacency_list__2_) {
        delete node;
      }
    }
};

TEST_F (GraphTest, printAdjacencyList) {
  Graph<char> my_graph(adjacency_list__2_);
  my_graph.printAdjacencyList();
}

TEST_F (GraphTest, printDFS) {
  Graph<char> my_graph(adjacency_list__2_);
  my_graph.printDFS(adjacency_list__2_.front());
}

TEST_F (GraphTest, printBFS) {
  Graph<char> my_graph(adjacency_list__2_);
  my_graph.printBFS(adjacency_list__2_.front());
}

TEST_F (GraphTest, dijkstra) {
  Graph<char> my_graph(adjacency_list__2_);
  my_graph.shortestPath(adjacency_list__2_.front(), adjacency_list__2_.back());
  auto it = adjacency_list__2_.begin();
  EXPECT_EQ((*it)->getShortestPath(), 0);
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 4);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'c');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 3);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'a');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 4);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'c');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 2);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'a');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 7);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'h');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 6);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'd');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 5);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'd');
  it++;
  EXPECT_EQ((*it)->getShortestPath(), 8);
  EXPECT_EQ((*it)->getPrevNode()->getKey(), 'g');
  it++;
}
