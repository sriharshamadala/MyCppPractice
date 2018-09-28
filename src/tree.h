#include <iostream>
#include <queue>      // For BFS

using namespace std;

// Example of a node with arbitrary fanout.
// This node can be augmented as needed.
struct Node {
  int key;
  struct Node * children;
  int nf_children;
};

template <typename T>
class Tree {
  private:
    T *root_;
  public:
    Tree (T *root_node) {
      root_ = root_node;
    }

    void assignRoot (T * root) {
      root_ = root;
    }

    T * getRoot () {
      return root_;
    }

    // Each of the traversal algorithm take a function pointer
    // that allows us to do different types of operations on each
    // node as we traverse. eg, print, modify node properties...
    void levelOrder (void (*operateOnNode)(T *)) {
      queue<T *> temp_queue;
      temp_queue.push(root_);
      do {
        T *curr_node = temp_queue.front();
        temp_queue.pop();
        operateOnNode(curr_node);
        for (int ii = 0; ii < curr_node->nf_children; ++ii) {
          temp_queue.push(curr_node->children[ii]);
        }
      } while (!temp_queue.empty());
    }

    void inorder (T *curr_node, void (*operateOnNode)(T *)) {
      operateOnNode(curr_node);
      // Visit all the children.
      for (int ii = 0; ii < curr_node->nf_children; ++ii) {
        inorder(&curr_node->children[ii], operateOnNode);
      }
    }

    void inorder (void (*operateOnNode)(T *)) {
      inorder(root_, operateOnNode);
    }
};
