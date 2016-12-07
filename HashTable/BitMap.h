#pragma once 
#include <vector>
#include<iostream>
using namespace std;

class BitMap
{
public:
	BitMap(size_t range)
	{
		size_t sz = (range >> 5) + 1;
		_bitMap.resize(sz);
	}

	void set(const int& x)
	{
		int index = x >> 5;      // �ҵ������ֶ�Ӧ��vector�±�
		int num = x % 32;      // �ҵ������ֶ�Ӧ���ǵڼ�λ

		_bitMap[index] |= (1 << num);
	}

	void reset(const int& x)
	{
		int index = x >> 5;      // �ҵ������ֶ�Ӧ��vector�±�
		int num = x % 32;      // �ҵ������ֶ�Ӧ���ǵڼ�λ

		_bitMap[index] &= (~(1 << num));
	}

	bool Test(const int& x)
	{
		int index = x >> 5;      // �ҵ������ֶ�Ӧ��vector�±�
		int num = x % 32;      // �ҵ������ֶ�Ӧ���ǵڼ�λ

		return _bitMap[index] & (1 << num);
	}

protected:
	vector<int> _bitMap;
};

void TestBitMap()
{
	BitMap  mp(100);
	mp.set(1);
	mp.set(2);
	mp.set(11);
	mp.set(22);
	cout << "test --<1>" << mp.Test(1) << endl;
	cout << "test --<2>" << mp.Test(2) << endl;
	cout << "test --<11>" << mp.Test(11) << endl;
	cout << "test --<22>" << mp.Test(22) << endl<<endl;

	mp.reset(2);
	cout << "test --<1>" << mp.Test(1) << endl;
	cout << "test --<2>" << mp.Test(2) << endl;
	cout << "test --<11>" << mp.Test(11) << endl;
	cout << "test --<22>" << mp.Test(22) << endl << endl;
}

