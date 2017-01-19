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
	// �������
	void InOrder()		// ������������������Ľ��һ���������
	{
		_inOrder(_root);
		cout << endl;
	}
	// �ݹ������
	bool InsertR(const T& x)
	{
		return _insertR(_root, x);
	}
	// �ݹ�ɾ�����
	bool RemoveR(const T& x)	// ע��2
	{
		return _removeR(_root,x);
	}
	// ���ҽ��
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
	// �ǵݹ����
	bool Insert(const T& x)			// ע��4
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)		// �ҵ��������
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
	// �ǵݹ�ɾ��
	bool Remove(const T& x)
	{
		if (_root == NULL)
			return false;
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_value == x)   //	�ҵ��ý�㣬��ɾ��
			{
				Node* del = cur;
				if (cur->_left == NULL)		// �ж�cur�ĸ�����ΪNULL
				{
					if (parent == NULL)	// curΪ���ڵ�
						_root = cur->_right;
					else if (cur == parent->_left)		// �ж�curΪparent���ĸ�����
						parent->_left = cur->_right;
					else  //cur == parent->_right
						parent->_right = cur->_right;
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)	// curΪ���ڵ�
						_root = cur->_left;
					else if (cur == parent->_left)		// �ж�curΪparent���ĸ�����
						parent->_left = cur->_left;
					else  //cur == parent->_right
						parent->_right = cur->_left;
				}
				else		// ��������--->�滻��ɾ����Ѱ�������������ҽ��
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

	void _inOrder(Node* root)
	{
		if (root != NULL)
		{
			_inOrder(root->_left);
			cout << root->_value << "  ";
			_inOrder(root->_right);
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
			Node* del = node;
			if (node->_left == NULL)
				node = node->_right;
			else if (node->_right == NULL)
				node = node->_left;
			else  // node->_left != NULL && node->_right != NULL���������������ҽ��
			{
				del = node->_left;
				Node* parent = node;
				while (del->_right)
				{
					parent = del;
					del = del->_right;
				}
				node->_value = del->_value;
				if (del == parent->_left)		// ע��3
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
	cout << "5���ڷ� " << tree.Find(5) << endl;
}

/*
ע��1�� ��Ϊ�������λ��ԭ��һ����NULL��
			  ���仰˵�������㣬node��ָ��һ���ᷢ���ı䣬��ָ��NULL����Ϊָ��һ�����
			  ���������봫�����ã��������Ҫ��ά��һ��parentָ������֤�������ȷ��
ע��2��ɾ���������е�һ����㣬��ô��һ����Ҫ���Ըõ�Ϊ���������������ҽ���������������������֮����
			�Ӷ�ά��������������
ע��3����ʱcurΪ�����������ҽ�㣬��cur��Ȼ�����������������Ҫ��cur�����������ҵ�����ж�
			���ѡ������������������㣬��������ͬ����ͬ���ǿ��ǵ���cur�����������ҵ�
ע��4���ǵݹ����һ����㣬������ʵ�֣�һ����ʹ��parent��һ�ֲ�ʹ��parent
			ʹ��parent�ķ�ʽ���������룻
			��ʹ��parent�ķ�ʽ����while()ѭ���ڲ�����x���ڻ���С��cur->_valueʱ���жϴ�ʱcur�ò���ӽ���Ƿ�ΪNULL
*/

