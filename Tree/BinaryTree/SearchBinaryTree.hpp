#pragma once
/**************��Ŀ��������*************	
		����������
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
public:		// Ĭ�ϳ�Ա����
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
			SearchBinaryTree<T> tmp(t);	// �������ã��������Ը�ֵ��������ٽ��п���
			std::swap(this->_root, tmp._root);
		}
		return *this;
	}
	~SearchBinaryTree()
	{
		_destory(_root);
	}
public:		// �Զ����Ա����
	// ǰ�����
	void PreOrder()		// ǰ����������������Ľ��һ���������
	{
		_preOrder(_root);
		cout << endl;
	}
	// ������
	bool InsertR(const T& x)
	{
		return _insertR(_root, x);
	}
	// ɾ�����
	bool RemoveR(const T& x)	// ע��2
	{
		return _removeR(_root,x);
	}
	//	void Inorder()
	//	bool Find(const T& x)
	//	bool Insert(const T& x)
	//	bool Insert(const T& x)
protected:	// ˽�����ó�Ա����
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
	
	bool _insertR(Node*& node, const T& x)		// ע��1
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
		else // x == node->_value��ɾ���ý��
		{
			if (node->_left == NULL)
				node = node->_right;
			else if (node->_right == NULL)
				node = node->_left;
			else  // node->_left != NULL && node->_right != NULL���������������ҽ��
			{
				Node* cur = node->_left;
				Node* parent = node;
				while (cur->_right)
				{
					parent = cur;
					cur = cur->_right;
				}
				node->_value = cur->_value;
				if (cur == parent->_left)		// ע��3
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
ע��1�� ��Ϊ�������λ��ԭ��һ����NULL��
			  ���仰˵�������㣬node��ָ��һ���ᷢ���ı䣬��ָ��NULL����Ϊָ��һ�����
			  ���������봫�����ã��������Ҫ��ά��һ��parentָ������֤�������ȷ��
ע��2��ɾ���������е�һ����㣬��ô��һ����Ҫ���Ըõ�Ϊ���������������ҽ���������������������֮����
			�Ӷ�ά��������������
ע��3����ʱcurΪ�����������ҽ�㣬��cur��Ȼ�����������������Ҫ��cur�����������ҵ�����ж�
			���ѡ������������������㣬��������ͬ����ͬ���ǿ��ǵ���cur�����������ҵ�
*/

