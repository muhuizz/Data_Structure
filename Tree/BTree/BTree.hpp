#pragma once

#include<iostream>
using namespace std;

template<typename K , int M>
struct BTreeNode
{
	K _key[M];											//关键字数组
	BTreeNode<K, M>* _sub[M + 1];		//孩子节点指针数组
	size_t _size;										//关键字个数
	BTreeNode<K, M>* _parent;				//父指针

	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		size_t i = 0;
		while (i < M)
		{
			_key[i] = K();
			_sub[i] = NULL;
			i++;
		}
		_sub[i] = NULL;
	}
};

template<typename K, int M>
class BTree
{
	typedef BTreeNode<K, M> Node;
	typedef pair<Node*, int> FindNode;
public:
	BTree()
		:_root(NULL)
	{}

	FindNode Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i < cur->_size)   // 在一个结点的关键字数组中查询
			{
				if (key < cur->_key[i]) // 向下查询，用 i 来寻找sub
				{
					break;
				}
				else if (key > cur->_key[i]) // i超过size则向下查询, i 加一寻找sub，没超过继续走当前循环
				{
					++i;
				}
				else // key == cur->_key[i]
				{
					return FindNode(cur, i);
				}
			}
			parent = cur;
			cur = cur->_sub[i];
		}

		return FindNode(parent, -1);//当cur为NULL时，表明没有找到
	}

	bool Insert(const K& key)
	{
		// 树是空树
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_parent = NULL;
			_root->_size = 1;
			return true;
		}

		// 在树中Find该结点
		FindNode ret = Find(key);
		if (ret.second != -1) // 树中找到该节点
			return false;

		Node* cur = ret.first;
		Node* parent = cur->_parent;
		Node* sub = NULL;
		int newkey = key;
		while (1)
		{
			//在 cur 节点里面插入key、sub
			//如果cur没满，跳出循环
			//cur->key满了，向上分裂
			InsertKey(cur, newkey, sub);

			if (cur->_size < M)
				return true;

			//开始分裂
			size_t mid = cur->_size / 2;
			newkey = cur->_key[mid]; // 获取下一次要插入的值
			Node* tmp = new Node;
			size_t j = 0;
			size_t i = 0;
			size_t sz = cur->_size;
			for (i = mid + 1; i < sz; i++)
			{
				tmp->_key[j] = cur->_key[i];
				tmp->_sub[j] = cur->_sub[i];
				//注意子节点的父指针
				if (tmp->_sub[j])
					tmp->_sub[j]->_parent = tmp;
				j++;

				tmp->_size++; // 调整size
				cur->_size--;

				cur->_key[i] = K(); // 将cur分裂出去的部分恢复默认值
				cur->_sub[i] = NULL;
			}
			tmp->_sub[j] = cur->_sub[i];
			
			//注意子节点的父指针
			if (tmp->_sub[j])
				tmp->_sub[j]->_parent = tmp;
			cur->_sub[i] = NULL;
			
			// 清空原来的key[mid]结点
			cur->_key[mid] = K();
			cur->_size--;
			//根节点
			if (parent == NULL)
			{
				_root = new Node;
				_root->_key[0] = newkey;
				_root->_size = 1;
				_root->_sub[0] = cur;
				_root->_sub[1] = tmp;
				cur->_parent = _root;
				tmp->_parent = _root;
				return true;
			}
			
			
			//非根节点
			cur = parent;
			parent = parent->_parent;
			sub = tmp;
		}
		return true;
	}

	//bool Insert2(const K& key)
	//{
	//	//树是空树
	//	if (_root == NULL)
	//	{
	//		_root = new Node;
	//		_root->_key[0] = key;
	//		_root->_size = 1;
	//		return true;
	//	}
	//	//
	//	FindNode ret = Find(key);
	//	if (ret.second != -1)
	//		return false;

	//	Node* cur = ret.first;
	//	Node* parent = cur->_parent;
	//	Node* sub = NULL; // 拆分出来的节点
	//	K newkey = key;
	//	while (1)
	//	{
	//		InsertKey(cur, newkey, sub);

	//		// 不用进行调整，满足B树，直接返回
	//		if (cur->_size != M)
	//			return true;

	//		// cur->_size != M
	//		// 开始分裂
	//		size_t mid = cur->_size >> 1;
	//		newkey = cur->_key[mid]; //插入完成之后，获取新的newkey 
	//		size_t j = 0; // sub节点的下标
	//		size_t i = 0; // cur节点的下标
	//		size_t sz = cur->_size;
	//		Node* tmp = new Node;
	//		for (i = mid + 1; i < sz; i++)
	//		{
	//			// 拷贝中间key之后的key，以及key连带其左边的孩子
	//			tmp->_key[j] = cur->_key[i];
	//			tmp->_sub[j] = cur->_sub[i];
	//			if (tmp->_sub[j] != NULL)
	//			{
	//				tmp->_sub[j]->_parent = sub;
	//			}
	//			// 修正size；将拷贝走的key及孩子赋值默认值
	//			cur->_size--;
	//			tmp->_size++;

	//			cur->_key[i] = K();
	//			cur->_sub[i] = NULL;
	//			//
	//			j++;

	//		}
	//		//拷贝最后一个孩子
	//		tmp->_sub[j] = cur->_sub[i];
	//		cur->_sub[i] = NULL;
	//		if (tmp->_sub[j] != NULL)
	//		{
	//			tmp->_sub[j]->_parent = tmp;
	//		}

	//		// 默认中间key值，修正cur->_size
	//		cur->_key[mid] = K();
	//		cur->_size--;

	//		//根节点
	//		if (parent == NULL)
	//		{
	//			_root = new Node;
	//			_root->_key[0] = newkey;
	//			_root->_sub[0] = cur;
	//			_root->_sub[1] = tmp;
	//			_root->_size++;
	//			cur->_parent = _root;
	//			tmp->_parent = _root;
	//			return true;
	//		}

	//		cur = parent;
	//		parent = parent->_parent;
	//		sub = tmp;
	//	}
	//}


	void InOrder()
	{
		if (_root == NULL)
			return;
		_InOrder(_root);
		cout << endl;
	}

protected:
	void InsertKey(Node* node, const K& key, Node* sub)
	{
		size_t index = node->_size-1;

		// 比key小的关键字连带孩子节点同时向后移动
		while (index >= 0)
		{
			if (node->_key[index] > key)
			{
				//向后移动
				node->_key[index + 1] = node->_key[index];
				node->_sub[index + 2] = node->_sub[index + 1];
			}
			else // (node->_key[index] < key)
			{
				break;
			}
			--index;
		}

		// 将key插入到node结点当中
		node->_key[index + 1] = key;

		// 将分裂产生的结点连接在node节点上
		node->_sub[index + 2] = sub;
		if (sub != NULL)
			sub->_parent = node;

		// 对node的size调整
		node->_size++;
		return;
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		for (size_t i = 0; i < root->_size; i++)
		{
			_InOrder(root->_sub[i]);
			cout << root->_key[i] << " ";
			//遍历过程中存在冲突，因为存在两个指针指向一个结点的情况
			//解决方案：只打印前一半，到最后一个key的时候再打印后一半
			if (i == root->_size-1)
				_InOrder(root->_sub[i + 1]);
		}
	}


	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		size_t i = 0;
		for (i = 0; i < root->_size; i++)
		{
			_InOrder(root->_sub[i]);
			cout << root->_key[i] << " ";
		}
		_InOrder(root->_sub[i]);
	}
protected:
	Node* _root;
};

void TestBTree()
{
	BTree<int, 3> bt;
	//int arr[] = { 53, 75, 139, 49, 145, 36, 101 };
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		bt.Insert2(arr[i]);
	}
	bt.InOrder();
}