#pragma once

#include <cassert>
#include <iostream>
using namespace std;

template<typename T>
class Stack
{
public:
	Stack()
		:_pdata(NULL)
		, _size(0)
		, _capacity(0)
	{}
	~Stack()
	{
		if (_pdata != NULL)
		{
			delete _pdata;
			_size = 0;
			_capacity = 0;
		}
	}
	void Push(const T& x)
	{
		CheckCapacity();
		_pdata[_size] = x;
		_size++;
	}
	void Pop()
	{
		assert(_size > 0);
		_size--;
	}
	size_t Size()
	{
		return _size;
	}
	T& Top()
	{
		assert(_size > 0);
		return _pdata[_size-1];
	}
	bool Empty()
	{
		return _size == 0;
	}
protected:
	void CheckCapacity()
	{
		if (_size == _capacity)
		{
			size_t NewCapacity = _capacity * 2 + 3;
			T* tmp = new T[NewCapacity];
			for (size_t i = 0; i < _size; i++)
			{
				tmp[i] = _pdata[i];
			}
			delete _pdata;
			_pdata = tmp;
			_capacity = NewCapacity;
		}
	}
protected:
	T *_pdata;
	size_t _size;
	size_t _capacity;
};


void TestStack()
{
	Stack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	s.Push(5);
	//while (auto c:s)
	//{
	//	cout << c << endl;
	//}
	while (!s.Empty())
	{
		cout << s.Top() << " ";
		s.Pop();
	}
	cout << endl;
	cout << s.Size() << endl;
}