#define _CRT_SECURE_NO_WARNINGS 1

#include "complex.h"


pComplexNode Create_Node(DataType x)
{
	pComplexNode pnode = (pComplexNode)malloc(sizeof(ComplexNode));
	if (NULL == pnode)
	{
		printf("out of memory\n");
		system("pasue");
		exit(EXIT_FAILURE);
	}
	pnode->data = x;
	pnode->pnext = NULL;
	pnode->prand = NULL;
	return pnode;
}

void Create_List(pComplexNode *phead)
{
	pComplexNode pnode1 = Create_Node(1);
	pComplexNode pnode2 = Create_Node(2);
	pComplexNode pnode3 = Create_Node(3);
	pComplexNode pnode4 = Create_Node(4);
	pnode1->pnext = pnode2;
	pnode2->pnext = pnode3;
	pnode3->pnext = pnode4;

	pnode1->prand = pnode4;
	pnode2->prand = NULL;
	pnode3->prand = pnode2;
	pnode4->prand = pnode1;
	
	(*phead) = pnode1;
}

void Print_List(pComplexNode phead)
{
	pComplexNode cur = phead;
	while (cur != NULL)
	{
		printf("the Node = 【%d",cur->data);
		if (NULL == cur->prand)
		{
			printf("with the random = NULL------->\n");
		}
		else
		{
			printf("with the random = [%d]------->\n", cur->prand->data);
		}
		cur = cur->pnext;
	}
	printf("\n");
}

pComplexNode copy_Node(pComplexNode *phead)
{
	pComplexNode cur = (*phead);
	pComplexNode newnode = NULL;
	if (cur == NULL)
	{
		return NULL;
	}
	newnode = (pComplexNode)malloc(sizeof(ComplexNode));
	newnode->data = cur->data;
	newnode->pnext = cur->pnext;
	newnode->prand = NULL;
	cur->pnext = newnode;
	cur->pnext->pnext = copy_Node(&(newnode->pnext));//递归拷贝结点
	return *phead;
}

pComplexNode Clone_List(pComplexNode *phead)
{
	//复制随机指针
	pComplexNode newhead = NULL;
	pComplexNode cur = (*phead);
	if (NULL == cur)
	{
		return NULL;
	}
	cur = copy_Node(phead);
	newhead = cur->pnext;
	while (cur != NULL)
	{
		if (cur->prand != NULL)
		{
			newhead->prand = cur->prand->pnext;
		}
		cur = cur->pnext->pnext;
		if (NULL == cur)
		{
			break;
		}
		newhead = newhead->pnext->pnext;
	}

	///分离链表
	pComplexNode tail = NULL;
	cur = (*phead);
	newhead = cur->pnext;
	tail = cur->pnext;
	while (cur != NULL)
	{
		cur->pnext = cur->pnext->pnext;
		cur = cur->pnext;
		if (NULL == cur)
		{
			break;
		}
		tail->pnext = tail->pnext->pnext;
		tail = tail->pnext;
	}
	tail->pnext = NULL;
	return newhead;
}