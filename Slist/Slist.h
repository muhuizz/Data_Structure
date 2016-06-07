#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;

typedef struct ListNode
{
	DataType data;
	struct ListNode *pnext;
}ListNode, *pListNode;


typedef struct LinkList
{
	pListNode phead;
}LinkList,*pLiskList;

void InitList(pLiskList plist);

void Destory_List(pLiskList plist);
void PushBack(pLiskList plist, DataType _data);
void PopBack(pLiskList plist);
void PushFront(pLiskList plist, DataType _data);
void PopFront(pLiskList plist);
pListNode FindList(pLiskList plist, DataType _data);
void Earse(pLiskList plist, pListNode pos);
void InsertSlist(pLiskList plist, pListNode pos, DataType _data);
void Printlist(pLiskList plist);
void Remove(pLiskList plist, DataType _data);


//√Ê ‘Ã‚


pListNode FindMidNode(pLiskList plist);
void ReverseList(pLiskList plist);
void InsertNotHead(pListNode pos, DataType _data);
void DelNotTailNode(pListNode pos);
void BubbleSort(pLiskList plist);
void SelectSort(pLiskList plist);


int HasCycle(pLiskList plist);
pListNode FindLastKNode(pLiskList plist, int K);
void EraseLastKNode(pLiskList plist, int k);


