#pragma once 

#include <cassert>
#include <iostream>
using namespace std;

//  计数排序
int GetRange(int* arr, size_t sz)
{
	int max = arr[0];
	for (size_t i = 1; i < sz; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
	}
	return max;
}
void CountingSort(int* arr, size_t sz)
{
	int range = GetRange(arr, sz)+1;
	int* tmp = new int[range];
	memset(tmp, 0, sizeof(int)* (range));
	for (size_t cur = 0; cur < sz; ++cur)
	{
		tmp[arr[cur]]++;
	}
	int index = 0;
	for (size_t cur = 0; cur < range; ++cur) // 遍历新开辟的数组
	{
		int num = tmp[cur];
		while (num--)
		{
			arr[index++] = cur;
		}
	}
}


// 基数排序
int GetLength(int* arr, size_t sz)
{
	int digit = 1;
	int num = 10;
	for (size_t i = 0; i < sz; ++i)
	{
		while (arr[i] > num)
		{
			digit++;
			num *= 10;
		}
	}

	return digit;
}
void LSDSort(int* arr, size_t sz)
{
	assert(arr);
	int* tmp = new int[sz];
	int digit = GetLength(arr, sz);
	
	int div = 1;
	while (digit--)
	{
		int count[10] = { 0 };
		int start[10] = { 0 };
		// 初始化count
		for (size_t i = 0; i < sz; ++i)
		{
			int num = arr[i]/div % 10;
			count[num]++;
		}

		// 初始化start
		for (size_t i = 1; i < 10; ++i)
		{
			start[i] = start[i - 1] + count[i - 1];
		}

		// 创建新数组，
		for (size_t i = 0; i < sz; ++i)
		{
			int num = arr[i];
			tmp[start[arr[i] / div % 10]++] = num;
		}

		// 将tmp内容重新拷贝给arr
		for (size_t i = 0; i < sz; ++i)
		{
			arr[i] = tmp[i];
		}
		div *= 10;
	}

	delete[] tmp;
}



void  PrintArray(int * arr, size_t sz)
{
	assert(arr);
	for (size_t i = 0; i < sz; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
void TestUncompareSort()
{
	int arr1[] = { 1, 111, 4, 56, 34, 8888, 22, 82, 5, 88, 9 };

	CountingSort(arr1, sizeof(arr1) / sizeof(arr1[0]));
	PrintArray(arr1, sizeof(arr1) / sizeof(arr1[0]));

	int arr2[] = { 1, 111, 4, 56, 34, 888888, 22, 82, 5, 88, 9 };
	LSDSort(arr2, sizeof(arr2) / sizeof(arr2[0]));
	PrintArray(arr2, sizeof(arr2) / sizeof(arr2[0]));
}