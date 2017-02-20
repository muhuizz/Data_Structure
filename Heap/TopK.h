#pragma once
/**************项目名称与简介*************	
	topk问题
***********************************/

// TopK_Max
#include <iostream>
#include <cassert>
using namespace std;
const int K = 5;

template<typename T>
void AdjustDown(T* arr, const size_t& sz, size_t parent)
{
	size_t child = 2 * parent + 1;
	while (child < sz)
	{
		if (child + 1 < sz && arr[child] < arr[child + 1])
			child++;
		if (arr[child] > arr[parent])
		{
			std::swap(arr[child], arr[parent]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}

template<typename T>
bool GetTopK(const T* arr, T* dst, const size_t& size)
{
	assert(arr);
	assert(dst);

	for (size_t i = 0; i < K; i++)
		dst[i] = arr[i];

	// 建堆
	for (int i = (K - 2) / 2; i >= 0; i--)
	{
		AdjustDown(dst, K, i);
	}
	
	// 调整
	for (size_t i = K; i < size; i++)
	{
		if (arr[i] < dst[0])
		{
			dst[0] = arr[i];
			AdjustDown(dst, K, 0);
		}
	}
	return true;
}

// 建大堆找出topk_min的
// 建小堆找出topk_max的

void TestTopK()
{
	int arr[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	int topk[K];
	bool ret = GetTopK(arr, topk, sizeof(arr)/sizeof(arr[0]));
	cout << "topK ----->";
	for (size_t i = 0; i < K; i++)
	{
		cout << topk[i]<<"  ";
	}
	cout << endl;
}