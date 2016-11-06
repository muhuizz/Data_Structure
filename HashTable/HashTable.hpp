#pragma once

#include <vector>
#include <iostream>
using namespace std;

enum State
{
	EMPTY,
	EXIST,
	DELETE
};

template<typename K>
struct __IntHashTable
{
	int operator()(const K& key)
	{
		return key;
	}
};

template<typename K>
struct __StringHashTable
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

	size_t operator()(const K& str)
	{
		return BKDRHash(str.c_str());
	}
};

template <typename K ,typename V>
struct KVNode
{
	K _key;
	V _value;
	State _state;

	KVNode(const K& key = K(), const V& value = V())
		:_key(key)
		, _value(value)
		, _state(EMPTY)
	{}
};

template <typename K, typename V, typename HASHTABLE = __IntHashTable<K>>
class HashTable
{
	typedef KVNode<K, V> Node;
public:
	HashTable()
		:_size(0)
	{}

	bool Insert(const K& key,const V& value)
	{
		_CheckSize();
		size_t index = _GetHashIndex(key);

		while (_table[index]._state == EXIST)
		{
			// 如果插入的key存在，返回false
			if (_table[index]._key == key)
				return false;
			
			index++;//线性探测
			if (index == _table.size())
				index = 0;
		}

		_table[index]._key = key;
		_table[index]._value = value;
		_table[index]._state = EXIST;
		_size++;

		return true;
	}
	
	Node* Find(const K& key)
	{
		// 空表，直接返回
		if (_table.empty())
			return NULL;

		size_t index = _GetHashIndex(key);
		int begin = index;
		
		while (_table[index]._state != EMPTY)
		{
			if (_table[index]._key == key)
			{
				// 该位置为已删除结点
				if (_table[index]._state == DELETE)
					return NULL;
				else
					return &_table[index];
			}
			
			//改变循环变量
			index++;
			if (index == _table.size())
				index = 0;

			// 循环一圈，没有找到
			if (index == begin)
				return NULL;
		}
		return NULL;
	}

	bool Remove(const K& key)
	{
		if (_table.empty())
			return false;
		Node* ret = Find(key);
		if (ret != NULL)
		{
			ret->_state = DELETE;
			--_size;
		}
		else
			return false;
	}

protected:
	size_t _GetHashIndex(const K& key)
	{
		HASHTABLE ht;
		return ht(key) % _table.size();
	}

	void Swap(HashTable<K, V, HASHTABLE>& ht)
	{
		_table.swap(ht._table);
	}

	void _CheckSize()
	{
		//空表，或载荷因子大于等于8
		if ((_table.size() == 0) || ((_size * 10) / _table.size() >= 8))
		{
			size_t newSize = _GetPrimeSize(_table.size());
			HashTable<K, V, HASHTABLE> hasht;
			hasht._table.resize(newSize);
			// 将原来的HashTable中的key，value插入到新表中
			for (size_t i = 0; i < _table.size(); i++)
			{
				if (_table[i]._state == EXIST)
				{
					hasht.Insert(_table[i]._key, _table[i]._value);
				}
			}

			this->Swap(hasht);
		}
	}

	// 从素数表找到下次扩容的容量
	size_t _GetPrimeSize(const size_t& size)
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

		for (size_t i = 0; i < _PrimeSize; i++)
		{
			if (_PrimeList[i] > size)
			{
				return _PrimeList[i];
			}
		}
		return _PrimeList[_PrimeSize-1];
	}

protected:
	vector<Node> _table;
	size_t _size;
};

void TestHashTable()
{
	int arr[] = { 89, 18, 49, 58, 9 };
	HashTable<int, int > ht;
	for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		ht.Insert(arr[i], i);
	}
	//for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	//{
	//	cout<< ht.Find(arr[i])<<endl;
	//}

	char* arr1[] = {"hash","table","hash","test","hast"};
	HashTable<string, int, __StringHashTable<string>> ht2;
	for (size_t i = 0; i < sizeof(arr1) / sizeof(arr[0]); i++)
	{
		KVNode<string,int>* ret = ht2.Find(arr1[i]);
		if (ret)
		{
			ret->_value++;
		}
		else
		{
			ht2.Insert(arr1[i],1);
		}
	}
}