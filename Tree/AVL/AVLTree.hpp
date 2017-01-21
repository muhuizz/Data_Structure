#pragma once
/**************��Ŀ��������*************
		AVL��
	AVL��Ҳ��һ��ƽ������һ�ø߶�ƽ��Ķ�������Ҫ���������ĸ߶ȼ�ȥ�������ĸ߶Ȳ�ľ���ֵ������1
	�߶Ȳ�ʹ��ƽ����������ʾ
***********************************/
#include <iostream>
using namespace std;

template <typename K, typename V>
struct AVLTreeNode
{
	int _bf;			// ƽ������
	K _key;			// �ؼ��� 
	V _value;		// ֵ
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	AVLTreeNode(const K& key)			// ֻ���ǹؼ��֣� ������ֵ
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

	// ������
	bool Insert(const K& x)
	{
		// ����
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}

		// ���ǿ���
		// �ҵ�λ�ò�������
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

		// ���е�����������Ͻ��е�����
		while (parent)									// ע��1
		{
			// ����parent��ƽ������
			if (x > parent->_key)
				parent->_bf++;
			else		// x < parent->_key
				parent->_bf--;
			// �ж��Ƿ���Ҫ�������Ͻ��е���
			if (parent->_bf == 0)					// ע��2
				return true;
			else if (parent->_bf == 1 || parent->_bf == -1)		// ����ƽ�⣬����Ϊ�ı���parent��ƽ�����ӣ�����ſϻ�ı��������ƽ��
			{
				cur = parent;
				parent = cur->_parent;
			}
			else			// ������ƽ�⣬��Ҫ������ת
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
ע��1������һ����㲻һ��ֻ��ı���parentΪ����������ƽ�⣬���п��ܼ���Ӱ���������ƽ��
			�����Ҫ���ϣ���ֹ���ڵ㣬��parentΪNULL

ע��2�����parent��ƽ�����ӽ��е���֮���Ϊ0����������Ľ��֮ǰ��parent��ƽ������Ϊ1��-1��
		������㵼������parentΪ���ڵ����������ƽ�⣬����δ���Ӹ������ĸ߶�
		��ˣ�һ��parent��ƽ������Ϊ0���Ͳ���Ҫ�������ϵ���

*/