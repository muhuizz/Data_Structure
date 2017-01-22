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

	bool Insert_R(const K& x)
	{

	}
	// ɾ�����
	bool Remove(const K& x){}

	// �������
	void InOrder()
	{
		_inOrder(_root);
		cout << endl;
	}

	// ���AVL���Ƿ�ƽ��
protected:
	// ����ת
	void _RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		Node* pparent = parent->_parent;
		// 1
		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;
		// 2
		subR->_left = parent;
		parent->_parent = subR;
		// 3
		if (pparent != NULL)
		{
			if (parent == pparent->_left)
				pparent->_left = subR;
			else		// parent == pparent->_right
				pparent->_right = subR;
		}
		else		// pparent == NULL������parentΪ���ڵ�
		{
			_root = subR;
		}
		subR->_parent = pparent;
		// ����ƽ������
		subR->_bf = 0;
		parent->_bf = 0;
	}
	// ����ת
	void _RotateR(Node* parent)
	{
		Node* pparent = parent->_parent;
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		// 1
		parent->_left = subLR;
		if (subLR != NULL)
			subLR->_parent = parent;
		// 2
		subL->_right = parent;
		parent->_parent = subL;
		// 3
		if (pparent != NULL)
		{
			if (parent == pparent->_left)
				pparent->_left = subL;
			else
				pparent->_right = subL;
		}
		else		// pparent == NULL
			_root = subL;
		subL->_parent = pparent;
		// ����ƽ������
		parent->_bf = 0;
		subL->_bf = 0;
	}
	// ����˫��
	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;		// ע��3
		_RotateL(subL);
		_RotateR(parent);			// ��ת�����в���Ҫ��ע�����ڵ��ƽ������

		// ����ƽ������
		if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else		// bf == 0
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}
	// ����˫��
	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;		// ע��3
		_RotateR(subR);
		_RotateL(parent);			// ��ת�����в���Ҫ��ע�����ڵ��ƽ������

		// ����ƽ������
		if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else		// bf == 0
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void _inOrder(Node* node)
	{
		if (node == NULL)
			return;
		_inOrder(node->_left);
		cout << node->_key << "  ";
		_inOrder(node->_right);
	}
protected:
	Node* _root;
};


void TestAVLTree()
{
	int arr[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	// int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> tree;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		tree.Insert(arr[i]);
	}
	tree.InOrder();
}


/*
ע��1������һ����㲻һ��ֻ��ı���parentΪ����������ƽ�⣬���п��ܼ���Ӱ���������ƽ��
			�����Ҫ���ϣ���ֹ���ڵ㣬��parentΪNULL

ע��2�����parent��ƽ�����ӽ��е���֮���Ϊ0����������Ľ��֮ǰ��parent��ƽ������Ϊ1��-1��
		������㵼������parentΪ���ڵ����������ƽ�⣬����δ���Ӹ������ĸ߶�
		��ˣ�һ��parent��ƽ������Ϊ0���Ͳ���Ҫ�������ϵ���
ע��3��ͨ��parent��subL�����˽���������ת��������Ҫͨ���ж�subLR->_bfȷ�����յĸ��ڵ��ƽ�����ӣ�
		��ת�����л�ı� subLR->_bf ��ֵ�����������Ҫ���б���
*/