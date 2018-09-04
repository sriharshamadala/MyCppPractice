#include <iostream>
#include <queue>

using namespace std;

struct node {
	int key;
	struct node* left;
	struct node* right;
};

class BinarySearchTree {
  private:
    struct node *root;
  public:
    BinarySearchTree (struct node *root_node);
    void insertNode (struct node *new_node);
    void printLevelOrder ();
    void printInorder (struct node *curr_node);
    void printInorder ();
    int distToRoot(int search_key);
    int distBtwnNodes(int node1, int node2);
    int leastCommonAncestor (int node1, int node2);
};

BinarySearchTree::BinarySearchTree (struct node *root_node) {
  root = root_node;
}

void BinarySearchTree::printLevelOrder () {
  queue<struct node *> temp_queue;
  temp_queue.push(root);
  do {
    struct node *curr_node = temp_queue.front();
    temp_queue.pop();
    cout << curr_node->key << " ";
    if (curr_node->left) {
      temp_queue.push(curr_node->left);
    }
    if (curr_node->right) {
      temp_queue.push(curr_node->right);
    }
  } while (!temp_queue.empty());
  cout << endl;
}

void BinarySearchTree::printInorder () {
  printInorder(root);
}

void BinarySearchTree::printInorder (struct node *curr_node) {
  if (curr_node->left) {
    printInorder(curr_node->left);
  }
  cout << curr_node->key << " ";
  if (curr_node->right) {
    printInorder(curr_node->right);
  }
}

/*
 * distToRoot Based on the key figure out how far down the node is from the root.
 * @param[in] search_key desired key
 * @return dist returns the distance or -1 if no node exists.
 */
int BinarySearchTree::distToRoot(int search_key) {
	int dist = -1;
	struct node* temp_node = root;
	while (temp_node) {
		if (search_key == temp_node->key) {
      dist++;
			break;
    } else if (search_key < temp_node->key) {
			temp_node = temp_node->left;
			dist++;
		}	else {
			temp_node = temp_node->right;
			dist++;
		}
	}	
	return dist;
}

int BinarySearchTree::leastCommonAncestor (int node1, int node2) {
	struct node* temp_node = root;
	int result;
	while(temp_node) {
    if ((node1 < temp_node->key) && (node2 < temp_node->key)) {
      temp_node = temp_node->left;
    } else if ((node1 > temp_node->key) && (node2 > temp_node->key)) {
      temp_node = temp_node->right;
    } else {
      return temp_node->key;
    }
  }
	cout << "Did not find a common ancestor" << endl;
	return -1;
}

int BinarySearchTree::distBtwnNodes(int node1, int node2) {
	int dist_1 = distToRoot(node1);
	dist_1 += distToRoot(node2);
	dist_1 -= 2*distToRoot(leastCommonAncestor(node1, node2));
	return dist_1;
}

void BinarySearchTree::insertNode (struct node *new_node) {
  struct node *temp_node = root;
  while (temp_node) {
    if (new_node->key < temp_node->key) {
      if (temp_node->left) {
        temp_node = temp_node->left;
      } else {
        temp_node->left = new_node;
        break;
      }
    } else {
      if (temp_node->right) {
        temp_node = temp_node->right;
      } else {
        temp_node->right = new_node;
        break;
      }
    }
  }
}

int main(int argc, char *argv[])
{
	struct node nodeArr[argc - 1];

	for (int ii = 0; ii < argc - 1; ii++)
	{
		nodeArr[ii].key = atoi(argv[ii + 1]);
		nodeArr[ii].left = nullptr;
		nodeArr[ii].right = nullptr;
  }
  BinarySearchTree bst(nodeArr);

  for (int ii = 1; ii < argc - 1; ++ii) {
    bst.insertNode(nodeArr + ii);
  }
  cout << "Tree in inorder: " << endl;
	bst.printInorder();
  cout << "Tree in level order: " << endl;
	bst.printLevelOrder();

  /*
  cout << "dist of 7 from root: " <<  bst.distToRoot(7) << endl;
	cout << "LCA of 4,7: " << bst.leastCommonAncestor(4, 7) << endl;
	cout << "distance between 21,1: " << bst.distBtwnNodes(21, 1) << endl;
  */
	return 0;
}
