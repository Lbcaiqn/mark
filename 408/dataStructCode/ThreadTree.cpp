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

//��������������
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

/*----------------------------------------------����������������---------------------------------------------------------------*/

void visitTree(BinTree T,int a)		//a==0/1/2/3,ǰ��/����/����/����
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

//�ǵݹ����,ջʵ��
void visitTreeStack(BinTree T,int a)		//a==0/1/2,����/����/����
{
	stack<TNode*> sta,sta2;				//���������Ҫ����һ��ջsta2
	TNode *p = T;
	switch(a)
	{
	case 0:
		while (p != NULL || !sta.empty())	//��p����ջ��ʱ���������
		{
			while (p != NULL)				//p�������ӣ�����p,p��������ջ
			{
				cout << p->data;
				sta.push(p);
				p = p->lchild;
			}
			if (!sta.empty())				//pû����������ջ����һЩû�з��ʵĽ��������Һ��ӣ��ȷ���p�Һ���
			{
				p = sta.top();
				sta.pop();
				p = p->rchild;
			}
		}
		break;
	case 1:
		while ( p!=NULL || !sta.empty())	//��p����ջ��ʱ���������
		{
			while (p != NULL)				//p�������ӣ�p��������ջ
			{
				sta.push(p);
				p = p->lchild;
			}
			if (!sta.empty())				//pû����������ջ����һЩû�з��ʵĽ�㣬����p
			{
				p = sta.top();
				cout << p->data;
				sta.pop();
				p = p->rchild;
			}
		}
		break;
	case 2:
		sta.push(p);				//����������ʣ�������ջ
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

/*--------------------------------------------------��������������----------------------------------------------------------*/

//������
void thread(BinTree T,TNode* &pre)
{
	if (T->lchild == NULL)					//������������ָ��ǰ��
	{
		T->lchild = pre;
		T->ltag = 1;
	}
	if (pre != NULL && pre->rchild == NULL)			//�Һ�����������ָ����
	{
		pre->rchild = T;
		pre->rtag = 1;
	}
	pre = T;
}

//����/����/�����������
void addThread(BinTree T, TNode* &pre, int a)
{
	switch (a)
	{
	case 0:
		if (T != NULL)
		{
			thread(T, pre);
			if (T->ltag == 0) addThread(T->lchild, pre, a);	//��ֹ�ջ�
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

//��������/����/��������������
void creatThreadTree(BinTree T,int a)		//a==0����,a==1����,a==2����
{
	TNode *pre = NULL;
	addThread(T, pre, a);
	if (pre->rchild == NULL) pre->rtag = 1;
}

/*--------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------������������ǰ������̺ͱ���---------------------------------------------------*/

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


//����/����/��������������������ݹ鷽����
void visitThreadTree(ThreadTree T, int a)	//a==0/1/2,����/����/����
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