#define _CRT_SECURE_NO_WARNINGS 1

#include "SList.h"

pListNode BuyNode(DataType _data)
{
	pListNode pnode = (pListNode)malloc(sizeof(ListNode));
	if (NULL == pnode)
	{
		printf("out of memory\n");
		system("pasue");
		exit(EXIT_FAILURE);
	}
	pnode->data = _data;
	pnode->pnext = NULL;
	return pnode;
}

void InitList(pListNode* phead)
{
	assert(phead);
	(*phead) = NULL;
}

void Destory_List(pListNode* phead)
{
	assert(phead);
	free(*phead);		
	(*phead) = NULL;
}

void PushBack(pListNode* phead, DataType _data)
{
	assert(phead);
	pListNode cur = (*phead);
	if (NULL == cur)
	{
		(*phead) = BuyNode(_data);
	}
	else
	{
		while (cur->pnext != NULL)
		{
			cur = cur->pnext;
		}
		cur->pnext = BuyNode(_data);
	}
}

void PopBack(pListNode* phead)
{
	assert(phead);
	pListNode cur = (*phead);
	pListNode ptmp = NULL;
	if (NULL == cur)
	{
		printf("The List is empty\n");
		return;
	}
	else if (NULL == cur->pnext)
	{
		free(cur);
		cur = NULL;
		(*phead) = NULL;
	}
	else
	{
		while (cur->pnext->pnext != NULL)
		{
			cur = cur->pnext;
		}
		free(cur->pnext);
		cur->pnext = NULL;
	}
}

void PushFront(pListNode* phead, DataType _data)
{
	assert(phead);
	pListNode cur = (*phead);
	if (NULL == cur)
	{
		(*phead) = BuyNode(_data);
	}
	else
	{
		pListNode ptmp = BuyNode(_data);
		ptmp->pnext = cur;
		(*phead) = ptmp;
	}

}

void PopFront(pListNode* phead)
{
	assert(phead);
	pListNode cur = (*phead);
	if (NULL == cur)
	{
		printf("The List is empty\n");
		return;
	}
	else
	{
		(*phead) = (*phead)->pnext;
		free(cur);
		cur = NULL;
	}
}

void PrintList(pListNode phead)//这里不需要对phead进行断言
{
	if (NULL == phead)
	{
		return;
	}
	while (phead != NULL)
	{
		printf("%d->",phead->data);
		phead = phead->pnext;
	}
	printf("NULL\n");
}

pListNode FindList(pListNode* phead, DataType _data)
{
	assert(phead);
	pListNode cur = (*phead);
	while (cur != NULL)
	{
		if (cur->data == _data)
		{
			return cur;
		}
		cur = cur->pnext;
	}
	return NULL;
}

void Earse(pListNode* phead, pListNode pos)
{
	assert(phead);
	pListNode cur = (*phead);
	if (((*phead) == NULL)||(pos == NULL))
	{
		return;
	}
	if (pos == (*phead))
	{
		(*phead) = (*phead)->pnext;
		free(pos);
		pos = NULL;
		return;
	}
	else
	{
		while (cur->pnext != pos)
		{
			cur = cur->pnext;
		}
		cur->pnext = cur->pnext->pnext;
		free(pos);
		pos = NULL;
	}
}

void InsertSlist(pListNode* phead, pListNode pos, DataType _data)
{
	assert(phead);
	pListNode cur = (*phead)->pnext;
	pListNode ptmp = NULL;
	if (((*phead) == NULL) || (pos == NULL))
	{
		return;
	}
	if (pos == (*phead))
	{
		PushFront(phead,_data);
	}
	else
	{
		while (cur->pnext != pos)
		{
			cur = cur->pnext;
		}
		ptmp = BuyNode(_data);
		ptmp->pnext = cur->pnext;
		cur->pnext = ptmp;
	}
}

void Remove(pListNode* phead, DataType _data)
{
	assert(phead);
	pListNode cur = (*phead);
	pListNode pre = NULL;
	if ((*phead) == NULL)
	{
		return;
	}
	while (cur)
	{
		if (_data == cur->data)
		{
			if (cur == (*phead))
			{
				(*phead) = (*phead)->pnext;				
			}
			else
			{
				pre->pnext = cur->pnext;
			}
			free(cur);
			cur = NULL;
			return;
		}
		else
		{
			pre = cur;
			cur = cur->pnext;
		}
	}
}

void RemoveAll(pListNode* phead, DataType _data)
{
	assert(phead);
	pListNode pre = NULL;
	pListNode cur = (*phead);
	while (cur)
	{
		if (cur->data == _data)
		{
			if (cur == (*phead))
			{
				(*phead) = cur->pnext;
				free(cur);
				cur = (*phead);
			}
			else
			{
				pre->pnext = cur->pnext;
				free(cur);
				cur = pre->pnext;
			}
		}
		else
		{
			pre = cur;
			cur = cur->pnext;
		}
	}
}

pListNode FindMidNode(pListNode phead)
{
	pListNode fast = phead;
	pListNode slow = phead;
	while ((fast != NULL) && (fast->pnext != NULL))
	{
		fast = fast->pnext->pnext;
		slow = slow->pnext;
	}
	return slow;
}

void ReverseList(pListNode* phead)
{
	assert(phead);
	pListNode newhead = NULL;
	pListNode cur = (*phead);
	pListNode pnode = NULL;
	while (cur != NULL)
	{
		pnode = cur;
		cur = cur->pnext;
		pnode->pnext = newhead;
		newhead = pnode;
	}
	(*phead) = newhead;
}

void InsertNotHead(pListNode pos, DataType _data)
{
	if (NULL == pos)
	{
		return;
	}
	pListNode ptmp = BuyNode(pos->data);
	ptmp->pnext = pos->pnext;
	pos->data = _data;
	pos->pnext = ptmp;
	
}

void DelNotTailNode(pListNode pos)
{
	pListNode ptmp = NULL;
	if (NULL == pos)
	{
		return;
	}
	ptmp = pos->pnext;
	pos->data = ptmp->data;
	pos->pnext = ptmp->pnext;
	free(ptmp);
	ptmp = NULL;
}

void BubbleSort(pListNode* phead)//由于这里不改变原指针的指向，因此传pListNode类型的变量也可以
{
	assert(phead);
	pListNode cur = (*phead);
	pListNode tail = NULL;
	int flag = 1;
	while (cur != tail)
	{
		flag = 1;
		while (cur->pnext != tail)
		{
			if ((cur->data) > (cur->pnext->data))
			{
				DataType tmp = cur->data;
				cur->data = cur->pnext->data;
				cur->pnext->data = tmp;
				flag = 0;
			}
			cur = cur->pnext;
		}
		if (1 == flag)
			break;
		tail = cur;
		cur = (*phead);
	}
}

void SelectSort(pListNode* phead)
{
	assert(phead);
	pListNode cur = (*phead);
	pListNode pnode = NULL;
	pListNode pcur = NULL;
	DataType tmp = 0;
	while (cur->pnext != NULL)
	{
		pcur = cur;
		pnode = cur->pnext;
		while (pnode != NULL)
		{
			if ((pcur->data) > (pnode->data))
			{
				pcur = pnode;
			}
			pnode = pnode->pnext;
		}
		tmp = pcur->data;
		pcur->data = cur->data;
		cur->data = tmp;
		cur = cur->pnext;
	}
}

void EraseLastKNode(pListNode* phead, int k)
{
	assert(phead);
	pListNode front = (*phead);
	pListNode back = (*phead);
	while (front)
	{
		k--;
		if (k < 0)
		{
			back = back->pnext;
		}
		front = front->pnext;
	}
	if (k < 1)
	{
		DelNotTailNode(back);
	}
}

pListNode MergeList(pListNode* pL1, pListNode* pL2)
{
	assert(pL1);
	assert(pL2);
	pListNode cur1 = *pL1;
	pListNode cur2 = *pL2;
	pListNode newhead = NULL;
	pListNode tail = NULL;
	if ((cur1->data) > (cur2->data))
	{
		newhead = cur2;
		tail = cur2;
		cur2 = cur2->pnext;
	}
	else if ((cur1->data) < (cur2->data))
	{
		newhead = cur1;
		tail = cur1;
		cur1 = cur1->pnext;
	}
	else
	{
		newhead = cur1;
		tail = cur1;
		cur1 = cur1->pnext;
		cur2 = cur2->pnext;
	}
	while ((cur1 != NULL) && (cur2 != NULL))
	{
		if ((cur1->data) > (cur2->data))
		{
			tail->pnext = cur2;
			cur2 = cur2->pnext;
		}
		else if ((cur1->data) < (cur2->data))
		{
			tail->pnext = cur1;
			cur1 = cur1->pnext;
		}
		else
		{
			tail->pnext = cur1;
			cur1 = cur1->pnext;
			cur2 = cur2->pnext;
		}
		tail = tail->pnext;
	}
	if (NULL == cur1)
	{
		tail->pnext = cur2;
	}
	else
	{
		tail->pnext = cur1;
	}
	return newhead;
}