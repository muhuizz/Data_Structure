#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 29.��һ�� �����г��ִ�������һ�����

bool IsInvalid = false;
int MoreThanHalf(int *arr, int sz)
{
	if (sz <= 0 || arr == NULL)
	{
		IsInvalid = true;
		return 0;
	}

	int res = arr[0];
	int count = 1;
	for (int i = 1; i < sz; i++)
	{
		if (count == 0)
			res = arr[i];
		if (arr[i] == res)
			count++;
		else
			count--;
	}
	return res;
}
int main()
{
	int arr[] = { 1, 4, 4, 4, 3, 4, 5, 4, 6, 2, 4 };
	int ret = MoreThanHalf(arr, sizeof(arr) / sizeof(arr[0]));
	if (!IsInvalid)
	{
		cout << "���ֳ���һ�������Ϊ" << ret << endl;
	}
	system("pause");
	return 0;
}
/*
����˼·��
	��������Ҫ��֤�������Ч�ԡ�
	һ������������ִ���������������Ԫ�ظ�����һ�룬Ҳ����˵��������ֳ��ֵĴ����������������ֳ��ִ���֮�ͻ��ࣨ���ٶ�һ������
	���ﶨ������������һ��Ϊ�����е�Ԫ�أ���һ��Ϊ������
	����������һ������ʱ������ͱ����������ͬ���������һ������ͱ�������ֲ�ͬ���������һ��������Ϊ0����Ҫ���±���������Ϊ���ǵ���ʱ���ִ����������֡�
	���������Ǿ仰����Ϊ���ִ�������һ�룬��ô��ʹÿ�κ�����������һ����Ҳ����Ӱ������������������
*/