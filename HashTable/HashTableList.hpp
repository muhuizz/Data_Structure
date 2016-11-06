#pragma once

#include <vector>
#include <list>
#include <string>
#include <iostream>
using namespace std;

//仿函数
template <typename K>
struct HashType
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

template<>
struct HashType<string>
{
	static size_t BKDRHash(const char*str)
	{
		unsigned int seed = 131;// 31 131 1313 13131 131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash*seed + (*str++);
		}
		return(hash & 0x7FFFFFFF);
	}
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};


template<typename K,typename V>
struct KVNode
{
	K _key;
	V _value;
	KVNode<K, V>* _next;

	KVNode(const K& key, const V& value)
		:_key(key)
		, _value(value)
		, _next(NULL)
	{}
};

template<typename K, typename V, typename __HashList = HashType<K>>
class HashTableList
{
	typedef KVNode<K, V> Node;
public:
	HashTableList()
		:_size(0)
	{}

	Node* Find(const K& key)
	{
		if (_htlist.empty())
			return NULL;
		int index = GetHashIndex(key);
		Node* cur = _htlist[index];
		while (cur)
		{
			if (cur->_key == key)
			{
				return cur;
			}
			cur = cur->_next;
		}
		return NULL;
	}

	bool Insert(const K& key,const V& value)
	{
		_Check();
		size_t index = GetHashIndex(key);

		if (Find(key))
		{
			return false;
		}
		Node* tmp = new Node(key, value);
		tmp->_next = _htlist[index];
		_htlist[index] = tmp;
		_size++;
		return true;
	}

	bool Remove(const K& key)
	{
		if (_htlist.empty())
			return false;
		int index = GetHashIndex(key);
		Node* cur = _htlist[index];
		Node* prev = NULL;
		while (cur)
		{
			if (cur->_key == key)
			{
				if (prev == NULL)
					_htlist[index] = cur->_next;
				else
					prev->_next = cur->_next;

				delete cur;
				cur = NULL;
				_size--;
				return true;
			}
			cur = cur->_next;
		}
		return false;
	}

	void Print()  // 测试函数
	{
		for (size_t i = 0; i < _htlist.size(); i++)
		{
			Node* cur = _htlist[i];
			cout << "the  "<< i << "th " << "->";
			while (cur)
			{
				cout << cur->_key << "->";
				cur = cur->_next;
			}
			cout << "NULL" << endl;
		}
	}

protected:
	int GetHashIndex(const K& key)
	{
		return __HashList()(key) % _htlist.size();
	}

	void Swap(HashTableList<K, V, __HashList>& ht)
	{
		_htlist.swap(ht._htlist);
	}

	void _Check()
	{
		if (_htlist.empty() || (_size == _htlist.size())) //  载荷因子提升到1
		{
			size_t newsize = GetNewSize(_size);

			vector<Node*> tmp;
			tmp.resize(newsize);
			// 拷贝
			for (size_t i = 0; i < _htlist.size(); i++)
			{
				Node*  cur = _htlist[i];
				while (cur)  //  哈希链处理
				{
					Node* next = cur->_next;
					_htlist[i] = next;
					size_t k = cur->_key;

					cur->_next = tmp[k % newsize];
					tmp[k % newsize] = cur;

					cur = next;
				}
			}
			_htlist.swap(tmp);
		}
	}

	size_t GetNewSize(const size_t& sz)
	{
		const int _PrimeSize = 28;
		static const unsigned long _PrimeList[_PrimeSize] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul,
			786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul,
			25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul,
			805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		for (size_t i = 0; i < _PrimeSize;i++)
		{
			if (sz < _PrimeList[i])
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize - 1];
	}

protected:
	vector<Node*> _htlist;
	size_t _size;
};


void TestHashTableList()
{
	HashTableList<int, int> ht;
	int arr[] = { 89, 18, 49, 58, 9, 52, 105 };
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		ht.Insert(arr[i], 0);
	}
	//cout << ht.Find(89) << endl;
	//cout<<ht.Remove(58)<<endl;

	for (size_t i = 0; i < 60; i++)
	{
		ht.Insert(i, i);
	}

	ht.Print();
	

	//HashTableList<string, int>ht2;
	//char* arr[] = {"aaa","bbb","ccc","aaa","aaa"};
	//for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	//{
	//	KVNode<string, int>* ret = ht2.Find(arr[i]);
	//	if (ret == NULL)
	//	{
	//		ht2.Insert(arr[i], 1);
	//	}
	//	else
	//	{
	//		ret->_value++;
	//	}
	//}
}