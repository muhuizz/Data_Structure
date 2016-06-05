#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int DataType;
#define MAX_SIZE 1000

typedef struct SeqList
{
	DataType data[MAX_SIZE];
	int sz;
}SeqList, *pSeqList;

void PrintSeqlist(pSeqList pseq);
void InitSeqList(pSeqList pseq);
void PushBack(pSeqList pseq,DataType  data);
void PopBack(pSeqList pseq);
void PushFront(pSeqList pseq, DataType  data);
void PopFront(pSeqList pseq);
void Insert(pSeqList pseq,int pos,DataType data);
void Remove(pSeqList pseq,DataType data);
void RemoveAll(pSeqList pseq,DataType data);
void Sort_bubble(pSeqList pseq);
void Sort_Select(pSeqList pseq);
void Sort_Insert(pSeqList pseq);
int BinarySearch(pSeqList pseq,DataType data);