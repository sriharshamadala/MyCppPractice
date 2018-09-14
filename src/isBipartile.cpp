#include <iostream>
#include <queue>
#define N 4

using namespace std;
bool isBipartile(int G[][N], int src)
{
	int color[N] = {0};
	int currcolor=1;
	color[src]=1;
	queue<int> q;
	q.push(src);

	int temp;
	while(!q.empty())
	{
		temp = q.front();
		currcolor = color[temp]*(-1);
		for(int i=0; i<N; i++)
		{
			if (G[temp][i]==1 && color[i] == 0)
			{				
				q.push(i);
				if(color[i]==0 || color[i]==currcolor)
					color[i] = currcolor;
				else
					return false;
			}
		}
		q.pop();
	}
	return true;
}


int main()
{
	int G[][N] = {{0,1,0,1}, {1,0,1,0}, {0,1,0,1}, {1,0,1,0}};
	isBipartile(G,0) ? cout << "Yes \n" : cout << "No\n";
	return 0;
}
