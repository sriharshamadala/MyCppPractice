#include <stdio.h>
#include <string.h>

struct node
{
	int key;
	struct node* left;
	struct node* right;
	int color;
};

struct stack
{
	struct node* currNode;
	struct stack* next;
};

void printTreeBFS(struct node* head)
{
	struct stack* start = new struct stack[25];
	start->currNode = head;
	start->next = start+1;
	while ( start->next != 0)
	{
		start[1].currNode = head->left;
		start->next = start+1;
		printf("%d \n", start->currNode->key);
		start[2].currNode = head->right;
		(start+1)->next = start+2;
	
}


void printTree(struct node* head)
{
// DFS- preorder tree traversal to print
	printf("%d \n", head->key);
	if (head->left !=0)
		printTree(head->left);
	if (head->right !=0)
		printTree(head->right);
}

int distToRoot(struct node* head, int nodekey)
{
	int dist=0;
	struct node* temp=head;
	while(temp!=0)
	{
		if (nodekey == temp->key)
			break;
		else if (nodekey < temp->key)
		{
			temp = temp->left;
			dist++;
		}
		else
		{
			temp = temp->right;
			dist++;
		}
	}	
	return dist;
}
			
int LeastCommonAncestor( struct node* head, int node1, int node2)
{
	struct node* temp=head;
	int result;
	while(temp!=0)
	{
		if ((node1 < temp->key && node2>temp->key) || (node1>temp->key && node2<temp->key))
			return temp->key;
		else if (node1 < temp->key && node2<temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	printf("entered same node twice\n");
	return 0;
}

int distBtwnNodes(struct node* head, int node1, int node2)
{
	int d = distToRoot(head, node1);
//	printf("%d \n", d);
	d = d + distToRoot(head, node2);
//	printf("%d \n", d);
	d = d - 2*distToRoot(head, LeastCommonAncestor(head,node1,node2));
//	printf("%d \n", d);
	return d;
}

int main(int argc, char *argv[])
{
	int i;
	struct node* temp;
	struct node nodeArr[argc-1];
	struct node* head = nodeArr;
	for (i=1; i<argc; i++)
	{
		nodeArr[i-1].key = atoi(argv[i]);
		nodeArr[i-1].left = 0;
		nodeArr[i-1].right = 0;
		nodeArr[i-1].color = 0;
		temp=head;
		while (temp != 0 && i>1)
		{
			if (nodeArr[i-1].key <= temp->key)
			{
				if (temp->left == 0)
				{	
					temp->left = nodeArr+i-1;
					break;
				}
				else
					temp = temp->left;
			}
			else
			{
				if (temp->right == 0)
				{
					temp->right = nodeArr+i-1;
					break;
				}
				else
					temp = temp->right;
			}
		}
	}
	printTree(head);
	printf("dist to node 7: %d \n", distToRoot(head, 7));
	printf("LCA of 4,7: %d \n", LeastCommonAncestor(head, 4, 7));
	printf("distance between 21,1: %d \n", distBtwnNodes(head, 21, 1));
	return 0;
}
