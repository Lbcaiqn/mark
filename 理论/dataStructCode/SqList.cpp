#include<iostream>
#include<stdlib.h>
using namespace std;

//˳���ṹ
typedef struct
{
	int *data;
	int maxSize = 0;
	int length = 0;
}SeqList;

//��ʼ��
void initSeq(SeqList &seq,int len)
{
	seq.data = (int*)malloc(sizeof(int)*len);
	seq.maxSize = len;
}

//��̬�����ڴ�ռ�
void addSeq(SeqList &seq, int len)
{
	int *p = seq.data;
	seq.data = (int*)malloc(sizeof(int)*(seq.maxSize + len));
	for (int i = 0; i < seq.maxSize; i++)
	{
		seq.data[i] = p[i];
	}
	free(p);
	seq.maxSize = seq.maxSize + len;
}

int main()
{
	SeqList L;
	initSeq(L, 5);
	for (int i = 0; i < 10; i++)
	{
		if (i >= L.maxSize) addSeq(L, 5);
		
		L.data[i] = i;
		L.length++;
		cout << L.data[i] << endl;
	}
	
	system("pause");
	return 0;
}