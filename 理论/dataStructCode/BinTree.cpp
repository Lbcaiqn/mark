#include<iostream>
#include<stdlib.h>
#include<queue>
using namespace std;

typedef struct BinTree
{
	int data;
	struct BinTree *leftChild;
	struct BinTree *rightChild;
}BinTree;

void initBinTree(BinTree* &TNode,int i)
{
	TNode = (BinTree*)malloc(sizeof(BinTree));
	cout << TNode<<endl;
}

void sortBinTree(BinTree *T,int i)
{
	if (i < T->data)
	{
		if(T->leftChild!=NULL) sortBinTree(T->leftChild, i);
		else
		{
			BinTree *TNode = (BinTree*)malloc(sizeof(BinTree));
			TNode->data = i;
			TNode->leftChild = NULL;
			TNode->rightChild = NULL;
			T->leftChild = TNode;
			
			return;
		}
	}
	else
	{
		if (T->rightChild != NULL) sortBinTree(T->rightChild, i);
		else
		{
			BinTree *TNode = (BinTree*)malloc(sizeof(BinTree));
			TNode->data = i;
			TNode->leftChild = NULL;
			TNode->rightChild = NULL;
			T->rightChild = TNode;
			
			return;
		}
	}
}

void midvisit(BinTree *T)
{
	if (T == NULL) return;
	midvisit(T->leftChild);
	cout << T->data;
	midvisit(T->rightChild);
}

void frontvisit(BinTree *T)
{
	if (T == NULL) return;
	cout << T->data;
	frontvisit(T->leftChild);
	frontvisit(T->rightChild);
}

void behindvisit(BinTree *T)
{
	if (T == NULL) return;
	behindvisit(T->leftChild);
	behindvisit(T->rightChild);
	cout << T->data;
}

void func(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main()
{
	/*BinTree *TNode;
	TNode = (BinTree*)malloc(sizeof(BinTree));
	TNode->data = 5;
	TNode->leftChild = NULL;
	TNode->rightChild = NULL;

	for (int i = 0; i <= 9; i++)
	{
		sortBinTree(TNode, i);
	}
	
	midvisit(TNode);
	cout << endl;
	frontvisit(TNode);
	cout << endl;
	behindvisit(TNode);
	cout << endl;*/

	BinTree *t = NULL;
	initBinTree(t, 5);
	cout << t<<endl;
	if (t == NULL) cout << "Ê§°Ü";
	else cout << "³É¹¦";
	cout << endl;

	int a = 2, b = 8;
	func(&a, &b);
	cout << a << b << endl;

	system("pause");
	return 0;
}