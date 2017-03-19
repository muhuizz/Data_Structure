#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;
#include <cassert>
// 找出最小的K个数

// 小堆
void _AdjustDownS(int *arr, int parent, int sz)
{
	int child = parent * 2 + 1;

	while (child < sz)
	{
		if (child + 1 < sz && arr[child + 1] < arr[child])
			child++;

		if (arr[parent] > arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void FindKMin_1(int *src, int sz, int *dst, int k)
{
	assert(src);
	assert(dst);
	assert(k > 0 && sz > 0 && k <= sz);
	for (int i = (sz - 2)/2; i >= 0; i--)
	{
		_AdjustDownS(src, i, sz);
	}
	for (int i = 0; i < k; i++)
	{
		dst[i] = src[0];
		std::swap(src[0], src[sz - 1 - i]);
		_AdjustDownS(src, 0, sz - i - 1);
	}
}


// 大堆
void _AdjustDownB(int *arr, int parent, int sz)
{
	int child = parent * 2 + 1;

	while (child < sz)
	{
		if (child + 1 < sz && arr[child + 1] > arr[child])
			child++;

		if (arr[parent] < arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void FindKMin_2(int *src, int sz, int *dst, int k)
{
	assert(src);
	assert(dst);
	assert(k > 0 && sz > 0 && k <= sz);

	int index = 0;
	for (; index < k; index++)
	{
		dst[index] = src[index];
	}

	// 对dst建堆
	for (int i = (k - 2) / 2; i >= 0; i--)
	{
		_AdjustDownB(dst, i, k);
	}

	for (; index < sz; index++)
	{
		if (dst[0] >src[index])
		{
			dst[0] = src[index];
			_AdjustDownB(dst, 0, k);
		}
		
	}
}
int main()
{
	int arr[] = { 1, 9, 8, 1, 3, 4, 5, 6, 7, 8 };
	int k = 4;
	int dst[4];
	//FindKMin_1(arr, sizeof(arr) / sizeof(arr[0]), dst, k);
	FindKMin_2(arr, sizeof(arr) / sizeof(arr[0]), dst, k);
	for (int i = 0; i < k; i++)
	{
		cout << dst[i] << endl;
	}
	system("pause");
	return 0;
}