#pragma once
/**************项目名称与简介*************	
	Heap（堆）
	堆的本质是数组，但是同时兼具树的结构
***********************************/
#include <vector>
#include <cassert>
#include <iostream>
using namespace std;

template<typename T>
struct Less
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 < t2;
	}
};

template<typename T>
struct Great
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 > t2;
	}
};
// 大堆
template<typename T, typename Comp = Great<T>>
class Heap
{
public:
	Heap(const T* arr, const size_t sz)
	{
		_vec.reserve(sz);
		for (size_t i = 0; i < sz; i++)
		{
			_vec.push_back(arr[i]);
		}
		for (size_t i = sz - 1; i >0; i--)
		{
			_AdjustUp(i);
		}
	}
	void Push(const T& x)
	{
		_vec.push_back(x);
		_AdjustUp(_vec.size()-1);
	}
	void Pop()
	{
		assert(!Empty());
		std::swap(_vec[0], _vec[_vec.size() - 1]);
		_vec.pop_back();
		_AdjustDown(0);
	}
	bool Empty()
	{
		return _vec.empty();
	}
	size_t Size()
	{
		return _vec.size();
	}
	const T& Top()
	{
		assert(!Empty());
		return _vec[0];
	}

protected:
	void _AdjustUp(size_t child)
	{		
		Comp comp;
		while (child > 0)
		{
			size_t parent = (child - 1) / 2;
			if (comp(_vec[child], _vec[parent]))
			{
				std::swap(_vec[child], _vec[parent]);
				child = parent;
			}
			else
				break;
		}
	}
	void _AdjustDown(size_t parent)
	{
		size_t child = 2 * parent + 1;
		Comp comp;
		while (child < _vec.size())
		{
			if (child +1 < Size() && comp(_vec[child + 1], _vec[child]))
				child++;
			if (comp(_vec[child], _vec[parent]))
			{
				std::swap(_vec[child], _vec[parent]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}
protected:
	vector<T> _vec;
};


// 优先级队列
template<class T, class Compare = Great<T>>
class PriorityQueue
{
public:
	PriorityQueue(const T* arr, const size_t& x)
		:_heap(arr, x)
	{}
	void Push(const T& x)
	{
		_heap.Push(x);
	}
	void Pop()
	{
		_heap.Pop();
	}
protected:
	Heap<T, Compare> _heap;
};
void TestHeap()
{
	int a[] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	Heap<int> myheap(a, sizeof(a) / sizeof(a[0]));
	//myheap.display();
	//myheap.Push(0);
	//myheap.Push(99);
	//myheap.display();
	
	//PriorityQueue<int, Less<int>> pqueue(a, sizeof(a)/sizeof(a[0]));
	//pqueue.Push(0);
	//pqueue.Push(1);
	//pqueue.Push(2);
	//pqueue.Push(3);
	//pqueue.Push(4);
	//pqueue.Push(5);
	//pqueue.Pop();
	//pqueue.Pop();
	//pqueue.Pop();


}
