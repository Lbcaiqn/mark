#include<iostream>
using namespace std;

//������ṹ
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode,*LinkList;

//��ʼ��
bool initList(LNode* &L)     
{
	L = (LNode*)malloc(sizeof(LNode)); //����һ��ͷ���
	if (L == NULL) return false;		//	����ʧ��
	L->next = NULL;
	if(L != NULL) return true;
}

//ͷ�巨
void insertHead(LinkList &L, int a)
{
	LNode *node = (LNode*)malloc(sizeof(LNode));
	node->data = a;
	node->next = L->next;
	L->next = node;
}

//β�巨
void insertTail(LinkList &L,int a)
{
	LNode *p = L;
	LNode *q = (LNode*)malloc(sizeof(LNode));
	while (p->next != NULL)	p = p -> next;
	q->data = a;
	q->next = NULL;
	p->next = q;

}


//��������
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
	/*LinkList L=NULL;         //����ָ��ʵ����Ҫ��ʼ��
	if (initList(L))	     //����LNode*Ҳ����
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
	if (L == NULL) cout << "ʧ��";
	else cout << "�ɹ�";

	system("pause");
	return 0;
}