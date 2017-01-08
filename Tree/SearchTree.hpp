#pragma once 

#include <iostream>
using namespace std;

template <typename K>
struct SearchTreeNode
{
	K _key;
	SearchTreeNode<K>* _left;
	SearchTreeNode<K>* _right;

	SearchTreeNode(const K& x)
		:_key(x)
		, _left(NULL)
		, _right(NULL)
	{}
};

template <typename K>
class SearchTree
{
	typedef SearchTreeNode<K> Node;
public:
	SearchTree()
		:_root(NULL)
	{}
	SearchTree(const SearchTree<K>& tree)
	{
		_root = _Copy(tree._root);
	}
	SearchTree<K> operator=(const SearchTree<K>& tree)
	{
		if (this != &tree)
		{
			/*_root = _Copy(tree._root);*/
			SearchTree<K> newtree = tree;
			std::swap(this->_root, newtree._root);
		}
		return *this;
	}
	~SearchTree()
	{
		_destory(_root);
	}
	bool InsertR(const K& x)
	{
		return _insert_r(_root, x);
	}
	bool RemoveR(const K& x)
	{
		return _remove_r(_root, x);
	}
	void Inorder()
	{
		_inorder(_root);
		cout << endl;
	}
	bool Find(const K& x)
	{
		Node* cur = _root;
		while (cur != NULL)
		{
			if (cur->_key == x)
				return true;
			else if (cur->_key > x)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		return false;
	}

	bool Insert(const K& x)
	{
		if (_root == NULL)
		{
			_root = new Node(x);
			return true;
		}
		Node* cur = _root;
		while (cur != NULL)
		{
			if (cur->_key == x)
			{
				return false;
			}
			if (x < (cur->_key))
			{
				if (cur->_left == NULL)
				{
					cur->_left = new Node(x);
					return true;
				}
				else
				{
					cur = cur->_left;
				}
			}
			else
			{
				if (cur->_right == NULL)
				{
					cur->_right = new Node(x);
					return true;
				}
				else
				{
					cur = cur->_right;
				}
			}
		}		
		return true;
	}

	bool Remove(const K& x)
	{
		//叶子节点
		//只有一个孩子
		//两个孩子 --->替换法删除   左子树最右节点或右子树的最左节点
		if (_root == NULL)
			return false;
		
		Node* cur = _root;
		Node* parent = NULL;
		while (cur != NULL)
		{
			//cur结点是待删除结点
			if (cur->_key == x)
			{
				//Node* del = cur;
				//parent = cur;
				//cur = cur->_right;
				//while (cur && cur->_right)
				//{
				//	parent = cur;
				//	cur = cur->_left;
				//}
				//if (cur == NULL)
				//{
				//	_root = parent->_left;
				//	delete parent;
				//	parent = NULL;
				//}
				//else
				//{
				//	std::swap(del->_key, cur->_key);
				//	delete cur;
				//	parent->_left = NULL;
				//}
				Node* del = cur;

				if (cur->_left == NULL)
				{
					if (parent == NULL)
					{
						_root = _root->_right;
					}
					else if (cur == parent->_left)
					{
						parent->_left = cur->_right;
					}
					else
					{
						parent->_right = cur->_right;
					}
				}
				else if (cur->_right == NULL)
				{
					if (parent == NULL)
					{
						_root = _root->_left;
					}
					else if (cur == parent->_left)
					{
						parent->_left = cur->_left;
					}
					else
					{
						parent->_right = cur->_left;
					}
				}
				//cur有两个孩子
				else
				{
					//找右树最左节点，替换删除		
					Node* minright = cur->_right;//minright一定存在
					parent = cur;	
					while (minright->_left != NULL)
					{
						parent = minright;
						minright = minright->_left;
					}
					//minright左子树为空
					del = minright;
					cur->_key = del->_key;
					if (minright == parent->_left)
						parent->_left = minright->_right;
					else
						parent->_right = minright->_right;
				}
				delete del;
				del = NULL;
				return true;
			}
			//
			else if (x > cur->_key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				parent = cur;
				cur = cur->_left;
			}
		}
		return false;
	}

private:
	void _inorder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_inorder(root->_left);
		cout << root->_key << " ";
		_inorder(root->_right);
	}
	bool _insert_r(Node*& root,const K& x)
	{
		if (root == NULL)
		{
			root = new Node(x);
			return true;
		}
		if (x > root->_key)
		{
			return _insert_r(root->_right, x);
		}
		else if (x < root->_key, x)
		{
			return _insert_r(root->_left, x);
		}
		else
		{
			return false;
		}
	}	
	bool _remove_r(Node*& root,const K& x)
	{
		if (root == NULL)
		{
			return false;
		}
		if (x > root->_key)
		{
			return _remove_r(root->_right, x);
		}
		else if (x < root->_key)
		{
			return _remove_r(root->_left, x);
		}
		else
		{
			if (root->_left == NULL)
			{
				root = root->_right;
			}
			else if (root->_right == NULL)
			{
				root = root->_left;
			}
			else
			{
				Node * parent = root;
				Node* minright = root->_right;
				
				while (minright->_left != NULL)
				{
					parent = minright;
					minright = minright->_right;
				}
				//minright为待删除节点的最小节点
				root->_key = minright->_key;
				if (minright == parent->_left)
				{
					parent->_left = minright->_right;
				}
				else
				{
					parent->_right = minright->_right;
				}
				delete minright;
				minright = NULL;
			}
			return true;
		}
	}

	Node* _Copy(const Node* root)
	{
		if (root == NULL)
		{
			return NULL;
		}
		Node* newnode = new Node(root->_key);
		newnode->_left = _Copy(root->_left);
		newnode->_right = _Copy(root->_right);
		return newnode;
	}
	
	void _destory(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_destory(root->_left);
		_destory(root->_right);

		delete root;
		root = NULL;
	}
private:
	Node* _root;
};

void TestSearTree()
{
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	//int arr[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	SearchTree<int> tree;
	for (int i = 0; i < 10; i++)
	{
		tree.InsertR(arr[i]);
	}
	tree.Inorder();

	//SearchTree<int> tree2 = tree;
	SearchTree<int> tree2;
	tree2= tree;

	tree2.Inorder();
	cout << tree.Find(0) << endl;
	cout << tree.Find(1) << endl;
	cout << tree.Find(2) << endl;
	cout << tree.Find(3) << endl;
	cout << tree.Find(4) << endl;
	cout << tree.Find(5) << endl;
	cout << tree.Find(6) << endl;
	cout << tree.Find(7) << endl;
	cout << tree.Find(8) << endl;
	cout << tree.Find(9) << endl;
	cout << tree.Find(10) << endl;
	cout << tree.Find(11) << endl;

	//tree.RemoveR(7);
	//tree.Inorder();
	//tree.RemoveR(5);
	//tree.Inorder();
	//tree.RemoveR(1);
	//tree.Inorder();

	//tree.RemoveR(2);
	//tree.RemoveR(3);
	//tree.RemoveR(4);
	//tree.RemoveR(5);
	//tree.RemoveR(6);
	//tree.Inorder();
	//tree.RemoveR(7);
	//tree.Inorder();

	//tree.RemoveR(8);
	//tree.Inorder();
	//tree.RemoveR(9);
	//tree.Inorder();
	//tree.RemoveR(0);
	//tree.Inorder();
}