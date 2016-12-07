#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>
using namespace std;

void InsertSort(int* arr, const size_t& sz)
{
	assert(arr);
	size_t index = 1;
	for (; index < sz; index++)
	{
		int tmp = arr[index];
		int pos = index - 1;
		while (pos >= 0 && arr[pos] > tmp)
		{
			arr[pos + 1] = arr[pos];
			pos--;
		}
		arr[pos + 1] = tmp;
	}
}

void SelectSort_2(int* arr, int sz)
{
	assert(arr);
	int left = 0;
	int right = sz - 1;

	while (left < right)
	{
		int max = right;
		int min = left;
		for (int i = left; i <= right; i++)
		{
			if (arr[i] < arr[min])
				min = i;
			if (arr[i] > arr[max])
				max = i;
		}
		std::swap(arr[left], arr[min]);
		if (max == left) // 对Bug的特殊处理
			max = min;
		std::swap(arr[right], arr[max]);
		++left;
		--right;
	}
}

void BubbleSort(int* arr, const size_t& sz)
{
	assert(arr);
	int flag = 1;
	size_t k = sz - 1;
	for (size_t i = 0; i < k; i++)
	{
		int m = 0;
		for (size_t j = 0; j < sz - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
				flag = 0;
				m = j;
			}
		}
		if (flag == 1)
			break;
		k = m;
	}
}

void ShellSort(int* arr, const size_t& sz)
{
	assert(arr);
	int gap = sz;
	while (gap > 1) // 预排序的每次间隔大小
	{
		gap = gap / 3 + 1;
		size_t index = gap;
		for (; index < sz; index++)
		{
			int pos = index - gap;
			int tmp = arr[index];
			while (pos >= 0 && arr[pos] > tmp)
			{
				arr[pos + gap] = arr[pos];
				pos -= gap;
			}
			arr[pos + gap] = tmp;
		}
	}
}

void SelectSort(int* arr, const size_t& sz)
{
	assert(arr);
	for (size_t i = 0; i < sz - 1; i++)
	{
		size_t index = i;
		for (size_t j = i + 1; j < sz; j++)
		{
			if (arr[index] > arr[j])
				index = j;
		}
		std::swap(arr[index], arr[i]);
	}
}

//  升序排序要用大堆
void _Adjustdown(int* arr, int i, int sz)
{
	int parent = i;
	int child = 2 * i + 1;

	while (child < sz)
	{
		if (child + 1 < sz && arr[child] < arr[child + 1])
			child++;
		if (arr[parent] < arr[child])
		{
			std::swap(arr[parent], arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}
void HeapSort(int* arr, const size_t& sz)
{
	if (arr == NULL)
		return;

	for (int i = (sz - 2) / 2; i >= 0; i--)
	{
		_Adjustdown(arr, i, sz);
	}

	for (int i = sz - 1; i > 0; i--)
	{
		std::swap(arr[i], arr[0]);
		_Adjustdown(arr, 0, i);
	}
}


void _MergeSort(int* arr, int* tmp, int begin, int end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	_MergeSort(arr, tmp, begin, mid);
	_MergeSort(arr, tmp, mid + 1, end);

	int left = begin;
	int right = mid + 1;
	int index = left;

	while ((left <= mid) && (right <= end))
	{
		if (arr[left] > arr[right])
			tmp[index++] = arr[right++];
		else
			tmp[index++] = arr[left++];
	}

	while (left <= mid)
		tmp[index++] = arr[left++];

	while (right <= end)
		tmp[index++] = arr[right++];

	for (int i = begin; i <= end; i++)
	{
		arr[i] = tmp[i];
	}
}

void MergeSort(int *arr, int begin, int end)
{
	int* tmp = new int[end - begin + 1];
	_MergeSort(arr, tmp, begin, end);
}

// 三数取中法
int GetMidNum(int* arr, int begin, int end)
{
	if (begin == end)
		return begin;

	int mid = begin + (end - begin) / 2;
	if (arr[begin] > arr[end] && arr[begin] < arr[mid])
		return begin;
	else if (arr[end] > arr[begin] && arr[end] < arr[mid])
		return end;
	else
		return mid;
}

// 左右指针法   
int PartFastSort(int* arr, int begin, int end)
{
	int left = begin;
	int right = end - 1;
	int key = arr[end];

	while (left < right)
	{
		while (left < right && arr[left] <= arr[end])
			left++;
		while (left < right && arr[right] >= arr[end])
			right--;
		if (left < right)
			std::swap(arr[left], arr[right]);
	}

	if (arr[left] <= arr[end])
	{
		return end;
	}
	else
	{
		std::swap(arr[end], arr[left]);
		return left;
	}
}
void FastSort(int* arr, int begin, int end)
{
	assert(arr);
	if (begin < end)
	{
		int sz = PartFastSort(arr, begin, end);
		FastSort(arr, begin, sz - 1);
		FastSort(arr, sz + 1, end);
	}
}

// 挖坑法
int PartFastSortHole(int* arr, int begin, int end)
{
	int left = begin;
	int right = end;
	int key = arr[end];
	int hole = end;
	while (left < right)
	{
		while (left < right && arr[left] <= key)
			left++;
		//if (left == right)
		//	break;
		arr[hole] = arr[left];
		hole = left;

		while (left < right && arr[right] >= key)
			right--;
		//if (left == right)
		//	break;

		arr[hole] = arr[right];
		hole = right;
	}
	arr[hole] = key;
	return hole;
}
void FastSortHole(int* arr, int begin, int end)
{
	assert(arr);
	if (begin < end)
	{
		int sz = PartFastSortHole(arr, begin, end);
		FastSort(arr, begin, sz - 1);
		FastSort(arr, sz + 1, end);
	}
}

// 新方法
// 插入优化
int PartFastSort3(int* arr, int begin, int end)
{
	int prev = begin - 1;
	int cur = begin;
	int index = GetMidNum(arr, begin, end);
	std::swap(arr[index], arr[end]);
	int key = arr[end];

	while (cur < end)
	{
		// 当cur对应的值小于key，prev++
		if (arr[cur] < key && (++prev != cur))
		{
			std::swap(arr[prev], arr[cur]); // prev没有追上cur的时候
		}
		cur++;
	}
	std::swap(arr[++prev], arr[end]);
	return prev;
}
void FastSort3(int* arr, int begin, int end)
{
	assert(arr);
	if (end - begin > 13) // 大量数据时选择13
	{
		int sz = PartFastSort3(arr, begin, end);
		FastSort3(arr, begin, sz - 1);
		FastSort3(arr, sz + 1, end);
	}
	else
	{
		InsertSort(arr + begin, end - begin + 1);
	}
}

// 快排非递归
#include <stack>
void QuickSortNonR(int* arr, int sz)
{
	stack<int> sta;
	int begin = 0;
	int end = sz - 1;

	sta.push(end);
	sta.push(begin);
	while (!sta.empty())
	{
		int left = sta.top();
		sta.pop();
		int right = sta.top();
		sta.pop();

		int mid = PartFastSort(arr, left, right);
		if (left < mid - 1)
		{
			sta.push(mid - 1);
			sta.push(left);
		}
		if (mid + 1 < right)
		{
			sta.push(right);
			sta.push(mid + 1);
		}
	}
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

void TestCompareSort()
{
	int arr1[] = { 9, 1, 2, 5, 3, 4, 8, 5, 6, 5 };
	int arr2[] = { 2, 5, 4, 9, 3, 6, 8, 7, 1, 0 };
	int arr3[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int arr4[] = { 5, 1, 2, 5, 3, 4, 8, 5, 6, 5 };

	//InsertSort(arr, sizeof(arr) / sizeof(arr[0]));
	//BubbleSort(arr, sizeof(arr) / sizeof(arr[0]));
	//ShellSort(arr, sizeof(arr) / sizeof(arr[0]));
	//SelectSort(arr, sizeof(arr) / sizeof(arr[0]));
	//HeapSort(arr, sizeof(arr) / sizeof(arr[0]));
	//MergeSort(arr, 0, (sizeof(arr) / sizeof(arr[0])) - 1);
	//SelectSort_2(arr, sizeof(arr) / sizeof(arr[0]));
	//FastSort(arr, 0, (sizeof(arr) / sizeof(arr[0])) - 1);
	//MergeSort(arr1, 0, sizeof(arr1) / sizeof(arr1[0]) - 1);
	//MergeSort(arr2, 0, sizeof(arr2) / sizeof(arr2[0]) - 1);
	//MergeSort(arr3, 0, sizeof(arr3) / sizeof(arr3[0]) - 1);
	//MergeSort(arr4, 0, sizeof(arr4) / sizeof(arr4[0]) - 1);
	SelectSort_2(arr1, sizeof(arr1) / sizeof(arr1[0]));
	SelectSort_2(arr2, sizeof(arr2) / sizeof(arr2[0]));
	SelectSort_2(arr3, sizeof(arr3) / sizeof(arr3[0]));
	SelectSort_2(arr4, sizeof(arr4) / sizeof(arr4[0]));


	PrintArray(arr1, sizeof(arr1) / sizeof(arr1[0]));
	PrintArray(arr2, sizeof(arr2) / sizeof(arr2[0]));
	PrintArray(arr3, sizeof(arr3) / sizeof(arr3[0]));
	PrintArray(arr4, sizeof(arr4) / sizeof(arr4[0]));
}