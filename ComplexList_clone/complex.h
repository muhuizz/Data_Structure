#ifndef __COMPLEX_H__
#define __COMPLEX_H__

#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct ComplexNode
{
	DataType data;
	struct ComplexNode *pnext;
	struct ComplexNode *prand;
}ComplexNode, *pComplexNode;

pComplexNode Create_Node(DataType x);
void Create_List(pComplexNode *phead);
void Print_List(pComplexNode phead);
pComplexNode Clone_List(pComplexNode *phead);

#endif    //__COMPLEX_H__