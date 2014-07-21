///Incomplete. use rand function rand()%N
#include <iostream>
using namespace std;

int numbMoves(int** pop, int x, int y)
{
	int count=0;
	int i,j;
	for(i=1; i<3; i++)
	{
		j = (2*i)%3;
		if ( x+i<8 )
		{
			if (y+j<8)
				count += (*(pop[x+i]+y+j) + 1)%2;
			if (y-j>0)
				count += (*(pop[x+i]+y-j) + 1)%2;
		}
		if (x-i>0)
		{
			if (y+j<8)
				count += (*(pop[x-i]+y+j) + 1)%2;
			if (y-j>0)
				count += (*(pop[x-i]+y-j) + 1)%2;
		}
	}
	return count;
}

int nextMove(int** pop, int x, int y, int* nextX, int* nextY)
{
	int tempx=0, tempy=0;
	int minMoves=8;
	int tempMoves[8]();
	int i,j;
	for(i=1; i<3; i++)
	{
		j = (2*i)%3;
		if ( x+i<8 )
		{
			if (y+j<8 && *(pop[x+i]+y+j)==0)
			{
				tempMoves[4*(i-1) + 0] = numbMoves(pop, x+i, y+j);
				if (tempMoves < minMoves)
				{
					minMoves = tempMoves;
					*nextX = x+i;
					*nextY = y+j;
				}
			}
			if (y-j>0 && *(pop[x+i]+y-j)==0)
			{
				tempMoves[4*(i-1) + 1] = numbMoves(pop, x+i, y-j);
				if (tempMoves < minMoves)
				{
					minMoves = tempMoves;
					*nextX = x+i;
					*nextY = y-j;
				}
			}
		}
		if (x-i>0)
		{
			if (y+j<8 && *(pop[x-i]+y+j)==0)
			{
				tempMoves[4*(i-1) + 2] = numbMoves(pop, x-i, y+j);
				if (tempMoves < minMoves)
				{
					minMoves = tempMoves;
					*nextX = x-i;
					*nextY = y+j;
				}
			}
			if (y-j>0 && *(pop[x-i]+y-j)==0)
			{
				tempMoves[4*(i-1) + 3] = numbMoves(pop, x-i, y-j);
				if (tempMoves < minMoves)
				{
					minMoves = tempMoves;
					*nextX = x-i;
					*nextY = y-j;
				}
			}
		}
	}
	*(pop[*nextX]+ *(nextY))=1;
	if (tempMoves==0)
		return 0;
	else
		return 1;
}


int main()
{
	int m=8, n=8;
// starting position 
	int x=3, y=7;
	int** pop = new int*[m];
	for (int i=0; i<m; i++)
		pop[i] = new int[n]();
	*(pop[x] + y)=1;
	int nextX=0, nextY=0;
	int flag =1;
	int count=0;
	while(flag==1)
	{
		count++;
		flag = nextMove(pop, x, y, &nextX, &nextY);
		cout << "(" << nextX << "," << nextY << ")" << endl;
		x = nextX;
		y = nextY;
	}
	cout << count << endl;
	return 0;
}
	
