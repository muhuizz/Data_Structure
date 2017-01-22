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

	bool Insert_R(const K& x)
	{

	}
	// 删除结点
	bool Remove(const K& x){}

	// 中序遍历
	void InOrder()
	{
		_inOrder(_root);
		cout << endl;
	}

	// 检查AVL树是否平衡
protected:
	// 左旋转
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
		else		// pparent == NULL，表明parent为根节点
		{
			_root = subR;
		}
		subR->_parent = pparent;
		// 调整平衡因子
		subR->_bf = 0;
		parent->_bf = 0;
	}
	// 右旋转
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
		// 调整平衡因子
		parent->_bf = 0;
		subL->_bf = 0;
	}
	// 左右双旋
	void _RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;		// 注释3
		_RotateL(subL);
		_RotateR(parent);			// 旋转过程中不需要关注各个节点的平衡因子

		// 调整平衡因子
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
	// 右左双旋
	void _RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;		// 注释3
		_RotateR(subR);
		_RotateL(parent);			// 旋转过程中不需要关注各个节点的平衡因子

		// 调整平衡因子
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
注释1：新增一个结点不一定只会改变以parent为根的子树的平衡，还有可能继续影响更高树的平衡
			因此需要不断，制止根节点，即parent为NULL

注释2：如果parent的平衡因子进行调整之后变为0，表明插入的结点之前，parent的平衡因子为1或-1，
		新增结点导致了以parent为根节点的子树左右平衡，但并未增加该子树的高度
		因此，一旦parent的平衡因子为0，就不需要继续向上调整
注释3：通过parent和subL决定了进行左右旋转，这里需要通过判断subLR->_bf确定最终的各节点的平衡因子，
		旋转过程中会改变 subLR->_bf 的值，因此这里需要进行保存
*/