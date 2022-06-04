#include<iostream>
using namespace std;

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

/*---------------------------------------------两种交换排序--------------------------------------------------------*/
void barbleSort(int a[],int n)
{
	bool flag = false;					//若排序某趟时有序，直接结束
	for (int i = 0; i < n - 1; i++)		//排序趟数
	{
		flag = false;
		for (int j = n - 1; j > i; j--)	//冒泡
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
	int pivot = a[low];	//枢轴
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

/*-----------------------------------------------三种插入排序--------------------------------------------------------*/
void directInsertSort(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; i++)	//从第二个元素开始
	{
		if (a[i - 1] > a[i])	//因为前面已经有序，所以只有a[i]大于前一个元素才需要排序
		{
			temp = a[i];
			for (j = i - 1; j >= 0 && a[j] > temp; j--)	//将元素后移
				a[j + 1] = a[j];
			a[j + 1] = temp;		//插入
		}
	}
}

void binaryInsertSort(int a[], int n)
{
	int i, j, temp;
	int low, high, mid;
	for (i = 1; i < n; i++)	//从第二个元素开始
	{
		if (a[i - 1] > a[i])	//因为前面已经有序，所以只有a[i]大于前一个元素才需要排序
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
	for (d = n / 2; d >= 1; d /= 2)		//增量序列d=n/2,n/2/2......
	{
		for (i = d; i < n; i++)			//交替处理各个子表
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

/*--------------------------------------------两种选择排序-----------------------------------------------------------*/
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

void heapAdjust(int a[], int n, int k)			//k是要调整的子树根结点
{
	int temp = a[k], i;
	for (i = 2 * k + 1; i < n; i = 2 * i + 1)	//1.根结点与左右孩子比较，最大值作为根结点
	{											//2.调整后，再检查孩子子树，也调整成大根堆
		if (i < n - 1 && a[i] < a[i + 1])	i++;	//i<n-1保证有右兄弟，找出较大的左右孩子
		if (temp >= a[i])	break;					//如果根结点是最大值，说明该子树已是大根堆，直接跳出循环
		else
		{
			a[k] = a[i];							//孩子调换成根结点
			k = i;									//k保存形参传入k最终的位置
		}
	}
	a[k] = temp;
}


void buildMaxHeap(int a[], int n)		//数组变成大根堆
{
	for (int i = (n - 2) / 2; i >= 0; i--)		//i初始化为最后一个非叶子结点
		heapAdjust(a, n, i);					//对每个非叶子结点进行调整
}



void heapSort(int a[], int n)
{
	buildMaxHeap(a, n);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(a[0], a[i]);				//把大根堆最大值放到最终位置
		heapAdjust(a, i , 0);			//修改数组后，忽略已排好序的元素，对其他元素调整成大根堆，这里只要处理根结点即可重新调整成大根堆
	}
}


/*----------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------归并排序------------------------------------------------------*/
void merge(int a[],int temp[],int low,int mid, int high)
{
	int i, j, k;
	for (k = low; k <= high; k++)	temp[k] = a[k];					//复制待处理数据
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k++)	//对比两个子表
	{
		if (temp[i] <= temp[j])	a[k] = temp[i++];
		else					a[k] = temp[j++];
	}
	//处理剩余有序元素
	while (i <= mid)	a[k++] = temp[i++];
	while (j <= high)	a[k++] = temp[j++];
}

void Sort(int a[],int temp[], int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		//二路归并
		Sort(a,temp, low, mid);					//划分成左子表
		Sort(a,temp, mid + 1, high);			//划分成右子表
		merge(a,temp, low,mid, high);			//合并
	}
}

void mergeSort(int a[], int n)
{
	int *temp = (int*)malloc(sizeof(int)*n);	//辅助数组
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
