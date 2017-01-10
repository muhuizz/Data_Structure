#pragma once

#include<iostream>
using namespace std;

template<typename K , int M>
struct BTreeNode
{
	K _key[M];											//�ؼ�������
	BTreeNode<K, M>* _sub[M + 1];		//���ӽڵ�ָ������
	size_t _size;										//�ؼ��ָ���
	BTreeNode<K, M>* _parent;				//��ָ��

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
			while (i < cur->_size)   // ��һ�����Ĺؼ��������в�ѯ
			{
				if (key < cur->_key[i]) // ���²�ѯ���� i ��Ѱ��sub
				{
					break;
				}
				else if (key > cur->_key[i]) // i����size�����²�ѯ, i ��һѰ��sub��û���������ߵ�ǰѭ��
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

		return FindNode(parent, -1);//��curΪNULLʱ������û���ҵ�
	}

	bool Insert(const K& key)
	{
		// ���ǿ���
		if (_root == NULL)
		{
			_root = new Node;
			_root->_key[0] = key;
			_root->_parent = NULL;
			_root->_size = 1;
			return true;
		}

		// ������Find�ý��
		FindNode ret = Find(key);
		if (ret.second != -1) // �����ҵ��ýڵ�
			return false;

		Node* cur = ret.first;
		Node* parent = cur->_parent;
		Node* sub = NULL;
		int newkey = key;
		while (1)
		{
			//�� cur �ڵ��������key��sub
			//���curû��������ѭ��
			//cur->key���ˣ����Ϸ���
			InsertKey(cur, newkey, sub);

			if (cur->_size < M)
				return true;

			//��ʼ����
			size_t mid = cur->_size / 2;
			newkey = cur->_key[mid]; // ��ȡ��һ��Ҫ�����ֵ
			Node* tmp = new Node;
			size_t j = 0;
			size_t i = 0;
			size_t sz = cur->_size;
			for (i = mid + 1; i < sz; i++)
			{
				tmp->_key[j] = cur->_key[i];
				tmp->_sub[j] = cur->_sub[i];
				//ע���ӽڵ�ĸ�ָ��
				if (tmp->_sub[j])
					tmp->_sub[j]->_parent = tmp;
				j++;

				tmp->_size++; // ����size
				cur->_size--;

				cur->_key[i] = K(); // ��cur���ѳ�ȥ�Ĳ��ָֻ�Ĭ��ֵ
				cur->_sub[i] = NULL;
			}
			tmp->_sub[j] = cur->_sub[i];
			
			//ע���ӽڵ�ĸ�ָ��
			if (tmp->_sub[j])
				tmp->_sub[j]->_parent = tmp;
			cur->_sub[i] = NULL;
			
			// ���ԭ����key[mid]���
			cur->_key[mid] = K();
			cur->_size--;
			//���ڵ�
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
			
			
			//�Ǹ��ڵ�
			cur = parent;
			parent = parent->_parent;
			sub = tmp;
		}
		return true;
	}

	//bool Insert2(const K& key)
	//{
	//	//���ǿ���
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
	//	Node* sub = NULL; // ��ֳ����Ľڵ�
	//	K newkey = key;
	//	while (1)
	//	{
	//		InsertKey(cur, newkey, sub);

	//		// ���ý��е���������B����ֱ�ӷ���
	//		if (cur->_size != M)
	//			return true;

	//		// cur->_size != M
	//		// ��ʼ����
	//		size_t mid = cur->_size >> 1;
	//		newkey = cur->_key[mid]; //�������֮�󣬻�ȡ�µ�newkey 
	//		size_t j = 0; // sub�ڵ���±�
	//		size_t i = 0; // cur�ڵ���±�
	//		size_t sz = cur->_size;
	//		Node* tmp = new Node;
	//		for (i = mid + 1; i < sz; i++)
	//		{
	//			// �����м�key֮���key���Լ�key��������ߵĺ���
	//			tmp->_key[j] = cur->_key[i];
	//			tmp->_sub[j] = cur->_sub[i];
	//			if (tmp->_sub[j] != NULL)
	//			{
	//				tmp->_sub[j]->_parent = sub;
	//			}
	//			// ����size���������ߵ�key�����Ӹ�ֵĬ��ֵ
	//			cur->_size--;
	//			tmp->_size++;

	//			cur->_key[i] = K();
	//			cur->_sub[i] = NULL;
	//			//
	//			j++;

	//		}
	//		//�������һ������
	//		tmp->_sub[j] = cur->_sub[i];
	//		cur->_sub[i] = NULL;
	//		if (tmp->_sub[j] != NULL)
	//		{
	//			tmp->_sub[j]->_parent = tmp;
	//		}

	//		// Ĭ���м�keyֵ������cur->_size
	//		cur->_key[mid] = K();
	//		cur->_size--;

	//		//���ڵ�
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

		// ��keyС�Ĺؼ����������ӽڵ�ͬʱ����ƶ�
		while (index >= 0)
		{
			if (node->_key[index] > key)
			{
				//����ƶ�
				node->_key[index + 1] = node->_key[index];
				node->_sub[index + 2] = node->_sub[index + 1];
			}
			else // (node->_key[index] < key)
			{
				break;
			}
			--index;
		}

		// ��key���뵽node��㵱��
		node->_key[index + 1] = key;

		// �����Ѳ����Ľ��������node�ڵ���
		node->_sub[index + 2] = sub;
		if (sub != NULL)
			sub->_parent = node;

		// ��node��size����
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
			//���������д��ڳ�ͻ����Ϊ��������ָ��ָ��һ���������
			//���������ֻ��ӡǰһ�룬�����һ��key��ʱ���ٴ�ӡ��һ��
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