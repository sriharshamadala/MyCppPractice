//Working code for a touring problem to determine for how many participants the tournamnet can be fixed.
#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>
#include <queue>

//using namespace std;

struct par
{
	int id;
	char color;
	struct par * next;
};

int dfs(par * head, int np, int i)
{
	
	//int * queue = new int[2*np]();
	std::queue<int> q;
	par *temp1, *temp2;
	q.push(i);
	int qLen=1;
	while (qLen != 0)
	{
		temp1 = head+q.front()-1;
		temp2 = temp1;
		//temp1->color = 1;
		while (temp1->next != NULL)
		{
			if (temp1->color == 0)
			{
				q.push(temp1->id);
				qLen++;
				temp1->color=1;
			}
			temp1 = temp1->next;
		}
		temp2->color=2;
		q.pop();
		qLen--;
	}
	//Scan through each participant to see if color=2
	int j=0;
	for(j=0; j<np; j++)
	{
		if ((head+j)->color != 2)
			return 0;
	}
	return 1;
}

int numMatchFixes(par * head, int np)
{
	int i,j;
	par* temp1;
	int nmf=0;
	for(i=0; i<np; i++)
	{
		nmf = nmf+dfs(head, np, i+1);	
		//remove the colors from prev dfs
		for(j=0; j<np; j++)
		{	
			temp1 = head+j;
			while(temp1->next != NULL)
			{
				temp1->color = 0; 	
				temp1 = temp1->next;
			}
		}
	}
	return nmf;
}


int main()
{
        int t, i, j, k;
        int *p;			//an array to store no of participants for each test case.
        par **m;        
	int temp1, temp2;     
	par *temp3;
        std::cin >> t;
	p = new int[t];
	m = new par* [t];
        for (i=0; i<t; i++)	//Loop through each test case
        {
		std::cin >> p[i];
		m[i] = new par[p[i]];
		for (j=0; j<p[i]; j++)	//Loop through each line for participant j
		{
			(m[i]+j)->id = 0;
			(m[i]+j)->color = 0;
			(m[i]+j)->next = NULL;
		}
		for (j=0; j<p[i]; j++)	//Loop through each line for participant j
		{
			std::cin >> temp1;
			for (k=0; k<temp1; k++)	//Loop through each possible victors against j
			{
				std::cin >> temp2;
				temp3 = (m[i]+temp2-1);
				while (temp3->next != NULL)
					temp3 = temp3->next;
				temp3->id = j+1;
				temp3->next = new par;
				temp3->next->color = 0;
				temp3->next->next = NULL;
			}
		}
		// The adjacency list is populated. Now path traversal.
		std::cout << numMatchFixes(m[i], p[i]) << std::endl;	
	} 
					
        //int start_s = clock();
	return 0;
}
