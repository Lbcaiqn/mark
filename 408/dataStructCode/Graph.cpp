
/*-------------------------------------�����ڽӾ���--------------------------------------------*/

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