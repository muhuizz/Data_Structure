#define _CRT_SECURE_NO_WARNINGS 1

#include "Slist.h"


void testt1()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);

	Printlist(&list);
	PopBack(&list);
	PopBack(&list);
	PopBack(&list);
	Printlist(&list);
	PopBack(&list);
}

void testt2()
{
	LinkList list;
	InitList(&list);
	PushFront(&list, 1);
	PushFront(&list, 2);
	PushFront(&list, 3);
	PushFront(&list, 4);
	Printlist(&list);
	PopFront(&list);
	PopFront(&list);
	PopFront(&list);
	PopFront(&list);

	Printlist(&list);
	PopFront(&list);

}

void testt3()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);

	pListNode ptmp = NULL;
	ptmp = FindList(&list, 9);

	//Earse(&list, ptmp);
	InsertSlist(&list, ptmp,99);
	Destory_List(&list);
}

void testt4()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 1);
	PushBack(&list, 2);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 5);

	//ReverseList(&list);
	Printlist(&list);
	pListNode pnode = NULL;
	pnode = FindList(&list,4);
	DelNotTailNode(pnode);
	Printlist(&list);
}

void testt5()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 5);
	PushBack(&list, 6);
	PushBack(&list, 3);
	PushBack(&list, 4);
	PushBack(&list, 1);
	Printlist(&list);

	SelectSort(&list);
	Printlist(&list);
}
void testt6()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 5);
	PushBack(&list, 6);
	PushBack(&list, 3);
	PushBack(&list, 3);
	PushBack(&list, 3);
	PushBack(&list, 3);

	PushBack(&list, 4);
	PushBack(&list, 1);
	Printlist(&list);
	Remove(&list, 1);
	Printlist(&list);
	Destory_List(&list);
}

void test1()
{
	LinkList list;
	InitList(&list);
	PushBack(&list, 6);
	PushBack(&list, 5);
	PushBack(&list, 4);
	PushBack(&list, 3);
	PushBack(&list, 2);
	PushBack(&list, 1);
	Printlist(&list);
	//SelectSort(&list);
	//Printlist(&list);
	//pListNode ptmp = FindLastKNode(&list,1);
	//printf("%d \n",ptmp->data);
	EraseLastKNode(&list, 6);
	Printlist(&list);

}

int main()
{


	test1();
	system("pause");
	return 0;
}