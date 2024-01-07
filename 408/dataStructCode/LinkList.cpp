#include<iostream>
using namespace std;

//单链表结构
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

//初始化
bool initList(LNode* &L)     
{
	L = (LNode*)malloc(sizeof(LNode)); //申请一个头结点
	if (L == NULL) return false;		//	申请失败
	L->next = NULL;
	if(L != NULL) return true;
}

//头插法
void insertHead(LinkList &L, int a)
{
	LNode *node = (LNode*)malloc(sizeof(LNode));
	node->data = a;
	node->next = L->next;
	L->next = node;
}

//尾插法
void insertTail(LinkList &L,int a)
{
	LNode *p = L;
	LNode *q = (LNode*)malloc(sizeof(LNode));
	while (p->next != NULL)	p = p -> next;
	q->data = a;
	q->next = NULL;
	p->next = q;

}


//遍历链表
void printList(LinkList &L)
{
	LNode *p = L;
	while (p->next != NULL)
	{
		p = p->next;
		cout << p->data<<endl;
	}
	free(p);
}

int main()
{
	/*LinkList L=NULL;         //传递指针实参需要初始化
	if (initList(L))	     //传递LNode*也可以
	{
		for (int i = 0; i < 10; i++)
		{
			insertTail(L, i);
			cout << i;
		}
	}
	cout << endl;
	printList(L);*/
	
	LinkList L = NULL;
	initList(L);
	if (L == NULL) cout << "失败";
	else cout << "成功";

	system("pause");
	return 0;
}