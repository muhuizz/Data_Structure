#ifndef __SKIPLIST_HPP_
#define __SKIPLIST_HPP_

#include <iostream>
#include <vector>

#define MAXLEVEL 8

// node define
template<typename K, typename V>
struct SkipListNode
{
	K _key;
	V _value;
	size_t _level;				                                 // the level of the node
	std::vector<SkipListNode*> _vec;              // the point of every level
	SkipListNode(const K& key = K(), const V& val = V(), const size_t& lev = MAXLEVEL)
		:_key(key)
		, _value(val)
		, _level(lev)
	{
		_vec.reserve(_level);
		for (size_t i = 0; i < _level; i++)
		{
			_vec.push_back(NULL);
		}
	}
	~SkipListNode()
	{
		_key = -1;
		_value = -1;
		_vec.clear();
	}
};

// SkipList define
template<typename K, typename V>
class SkipList
{
	typedef SkipListNode<K, V> Node;
public:
	SkipList()
		: _maxLevel(1)
		, _totalSize(0)
	{
		_head = new Node(-1, -1, MAXLEVEL);
	}
	~SkipList()
	{}

public:
	bool Insert(const K& key, const V& val)
	{
		Node* cur = _head;
		int lev = _maxLevel - 1;
		
		std::vector<Node*> prev;		// MAXLEVEL
		prev.resize(MAXLEVEL);						// 表示每一层的前驱
		for (int i = 0; i < MAXLEVEL; i++)		// 前驱node的初始化
			prev[i] = _head;

		// 找到插入点，并保存前驱node
		while (lev >= 0)		// 从当前node开始，向下找
		{
			while (cur->_vec[lev])	// 只负责向后找，直到key的值小于该node的key值
			{
				if (key > (cur->_vec[lev]->_key))
					cur = cur->_vec[lev];
				else if (key == (cur->_vec[lev]->_key))
					return false;
				else
					break;
			}
			prev[lev] = cur;		// 只有当cur不可以继续水平向后查找时，才可以确定该层的前驱
			--lev;
		}

		// 插入点在cur之后
		size_t newLevel = Rand_Level();		// newLevel <= MAXLEVEL
		Node* newNode = new Node(key, val, newLevel);
		if (newLevel > _maxLevel)
			_maxLevel = newLevel;

		for (size_t i = 0; i < newLevel; i++)
		{
			newNode->_vec[i] = prev[i]->_vec[i];
			prev[i]->_vec[i] = newNode;
		}
		return true;
	}

	bool Erase(const K& key)
	{
		std::vector<Node*> prev;
		
		Node* cur = _head;
		size_t lev = _maxLevel - 1;
		int tmpLevel = 0;
		while (lev >= 0)
		{
			while (cur->_vec[lev])
			{
				if (cur->_vec[lev]->_key < key)
				{
					cur = cur->_vec[lev];
					tmpLevel = tmpLevel>lev ? tmpLevel : lev;
				}
				else if (cur->_vec[lev]->_key > key)
				{
					tmpLevel = tmpLevel>lev ? tmpLevel : lev;
					break;
				}
				else		// cur->_vec[lev]->_key == key，准备删除该Node
				{
					Node* dst = cur->_vec[lev];
					prev.resize(lev + 1);		// key 对应的node有lev层
					prev[lev--] = cur;

					while (lev >= 0)			// 获取每一层前驱
					{
						while (cur->_vec[lev]->_key != key)
						{
							cur = cur->_vec[lev];
						}
						prev[lev--] = cur;
					}


					// 获取除dst之外的maxlevel
					if (tmpLevel == 0)
					{
						size_t l = dst->_level-1;
						while (dst->_vec[l] == NULL)
							--l;
						tmpLevel = l;
					}
					// 更新_maxLevel
					_maxLevel = tmpLevel + 1;

					for (size_t i = 0; i < prev.size(); i++)	// 断开旧连接，建立新连接
					{
						prev[i]->_vec[i] = dst->_vec[i];
					}
					delete dst;
					dst = NULL;
					return true;
				}
			}
			lev--;
		}
		return false;
	}

	void Print()
	{
		if (_head == NULL)
			return;
		Node* cur = _head;
		while (cur != NULL)
		{
			if (cur == _head)
			{
				cur = cur->_vec[0];
				continue;
			}
			std::cout << "[" <<cur->_key << "-" << cur->_value << "].(" << cur->_level<<")--->";
			cur = cur->_vec[0];
		}
		std:: cout << std::endl;
	}
private:
	SkipList(const SkipList& sl);
	SkipList<K, V>& operator=(const SkipList& sl);
	int Rand_Level(void) {
		int level = 1;
		while (rand() % 2) 
			++level;
		level = (MAXLEVEL > level) ? level : MAXLEVEL;
		return level;
	}
private:
	Node* _head;
	size_t _maxLevel;
	size_t _totalSize;
};



#endif	// __SKIPLIST_HPP_



/// levelDB--> random

//#include <stdint.h>  
//
//typedef unsigned int           uint32_t;  
//typedef unsigned long long     uint64_t;  
//
//
//class Random {
//private:
//	uint32_t seed_;
//public:
//	explicit Random(uint32_t s) : seed_(s & 0x7fffffffu) {
//		// Avoid bad seeds.  
//		if (seed_ == 0 || seed_ == 2147483647L) {
//			seed_ = 1;
//		}
//	}
//	uint32_t Next() {
//		static const uint32_t M = 2147483647L;   // 2^31-1  
//		static const uint64_t A = 16807;  // bits 14, 8, 7, 5, 2, 1, 0  
//
//		uint64_t product = seed_ * A;
//
//		seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
//
//		if (seed_ > M) {
//			seed_ -= M;
//		}
//		return seed_;
//	}
//	uint32_t Uniform(int n) { return (Next() % n); }
//
//	bool OneIn(int n) { return (Next() % n) == 0; }
//
//	uint32_t Skewed(int max_log) {
//		return Uniform(1 << Uniform(max_log + 1));
//	}
//};