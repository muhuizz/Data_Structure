#pragma once
/**************项目名称与简介*************	
				普通二叉树
包含：
	递归与非递归前中后序遍历
	层序遍历
	Size();	Depth();
***********************************/
#include <stack>
#include <queue>

template<class T>
struct BinaryTreeNode
{
	BinaryTreeNode* _left;
	BinaryTreeNode* _right;
	T _value;
	BinaryTreeNode(const T& x)
		: _left(NULL)
		, _right(NULL)
		, _value(x)
	{}
};

template <class T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree(T* data, size_t size, const T& invalid)	
	{
		size_t i = 0;
		_root = _createBinaryTree(data, i, size, invalid);
	}
	BinaryTree(const BinaryTree<T>& t)
	{
		_root = _copy(t._root);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)
	{
		if (this != &t)
		{
			Node* newRoot = _copy(t._root);
			_destory(_root);
			_root = newRoot;
		}
		return *this;
	}
	~BinaryTree()
	{
		_destory(_root);
	}
public:
	void PreOrder()	// 前序递归遍历
	{
		cout << "前序遍历：";
		_preorder(_root);
		cout << endl;
	}

	void InOrder()	// 递归中序遍历
	{
		cout << "中序遍历：";
		_inorder(_root);
		cout << endl;
	}

	void PostOrder()	// 递归后续遍历
	{
		cout << "后序遍历：";
		_postorder(_root);
		cout << endl;
	}

	void PreOrdrNonR()	// 前序非递归遍历
	{
		cout << "前序遍历：";
		if (_root == NULL)
			return;
		stack<Node*> sta;		
		Node* top = NULL;
		Node* cur = _root; 
		while (!sta.empty() || cur != NULL)
		{
			while (cur != NULL)
			{
				cout << cur->_value << "  ";
				sta.push(cur);
				cur = cur->_left;
			}
			top = sta.top();
			cur = top->_right;
			sta.pop();
		}
		cout << endl;
	}
	void InOrdrNonR()	// 中序非递归遍历
	{
		cout << "中序遍历：";
		if (_root == NULL)
			return;
		stack<Node*> sta;
		Node* cur = _root;
		Node* top = NULL;
		while (!sta.empty() || cur != NULL)
		{
			while (cur != NULL)
			{
				sta.push(cur);
				cur = cur->_left;
			}
			top = sta.top();
			cout << top->_value << "  ";
			sta.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrdrNonR()	// 后序非递归遍历
	{
		cout << "后序遍历：";
		if (_root == NULL)
			return;
		Node* cur = _root;
		Node*prev = NULL;
		stack<Node*> sta;
		while (cur != NULL || !sta.empty())
		{
			while (cur != NULL)
			{
				sta.push(cur);
				cur = cur->_left;
			}
			Node* top = sta.top();
			if (top->_right == NULL || top->_right == prev)
			{
				cout << top->_value << "  ";
				prev = top;
				sta.pop();
			}
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}

	void LevelOrder()	// 层序遍历
	{
		cout << "层序遍历：";
		if (_root == NULL)
			return;
		queue<Node*> que;		
		que.push(_root);
		while (!que.empty())
		{
			Node* front = que.front();
			if (front->_left != NULL)
				que.push(front->_left);
			if (front->_right != NULL)
				que.push(front->_right);
			cout << front->_value << "  ";
			que.pop();
		}
		cout << endl;
	}

	size_t Size()	// 树中元素个数
	{
		return _size(_root);
	}

	size_t Depth()	// 树的深度
	{
		return _depth(_root);
	}
	size_t LeafNum()
	{
		return _leafnum(_root);
	}
	size_t NumKLevel(size_t k)
	{
		return _numklevel(_root, k);
	}
	Node* FindNum(const T& x)
	{
		return _find(_root, x);
	}
protected:
	void _preorder(Node* node)
	{
		if (node == NULL)
		{
			return;
		}
		cout << node->_value << "  ";
		_preorder(node->_left);
		_preorder(node->_right);
	}
	void _inorder(Node* node)
	{
		if (node == NULL)
			return;
		_inorder(node->_left);
		cout << node->_value << "  ";
		_inorder(node->_right);
	}
	void _postorder(Node* node)
	{
		if (node == NULL)
			return;
		_postorder(node->_left);
		_postorder(node->_right);
		cout << node->_value << "  ";
	}
	size_t _size(Node* node)
	{
		if (node == NULL)
			return 0;
		return _size(node->_left) + _size(node->_right) +1;
	}
	size_t _depth(Node* node)
	{
		if (node == NULL)
			return 0;
		size_t left_depth = _depth(node->_left);
		size_t right_depth = _depth(node->_right);
		return left_depth > right_depth ? left_depth +1: right_depth+1;
	}
	size_t _leafnum(Node* root)
	{
		if (root == NULL)
			return 0;
		if (root->_left == NULL && root->_right == NULL)
			return 1;
		return _leafnum(root->_left) + _leafnum(root->_right);
	}
	size_t _numklevel(Node* root, const size_t k)
	{
		if (root == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _numklevel(root->_left, k - 1) + _numklevel(root->_right, k - 1);
	}
	Node* _find(Node* root, const T& x)
	{
		Node* ret = NULL;
		if (root == NULL)
			return NULL;
		if (root->_value == x)
			return root;
		ret  = _find(root->_left, x);
		if (ret == NULL)
			ret = _find(root->_right, x);
		return ret;
	}
protected:
	Node* _createBinaryTree(T* data, size_t& index, const size_t& size, const T& invalid)
	{
		if (index >= size)
			return NULL;
		
		Node* node = NULL;
		if (data[index] != invalid)
		{
			node = new Node(data[index]);
			node->_left = _createBinaryTree(data, ++index, size, invalid);
			node->_right = _createBinaryTree(data, ++index, size, invalid);		// 注释1
		}
		return node;
	}

	Node* _copy(Node* root)
	{
		if (root == NULL)
			return NULL;
		Node* node = new Node(root->_value);
		node->_left = _copy(root->_left);
		node->_right = _copy(root->_right);
		return node;
	}
	void _destory(Node* root)
	{
		if (root == NULL)
			return;
		_destory(root->_left);
		_destory(root->_right);
		delete root;
	}
protected:
	Node* _root;
};

void TestBinaryTree()
{
	//int array1[] = { 1, 2, 3, '#', '#', 4, '#', 7, '#', '#', 5, 6 };	// 中序
	//int array1[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	int array1[] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, 9, 10, '#', '#', '#', '#', 8 };

	int sz = sizeof(array1) / sizeof(array1[0]);
	BinaryTree<int> tree1(array1, sz, '#');
	BinaryTree<int> tree2 = tree1;

	tree2.PreOrder();
	tree2.InOrder();
	tree2.PostOrder();
	cout << "----------" << endl;
	tree2.PreOrdrNonR();
	tree2.InOrdrNonR();
	tree2.PostOrdrNonR();
	tree2.LevelOrder();
	cout << "元素个数-->" << tree2.Size() << endl;
	cout << "二叉树的深度-->" << tree2.Depth() << endl;
	cout << "叶子结点的数目："<< tree2.LeafNum() << endl;
	cout << "某个结点的Node：" << tree2.FindNum(99) << endl;
	cout << "第7层结点的数目：" << tree2.NumKLevel(3) << endl;
}




/*
注释1：
	由于这里的index要传递引用，因此，index不可以为后置++。		通过调整其他地方，实现前置++。

注释2：
	对比三种非递归排序：
		前序在入栈的时候就进行输出结点内容；
		中序在出栈的时候输出结点内容；
		后序也是在出栈的时候不一定要打印内容，需要进行判断，因此多保留一个prev指针
*/