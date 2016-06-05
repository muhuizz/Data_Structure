#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqList.h"

void PrintSeqlist(pSeqList pseq)
{
	int i = 0;
	assert(pseq);
	for (i = 0; i < pseq->sz; ++i)
	{
		printf("%d ",pseq->data[i]);
	}
	printf("\n");
}

void InitSeqList(pSeqList pseq)
{
	assert(pseq);
	pseq->sz = 0;
	memset(pseq,0,sizeof(DataType)*MAX_SIZE);
}

void PushBack(pSeqList pseq, DataType  data)
{
	assert(pseq);
	pseq->data[pseq->sz] = data;
	++pseq->sz;
}

void PopBack(pSeqList pseq)
{
	assert(pseq);
	--pseq->sz;
}

void PushFront(pSeqList pseq, DataType  data)
{
	int i = 0;
	assert(pseq);
	for (i = pseq->sz; i > 0; --i)
	{
		pseq->data[i] = pseq->data[i - 1];
	}
	pseq->data[0] = data;
	++pseq->sz;
}

void PopFront(pSeqList pseq)
{
	int i = 0;
	assert(pseq);
	for (i = 0; i < pseq->sz-1; ++i)
	{
		pseq->data[i] = pseq->data[i + 1];
	}
	--pseq->sz;
}

void Insert(pSeqList pseq, int pos, DataType data)
{
	int i = 0;
	assert(pseq);
	for (i = pseq->sz; i > pos; --i)
	{
		pseq->data[i] = pseq->data[i - 1];
	}
	pseq->data[pos] = data;
	++pseq->sz;
}

void Remove(pSeqList pseq, DataType data)
{
	int i = 0;
	assert(pseq);
	for (i = 0; i < pseq->sz; ++i)
	{
		if (pseq->data[i] == data)
		{			
			break;
		}
	}
	if (i != pseq->sz)
	{
		while (i < pseq->sz - 1)
		{
			pseq->data[i] = pseq->data[i + 1];
			++i;
		}
		--pseq->sz;
	}
	else
	{
		printf("查无此数\n");
	}
}

void RemoveAll(pSeqList pseq, DataType data)
{
	int i = 0;
	int count = 0;
	int j = 0;
	assert(pseq);
	for (i = 0; i < pseq->sz; ++i)
	{
		if (pseq->data[i] == data)
		{
			count++;
			continue;
		}
		pseq->data[j++] = pseq->data[i];
	}
	pseq->sz -= count;
	if (count == 0)
	{
		printf("查无此数\n");
	}
}

void Sort_Bubble(pSeqList pseq)
{
	assert(pseq);
	int i = 0;
	int j = 0;
	int flag = 1;
	for (i = 0; i < pseq->sz - 1; ++i)
	{
		flag = 1;
		for (j = 0; j < pseq->sz - i - 1; ++j)
		{
			if (pseq->data[j]>pseq->data[j + 1])
			{
				int tmp = pseq->data[j];
				pseq->data[j] = pseq->data[j + 1];
				pseq->data[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag == 0)
		{
			break;
		}
	}
}

void Sort_Select (pSeqList pseq)
{
	assert(pseq);
	int i = 0;
	int j = 0;
	int index = 0;
	for (i = 0; i < pseq->sz-1; ++i)
	{
		index = i;
		for (j = i+1; j < pseq->sz; ++j)
		{
			if (pseq->data[index]>pseq->data[j])
			{
				index = j;
			}				
		}
		DataType tmp = pseq->data[i];
		pseq->data[i] = pseq->data[index];
		pseq->data[index] = tmp;
	}
}

void Sort_Insert(pSeqList pseq)//时间复杂度为n^2
{
	assert(pseq);
	int i = 0;
	int j = 0;
	DataType tmp = 0;
	for (i = 1; i < pseq->sz; ++i)
	{
		tmp = pseq->data[i];
		j = i - 1;
		while ((j >= 0) && (pseq->data[j]) >tmp)
		{
			pseq->data[j + 1] = pseq->data[j];
			--j;
		}
		pseq->data[j + 1] = tmp;
	}
}

int BinarySearch(pSeqList pseq, DataType data)
{
	DataType left = 0;
	DataType right = pseq->sz-1;
	DataType mid = 0;
	assert(pseq);
	while (left < right)
	{
		mid = (left & right) + ((left^right) >> 1);
		if (pseq->data[mid] > data)
		{
			right = mid - 1;
		}
		else if (pseq->data[mid] < data)
		{
			left = mid + 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

















