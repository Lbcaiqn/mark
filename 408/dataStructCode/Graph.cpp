#include<iostream>
#include<queue>
#include<stdlib.h>
using namespace std;
#define MAX_VERTEX 100
#define VEX 8;

int gData[8][8] =
{ 0,1,0,0,0,0,0,0,
1,0,1,0,0,0,0,0,
0,1,0,1,0,0,0,0,
0,0,1,0,1,1,0,0,

0,0,0,1,0,1,1,0,
0,0,0,1,1,0,1,1,
0,0,0,0,1,1,0,1,
0,0,0,0,0,1,1,0 };

//ÁÚ½Ó¾ØÕó
typedef struct GraphMartix
{
	int vexnum;
	char vertex[MAX_VERTEX];
	int edge[MAX_VERTEX][MAX_VERTEX];
}GraphMartix;

void creatGraphMartix(GraphMartix &G,int n)
{
	G.vexnum = n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			G.edge[i][j] = gData[i][j];
	for (int i = 0; i < n; i++)
	{
		G.vertex[i] = 'A'+i;
	}
}	

/*-------------------------------------±éÀúÁÚ½Ó¾ØÕó--------------------------------------------*/

void BFS(GraphMartix G,bool isVisit[],int n)
{
	queue<int> que;
	int temp;
	que.push(n);
	isVisit[n] = true;
	while (!que.empty())
	{
		temp = que.front();
		que.pop();
		cout << G.vertex[temp] << " ";
		
		for (int i = 0; i < 8; i++)
			if (G.edge[temp][i] == 1 && isVisit[i] == false)
			{
				que.push(i);
				isVisit[i] = true;
			}
		
	}

}

void DFS(GraphMartix G,bool isVisit[], int n)
{
	cout << G.vertex[n] << " ";
	isVisit[n] = true;
	for (int i = 0; i < 8; i++)
		if (G.edge[n][i] == 1 && isVisit[i] == false)
			DFS(G,isVisit,i);
}

void visitGraphMartix(GraphMartix G, int BFS_DFS,int beginVertex)
{
	bool isVisit[8] = { false };
	switch(BFS_DFS)
	{
	case 0:
		//BFS
		BFS(G, isVisit, beginVertex);
		for (int i = 0; i < 8; i++)
			if (isVisit[i] == false)
			{
				BFS(G, isVisit, i);
				i = 0;
			}
		break;
	case 1:
		//DFS
		DFS(G, isVisit, beginVertex);
		for (int i = 0; i < 8; i++)
			if (isVisit[i] == false)
			{
				DFS(G, isVisit, i);
				i = 0;
			}
		break;
	default:break;
	}
}
/*-----------------------------------------------------------------------------------------*/



int main()
{
	GraphMartix  G;
	creatGraphMartix(G, 8);
	
	visitGraphMartix(G, 0, 2);
	

	system("pause");
	return 0;
}