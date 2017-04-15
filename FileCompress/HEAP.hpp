#pragma once

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

//仿函数
template<typename T>
struct _MAX
{
	bool operator()(const T& x1,const T& x2)
	{
		return x1 > x2;
	}
};
template<typename T>
struct _MIN
{
	bool operator()(const T& x1, const T& x2)
	{
		return x1 < x2;
	}
};
//堆不需要考虑两个孩子之间的大小关系
template <typename T,typename Compare = _MAX<T>>
class HEAP
{
public:
	HEAP(T* a,size_t sz)
	{
		for (size_t i = 0; i < sz; i++)
		{
			_a.push_back(a[i]);
		}

		for (int i = (sz - 2) / 2; i >= 0;i--)
		{
			_AdjustDown(i);
		}
	}
	HEAP()
	{}

	void Push(const T& x)
	{
		_a.push_back(x);
		_AdjustUp(_a.size() - 1);
	}
	void Pop()
	{
		assert(!_a.empty());
		std::swap(_a[0], _a[_a.size() - 1]);
		_a.pop_back();
		_AdjustDown(0);
	}
	T Top()
	{
		return _a[0];
	}
	bool Empty()
	{
		return _a.empty();
	}
	size_t Size()
	{
		return _a.size();
	}
private:
	void _AdjustDown(int parent)
	{
		int child = parent * 2 + 1;
		int size = _a.size();
		Compare com;
		
		while (child < size)
		{
			if (child + 1 < size && com(_a[child+1], _a[child]))/*_a[child] < _a[child + 1]*/
			{
				child++;
			}
			if (com(_a[child], _a[parent]))//_a[child] > _a[parent]
			{
				std::swap(_a[child], _a[parent]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		Compare com;
		while (child >= 0)
		{
			//向上调整，只需要考虑孩子和父亲的大小，不需要关心兄弟之间的大小
			if (com(_a[child] , _a[parent]))//_a[child] > _a[parent]
			{
				std::swap(_a[child], _a[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _a;
};

