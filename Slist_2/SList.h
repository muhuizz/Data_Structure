#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType;

typedef struct ListNode
{
	DataType data;
	struct ListNode *pnext;
}ListNode, *pListNode ;


void InitList(pListNode* phead);
void Destory_List(pListNode* phead);
void PushBack(pListNode* phead, DataType _data);
void PopBack(pListNode* phead);
void PushFront(pListNode* phead, DataType _data);
void PopFront(pListNode* phead);
void PrintList(pListNode phead);

pListNode FindList(pListNode* phead, DataType _data);
void Earse(pListNode* phead, pListNode pos);
void InsertSlist(pListNode* phead, pListNode pos, DataType _data);
void Remove(pListNode* phead, DataType _data);
void RemoveAll(pListNode* phead, DataType _data);

void BubbleSort(pListNode* phead);
void SelectSort(pListNode* phead);
//√Ê ‘Ã‚

///void PrintList_reverse(pListNode* phead);
pListNode FindMidNode(pListNode phead);
void ReverseList(pListNode* phead);
void InsertNotHead(pListNode pos, DataType _data);
void DelNotTailNode(pListNode pos);
void EraseLastKNode(pListNode* phead, int k);
pListNode MergeList(pListNode* pL1, pListNode* pL2);

pListNode HasCycle(pListNode* phead);

int IsListCrose(pListNode* pL1, pListNode* pL2);

pListNode JosephCircle(pListNode* phead, int M);

int GetCyleLen(pListNode pMeetNode);


pListNode* FindEnterNode(pListNode* phead, pListNode* pMeetNode);

int IsListCrose(pListNode* pL1, pListNode* pL2);

int IsListCroseWithCycle(pListNode* pL1, pListNode* pL2);
