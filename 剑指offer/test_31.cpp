#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <cassert>

int FindGreatest(int *arr,int sz)
{
	assert(arr);
	if (sz <= 0)
		return 0;
	int max = 0x80000000;
	int sum = 0;
	for (int i = 0; i < sz; i++)
	{
		sum = sum + arr[i];
		if (sum < arr[i])		// 从第i位开始重新求和
			sum = arr[i];
		if (max < sum)
			max = sum;
	}
	return max;
}

int main()
{
	int arr[] = { 1, -2, 3, 10, -4, 7, 2, -5 };
	int ret = FindGreatest(arr, sizeof(arr)/sizeof(arr[0]));
	cout << "max is " << ret << endl;
	system("pause");
	return 0;
}