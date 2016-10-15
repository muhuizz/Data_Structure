#pragma once

#include <cassert>
#include <iostream>
using namespace std;

template <typename T>
struct QueueNode
{
public:
	QueueNode(const T& x)
		:_data(x)
		,_next(NULL)
	{}
public:
	T _data;
	QueueNode<T>* _next;
};
template <typename T>
class Queue
{
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
	{}
	~Queue()
	{
		QueueNode<T>* cur = _head;
		while (cur != NULL)
		{
			QueueNode<T>* node = cur;
			cur = cur->_next;
			delete node;
			node = NULL;
		}
		_head = NULL;
		_tail = NULL;
	}
	void Push(const T& x)
	{
		if (_head == NULL)
		{
			_head = _tail = new QueueNode<T>(x);
		}
		else
		{
			_tail->_next = new QueueNode<T>(x);
			_tail = _tail->_next;
		}
	}
	void Pop()
	{
		assert(_head);
		QueueNode<T>* tmp = _head;
		_head = _head->_next;
		delete tmp;
		if (_head == NULL)
		{
			_tail = NULL;
		}
	}
	bool Empty()
	{
		return _head == NULL;
	}
	T& Front()
	{
		assert(_head);
		return _head->_data;
	}
	T& Back()
	{
		assert(_head);
		return _tail->_data;
	}
	size_t Size()
	{
		QueueNode<T> *cur = _head;
		size_t count = 0;
		while (cur != NULL)
		{
			count++;
			cur = cur->_next;
		}
		return count;
	}
protected:
	QueueNode<T> *_head;
	QueueNode<T> *_tail;
};



void TestQueue()
{
	Queue<int> que;
	que.Push(1);
	que.Push(2);
	que.Push(3);
	que.Push(4);
	que.Push(5);
	while (!que.Empty())
	{
		cout << que.Front() << "--" << que.Back() << endl;
		que.Pop();
	}

}













