#pragma once
#include <iostream>
#include <vector>
using namespace std;

class UnionFindSet
{
public:
	UnionFindSet(size_t sz)
		:_sz(sz)
	{
		_arr = new int[sz + 1];
		for (size_t i = 0; i < sz + 1; i++)
		{
			_arr[i] = -1;
		}
	}

	int friends(int n, int m, int r[][2])
	{
		int num1 = 0;
		int num2 = 0;

		for (size_t i = 0; i < m; ++i)
		{
			num1 = r[i][0];
			num2 = r[i][1];
			_Union(num1, num2);
		}

		return _TheCircleCount();
	}

	int _TheCircleCount()
	{
		int count = 0;
		for (size_t i = 0; i < _sz; ++i)
		{
			if (_arr[i] < 0)
			{
				count++;
			}
		}
		return count - 1;
	}


	~UnionFindSet()
	{
		if (_arr!= NULL)
		{
			delete _arr;
			_arr = NULL;
			_sz = 0;
		}
	}

protected:
	int _FindRoot(int x)
	{
		int root = x;
		while (_arr[root] >= 0)
		{
			root = _arr[root];
		}
		return root;
	}

	void _Union(int f1, int f2)
	{
		int root1 = _FindRoot(f1);
		int root2 = _FindRoot(f2);

		if (root1 != root2)
		{
			_arr[root1] += _arr[root2]; // 负数的绝对值表示该朋友圈共有多少人
			_arr[root2] = root1;
		}
	}
protected:
	int* _arr;
	size_t _sz;
};

void TestUnionFindSet()
{
	int r[][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 }, { 1,3 } };
	UnionFindSet Circle_Of_Friends(5);
	cout << "朋友圈的个数为 --> "<<Circle_Of_Friends.friends(5, 4, r) << endl;
}