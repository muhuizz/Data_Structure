#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define INIT_MAX 2
#define ADD_MAX 3

typedef int DataType;
typedef struct D_SeqList
{
	DataType *data;
	int size;
	int capacity;
}Seq,*pSeq;


void Init_DSeqlist(pSeq pseq);
void Destory_DSeqList(pSeq pseq);
void Push_Back(pSeq pseq, DataType data);
void Pop_Back(pSeq pseq);
void Push_Front(pSeq pseq, DataType data);
void Pop_Front(pSeq pseq);
void Print_Dseqlist(pSeq pseq);

void Remove(pSeq pseq,DataType data);
void RemoveAll(pSeq pseq,DataType data);
void Bubble_Sort(pSeq pseq);
void Inset_Sort(pSeq pseq);
void Select_Sort(pSeq pseq);
int BinarySearch(pSeq pseq,DataType data);
void Erase(pSeq pseq,int pos);