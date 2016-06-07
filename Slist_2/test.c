#define _CRT_SECURE_NO_WARNINGS 1

#include "SList.h"

void test1()
{
	//pListNode phead;
	//InitList(&phead);
	//PushBack(&phead, 1);
	//PushBack(&phead, 2);
	//PushBack(&phead, 3);
	//PushBack(&phead, 4);
	//PushBack(&phead, 5);
	//PrintList(phead);
	//PopBack(&phead);
	//PrintList(phead);
	//PopBack(&phead);
	//PopBack(&phead);
	//PopBack(&phead);
	//PopBack(&phead);
	//PopBack(&phead);
	//PrintList(phead);
	pListNode phead;
	InitList(&phead);
	PushFront(&phead, 1);
	PushFront(&phead, 2);
	PushFront(&phead, 3);
	PushFront(&phead, 4);
	PushFront(&phead, 5);
	PrintList(phead);
	PopFront(&phead);
	PrintList(phead);
	PopFront(&phead);
	PopFront(&phead);
	PopFront(&phead);
	PopFront(&phead);
	PopFront(&phead);
	PrintList(phead);
}

void test2()
{
	pListNode phead;
	pListNode ret = NULL;

	InitList(&phead);
	PushBack(&phead, 1);
	PushBack(&phead, 2);
	PushBack(&phead, 3);
	PushBack(&phead, 4);
	PushBack(&phead, 5);
	PrintList(phead);
	ret = FindList(&phead, 1);
	if (ret != NULL)
	{
		//printf("ret = %d\n", ret->data);
		Earse(&phead, ret);
		PrintList(phead);
	}
//	InsertSlist(&phead,ret,99);
	//PrintList(phead);


}

void test3()
{
	pListNode phead;
	pListNode ret = NULL;
	InitList(&phead);
	PushBack(&phead, 3);

	PushBack(&phead, 1);
	PushBack(&phead, 2);
	PushBack(&phead, 3);
	PushBack(&phead, 4);
	PushBack(&phead, 3);
	PushBack(&phead, 3);
	PushBack(&phead, 3);

	PushBack(&phead, 5);
	PrintList(phead);
	//ReverseList(&phead);
	//PrintList(phead);
	//ret = FindList(phead, 1);
	//if (ret != NULL)
	//{
	//	//printf("ret->data = %d\n",ret->data);
	////	InsertNotHead(ret,999);
	//}
	RemoveAll(&phead, 3);
	PrintList(phead);
}

void test4()
{
	pListNode phead;
	InitList(&phead);
	PushBack(&phead, 5);
	PushBack(&phead, 4);
	PushBack(&phead, 3);
	PushBack(&phead, 2);
	PushBack(&phead, 1);
	PrintList(phead);
	//SelectSort(&phead);
	//PrintList(phead);
	EraseLastKNode(&phead,5);
	PrintList(phead);
}

void test5()
{
	pListNode phead1,phead2;
	InitList(&phead1);
	InitList(&phead2);

	PushBack(&phead1, 1);
	PushBack(&phead1, 3);
	PushBack(&phead1, 5);
	PushBack(&phead1, 7);
	PushBack(&phead1, 9);

	PushBack(&phead2, 2);
	PushBack(&phead2, 4);
	PushBack(&phead2, 6);
	PushBack(&phead2, 8);
	PushBack(&phead2, 10);

	PrintList(phead1);
	pListNode newhead = MergeList(&phead1, &phead2);
	PrintList(newhead);

}
int main()
{
	test5();
	system("pause");
	return 0;
}