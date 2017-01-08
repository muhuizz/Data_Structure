#pragma once
#include <iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};

template<typename K, typename V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;
	K _key;
	V _value;	
	Color _color;

	RBTreeNode(const K& key,const V& value)
		:_left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _color(RED)//Ĭ�Ϲ����ɫ���
	{}
};

template<typename K, typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	bool Insert(const K& key,const V& value)
	{
		//����
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_color = BLACK;
			return true;
		}

		//�����ڵ㣬�����뵽��Ӧλ��
		Node* cur = _root;
		Node* parent = NULL;
		while (cur != NULL)
		{
			if (key > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (key < cur->_key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		
		cur = new Node(key, value);
		if (key > (parent->_key))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		
		//��ʼ����
		while (cur != _root && parent->_color == RED)
		{
			//���parent��colorΪRED��parentһ�����Ǹ��ڵ㣬���游�ڵ�colorΪBLACK
			Node* grandparentnode = parent->_parent;//grandparentnode->_color = BLACK;
			if (parent == grandparentnode->_left)
			{
				Node* unclenode = grandparentnode->_right;		//����ڵ�uncle		

				if (unclenode && (unclenode->_color == RED))//uncle��Ϊ�գ���uncle->colorΪRED
				{
					parent->_color = BLACK;
					unclenode->_color = BLACK;
					grandparentnode->_color = RED;

					cur = grandparentnode;
					parent = cur->_parent;
				}
				else//uncleΪ�գ���uncle->colorΪBLACK
				{
					if (cur == parent->_right)
					{
						RotateL(parent);
						std::swap(parent, cur);
					}
					
					RotateR(grandparentnode);
					parent->_color = BLACK;
					grandparentnode->_color = RED;

					break;
				}
			}
			else//parent == grandparent->_right
			{
				Node* unclenode = grandparentnode->_left;
				if (unclenode && (unclenode->_color == RED))//uncle���ڣ���colorΪ RED
				{
					parent->_color = BLACK;
					unclenode->_color = BLACK;
					grandparentnode->_color = RED;

					cur = grandparentnode;
					parent = cur->_parent;
				}
				else//uncle�����ڣ���uncle->colorΪ��ɫ
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						std::swap(cur,parent);
					}

					RotateL(grandparentnode);
					grandparentnode->_color = RED;
					parent->_color = BLACK;

					break;
				}
			}
		}
		_root->_color = BLACK;
		return true;
	}

	void InOrder()
	{
		if (_root == NULL)
			return;
		_inorder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root == NULL)
			return true;

		if (_root->_color == RED)
			return false;

		int count = 0;
		Node* cur = _root;
		while (cur != NULL)
		{
			if (cur->_color == BLACK)
			{
				count++;
			}
			cur = cur->_left;
		}

		int k = 0;
		return _IsBalance(_root, count, k);
	}

protected:
	void _inorder(Node* root)
	{
		if (root == NULL)
			return;
		_inorder(root->_left);
		cout << root->_key << " ";
		_inorder(root->_right);
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* ppNode = parent->_parent;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			subR->_parent = NULL;
			_root = subR;
		}
		else
		{
			if (subR->_key > ppNode->_key)
			{
				ppNode->_right = subR;
				subR->_parent = ppNode;
			}
			else
			{
				ppNode->_left = subR;
				subR->_parent = ppNode;
			}
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		Node* ppNode = parent->_parent;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == NULL)
		{
			subL->_parent = NULL;
			_root = subL;
		}
		else
		{
			if (subL->_key > ppNode->_key)
			{
				ppNode->_right = subL;
				subL->_parent = ppNode;
			}
			else
			{
				ppNode->_left = subL;
				subL->_parent = ppNode;
			}
		}
	}

	bool _IsBalance(Node* root, const int& count, int k)
	{
		if (root == NULL)
			return true;
		
		if (root != _root && root->_color == RED)
		{
			if (root->_parent->_color == RED)
			{
				cout << "������ɫ���" << root->_key << endl;
				return false;
			}
		}

		if (root->_color == BLACK)
			k++;
		if (root->_left == NULL && root->_right == NULL)
		{
			if (k == count)
				return true;
			else
			{
				cout << "��ɫ�ڵ㲻���" << root->_key << endl;
				return false;
			}
		}
		
		return _IsBalance(root->_left, count, k) \
				&& _IsBalance(root->_right, count, k);


	}
protected:
	Node* _root;
};



void TestRHTree()
{
	RBTree<int, int> tree;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	size_t size = sizeof(arr) / sizeof(arr[0]);
	for (size_t i = 0; i < size; i++)
	{
		tree.Insert(arr[i], i);
	}
	tree.InOrder();
	cout << "RBTree�Ƿ�ƽ��" << tree.IsBalance() << endl;
}