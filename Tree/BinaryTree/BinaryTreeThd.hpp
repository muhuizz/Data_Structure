#pragma once
/**************项目名称与简介*************	
		二叉树线索化
***********************************/

#include <iostream>
using namespace std;

enum PointTag
{
	THREAD,
	LINK
};

template<typename T>
struct BinaryTreeThdNode
{
	T _value;
	BinaryTreeThdNode<T>* _left;
	BinaryTreeThdNode<T>* _right;
	PointTag _leftTag;
	PointTag _rightTag;
	BinaryTreeThdNode(const T& value = T())
		:_value(value)
		, _left(NULL)
		, _right(NULL)
		, _leftTag(LINK)
		, _rightTag(LINK)
	{}
};

template<typename T>
class BinaryTreeThd
{
	typedef BinaryTreeThdNode<T> Node;
public:
	BinaryTreeThd(T* arr, size_t sz, const T& invalid)
	{
		size_t index = 0;
		_root = _creatBinaryTree(arr, index, sz, invalid);
	}
	~BinaryTreeThd()	// 序列化后，原来所有的析构函数需要重新设定，不同序列化方式的结果，需要对应不同的析构函数
	{
	//	_destory(_root);
	}
	void PreThreading()	// 前序序列化后，_root依旧为第一个结点
	{
		Node* prev = NULL;
		_preThreading(_root, prev);
	}
	void PrevThdOrder()	// 前序序列化遍历
	{
		cout << "前序序列化遍历" << endl;
		Node* cur = _root;
		while (cur)
		{
			cout << cur->_value << " ";
			if (cur->_leftTag == THREAD)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		cout << endl;
	}

	void InThreading()	// 中序序列化
	{
		Node* prev = NULL;
		_inThreading(_root, prev);
	}
	void InThdOrder()	// 中序序列化遍历
	{
		cout << "中序序列化遍历" << endl;
		if (_root == NULL)
			return;
		Node* cur = _root;
		// 此时cur为中序遍历的起点
		while (cur)
		{
			while (cur->_leftTag == LINK)
			{
				cur = cur->_left;
			}
			cout << cur->_value << "  ";
			while (cur->_rightTag == THREAD)
			{
				cur = cur->_right;
				cout << cur->_value << "  ";
			}
			cur = cur->_right;
		}
		cout << endl;
	}
protected:
	Node* _creatBinaryTree(T* arr, size_t& index, size_t sz, const T& invalid)
	{
		Node* node = NULL;
		if (index < sz && arr[index] != invalid)
		{
			node = new Node(arr[index]);
			node->_left = _creatBinaryTree(arr, ++index, sz, invalid);
			node->_right = _creatBinaryTree(arr, ++index, sz, invalid);
		}
		return node;
	}
	void _preThreading(Node* node, Node*& prev)		// prev必须传递引用
	{
		if (node == NULL)
			return;
		if (node->_left == NULL)
		{
			node->_left = prev;
			node->_leftTag = THREAD;
		}
		if (prev != NULL && prev->_right == NULL)
		{
			prev->_right = node;
			prev->_rightTag = THREAD;
		}
		prev = node;
		// 线索化左子树
		if (node->_leftTag == LINK)
			_preThreading(node->_left, prev);
		// 线索化右子树
		if (node->_rightTag == LINK)
			_preThreading(node->_right, prev);
	}
	void _inThreading(Node* node, Node*& prev)
	{
		if (node == NULL)
			return;
		if (node->_leftTag == LINK)
			_inThreading(node->_left, prev);
		if (node->_left == NULL)
		{
			node->_left = prev;
			node->_leftTag = THREAD;
		}
		if (prev != NULL && prev->_right == NULL)
		{
			prev->_right = node;
			prev->_rightTag = THREAD;
		}
		prev = node;
		if (node->_rightTag == LINK)
			_inThreading(node->_right, prev);
	}

protected:
	Node* _root;
};

void TestBinaryTreeThd()
{
	//int array1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	size_t sz1 = sizeof(array1) / sizeof(array1[0]);
	BinaryTreeThd<int> tree1(array1, sz1, '#');
	tree1.PreThreading();
	tree1.PrevThdOrder();
	//tree1.InThreading();
	//tree1.InThdOrder();
}