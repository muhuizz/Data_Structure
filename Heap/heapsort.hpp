#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cassert>
using namespace std;

template<typename T>
void AdjustDown(T* arr, size_t sz, size_t parent)
{
	assert(arr);
	size_t child = parent * 2 + 1;
	while (child < sz)
	{
		if (child +1 < sz && arr[child] < arr[child + 1])
			child++;
		if (arr[child] > arr[parent])
		{
			std::swap(arr[child], arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			break;
	}
}

// …˝–Ú£¨Ω®¥Û∂—

void TestHeapSort()
{
	int arr[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	size_t sz = sizeof(arr) / sizeof(arr[0]);
	// Ω®∂—
	for (int i = (sz - 2) / 2; i >= 0; i--)
	{
		AdjustDown(arr, sz, i);
	}

	// ≈≈–Ú
	size_t end = sz - 1;
	while (end > 0)
	{
		std::swap(arr[0], arr[end]);
		end--;
		AdjustDown(arr, end, 0);
	}

	// ¥Ú”°
	for (size_t i = 0; i < sz; i++)
	{
		cout << arr[i] << "---";
	}
	cout << endl;
}