#include <iostream>
#define N 7
using namespace std;

int bfs[N] = {20, 8, 22, 4, 12, 10, 14};

struct node
{
	int key;
	struct node* left;
	struct node* right;
};

void printTree(struct node* head)
{
	if( head->left != 0)
		printTree(head->left);
	cout << head->key << endl;
	if( head->right != 0)
		printTree( head->right);
	return;
}

struct node*  create(int* in, int size, int currLevel)
{
	if (size==1)
	{
		struct node temp;
		temp.key = in[0];
		temp.left = 0;
		temp.right = 0;
		return &temp;
	}
	else
	{
		int leftSize, rightSize;
		int left[N];
		int right[N];
		split(in, size, left, leftSize, right, rightSize, currLevel);
		currLevel++;
		head->left = create(left, leftSize, currLevel);
		currLevel++;
		head->right = create(right, rightSize, currLevel);
		currLevel++;
	}


}

void split( int* in, int inSize, int* left, int* leftSize, int* right, int* rightSize, int currLevel)
{
	int* left = int* in;
	for(int i=0; i<inSize; i++)
	{
		if (in[i]==bfs[currLevel])
		{
			*leftSize = i;
			right = in+i+1;
			*rightSize = inSize-leftSize-1;
			return;
		}
	}
	cout << "Invalid traversal inputs\n";
}
		

int main()
{
	int in[N] = {4, 8, 10,12, 14, 20, 22};
	struct node* head;
	head->key = bfs[0];
	head->left = 0;
	head->right = 0;
	int* leftSize, rightSize;
	int left[N];
	int right[N];
	int currLevel=0;
	split(in, N, left, leftSize, right, rightSize, currLevel);
	currLevel++;
	head->left = create(left, leftSize, currLevel);
	currLevel++;
	head->right = create(right, rightSize, currLevel);
	printTree(head);
	return 0;
}
