#pragma once
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct ListNode
{
public:
	ListNode(const T& x)
		:_data(x)
		, _next(NULL)
		, _prev(NULL)
	{}
public:
	ListNode<T>* _next;
	ListNode<T>* _prev;
	T _data;

};

//
//STL----->复用+效率
//
template<class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListIterator<T, Ref, Ptr> Self;// 重定义寄存器
	typedef ListNode<T> Node;			//重定义结点
public:
	ListIterator(Node* node)
		:_node(node)
	{}
	ListIterator()
	{}
	ConstIterator(Node* node)
		:_node(node)
	{}
	ConstIterator()
	{}
	Ref operator*()
	{
		return _node->_data;
	}
	Ptr operator->()
	{
		//return &(_node->_data);
		return &(operator*());
	}

	bool operator==(const Self& it) const
	{
		return _node == it._node;
	}

	bool operator!=(const Self& it) const
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		//return ListIterator(_node->_next);
		_node = _node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(_node);
		_node = _node->_next;
		return tmp;
	}

	Self& operator--()
	{
		//retrun ListIterator(_node->_prev);
		_node = _node->_prev;
		return *this;
	}

	Self operator--(int)
	{
		Self tmp(_node);
		_node = _node->_prev;
		retrun tmp;
	}
public:
	Node* _node;
};

template<typename T>
class List
{
public:

	typedef ListNode<T> Node;
	typedef ListIterator<T, T&, T*> Iterator;// 重定义寄存器
	typedef ListIterator<T, const T&, const T*> ConstIterator;//重定义const类型的迭代器
	//两个模板参数方便实现

	List()
	{
		_head = BuyNode(T());
		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		//return Iterator(_head->_next);
		return _head->_next;
	}
	Iterator End()
	{
		//return Iterator(_head);
		return _head;
	}
	//const对象调用的
	ConstIterator Begin() const
	{
		return Iterator(_head->_next);
	}
	ConstIterator End() const
	{
		return Iterator(_head);
		//return _head;//类型强转 explicit
	}
	void Insert(const Iterator& it, const T& x)
	{
		Node* front = it._node->_prev;
		Node* node = BuyNode(x);

		node->_next = it._node;
		node->_prev = front;
		front->_next = node;
		it._node->_prev = node;
	}
	Iterator Erase(Iterator it)
	{
		assert(it != End());
		Node* front = it._node->_prev;
		Node* next = it._node->_next;
		front->_next = next;
		next->_prev = front;
		delete Iterator(it._node);
	}
	void PushBack(const T& x)
	{
		//Insert(_head->_prev, x);
		Insert(End(), x);
	}
	void PopBack()
	{
		assert(_head != _head->_next);
		Erase(Iterator(_head->_prev));
	}
	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}
	void PopFront()
	{
		assert(_head != _head->_next);
		Erase(Begin());
	}
	void PrintList()
	{
		List<T>::Iterator it1 = 
	}
private:
	Node* BuyNode(const T& x)
	{
		Node* tmp = new Node(x);
		return tmp;
	}
private:
	Node* _head;
};

struct A
{
	int _i;
	char _c;
	A(int i = 10,char c = 'a')
		:_i(i)
		, _c(c)
	{}
};

void TestList()
{
	List<int> li;
	//li.PushBack(1);
	//li.PushBack(2);
	//li.PushBack(3);
	//li.PushBack(4);
	//li.PushBack(5);
	li.PushFront(1);
	li.PushFront(2);
	li.PushFront(3);
	li.PushFront(4);
	li.PushFront(5);
	//li.PopFront();
	//li.PopFront();

	//li.PopBack();
	//li.PopBack();
	//li.PopBack();
	//li.PopBack();
	//li.PopBack();
	//li.PopBack();

	List<int>::Iterator it = li.Begin();
	while (it != li.End())
	{
		cout << *it<< " ";
		it++;
	}
	cout << endl;
}

void TestList2()
{
	List<A> li;
	li.PushBack(A());
	li.PushBack(A());
	li.PushBack(A());
	li.PushBack(A());
	li.PushBack(A());

	List<A>::Iterator it = li.Begin();
	for (; it != li.End(); it++)
	{
		cout << it->_c << endl;
	}

}