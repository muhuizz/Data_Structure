#define _CRT_SECURE_NO_WARNINGS 1

#include "Slist.h"

pListNode Byenode(DataType _data)
{
	pListNode pnode = NULL;
	pnode = (pListNode)malloc(sizeof(ListNode));
	if (pnode == NULL)
	{
		printf("out of memory\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	pnode->data = _data;
	pnode->pnext = NULL;
	return pnode;
}

void InitList(pLiskList plist)
{
	assert(plist);
	plist->phead = NULL;
}

void Destory_List(pLiskList plist)
{
	if (plist == NULL)
	{
		return;
	}
	free(plist->phead);
	plist->phead = NULL;
}

void PushBack(pLiskList plist, DataType _data)
{
	assert(plist);
	pListNode pnode = plist->phead;
	if (plist->phead == NULL)
	{
		plist->phead = Byenode(_data);
	}
	else
	{
		while (pnode->pnext != NULL)
		{
			pnode = pnode->pnext;
		}
		pnode->pnext = Byenode(_data);
	}
}

void PopBack(pLiskList plist)
{
	assert(plist);
	if (plist->phead == NULL)
	{
		printf("warning:>List is empty\n");
		return;
	}
	else if (plist->phead->pnext == NULL)
	{
		free(plist->phead);
		plist->phead = NULL;
	}
	else
	{
		pListNode pnode = plist->phead;
		while (pnode->pnext->pnext != NULL)
		{
			pnode = pnode->pnext;
		}
		free(pnode->pnext);
		pnode->pnext = NULL;
	}
}

void PushFront(pLiskList plist, DataType _data)
{
	assert(plist);
	pListNode ptmp = plist->phead;
	if (plist->phead == NULL)
	{
		plist->phead = Byenode(_data);
	}
	else
	{
		ptmp = Byenode(_data);
		ptmp->pnext = plist->phead;
		plist->phead = ptmp;
	}
}

void PopFront(pLiskList plist)
{
	assert(plist);
	if (plist->phead == NULL)
	{
		printf("warning:>List is empty\n");
		return;
	}
	//else if ((plist->phead)->pnext == NULL)
	//{
	//	free((plist->phead));
	//	(plist->phead) = NULL;
	//}
	//else
	//{
	//	pListNode ptmp = (plist->phead);
	//	(plist->phead) = (plist->phead)->pnext;
	//	free(ptmp);
	//	ptmp = NULL;
	//}
	else
	{
		pListNode ptmp = (plist->phead);
		plist->phead = plist->phead->pnext;
		free(ptmp);
		ptmp = NULL;
	}
}

pListNode FindList(pLiskList plist, DataType _data)
{
	assert(plist);
	pListNode Cur = plist->phead;
	while (Cur != NULL)
	{
		if (Cur->data == _data)
		{
			return Cur;
		}
		Cur = Cur->pnext;
	}
	return NULL;
}

void Earse(pLiskList plist, pListNode pos)
{
	assert(plist);
	pListNode pnode = (plist->phead);
	if (pos == NULL)
	{
		return;
	}
	if (plist->phead == pos)
	{
		PopFront(plist);
	}
	else if (pos->pnext == NULL)
	{
		PopBack(plist);
	}
	else
	{
		while (pnode->pnext != pos)
		{
			pnode = pnode->pnext;
		}
		pnode->pnext = pnode->pnext->pnext;
		free(pos);
		pos = NULL;
	}
}

void InsertSlist(pLiskList plist, pListNode pos, DataType _data)
{
	assert(plist);
	if (pos == NULL)
	{
		printf("��Ч�ڵ㣬����ʧ��\n");
		return;
	}
	if (pos == plist->phead)
	{
		PushFront(plist, _data);
	}
	else if (pos->pnext == NULL)
	{
		PushBack(plist, _data);
	}
	else
	{
		pListNode pnode = plist->phead;
		pListNode ptmp = NULL;
		while (pnode->pnext != pos)
		{
			pnode = pnode->pnext;
		}
		ptmp = Byenode(_data);
		pnode->pnext = ptmp;
		ptmp->pnext = pos;
	}
}

void Printlist(pLiskList plist)
{
	assert(plist);
	pListNode Cur = plist->phead;
	if (plist->phead == NULL)
	{
		printf("List has been enpty\n");
		return;
	}
	while (Cur)
	{
		printf("%d->", Cur->data);
		Cur = Cur->pnext;
	}
	printf("NULL\n");
}

void Remove(pLiskList plist, DataType _data)
{
	assert(plist);
	pListNode Cur = plist->phead;
	pListNode Pre = NULL;

	if (NULL == plist->phead)
	{
		return;
	}
	while (Cur)
	{
		if (Cur->data == _data)
		{
			if (Cur == plist->phead)
			{
				PopFront(plist);
			}
			else
			{
				Pre->pnext = Cur->pnext;
				free(Cur);
			}
			Cur = NULL;
		}
		else
		{
			Pre = Cur;
			Cur = Cur->pnext;
		}
	}
}


//������



pListNode FindMidNode(pLiskList plist)
{
	assert(plist);
	pListNode pfast = plist->phead;
	pListNode pslow = plist->phead;
	if (plist->phead == NULL)
	{
		return NULL;
	}
	while ((pfast->pnext != NULL) && (pfast->pnext->pnext != NULL))
	{
		pfast = pfast->pnext->pnext;
		pslow = pslow->pnext;
	}
	//����ڵ����Ϊż���������м�ϴ��һ��
	return pslow;
}

void ReverseList(pLiskList plist)
{
	assert(plist);
	pListNode cur = plist->phead;
	pListNode pnode = NULL;
	pListNode pnewhead = NULL;

	if ((NULL == plist->phead) || (NULL == plist->phead))
	{
		return;
	}	
	while (cur != NULL)
	{
		pnode = cur;
		cur = cur->pnext;
		pnode->pnext = pnewhead;
		pnewhead = pnode;
	}
	plist->phead = pnode;
}

void InsertNotHead(pListNode pos, DataType _data)
{
	if (NULL == pos)
	{
		printf("ָ��λ��Ϊ��\n");
		return;
	}
	//posΪ��ͷ���
	pListNode ptmp = Byenode(pos->data);
	ptmp->pnext = pos->pnext;
	pos->pnext = ptmp;
	pos->data = _data;
}

void DelNotTailNode(pListNode pos)
{
	if (NULL == pos)
	{
		printf("ָ��λ��Ϊ��\n");
		return;
	}
	//����pos�Ƿ�β��㣬���Բ����ж�pos->pnext�ǲ���NULL��Ҳ������ΪNULL
	pListNode ptmp = pos->pnext;
	pos->data = ptmp->data;
	pos->pnext = ptmp->pnext;
	free(ptmp);
	ptmp = NULL;
}

//void SortList(pLiskList plist)
//{
//	assert(plist);
//	int i = 0;
//	int j = 0;
//	int count = 0;
//	int flag = 1;
//	pListNode cur = plist->phead;
//	for (i = 0; cur != NULL; i++)
//	{
//		count++;
//		cur = cur->pnext;
//	}
//
//	for (i = 0; i < count - 1; i++)
//	{
//		flag = 1;
//		cur = plist->phead;
//		for (j = 0; j < count - i - 1; j++)
//		{
//			if ((cur->data)>(cur->pnext->data))
//			{
//				DataType tmp = 0;
//				tmp = cur->data;
//				cur->data = cur->pnext->data;
//				cur->pnext->data = tmp;
//				flag = 0;
//			}
//			cur = cur->pnext;
//		}
//		if (flag == 1)
//		{
//			break;
//		}
//	}
//}

int HasCycle(pLiskList plist)
{
	assert(plist);
	pListNode fast = plist->phead;
	pListNode slow = plist->phead;
	if (NULL == plist->phead)
	{
		return 0;
	}
	while ((fast != NULL) && (fast->pnext != NULL))
	{
		slow = slow->pnext;
		fast = fast->pnext->pnext;
		if (slow == fast)
		{
			return 1;
		}
	}
	return 0;
}

//pListNode FindLastKNode(pLiskList plist, int k)
//{
//	assert(plist);
//	pListNode slow = plist->phead;
//	pListNode fast = plist->phead;
//	if (NULL == plist->phead)
//	{
//		return NULL;
//	}
//	while (k--)
//	{
//		fast = fast->pnext;
//		if ((NULL == fast) && (k != 0))
//		{
//			return NULL;
//		}
//	}
//	while (fast != NULL)
//	{
//		fast = fast->pnext;
//		slow = slow->pnext;
//	}
//	return slow;
//}

void BubbleSort(pLiskList plist)
{
	assert(plist);
	pListNode cur = plist->phead;
	pListNode tail = NULL;
	while (cur != tail)
	{
		while (cur->pnext != tail)
		{
			if ((cur->data) > (cur->pnext->data))
			{
				DataType tmp = cur->data;
				cur->data = cur->pnext->data;
				cur->pnext->data = tmp;
			}
			cur = cur->pnext;
		}
		tail = cur;
		cur = plist->phead;
	}
}

void SelectSort(pLiskList plist)
{
	assert(plist);
	pListNode cur = plist->phead;
	pListNode pcur = plist->phead;
	pListNode pnode = NULL;
	DataType tmp = 0;

	if (NULL == cur)
	{
		return;
	}
	while (cur->pnext != NULL)
	{
		pnode = cur->pnext;
		pcur = cur;
		while (pnode != NULL)
		{
			if (pcur->data > pnode->data)
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

void EraseLastKNode(pLiskList plist, int k)
{
	assert(plist);
	pListNode front = plist->phead;
	pListNode back = plist->phead;
	if (k <= 1)	while (front)

	{
		return;
	}
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