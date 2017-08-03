#define _CRT_SECURE_NO_WARNINGS 1


#include"SkipList.hpp"
#include <cassert>

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

	//std::cout << skip.Find(1) << std::endl;
	//std::cout << skip.Find(5) << std::endl;
	//std::cout << skip.Find(0) << std::endl;
	//skip.Print();
	//skip.Erase(6);
	//skip.Print();
	//skip.Erase(5);
	//skip.Print();
	//skip.Erase(7);
	//skip.Print();

}

int main()
{
	test();
	system("pause");
	return 0;
}