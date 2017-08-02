#define _CRT_SECURE_NO_WARNINGS 1


#include"SkipList.hpp"
#include <cassert>

//void temp()
//{
//	std::vector<int> vec;
//	vec.resize(10);
//	vec.reserve(7);
//	vec.reserve(6);
//	vec.reserve(5);
//	vec.reserve(8);
//}


void test()
{
	SkipList<int, int> skip;
	skip.Insert(1, 1);
	skip.Insert(2, 2);
	skip.Insert(3, 3);
	skip.Insert(4, 4);
	skip.Insert(5, 5);
	skip.Insert(6, 6);
	skip.Insert(7, 7);
	skip.Insert(8, 8);
	skip.Insert(9, 9);
	skip.Print();
	skip.Erase(6);
	skip.Erase(5);
	skip.Erase(7);
}

int main()
{
	test();
	// temp();
	system("pause");
	return 0;
}