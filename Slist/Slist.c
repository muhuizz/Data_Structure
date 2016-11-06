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
		printf("无效节点，插入失败\n");
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


//面试题

//void PrintList_reverse(pLiskList plist)
//{
//	assert(plist);
//	pListNode Cur = plist->phead;
//	if (Cur == NULL)
//	{
//		return;
//	}
//	if (Cur != NULL)
//	{
//		PrintList_reverse(Cur->pnext);
//	}
//	printf("%d<-", Cur->data);
//}

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
	//如果节点个数为偶数，返回中间较大的一个
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
		printf("指定位置为空\n");
		return;
	}
	//pos为非头结点
	pListNode ptmp = Byenode(pos->data);
	ptmp->pnext = pos->pnext;
	pos->pnext = ptmp;
	pos->data = _data;
}

void DelNotTailNode(pListNode pos)
{
	if (NULL == pos)
	{
		printf("指定位置为空\n");
		return;
	}
	//由于pos是非尾结点，所以不用判断pos->pnext是不是NULL，也不允许为NULL
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

//int HasCycle(pLiskList plist)
//{
//	assert(plist);
//	pListNode fast = plist->phead;
//	pListNode slow = plist->phead;
//	if (NULL == plist->phead)
//	{
//		return 0;
//	}
//	while ((fast != NULL) && (fast->pnext != NULL))
//	{
//		slow = slow->pnext;
//		fast = fast->pnext->pnext;
//		if (slow == fast)
//		{
//			return 1;
//		}
//	}
//	return 0;
//}


pListNode HasCycle(pLiskList plist)
{
	assert(plist);
	pListNode fast = plist->phead;
	pListNode slow = plist->phead;
	if (NULL == plist->phead)
	{
		return NULL;
	}
	while ((fast != NULL) && (fast->pnext != NULL))
	{
		slow = slow->pnext;
		fast = fast->pnext->pnext;
		if (slow == fast)
		{
			return slow;
		}
	}
	return NULL;
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

int IsListCrose(pLiskList pL1, pLiskList pL2)
{
	assert(pL1);
	assert(pL2);
	pListNode ptmp1 = pL1->phead;
	pListNode ptmp2 = pL2->phead;
	if ((ptmp1 == NULL) || (ptmp2 == NULL))
	{
		return 0;
	}
	while (ptmp1->pnext != NULL)
	{
		ptmp1 = ptmp1->pnext;
	}
	while (ptmp2->pnext != NULL)
	{
		ptmp2 = ptmp2->pnext;
	}
	if (ptmp1 == ptmp2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

pListNode JosephCircle(pLiskList plist, int M)
{
	assert(plist);
	int k = 0;
	pListNode del = NULL;
	pListNode cur = plist->phead;
	if (M <= 0)
	{
		return NULL;
	}
	else
	{
		while (cur->pnext != cur)
		{
			k = M;
			while (--k)
			{
				cur = cur->pnext;
			}
			del = cur->pnext;
			cur->pnext = del->pnext;
			free(del);
			del = NULL;
		}
	}
	return cur;
}


pListNode FindEnterNode(pLiskList plist)
{
	assert(plist);
	pListNode ret = HasCycle(plist);
	if (ret == NULL)
	{
		return NULL;
	}
	pListNode back = plist->phead;
	pListNode front = ret;
	while (back != front)
	{
		back = back->pnext;
		front = front->pnext;
	}
	return back;
}

int IsListCroseWithCycle(pLiskList pL1, pLiskList pL2)
{
	assert(pL1);
	assert(pL2);
	pListNode pmeet1 = HasCycle(pL1);
	pListNode pmeet2 = HasCycle(pL2);

	if ((NULL == pmeet1) && (NULL == pmeet2))
	{
		pListNode cur1 = pL1->phead;
		pListNode cur2 = pL2->phead;
		if ((cur1 == NULL) || (cur2 == NULL))
		{
			return 0;
		}
		while (cur1->pnext != NULL)
		{
			cur1 = cur1->pnext;
		}
		while (cur2->pnext != NULL)
		{
			cur2 = cur2->pnext;
		}
		if (cur1 == cur2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	if ((NULL != pmeet1) && (NULL != pmeet2))
	{
		pListNode cur1 = pmeet1;
		pListNode cur2 = pmeet2;
		if (cur2 == cur1)
		{
			return 1;
		}
		while (cur1->pnext != cur1)
		{
			if (cur1 == cur2)
			{
				return 1;
			}
			cur1 = cur1->pnext;
		}
	}
	return 0;
}

pListNode MergeList(pLiskList pL1, pLiskList pL2)
{
	assert(pL1);
	assert(pL2);
	pListNode cur1 = pL1->phead;
	pListNode cur2 = pL2->phead;
	pListNode pnode = NULL;

	pListNode newhead = NULL;
	pListNode tail = NULL;
	
	if (NULL == cur1)
	{
		return cur2;
	}
	if (NULL == cur2)
	{
		return cur1;
	}

	if (cur1->data > cur2->data)
	{
		pnode = cur2;
		cur2 = cur2->pnext;
	}
	else
	{
		pnode = cur1;
		cur1 = cur1->pnext;
	}
	newhead = pnode;
	tail = pnode;
	while ((NULL != cur1) && (NULL != cur2))
	{
		if (cur1->data > cur2->data)
		{
			pnode = cur2;
			cur2 = cur2->pnext;
		}
		else
		{
			pnode = cur1;
			cur1 = cur1->pnext;
		}
		tail->pnext = pnode;
		tail = tail->pnext;
	}
	if (NULL == cur1)
	{
		tail->pnext = cur2;
		return newhead;
	}
	else
	{
		tail->pnext = cur1;
		return newhead;
	}
}

int GetCyleLen(pListNode pMeetNode)
{
	if (pMeetNode == NULL)
	{
		return 0;
	}
	int count = 1;
	pListNode cur = pMeetNode;
	while (cur->pnext != pMeetNode)
	{
		cur = cur->pnext;
		count++;
	}
	return count;
}


