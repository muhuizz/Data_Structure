#pragma once
/**************项目名称与简介*************
		AVL树
	AVL树也是一棵平衡树，一棵高度平衡的二叉树，要求右子树的高度减去左子树的高度差的绝对值不超过1
	高度差使用平衡因子来表示
***********************************/
#include <iostream>
using namespace std;

template <typename K, typename V>
struct AVLTreeNode
{
	int _bf;			// 平衡因子
	K _key;			// 关键字 
	V _value;		// 值
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	AVLTreeNode(const K& key)			// 只考虑关键字， 不考虑值
		: _bf(0)
		, _key(key)
		, _value(0)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template<typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		: _root(NULL)
	{}

	AVLTree(const AVLTree<K, V>& t)
	{
		_root = _CopyAVLTree(t._root);
	}

	AVLTree<K, V>& operator=(const AVLTree<K, V>& t)
	{
		if (this != &t)
		{
			_root = _CopyAVLTree(t._root);
		}
		return *this;
	}

	// 插入结点
	bool Insert(const K& x)
	{
		// 空树
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}

		// 不是空树
		// 找到位置并插入结点
		Node* cur = _root;
		Node* parent = NULL;
		Node* node = NULL;
		while (cur != NULL)
		{
			parent = cur;
			if (x > cur->_key)
				cur = cur->_right;
			else if (x < cur->_key)
				cur = cur->_left;
			else
				return false;
		}
		node = new Node(x);
		node->_parent = parent;
		if (x > parent->_key)
			parent->_right = node;
		else		// x < parent->_key
			parent->_left = node;

		// 进行调整（逐层向上进行调整）
		while (parent)									// 注释1
		{
			// 调整parent的平衡因子
			if (x > parent->_key)
				parent->_bf++;
			else		// x < parent->_key
				parent->_bf--;
			// 判断是否需要继续向上进行调整
			if (parent->_bf == 0)					// 注释2
				return true;
			else if (parent->_bf == 1 || parent->_bf == -1)		// 满足平衡，但因为改变了parent的平衡因子，因此优肯会改变更高树的平衡
			{
				cur = parent;
				parent = cur->_parent;
			}
			else			// 不满足平衡，需要进行旋转
			{
				if (parent->_bf == 2)
				{
					
					if (cur->_bf == 1)
						_RotateL(parent);
					else		// cur->_bf == -1
						_RotateRL(parent);
					break;
					
				}
				else		// parent->_bf == -2
				{
					if (cur->_bf == 1)
						_RotateLR(parent);
					else
						_RotateR(parent);
					break;
				}
			}
		}
		return true;
	}
protected:
	void _RotateL(Node* node){}
	void _RotateR(Node* node){}
	void _RotateLR(Node* node){}
	void _RotateRL(Node* node){}
protected:
	Node* _root;
};


void TestAVLTree()
{
	// int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> tree;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		tree.Insert(arr[i]);
	}
}


/*
注释1：新增一个结点不一定只会改变以parent为根的子树的平衡，还有可能继续影响更高树的平衡
			因此需要不断，制止根节点，即parent为NULL

注释2：如果parent的平衡因子进行调整之后变为0，表明插入的结点之前，parent的平衡因子为1或-1，
		新增结点导致了以parent为根节点的子树左右平衡，但并未增加该子树的高度
		因此，一旦parent的平衡因子为0，就不需要继续向上调整

*/