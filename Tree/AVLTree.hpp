#pragma once

#include <iostream>
using namespace std;

template <typename K, typename V>
struct AVLTreeNode
{
	int _bf;
	K _key;
	V _value;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	AVLTreeNode(const K& key, const V& value)
		:_bf(0)
		, _key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
		, _parent(NULL)
	{}
};

template <typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	
	//拷贝构造
	AVLTree(const AVLTree<K, V>& t)
	{
		if (t._root == NULL)
			_root == NULL;
		else
			_root = _Copy(t._root);
	}
	
	//赋值运算符
	AVLTree<K, V> operator=(const AVLTree<K, V>& t)
	{
		if (this == &t)
			return *this;

		_root = _Copy(t._root);
	}

	//析构
	~AVLTree()
	{
		if (_root != NULL)
			_destory(_root);
	}

	////删除
	//bool Erase(const K& k)
	//{
	//	if (cur == NULL)
	//		return false;

	//	Node* cur = _root;
	//	while (cur != NULL)
	//	{
	//		if (k > cur->_key)
	//			cur = cur->_right;
	//		else if (k < cur->_key)
	//			cur = cur->_left;
	//		else
	//			break;
	//	}
	//	
	//	if (cur == NULL)
	//		return false;

	//	//cur是待删除结点


	//}

	bool  Insert(const K& k, const V& v)
	{
		if (_root == NULL)
		{
			_root = new Node(k, v);
			return true;
		}
		//找到待插入结点位置
		Node* cur = _root;
		Node* parent = NULL;
		while (cur != NULL)
		{
			parent = cur;
			if (k > cur->_key)
			{
				cur = cur->_right;
			}
			else if (k < cur->_key)
			{
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		//插入节点，建立指向关系
		cur = new Node(k, v);
		if (k < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_right = cur;
			cur->_parent = parent;
		}

		while (parent)
		{
			//调整parent的bf
			if (k < parent->_key)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}
			
			//如果parent的bf为0，表面插入结点之后，堆parent以上节点的bf无影响
			if (parent->_bf == 0)
			{
				return true;
			}
			else if (abs(parent->_bf) == 1)  //为1、-1时继续向上调整
			{
				cur = parent;
				parent = cur->_parent;
			}
			else//2、-2   为2、-2时进行旋转调整
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
						break;
					}
					else if (cur->_bf == -1)
					{
						RotateRL(parent);
						break;
					}
				}
				else//parent->_bf == -2
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
						break;
					}
					else if (cur->_bf == 1)
					{
						RotateLR(parent);
						break;
					}
				}
			}
		}
		return true;
	}

	void Inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	bool IsBalance()
	{
		if (_root == NULL)
			return false;
		return _IsBalance(_root);
	}

	bool IsBalance_better()
	{
		int sz = 0;
		return _IsBalance_better(_root, sz);
	}

	size_t Height()
	{
		return _height(_root);
	}

protected:
	Node* _Copy(Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		Node* newnode = new Node(root->_key, root->_value);
		newnode->_bf = root->_bf;

		newnode->_left = _Copy(root->_left);
		if (newnode->_left != NULL)
			newnode->_left->_parent = newnode;

		newnode->_right = _Copy(root->_right);
		if (newnode->_right != NULL)
			newnode->_right->_parent = newnode;
		return newnode;
	}

	void _destory(Node* root)
	{
		if (root == NULL)
			return;

		_destory(root->_left);
		_destory(root->_right);

		delete root;
		root = NULL;
	}

	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;

		if ((abs(root->_bf) >= 2) || (root->_bf != _height(root->_right) - _height(root->_left)))
		{
			cout << "该结点不平衡" << root->_key << endl;
		}

		return _IsBalance(root->_left) && _IsBalance(root->_right);
	}

	bool _IsBalance_better(Node* root,int& height)
	{
		if (root == NULL)
			return true;

		int leftheight = 0;
		if (_IsBalance_better(root->_left, leftheight) == false)
			return false;

		int rightheight = 0;
		if (_IsBalance_better(root->_right, rightheight) == false)
			return false;

		height = leftheight > rightheight ? leftheight : rightheight;
		
		return abs(leftheight - rightheight) < 2 && (root->_bf == rightheight - leftheight);
	}

	size_t _height(Node* root)
	{
		if (root == NULL)
			return 0;
		size_t leftheight = _height(root->_left) + 1;
		size_t rightheight = _height(root->_right) + 1;

		return leftheight > rightheight ? leftheight : rightheight;
	}

	void _inorder(Node* root)
	{
		if (root == NULL)
			return;
		_inorder(root->_left);
		cout << root->_key << " ";
		_inorder(root->_right);
	}

	//左旋转
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;	
		
		parent->_right = subRL;
		if (subRL != NULL)
			subRL->_parent = parent;


        Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			if (parent == ppNode->_right)
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

		parent->_bf = 0;
		subR->_bf = 0;
	}

	//右旋转
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR != NULL)
		{
			subLR->_parent = parent;
		}
		Node* ppNode = parent->_parent;
		subL->_right = parent;
	    parent->_parent = subL;

		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
           subL->_parent = ppNode;
		}
		
		parent->_bf = 0;
		subL->_bf = 0;
	}

	//左右旋转
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		size_t bf = subLR->_bf;
		RotateL(parent->_left);
		RotateR(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
	}

	//右左旋转
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		size_t bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);

		if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
	}

protected:
	Node* _root;
};

void TestAVLTree()
{
	//int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	//AVLTree<int, int> tree;
	//size_t size = sizeof(arr) / sizeof(arr[0]);
	//for (size_t i = 0; i < size; i++)
	//{
	//	tree.Insert(arr[i], i);
	//}
	//tree.Inorder();
	//cout << tree.Height() << endl;


	/*-----------------------------------------*/
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> tree2;
	AVLTree<int, int> tree3;
	AVLTree<int, int> tree4;

	size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
	for (size_t i = 0; i < size2; i++)
	{
		tree2.Insert(arr2[i], i);
	//	tree2.IsBalance();
	}
	tree2.Inorder();
	cout << tree2.Height() << endl;
	cout << tree2.IsBalance_better() << endl;
	//tree2.IsBalance();

}