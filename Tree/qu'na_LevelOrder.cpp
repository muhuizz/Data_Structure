#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;
#include <vector>
#include<queue>
#include <algorithm>

typedef vector<int> Vector;
typedef vector<int>::iterator Iterator;
typedef queue<Vector> Queue;

void GetLevel(Vector pre, Vector inorder, Vector& lev)
{
	Queue queP;
	Queue queI;
	queP.push(pre);
	queI.push(inorder);
	while (!queP.empty())
	{
		Vector tmp = queP.front();
		queP.pop();
		Vector tmpI = queI.front();
		queI.pop();

		lev.push_back(tmp.front());
		Iterator pos = find(tmpI.begin(), tmpI.end(), tmp.front());
		int leftSize = pos - tmpI.begin();
		int rightSize = tmpI.end() - pos - 1;
		Vector leftPrev(tmp.begin() + 1, tmp.begin() + leftSize + 1);
		Vector rightPrev(tmp.begin() + leftSize + 1, tmp.end());
		Vector leftInorder(tmpI.begin(), pos);
		Vector rightInorder(pos + 1, tmpI.end());
		if (!leftPrev.empty()){
			queP.push(leftPrev);
			queI.push(leftInorder);
		}
		if (!rightPrev.empty()){
			queP.push(rightPrev);
			queI.push(rightInorder);
		}
	}
}

int main()
{
	Vector pre = { 1, 2, 4, 8, 9, 5, 10, 11, 3, 6, 12, 13, 7, 14, 15 };
	Vector inorder = { 8, 4, 9, 2, 10, 5, 11, 1, 12, 6, 13, 3, 14, 7, 15 };
	vector<int> ret;
	GetLevel(pre, inorder, ret);
	Iterator it = ret.begin();
	while (it != ret.end())
	{
		cout << *it << endl;
		it++;
	}
	system("pause");
	return 0;
}


//void GetLevel(Vector pre, Vector inorder, Vector& lev)
//{
//	if (pre.size() == 0)
//		return;
//	lev.push_back(pre.front());
//	int value = pre.front();
//	Iterator pos = find(inorder.begin(), inorder.end(), value);
//	int leftSize = pos - inorder.begin();
//	int rightSize = inorder.end() - pos - 1;
//	Vector leftPrev(pre.begin()+1, pre.begin()+leftSize+1);
//	Vector leftInorder(inorder.begin(), pos);
//	Vector rightPrev(pre.begin() + leftSize + 1, pre.end());
//	Vector rightInorder(pos + 1, inorder.end());
//
//	GetLevel(leftPrev, leftInorder, lev);
//	GetLevel(rightPrev, rightInorder, lev);
//}