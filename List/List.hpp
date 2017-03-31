#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
using namespace std;

template <typename T>
struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	T _data;
	ListNode(const T& x=T())
		:_next(NULL)
		 ,_prev(NULL)
		 ,_data(x)
	{}
};

template <typename T, typename Ref, typename Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;
public:
	ListIterator(Node* node)
		:_node(node)
	{}

	bool operator==(const Self& it)
	{
		return (it._node == _node);
	}
	bool operator!=(const Self& it)
	{
		return (it._node != _node);
	}
	Self operator++(int)	// hou zhi 
	{
		Self tmp(_node);
		_node = _node->_next;
		return tmp;
	}
	Self& operator++()
	{
		_node=_node->_next;
		return _node;
	}
	Self operator--(int)
	{
		Node tmp(_node);
		_node=_node->_prev;
		return tmp;
	}
	Self& operator--()
	{
		_node=_node->_prev;
		return _node;
	}
	
	T& operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &(operator*());
	}

public:
	Node* _node;
};

template <typename T>
class List
{
	typedef ListNode<T> Node;
public:
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<const T, const T&, const T*> ConstIterator;
	List()
	{
		_head = _buyNode(T());
		_head->_next = _head;
		_head->_prev = _head;
	}

	Iterator Begin()
	{
		return Iterator(_head->_next);
	}
	Iterator End()
	{
		return Iterator(_head);
	}
	void Insert(Iterator pos, const T& x)
	{
		Node* tmp = _buyNode(x);
		Node* prev = pos._node->_prev;
		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = pos._node;
		pos._node->_prev = tmp;
	}
	void Erase(Iterator pos)
	{
		if(pos == End())
			return;
		Node* prev = pos._node->_prev;
		Node* next = pos._node->_next;
		prev->_next = next;
		next->_prev = prev;
		_destory(pos._node);
	}
	void PushBack(const T& x)
	{
		Insert(End(), x);
	}
	void PopBack()
	{
		if(_head->_next != _head)
		{
			Erase(Iterator(_head->_prev));
		}
	}
	void PushFront(const T& x)
	{
		Insert(Begin(), x);
	}

	void PopFront()
	{
		if(_head->_next != _head)
		{
			Erase(Begin());
		}
	}
protected:
	Node* _buyNode(const T& x)
	{
		Node* tmp = new Node(x);
		return tmp;
	}

	void _destory(Node* node)
	{
		if(node != NULL)
		{
			delete node;
			node = NULL;
		}
	}
protected:
	Node* _head;	// shao bin
};

#endif// __LIST_HPP__
