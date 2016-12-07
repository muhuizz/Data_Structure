#pragma once 

#include<string>
#include "BitMap.h"
#include <iostream>
using namespace std;

struct HashFunc1
{
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;   // 也可以乘以31、131、1313、13131、131313..          
		}
		return hash;
	}

	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};
struct HashFunc2
{
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
			//hash = (size_t)ch + (hash << 6) + (hash << 16) - hash;  
		}
		return hash;
	}
	size_t operator()(const string& str)
	{
		return SDBMHash(str.c_str());
	}
};
struct HashFunc3
{
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
	size_t operator()(const string& str)
	{
		return RSHash(str.c_str());
	}
};
struct HashFunc4
{
	size_t APHash(const char *str)
	{
		register size_t hash = 0;
		size_t ch;
		for (long i = 0; ch = (size_t)*str++; i++)
		{
			if ((i & 1) == 0)
			{
				hash ^= ((hash << 7) ^ ch ^ (hash >> 3));
			}
			else
			{
				hash ^= (~((hash << 11) ^ ch ^ (hash >> 5)));
			}
		}
		return hash;
	}
	size_t operator()(const string& str)
	{
		return APHash(str.c_str());
	}
};
struct HashFunc5
{
	size_t JSHash(const char *str)
	{
		if (!*str)        // 这是由本人添加，以保证空字符串返回哈希值0  
			return 0;
		register size_t hash = 1315423911;
		while (size_t ch = (size_t)*str++)
		{
			hash ^= ((hash << 5) + ch + (hash >> 2));
		}
		return hash;
	}
	size_t operator()(const string& str)
	{
		return JSHash(str.c_str());
	}
};

template <typename K = string
	, class _HashFunc1 = HashFunc1
	, class _HashFunc2 = HashFunc2
	, class _HashFunc3 = HashFunc3
	, class _HashFunc4 = HashFunc4
	, class _HashFunc5 = HashFunc5>
class BloomFulter
{
public:
	BloomFulter(const size_t& size)
		:_bitMap(size*5)
		, _range(size*5)
	{}

	void Set(const K& key)
	{
		size_t hash1 = _HashFunc1()(key) % _range;
		size_t hash2 = _HashFunc2()(key) % _range;
		size_t hash3 = _HashFunc3()(key) % _range;
		size_t hash4 = _HashFunc4()(key) % _range;
		size_t hash5 = _HashFunc5()(key) % _range;

		_bitMap.set(hash1);
		_bitMap.set(hash2);
		_bitMap.set(hash3);
		_bitMap.set(hash4);
		_bitMap.set(hash5);
	}

	bool Test(const K& key)
	{
		size_t hash1 = _HashFunc1()(key) % _range;
		if (_bitMap.Test(hash1) == false)
			return false;

		size_t hash2 = _HashFunc2()(key) % _range;
		if (_bitMap.Test(hash2) == false)
			return false;

		size_t hash3 = _HashFunc3()(key) % _range;
		if (_bitMap.Test(hash3) == false)
			return false;

		size_t hash4 = _HashFunc4()(key) % _range;
		if (_bitMap.Test(hash4) == false)
			return false;

		size_t hash5 = _HashFunc5()(key) % _range;
		if (_bitMap.Test(hash5) == false)
			return false;

		return true;
	}

	void Reset()
	{}

protected:
	BitMap _bitMap;
	size_t _range;
};

void TestBloomFilter()
{
	char* str1 = "http://www.ganji.com/?ca_s=tg_hao123&ca_n=mingzhan1";
	char* str2 = "http://www.ganji.com/?ca_s=tg_hao123&ca_n=mingzhan2";
	char* str3 = "http://www.ganji.com/?ca_s=tg_hao123&ca_n=mingzhan3";
	char* str4 = "http://www.ganji.com/?ca_s=tg_hao123&ca_n=mingzhan4";

	BloomFulter<> bloom(100);
	bloom.Set(str1);
	bloom.Set(str2);
	bloom.Set(str3);

	cout << "Test(str1)       " << bloom.Test(str1) << endl;
	cout << "Test(str2)       " << bloom.Test(str2) << endl;
	cout << "Test(str3)       " << bloom.Test(str3) << endl;
	cout << "Test(str4)       " << bloom.Test(str4) << endl;
	cout << "Test(heheda)      " << bloom.Test("heheda") << endl;
}

////增加引用计数
//template<typename K>
//class BloomFilter
//{
//public:
//	BloomFilter()
//
//	{}
//protected:
//	vector<size_t> _bitmap;
//};