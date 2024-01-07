#include<iostream>
#include<queue>
#include<stack>
#include<stdlib.h>
using namespace std;

typedef struct TNode
{
	int data;
	int ltag, rtag;
	struct TNode *lchild;
	struct TNode *rchild;
}TNode,*BinTree,*ThreadTree;

TNode* newTNode(int a)
{
	TNode *T = (TNode*)malloc(sizeof(TNode));
	T->data = a;
	T->ltag = 0;
	T->rtag = 0;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

//创建二叉排序树
void creatSortBinTree(BinTree &T, int i)
{
	if (i < T->data)
	{
		if (T->lchild != NULL) creatSortBinTree(T->lchild, i);
		else                   T->lchild = newTNode(i);
	}
	else
	{
		if (T->rchild != NULL) creatSortBinTree(T->rchild, i);
		else                   T->rchild = newTNode(i);
	}
}

/*----------------------------------------------遍历非线索二叉树---------------------------------------------------------------*/

void visitTree(BinTree T,int a)		//a==0/1/2/3,前序/中序/后序/层序
{
	switch(a)
	{
	case 0:
		if (T != NULL)
		{
			cout << T->data;
			visitTree(T->lchild,a);
			visitTree(T->rchild,a);
		}
		break;
	case 1:
		if (T != NULL)
		{
			visitTree(T->lchild, a);
			cout << T->data;
			visitTree(T->rchild, a);
		}
		break;
	case 2:
		if (T != NULL)
		{
			visitTree(T->lchild, a);
			visitTree(T->rchild, a);
			cout << T->data;
		}
	default:break;
	}
	if (a == 3)
	{
		queue<TNode*> que;
		TNode *p = NULL;
		que.push(T);
		while (!que.empty())
		{
			p = que.front();
			cout << p->data;
			que.pop();
			if (p->lchild != NULL) que.push(p->lchild);
			if (p->rchild != NULL) que.push(p->rchild);
		}
	}
}

//非递归遍历,栈实现
void visitTreeStack(BinTree T,int a)		//a==0/1/2,先序/中序/后序
{
	stack<TNode*> sta,sta2;				//后序遍历需要多用一个栈sta2
	TNode *p = T;
	switch(a)
	{
	case 0:
		while (p != NULL || !sta.empty())	//当p空且栈空时，遍历完成
		{
			while (p != NULL)				//p还有左孩子，访问p,p的左孩子入栈
			{
				cout << p->data;
				sta.push(p);
				p = p->lchild;
			}
			if (!sta.empty())				//p没有左孩子了且栈还有一些没有访问的结点可能有右孩子，先访问p右孩子
			{
				p = sta.top();
				sta.pop();
				p = p->rchild;
			}
		}
		break;
	case 1:
		while ( p!=NULL || !sta.empty())	//当p空且栈空时，遍历完成
		{
			while (p != NULL)				//p还有左孩子，p的左孩子入栈
			{
				sta.push(p);
				p = p->lchild;
			}
			if (!sta.empty())				//p没有左孩子了且栈还有一些没有访问的结点，访问p
			{
				p = sta.top();
				cout << p->data;
				sta.pop();
				p = p->rchild;
			}
		}
		break;
	case 2:
		sta.push(p);				//根结点最后访问，最先入栈
		while (!sta.empty())
		{
			p = sta.top();
			sta2.push(p);
			sta.pop();
			if (p->lchild != NULL) sta.push(p->lchild);
			if (p->rchild != NULL) sta.push(p->rchild);
		}
		while (!sta2.empty())
		{
			p = sta2.top();
			cout << p->data;
			sta2.pop();
		}
		break;
	default:break;
	}
}


/*------------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------创建线索二叉树----------------------------------------------------------*/

//线索化
void thread(BinTree T,TNode* &pre)
{
	if (T->lchild == NULL)					//左孩子线索化，指向前驱
	{
		T->lchild = pre;
		T->ltag = 1;
	}
	if (pre != NULL && pre->rchild == NULL)			//右孩子线索化，指向后继
	{
		pre->rchild = T;
		pre->rtag = 1;
	}
	pre = T;
}

//先序/中序/后序添加线索
void addThread(BinTree T, TNode* &pre, int a)
{
	switch (a)
	{
	case 0:
		if (T != NULL)
		{
			thread(T, pre);
			if (T->ltag == 0) addThread(T->lchild, pre, a);	//防止闭环
			addThread(T->rchild, pre, a);
		}
		break;
	case 1:
		if (T != NULL)
		{
			addThread(T->lchild, pre, a);
			thread(T, pre);
			addThread(T->rchild, pre, a);
		}
		break;
	case 2:
		if (T != NULL)
		{
			addThread(T->lchild, pre, a);
			addThread(T->rchild, pre, a);
			thread(T, pre);
		}
		break;
	default: break;
	}
}

//创建先序/中序/后序线索二叉树
void creatThreadTree(BinTree T,int a)		//a==0先序,a==1中序,a==2后序
{
	TNode *pre = NULL;
	addThread(T, pre, a);
	if (pre->rchild == NULL) pre->rtag = 1;
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------线索二叉树找前驱，后继和遍历---------------------------------------------------*/

TNode* firstTNode(TNode* T)
{
	while (T->ltag==0) T = T->lchild;
	return T;
}
TNode* lastTNode(TNode* T)
{
	while (T->rtag == 0) T = T->rchild;
	return T;
}

TNode* frontTNode(TNode* T)
{
	if (T->ltag == 1) return T->lchild;
	else			  return lastTNode(T->lchild);
}

TNode* behindTNode(TNode* T)
{
	if (T->rtag == 1) return T->rchild;
	else			  return firstTNode(T->rchild);
}

void visitThreadTree2(ThreadTree T)
{
	for (TNode* i = firstTNode(T); i != NULL; i = behindTNode(i)) cout << i->data;
}


//先序/中序/后序遍历线索二叉树（递归方法）
void visitThreadTree(ThreadTree T, int a)	//a==0/1/2,先序/中序/后序
{
	switch (a)
	{
	case 0:
		if (T != NULL)
		{
			cout << T->data;
			if (T->ltag == 0) visitThreadTree(T->lchild, a);
			if (T->rtag == 0) visitThreadTree(T->rchild, a);
		}
		break;
	case 1:
		if (T != NULL)
		{
			if (T->ltag == 0) visitThreadTree(T->lchild, a);
			cout << T->data;
			if (T->rtag == 0) visitThreadTree(T->rchild, a);
		}break;
	case 2:
		if (T != NULL)
		{
			if (T->ltag == 0) visitThreadTree(T->lchild, a);
			if (T->rtag == 0) visitThreadTree(T->rchild, a);
			cout << T->data;
		}
		break;
	default:break;
	}
}

/*----------------------------------------------------------------------------------------------------------------------*/

int main()
{
	BinTree tree=NULL;
	tree = newTNode(5);
	for (int i = 0; i <= 9; i++)
	{
		creatSortBinTree(tree, i);
	}
	visitTree(tree,0);
	cout << endl;
	//creatThreadTree(tree,1);

	visitTreeStack(tree,0);
	

	system("pause");
	return 0;
}