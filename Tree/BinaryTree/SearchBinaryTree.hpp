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
	// 中序遍历
	void InOrder()		// 中序遍历搜索二叉树的结果一定是有序的
	{
		_inOrder(_root);
		cout << endl;
	}
	// 递归插入结点
	bool InsertR(const T& x)
	{
		return _insertR(_root, x);
	}
	// 递归删除结点
	bool RemoveR(const T& x)	// 注释2
	{
		return _removeR(_root,x);
	}
	// 查找结点
	bool Find(const T& x)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_value < x)
				cur = cur->_right;
			else if (cur->_value > x)
				cur = cur->_left;
			else
				return true;
		}
		return false;
	}
	// 非递归插入
	bool Insert(const T& x)			// 注释4
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)		// 找到待插入点
		{
			if (x > cur->_value)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (x < cur->_value)
			{
				parent = cur;
				cur = cur->_left;
			}
			else  // x == cur->_value
			{
				return false;
			}
		}
		if (x > parent->_value)
			parent->_right = new Node(x);
		else    // x < parent->_value
			parent->_left = new Node(x);
		return true;
	}
	// 非递归删除
	bool Remove(const T& x)
	{
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_value == x)   //	找到该结点，并删除
			{
				Node* del = cur;
				if (cur->_left == NULL)		// 判断cur哪个子树为NULL
				{
					if (parent == NULL)	// cur为根节点
						_root = cur->_right;
					else if (cur == parent->_left)		// 判断cur为parent的哪个子树
						parent->_left = cur->_right;
					else  //cur == parent->_right
						parent->_right = cur->_right;
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)	// cur为根节点
						_root = cur->_left;
					else if (cur == parent->_left)		// 判断cur为parent的哪个子树
						parent->_left = cur->_left;
					else  //cur == parent->_right
						parent->_right = cur->_left;
				}
				else		// 两个孩子--->替换法删除，寻找左子树的最右结点
				{
					del = cur->_left;
					parent = cur;
					while (del->_right)
					{
						parent = del;
						del = del->_right;
					}
					cur->_value = del->_value;
					if (del == parent->_left)
						parent->_left = del->_left;
					else
						parent->_right = del->_left;
				}
				delete del;
				del = NULL;
				return true;
			}
			else if (x > cur->_value)
			{
				parent = cur;
				cur = cur->_right;
			}
			else  // x < cur->_value 
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		return false;
	}
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

	void _inOrder(Node* root)
	{
		if (root != NULL)
		{
			_inOrder(root->_left);
			cout << root->_value << "  ";
			_inOrder(root->_right);
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
			Node* del = node;
			if (node->_left == NULL)
				node = node->_right;
			else if (node->_right == NULL)
				node = node->_left;
			else  // node->_left != NULL && node->_right != NULL，找左子树的最右结点
			{
				del = node->_left;
				Node* parent = node;
				while (del->_right)
				{
					parent = del;
					del = del->_right;
				}
				node->_value = del->_value;
				if (del == parent->_left)		// 注释3
					parent->_left = del->_left;
				else
					parent->_right = del->_left;
			}
			delete del;
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
		//tree.InsertR(arr[i]);
		tree.Insert(arr[i]);
	}
	tree.InOrder();
	tree.Remove(9);
	tree.InOrder();
	cout << "----------" << endl;
	cout << "5存在否？ " << tree.Find(5) << endl;
}

/*
注释1： 因为插入结点的位置原来一定是NULL，
			  换句话说，插入结点，node的指向一定会发生改变，从指向NULL，变为指向一个结点
			  因此这里必须传递引用，否则就需要多维护一个parent指针来保证插入的正确性
注释2：删除搜索树中的一个结点，那么就一定需要将以该点为根，左子树的最右结点或者右子树是最左结点与之交换
			从而维持搜索树的性质
注释3：此时cur为左子树的最右结点，但cur依然可能有左子树，因此要对cur的左子树悬挂点进行判断
			如果选择的是右子树的最左结点，处理方法相同，不同的是考虑的是cur的右子树悬挂点
注释4：非递归插入一个结点，有两种实现，一种是使用parent，一种不使用parent
			使用parent的方式如上述代码；
			不使用parent的方式是在while()循环内部，当x大于或者小于cur->_value时，判断此时cur该侧的子结点是否为NULL
*/

