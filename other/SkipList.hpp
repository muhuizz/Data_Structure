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
		prev.resize(MAXLEVEL);						// ��ʾÿһ���ǰ��
		for (int i = 0; i < MAXLEVEL; i++)		// ǰ��node�ĳ�ʼ��
			prev[i] = _head;

		// �ҵ�����㣬������ǰ��node
		while (lev >= 0)		// �ӵ�ǰnode��ʼ��������
		{
			while (cur->_vec[lev])	// ֻ��������ң�ֱ��key��ֵС�ڸ�node��keyֵ
			{
				if (key > (cur->_vec[lev]->_key))
					cur = cur->_vec[lev];
				else if (key == (cur->_vec[lev]->_key))
					return false;
				else
					break;
			}
			prev[lev] = cur;		// ֻ�е�cur�����Լ���ˮƽ������ʱ���ſ���ȷ���ò��ǰ��
			--lev;
		}

		// �������cur֮��
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
				else		// cur->_vec[lev]->_key == key��׼��ɾ����Node
				{
					Node* dst = cur->_vec[lev];
					prev.resize(lev + 1);		// key ��Ӧ��node��lev��
					prev[lev--] = cur;

					while (lev >= 0)			// ��ȡÿһ��ǰ��
					{
						while (cur->_vec[lev]->_key != key)
						{
							cur = cur->_vec[lev];
						}
						prev[lev--] = cur;
					}


					// ��ȡ��dst֮���maxlevel
					if (tmpLevel == 0)
					{
						size_t l = dst->_level-1;
						while (dst->_vec[l] == NULL)
							--l;
						tmpLevel = l;
					}
					// ����_maxLevel
					_maxLevel = tmpLevel + 1;

					for (size_t i = 0; i < prev.size(); i++)	// �Ͽ������ӣ�����������
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