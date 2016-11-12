#pragma once 

#include <iostream>
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

	BinaryTreeNodeThd(const T& x = T())
		:_data(x)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}

};

template <typename T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
	typedef BinaryTreeIterator<T, T&, T*> Iterator;
	typedef BinaryTreeIterator<T, const T&, const T*> ConstIterator;

public:
	BinaryTreeThd(T *arr, size_t sz, T invalid)
	{
		size_t index = 0;
		_root = _CreatTree(arr, sz, invalid, index);
	}
	void PrevTreeThding()
	{
		if (_root == NULL)
			return;
		Node* prev = NULL;
		_PrevTreeThding(_root,prev);
	}
	void PrevTreeThdOrder()
	{
		Node* cur = _root;
		while (cur)
		{
			cout << cur->_data << " ";
			if (cur->_leftTag == THREAD)
				cur = cur->_right;
		}
	}

private:
	Node* _CreatTree(int *arr, size_t sz, T& invalid, size_t& index)//index需要传引用，保证在递归的过程中index一直在改变
	{
		Node* root = NULL;
		if ((index < sz) && (arr[index] != invalid))
		{
			root = new Node(arr[index]);
			root->_left = _CreatTree(arr, sz, invalid, ++index);
			root->_right = _CreatTree(arr, sz, invalid, ++index);
		}
		return root;
	}
	void _PrevTreeThding(Node* cur,Node*& prev)
	{
		//if (cur == NULL)
		//	return;
		////Prev先处理，之后左循环、右循环
		////先序列化左边
		//if (cur->_left == NULL)
		//{
		//	cur->_left = prev;
		//	cur->_leftTag = THREAD;
		//}
		//if (prev && prev->_right == NULL)
		//{
		//	prev->_rightTag = THREAD;
		//	prev->_right = cur;
		//}
		//prev = cur;
		//if (cur->_leftTag == LINK)
		//	_PrevTreeThding(cur,prev);
		//if (cur->_rightTag == LINK)
		//	_PrevTreeThding(cur, prev);



		if (cur == NULL)
		{
			return;
		}
		if (cur->_left == NULL)
		{
			cur->_leftTag == THREAD;
			cur->_left = prev;
		}
		if (prev != NULL && prev->_right == NULL)
		{
			prev->_rightTag = THREAD;
			prev->_right = cur;
		}

		//prev永远保存最后一个序列化过的结点
		prev = cur;

		if (cur->_leftTag == LINK)
			_PrevTreeThding(cur->_left,prev);
		if (cur->_rightTag == LINK)
			_PrevTreeThding(cur->_right, prev);
	}
private:
	Node* _root;
};


void TestBinaryTreeThd()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	size_t sz1 = sizeof(array1) / sizeof(array1[0]);
	BinaryTreeThd<int> tree1(array1, sz1, '#');
	tree1.PrevTreeThding();
	tree1.PrevTreeThdOrder();
}