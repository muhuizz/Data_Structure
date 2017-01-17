#pragma once

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
	T _data;
	BinaryTreeNode<T> *_left;
	BinaryTreeNode<T>* _right;
	BinaryTreeNode(const T& x)
		:_data(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	//默认函数
	BinaryTree(int *arr, size_t sz,T invalid)
	{
		size_t index = 0;
		_root = _CreatTree(arr, sz, invalid, index);
	}
	BinaryTree(const BinaryTree<T>& tree)
	{
		_root = _Copy(tree._root);
	}
	BinaryTree<T> operator=(const BinaryTree<T>& tree)
	{
		if (this != &tree)
		{
			Node* tmp = _Copy(tree._root);
			_Destory(_root);
			_root = tmp;
		}
		return *this;
	}
	~BinaryTree()
	{
		_Destory(_root);
	}

	//递归遍历
	void PreOrder()
	{
		_preorder(_root);
		cout << endl;
	}
	void InOrder()
	{
		_inorder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		_postorder(_root);
		cout << endl;
	}

	//非递归遍历
	void PreOrderNonR()
	{
		stack<Node*> sta;
		Node* cur = _root;
		if (cur == NULL)
		{
			return;
		}
		while ((cur != NULL) || (!sta.empty()))
		{
			while (cur != NULL)
			{
				sta.push(cur);
				cout << cur->_data << "  ";
				cur = cur->_left;
			}
			Node* top = sta.top();
			sta.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void InOrderNonR()
	{
		Node* cur = _root;
		stack<Node*> sta;
		while ((cur != NULL) || (!sta.empty()))
		{
			while (cur)
			{
				sta.push(cur);
				cur = cur->_left;
			}
			Node* top = sta.top();
			cout << top->_data << "  ";
			sta.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	void PostOrderNonR()
	{
		Node* cur = _root;
		stack<Node*> sta;
		Node* prev = NULL;
		while ((cur != NULL) || (!sta.empty()))
		{
			while (cur)
			{
				sta.push(cur);
				prev = cur;
				cur = cur->_left;
			}
			Node* top = sta.top();

			if ((top->_right == NULL) || (top->_right == prev))
			{
				cout << top->_data << "  ";
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
	void LevelOrder()
	{
		queue<Node*> myqueue;
		Node* front = NULL;
		if (_root != NULL)
		{
			myqueue.push(_root);
		}
		while ((!myqueue.empty()))
		{
			front = myqueue.front();
			cout << front->_data << "  ";
			myqueue.pop();
			if (front->_left != NULL)
			{
				myqueue.push(front->_left);
			}
			if (front->_right != NULL)
			{
				myqueue.push(front->_right);
			}
		}
		cout << endl;
	}

	//其他函数
	size_t Size()
	{
		return _size(_root);
	}
	size_t Depth()
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
	Node* _Copy(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		Node* newroot = new Node(root->_data);
		newroot->_left = _Copy(root->_left);
		newroot->_right = _Copy(root->_right);
		return newroot;
	}
	void _Destory(Node* root)//后序delete，确保两个孩子都被释放之后，在释放根节点
	{
		if (root == NULL)
		{
			return;
		}
		_Destory(root->_left);
		_Destory(root->_right); 
		delete root;
	}

	//遍历
	void _preorder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->_data<<"  ";
		_preorder(root->_left);
		_preorder(root->_right);
	}
	void _inorder(Node* root)
	{
		if (root == NULL)
			return;
		_inorder(root->_left);
		cout << root->_data << "  ";
		_inorder(root->_right);
	}
	void _postorder(Node* root)
	{
		if (root == NULL)
			return;
		_postorder(root->_left);
		_postorder(root->_right);
		cout << root->_data << "  ";
	}

	//size
	size_t _size(Node* root)
	{
		if (root == NULL)
			return 0;
		return _size(root->_left) + _size(root->_right) + 1;
	}
	size_t _depth(Node* root)
	{
		if (root == NULL)
			return 0;
		return _depth(root->_left) > _depth(root->_right) ? _depth(root->_left)+1 : _depth(root->_right)+1;
	}
	size_t _leafnum(Node* root)
	{
		if (root == NULL)
			return 0;
		if ((root->_left == NULL) && (root->_right == NULL))
			return 1;
		return _leafnum(root->_left) + _leafnum(root->_right);
	}
	//size_t _leafnum(Node* root)
	//{
	//	static size_t num = 0;//静态变量做多组测试时会累加，出错
	//	if (root == NULL)
	//		return 0;
	//	if ((root->_left == NULL) && (root->_right == NULL))
	//		num++;
	//	_leafnum(root->_left);
	//	_leafnum(root->_right);
	//	return num;
	//}
	size_t _numklevel(Node* root,size_t k)
	{
		if (root == NULL)
			return 0;
		if (k == 1)
			return 1;
		return _numklevel(root->_left, k - 1) + _numklevel(root->_right, k - 1);
	}

	Node* _find(Node* root,const T& x)
	{
		if (root == NULL)
			return NULL;
		if (root->_data == x)
		{
			return root;
		}
		Node* ret = NULL;
		ret = _find(root->_left, x);
		if (ret == NULL)
		{
			ret = _find(root->_right,x);
		}
		return ret;
	}
protected:
	Node* _root;
};





void TestBinaryTree()
{
	int array1[10] = { 1, 2, 3, '#', '#', 4, '#', '#', 5, 6 };
	size_t sz1 = sizeof(array1) / sizeof(array1[0]);
	BinaryTree<int> tree1(array1, sz1, '#');
	tree1.PreOrder();
	tree1.InOrder();
	tree1.PostOrder();
	//BinaryTree<int> tree1tmp = tree1;
	//tree1tmp.PreOrder();
	//tree1tmp.InOrder();
	//tree1tmp.PostOrder();

	//cout << "层序遍历" << endl;
	//tree1.LevelOrder();
	tree1.PreOrderNonR();
	tree1.InOrderNonR();
	tree1.PostOrderNonR();

	cout << "节点个数" << tree1.Size() << endl;
	cout << "叶子节点个数" << tree1.LeafNum() << endl;
	cout << "深度" << tree1.Depth() << endl;
	cout << "NumKLevel" << tree1.NumKLevel(4) << endl;


	BinaryTreeNode<int> *ret = tree1.FindNum(9);
	if (ret != NULL)
		cout << ret->_data << endl;
	//************************************************************************************************************
	int array2[15] = { 1, 2, '#', 3, '#', '#', 4, 5, '#', 6, '#', 7, '#', '#', 8 };
	size_t sz2 = sizeof(array2) / sizeof(array2[0]);
	BinaryTree<int> tree2(array2, sz2, '#');
	tree2.PreOrder();
	tree2.InOrder();
	tree2.PostOrder();
	//tree1tmp = tree2;
	//tree1tmp.PreOrder();
	//tree1tmp.InOrder();
	//tree1tmp.PostOrder();

	//cout << "层序遍历" << endl;
	//tree2.LevelOrder();
	tree2.PreOrderNonR();
	tree2.InOrderNonR();
	tree2.PostOrderNonR();

	cout << "节点个数" << tree2.Size() << endl;
	cout << "叶子节点个数" << tree2.LeafNum() << endl;
	cout << "深度" << tree2.Depth() << endl;
	cout << "NumKLevel" << tree2.NumKLevel(4) << endl;


	ret = tree2.FindNum(8);
	cout << ret->_data << endl;
}