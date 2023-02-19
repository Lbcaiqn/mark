#include<iostream>
using namespace std;

int midSearch(int a[], int n, int key)
{
	int low = 0, high = n - 1, mid;
	while (low < high)
	{
		mid = (low + high) / 2;
		if (a[mid] == key) return mid;
		else if (a[mid] < key) low = mid + 1;
		else high = mid - 1;
	}
}

int main()
{
	int a[100];
	for (int i = 0; i < 100; i++) a[i] = 2*i;
	cout << midSearch(a, 100, 55) << endl;
	system("pause");
	return 0;
}