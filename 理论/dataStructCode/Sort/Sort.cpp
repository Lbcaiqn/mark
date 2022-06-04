#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

/*---------------------------------------------���ֽ�������--------------------------------------------------------*/
void barbleSort(int a[],int n)
{
	bool flag = false;					//������ĳ��ʱ����ֱ�ӽ���
	for (int i = 0; i < n - 1; i++)		//��������
	{
		flag = false;
		for (int j = n - 1; j > i; j--)	//ð��
			if (a[j - 1] > a[j])
			{
				swap(a[j - 1],a[j]);
				flag = true;
			}
		if (flag == false)	break;
	}
}


int partition(int a[], int low, int high)
{
	int pivot = a[low];	//����
	while (low < high)
	{
		while (low < high && a[high] >= pivot) --high;
		a[low] = a[high];
		while (low < high && a[low] <= pivot) ++low;
		a[high] = a[low];
	}
	a[low] = pivot;
	return low;
}

void quickSort(int a[], int low, int high)
{
	if (low < high)
	{
		int pivotpos = partition(a, low, high);
		quickSort(a, low, pivotpos - 1);
		quickSort(a, pivotpos + 1, high);
	}
}

/*------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------���ֲ�������--------------------------------------------------------*/
void directInsertSort(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)	//�ӵڶ���Ԫ�ؿ�ʼ
	{
		if (a[i - 1] > a[i])	//��Ϊǰ���Ѿ���������ֻ��a[i]����ǰһ��Ԫ�ز���Ҫ����
		{
			temp = a[i];
			for (j = i - 1; j >= 0 && a[j] > temp; j--)	//��Ԫ�غ���
				a[j + 1] = a[j];
			a[j + 1] = temp;		//����
		}
	}
}

void binaryInsertSort(int a[], int n)
{
	int i, j, temp;
	int low, high, mid;
	for (i = 1; i < n; i++)	//�ӵڶ���Ԫ�ؿ�ʼ
	{
		if (a[i - 1] > a[i])	//��Ϊǰ���Ѿ���������ֻ��a[i]����ǰһ��Ԫ�ز���Ҫ����
		{
			temp = a[i];
			low = 0;
			high = i - 1;
			while (low <= high)
			{
				mid = (low + high) / 2;
				if (a[mid] > temp) high = mid - 1;
				else			   low = mid + 1;
			}
			for (j = i - 1; j >= high+1; j--)
				a[j + 1] = a[j];
			a[high+1] = temp;
		}
	}
}

void shellSort(int a[], int n)
{
	int i, j, d,temp;
	for (d = n / 2; d >= 1; d /= 2)		//��������d=n/2,n/2/2......
	{
		for (i = d; i < n; i++)			//���洦������ӱ�
		{
			if (a[i] < a[i - d])
			{
				temp = a[i];
				for (j = i - d; j >= 0 && a[j] > temp; j -= d)
					a[j + d] = a[j];
				a[j + d] = temp;
			}
		}
	}
}

/*-----------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------����ѡ������-----------------------------------------------------------*/
void selectSort(int a[], int n)
{
	int min;
	for (int i = 0; i < n - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < n; j++)
			if (a[j] < a[min]) min = j;
		if (min != i) swap(a[min], a[i]);
	}
}

void heapAdjust(int a[], int n, int k)			//k��Ҫ���������������
{
	int temp = a[k], i;
	for (i = 2 * k + 1; i < n; i = 2 * i + 1)	//1.����������Һ��ӱȽϣ����ֵ��Ϊ�����
	{											//2.�������ټ�麢��������Ҳ�����ɴ����
		if (i < n - 1 && a[i] < a[i + 1])	i++;	//i<n-1��֤�����ֵܣ��ҳ��ϴ�����Һ���
		if (temp >= a[i])	break;					//�������������ֵ��˵�����������Ǵ���ѣ�ֱ������ѭ��
		else
		{
			a[k] = a[i];							//���ӵ����ɸ����
			k = i;									//k�����βδ���k���յ�λ��
		}
	}
	a[k] = temp;
}


void buildMaxHeap(int a[], int n)		//�����ɴ����
{
	for (int i = (n - 2) / 2; i >= 0; i--)		//i��ʼ��Ϊ���һ����Ҷ�ӽ��
		heapAdjust(a, n, i);					//��ÿ����Ҷ�ӽ����е���
}



void heapSort(int a[], int n)
{
	buildMaxHeap(a, n);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);				//�Ѵ�������ֵ�ŵ�����λ��
		heapAdjust(a, i , 0);			//�޸�����󣬺������ź����Ԫ�أ�������Ԫ�ص����ɴ���ѣ�����ֻҪ�������㼴�����µ����ɴ����
	}
}


/*----------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------�鲢����------------------------------------------------------*/
void merge(int a[],int temp[],int low,int mid, int high)
{
	int i, j, k;
	for (k = low; k <= high; k++)	temp[k] = a[k];					//���ƴ���������
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)	//�Ա������ӱ�
	{
		if (temp[i] <= temp[j])	a[k] = temp[i++];
		else					a[k] = temp[j++];
	}
	//����ʣ������Ԫ��
	while (i <= mid)	a[k++] = temp[i++];
	while (j <= high)	a[k++] = temp[j++];
}

void Sort(int a[],int temp[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		//��·�鲢
		Sort(a,temp, low, mid);					//���ֳ����ӱ�
		Sort(a,temp, mid + 1, high);			//���ֳ����ӱ�
		merge(a,temp, low,mid, high);			//�ϲ�
	}
}

void mergeSort(int a[], int n)
{
	int *temp = (int*)malloc(sizeof(int)*n);	//��������
	Sort(a, temp, 0, n - 1);
	free(temp);
}

/*-----------------------------------------------------------------------------------------------------------------*/

int main()
{
	int a[10] = { 12,35,2,45,91,22,5,8,9,18 };
	for (int i = 0; i < 10; i++) cout << a[i] << " ";
	cout << endl;

	//quickSort(a, 0, 9);
	//barbleSort(a, 10);

	//directInsertSort(a, 10);
	//binaryInsertSort(a, 10);
	//shellSort(a, 10);

	//selectSort(a, 10);
	//heapSort(a, 10);
	
	mergeSort(a, 10);

	for (int i = 0; i < 10; i++) cout << a[i] << " ";
	system("pause");
	return 0;
}
