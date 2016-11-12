#pragma once 

#include <iostream>
#include <cassert>
using namespace std;

enum PointTag
{
	THREAD,
	LINK
};

template <typename T>
struct BinaryTreeNodeThd
{
	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	PointTag _leftTag;
	PointTag _rightTag;

	BinaryTreeNodeThd(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};
template <typename T,typename Ref,typename Ptr>
struct __TreeIterator
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef __TreeIterator<T, Ref, Ptr> Self;

	__TreeIterator()
	{}
	__TreeIterator(Node* node)
		:_node(node)
	{}

	Self& operator++()
	{
		assert(_node);
		if (_node->_rightTag == LINK)//找右子树的最左结点
		{
			Node* tmp = _node->_right;
			while (tmp && tmp->_leftTag == LINK)
			{
				tmp = tmp->_left;
			}
			_node = tmp;
		}
		else
		{
			_node = _node->_right;
		}
		return *this;
	}
	Self operator++(int)
	{
		Self tmp(*this);
		++(*this);
		return tmp;
	}
	Self& operator--()
	{
		assert(_node);
		if (_node->_lefTag == LINK)//左子树的最右结点
		{
			Node* tmp = _node->_left;
			while (tmp && tmp->_right == LINK)
			{
				tmp = tmp->_right;
			}
			_node = right;
		}
		else
		{
			_node = _node->_left;
		}
		return *this;
	}
	Self operator--(int)
	{
		Self tmp(*this);
		--(*this);
		return tmp;
	}

	bool operator!=(const Self& iter) const
	{
		return _node != iter._node;
	}
	Ref operator*()
	{
		assert(_node);
		return _node->_data;
	}

	Node* _node;
};



template <typename T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
public:
	typedef __TreeIterator<T, T&, T*>  Iterator;
	typedef __TreeIterator<T, const T&, const T*>  ConstIterator;

	Iterator Begin()
	{
		Node* cur = _root;
		while (cur && cur->_leftTag == LINK)
		{
			cur = cur->_left;
		}
		return Iterator(cur);
	}
	Iterator End()
	{
		return Iterator(0);
	}

	BinaryTreeThd(T *arr, size_t& sz, const T& invalid)//invalid必须要传递const 类型的引用
	{
		size_t index = 0;
		_root = _CreatTree(arr, sz, invalid, index);
	}
	~BinaryTreeThd()
	{
		Node* cur = _root;
		Node* del = NULL;
		while (cur != NULL)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			while (cur->_rightTag == THREAD)
			{
				del = cur;
				cur = cur->_right;
				delete del;
				del = NULL;
			}

			del = cur;
			cur = cur->_right;
			delete del;
			del = NULL;

		}
	}
	void InThreading()
	{
		if (_root != NULL)
		{
			Node* prev = NULL;
			_inthreading(_root, prev);
		}
	}
	void InOrder()
	{
		Node* cur = _root;
		while (cur != NULL)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while (cur->_rightTag == THREAD)  // 防止单链，if--->while
			{
				cur = cur->_right;
				cout << cur->_data << " ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}
protected:
	Node* _CreatTree(int *arr, size_t& sz, const  T& invalid, size_t& index)//index需要传引用，保证在递归的过程中index一直在改变
	{
		Node* root = NULL;
		if (index < sz && arr[index] != invalid)
		{
			root = new Node(arr[index]);

			root->_left = _CreatTree(arr, sz, invalid, ++index);
			root->_right = _CreatTree(arr, sz, invalid, ++index);
		}
		return root;
	}

	void _inthreading(Node* cur,Node*& prev)
	{
		//访问到最左结点
		if (cur == NULL)
			return;
		_inthreading(cur->_left, prev);
		
		if (cur->_left == NULL)
		{
			cur->_leftTag = THREAD;
			cur->_left = prev;
		}
		if (prev && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;//cur回退到上一层的时候，进行序列化，从下往上指
			prev->_right = cur;
		}
		
		prev = cur;
		//prev保存最后一个序列化的结点
		_inthreading(cur->_right, prev);
	}
protected:
	Node* _root;
};

void TestInBinaryTreeThd()
{
	int array[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	size_t sz1 = sizeof(array) / sizeof(array[0]);
	BinaryTreeThd<int> t1((int*)array, sz1, '#');
	t1.InThreading();
	t1.InOrder();
	BinaryTreeThd<int>::Iterator it = t1.Begin();
	while (it != t1.End())
	{
		cout << *it <<" ";
		++it;
	}
	cout << endl;
}