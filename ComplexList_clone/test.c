#define _CRT_SECURE_NO_WARNINGS 1

#include "complex.h"


void test()
{
	pComplexNode phead;
	pComplexNode ret;

	Create_List(&phead);
	Print_List(phead);
	ret = Clone_List(&phead);
	Print_List(phead);

	Print_List(ret);
}

int main()
{
	test();
	system("pause");
	return 0;
}