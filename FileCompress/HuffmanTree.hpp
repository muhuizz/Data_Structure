#pragma once 
#include <iostream>
#include "HEAP.hpp"
using namespace std;

template <typename T>
struct HuffmanTreeNode
{
	T _weight;
	HuffmanTreeNode* _left;
	HuffmanTreeNode* _right;
	HuffmanTreeNode* _parent;
	HuffmanTreeNode(const T& x= T())
		:_weight(x)
		, _right(NULL)
		, _left(NULL)
		, _parent(NULL)
	{}
};

template <typename T>
class HuffmanTree
{
	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(T* a, size_t size,const T& invalid)
	{
		//仿函数
		struct MIN_NODE
		{
			bool operator()(const Node* l,const Node* r)
			{
				return (l->_weight) < (r->_weight);
			}
		};
		//HuffmanTree要构建最小堆
		HEAP<Node*, MIN_NODE> min_heap;
		for (size_t i = 0; i < size; i++)
		{
			if (a[i] != invalid)
			{
				Node* newnode = new Node(a[i]);
				min_heap.Push(newnode);
			}
		}
		
		//构建HuffmanTree，每次去除最小的两个Node
		while (!min_heap.Empty())
		{
			Node* left = min_heap.Top();
			min_heap.Pop();
			if (min_heap.Empty())
			{
				_root = left;
			}
			else
			{
				Node* right = min_heap.Top();
				min_heap.Pop();
				Node* parent = new Node(left->_weight + right->_weight);

				parent->_left = left;
				parent->_right = right;
				left->_parent = parent;
				right->_parent = parent;
				min_heap.Push(parent);
				_root = parent;
			}
		}
	}
	Node* GetRoot()
	{
		return _root;
	}
private:
	Node* _root;
};

//void Test()
//{
//	int a[] = { 1, 2, 3, 4, 0 };
//	size_t size = sizeof(a) / sizeof(a[0]);
//	HuffmanTree<int> tree((int*)a, size,10);
//}