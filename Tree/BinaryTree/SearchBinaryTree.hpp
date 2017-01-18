#pragma once
/**************项目名称与简介*************	
		搜索二叉树
***********************************/
#include <iostream>
using namespace std;

template<typename T>
struct SearchBinaryTreeNode
{
	SearchBinaryTreeNode<T>* _left;
	SearchBinaryTreeNode<T>* _right;
	T _value;
	SearchBinaryTreeNode(const T& x)
		: _value(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<typename T>
class SearchBinaryTree
{
	typedef SearchBinaryTreeNode<T> Node;
public:		// 默认成员函数
	SearchBinaryTree()
		: _root(NULL)
	{}
	SearchBinaryTree(const SearchBinaryTree<T>& t)
	{
		_root = _copySearchBinaryTree(t._root);
	}
	SearchBinaryTree<T>& operator=(const SearchBinaryTree<T>& t)
	{
		if (this != &t)
		{
			SearchBinaryTree<T> tmp(t);	// 传递引用，当不是自赋值的情况下再进行拷贝
			std::swap(this->_root, tmp._root);
		}
		return *this;
	}
	~SearchBinaryTree()
	{
		_destory(_root);
	}
public:		// 自定义成员函数
	// 前序遍历
	void PreOrder()		// 前序遍历搜索二叉树的结果一定是有序的
	{
		_preOrder(_root);
		cout << endl;
	}
	// 插入结点
	bool InsertR(const T& x)
	{
		return _insertR(_root, x);
	}
	// 删除结点
	bool RemoveR(const T& x)	// 注释2
	{
		return _removeR(_root,x);
	}
	//	void Inorder()
	//	bool Find(const T& x)
	//	bool Insert(const T& x)
	//	bool Insert(const T& x)
protected:	// 私有内置成员函数
	Node* _copySearchBinaryTree(Node* node)
	{
		if (node != NULL)
		{
			Node* tmp = new Node(node->_value);
			tmp->_left = _copySearchBinaryTree(node->_left);
			tmp->_right = _copySearchBinaryTree(node->_right);
			return tmp;
		}
		return NULL;
	}
	
	void _destory(Node* root)
	{
		if (root != NULL)
		{
			_destory(root->_left);
			_destory(root->_right);
			delete root;
		}
	}

	void _preOrder(Node* root)
	{
		if (root != NULL)
		{
			_preOrder(root->_left);
			cout << root->_value << "  ";
			_preOrder(root->_right);
		}
	}
	
	bool _insertR(Node*& node, const T& x)		// 注释1
	{
		if (node == NULL)
		{
			node = new Node(x);
			return true;
		}
		if (x > node->_value)
			return _insertR(node->_right, x);
		else if (x < node->_value)
			return _insertR(node->_left, x);
		else
			return false;
	}

	bool _removeR(Node*& node, const T& x)
	{
		if (node == NULL)
			return false;
		if (x > node->_value)
			return _removeR(node->_right, x);
		else if (x < node->_value)
			return _removeR(node->_left, x);
		else // x == node->_value，删除该结点
		{
			if (node->_left == NULL)
				node = node->_right;
			else if (node->_right == NULL)
				node = node->_left;
			else  // node->_left != NULL && node->_right != NULL，找左子树的最右结点
			{
				Node* cur = node->_left;
				Node* parent = node;
				while (cur->_right)
				{
					parent = cur;
					cur = cur->_right;
				}
				node->_value = cur->_value;
				if (cur == parent->_left)		// 注释3
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
				delete cur;
			}
			return true;
		}
	}
protected:
	Node* _root;
};

void TestSearchBinaryTree()
{
	//int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int arr[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	SearchBinaryTree<int> tree;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		tree.InsertR(arr[i]);
	}
	tree.PreOrder();
	tree.RemoveR(5);
	tree.PreOrder();

}

/*
注释1： 因为插入结点的位置原来一定是NULL，
			  换句话说，插入结点，node的指向一定会发生改变，从指向NULL，变为指向一个结点
			  因此这里必须传递引用，否则就需要多维护一个parent指针来保证插入的正确性
注释2：删除搜索树中的一个结点，那么就一定需要将以该点为根，左子树的最右结点或者右子树是最左结点与之交换
			从而维持搜索树的性质
注释3：此时cur为左子树的最右结点，但cur依然可能有左子树，因此要对cur的左子树悬挂点进行判断
			如果选择的是右子树的最左结点，处理方法相同，不同的是考虑的是cur的右子树悬挂点
*/

