#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 29.求一个 数组中出现次数超过一半的数

bool IsInvalid = false;
int MoreThanHalf(int *arr, int sz)
{
	if (sz <= 0 || arr == NULL)
	{
		IsInvalid = true;
		return 0;
	}

	int res = arr[0];
	int count = 1;
	for (int i = 1; i < sz; i++)
	{
		if (count == 0)
			res = arr[i];
		if (arr[i] == res)
			count++;
		else
			count--;
	}
	return res;
}
int main()
{
	int arr[] = { 1, 4, 4, 4, 3, 4, 5, 4, 6, 2, 4 };
	int ret = MoreThanHalf(arr, sizeof(arr) / sizeof(arr[0]));
	if (!IsInvalid)
	{
		cout << "出现超过一半的数字为" << ret << endl;
	}
	system("pause");
	return 0;
}
/*
解题思路：
	首先我们要保证输入的有效性。
	一个数，如果出现次数超过超过数组元素个数的一半，也就是说，这个数字出现的次数比其他所有数字出现次数之和还多（至少多一个）；
	这里定义两个变量，一个为数组中的元素，另一个为次数；
	当遍历到下一个数字时，如果和保存的数字相同，则次数加一；如果和保存的数字不同，则次数减一；当次数为0后需要重新保存数字作为我们的临时出现次数最多的数字。
	还是上面那句话，因为出现次数超过一半，那么即使每次和其他数抵消一个，也不会影响最终它会留下来。
*/