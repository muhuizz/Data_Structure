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
			for (i = mid + 1; i < cur->_size; i++)
			{
				tmp->_key[j] = cur->_key[i];
				tmp->_sub[j] = cur->_sub[i];
				j++;

				tmp->_size++; // ����size
				cur->_size--;

				cur->_key[i] = K(); // ��cur���ѳ�ȥ�Ĳ��ָֻ�Ĭ��ֵ
				cur->_sub[i] = NULL;
			}
			tmp->_sub[j] = cur->_sub[i];
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

	void InOrder()
	{
		if (_root == NULL)
			return;
		_InOrder(_root);
	}

protected:
	void InsertKey(Node* node, const K& key, Node* sub)
	{
		size_t index = node->_size-1;
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
		node->_key[index + 1] = key;
		node->_sub[index + 2] = sub;
		if (sub != NULL)
			sub->_parent = node;

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
			_InOrder(root->_sub[i+1]);
		}
	}
protected:
	Node* _root;
};

void TestBTree()
{
	BTree<int, 3> bt;
	int arr[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		bt.Insert(arr[i]);
	}
	bt.InOrder();
}