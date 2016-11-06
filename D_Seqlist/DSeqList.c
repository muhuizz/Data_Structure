#define _CRT_SECURE_NO_WARNINGS 1

#include "DSeqList.h"

void Init_DSeqlist(pSeq pseq)
{
	assert(pseq);
	pseq->capacity = INIT_MAX;
	pseq->size = 0;
	pseq->data = (DataType *)malloc(sizeof(DataType)*pseq->capacity);
	if (NULL == pseq->data)
	{
		printf("out of memory\n");
		system("pasue");
		exit(EXIT_FAILURE);
	}
}

void Check_DSeqlist(pSeq pseq)
{
	assert(pseq);
	if (pseq->size == pseq->capacity)
	{
		DataType* ptmp = NULL;
		ptmp= (DataType*)realloc(pseq->data,sizeof(DataType)*(pseq->capacity + ADD_MAX));
		if (NULL == ptmp)
		{
			printf("out of memory\n");
			system("pasue");
			exit(EXIT_FAILURE);
		}
		pseq->data = ptmp;
		pseq->capacity += ADD_MAX;
	}
}

void Destory_DSeqList(pSeq pseq)
{
	assert(pseq);
	free(pseq->data);
	pseq->data = NULL;
	pseq->capacity = 0;
	pseq->size = 0;
}

void Push_Back(pSeq pseq, DataType data)
{
	Check_DSeqlist(pseq);
	pseq->data[pseq->size] = data;
	pseq->size++;
}

void Pop_Back(pSeq pseq)
{
	if (pseq->size == 0)
	{
		printf("SeqList is empty\n");
		system("pause");
		return;
	}
	pseq->size--;
}

void Push_Front(pSeq pseq, DataType data)
{
	assert(pseq);
	Check_DSeqlist(pseq);
	int i = 0;
	for (i = pseq->size; i >0;i--)
	{
		pseq->data[i] = pseq->data[i - 1];
	}
	pseq->data[0] = data;
	pseq->size++;
}

void Pop_Front(pSeq pseq)
{
	assert(pseq);
	int i = 0;
	for (i = 0; i < pseq->size-1; i++)
	{
		pseq->data[i] = pseq->data[i + 1];
	}
	pseq->size--;
}

void Print_Dseqlist(pSeq pseq)
{
	assert(pseq);
	if (pseq == NULL)
	{
		printf("DSeqList is empty\n");
		system("pause");
		return;
	}
	for (int i = 0; i < pseq->size; i++)
	{
		printf("%d ",pseq->data[i]);
	}
	printf("\n");
}

void Remove(pSeq pseq, DataType data)
{
	assert(pseq);
	int i = 0;
	for (i = 0; i < pseq->size; i++)
	{
		if (pseq->data[i] == data)
		{
			break;
		}
	}
	if (i == pseq->size)
	{
		printf("查无此数\n");
		return;
	}
	else
	{
		while (i < pseq->size-1)
		{
			pseq->data[i] = pseq->data[i + 1];
			i++;
		}
		pseq->size--;
	}
}

void RemoveAll(pSeq pseq, DataType data)
{
	assert(pseq);
	int count = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i< pseq->size; i++)
	{
		if (pseq->data[i] == data)
		{
			count++;
			continue;
		}
		pseq->data[j++] = pseq->data[i];
	}
	pseq->size -= count;
}

void Bubble_Sort(pSeq pseq)
{
	assert(pseq);
	int i = 0;
	int j = 0;
	int flag = 0;
	int k = pseq->size - 1;
	for (i = 0; i < pseq->size - 1; i++)
	{
		int m = 0;
		flag = 1;	
		for (j = 0; j < k; j++)
		{
			if (pseq->data[j]>pseq->data[j + 1])
			{
				DataType tmp = pseq->data[j];
				pseq->data[j] = pseq->data[j + 1];
				pseq->data[j + 1] = tmp;
				flag = 0;
				m = j;
			}			
		}
		k = m;
		if (flag == 1)
		{
			break;
		}
	}
}

void Inset_Sort(pSeq pseq)
{
	assert(pseq);
	int i = 0;
	int j = 0;
	int tmp = 0;
	for (i = 1; i < pseq->size; i++)
	{
		tmp = pseq->data[i];
		for (j = i - 1; (j >= 0) && (pseq->data[j] >tmp); j--)
		{
			pseq->data[j + 1] = pseq->data[j];
		}
		pseq->data[j+1] = tmp;
	}
}

void Select_Sort(pSeq pseq)
{
	assert(pseq);
	int i = 0; 
	int j = 0;
	int index = 0;
	DataType tmp = 0;
	for (i = 0; i < pseq->size - 1; i++)
	{
		index = i;
		for (j = i+1; j < pseq->size; j++)
		{
			if (pseq->data[index]>pseq->data[j])
			{
				index = j;
			}
		}
		tmp = pseq->data[index];
		pseq->data[index] = pseq->data[i];
		pseq->data[i] = tmp;
	}
}

int BinarySearch(pSeq pseq, DataType data)
{
	assert(pseq);
	DataType left = 0;
	DataType right = pseq->size - 1;
	DataType mid = 0;
	assert(pseq);
	while (left <= right)
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
		else if (pseq->data[mid] == data)
		{
			return mid;
		}
	}
	printf("查无此数\n");
	return -1;
}

void Erase(pSeq pseq, int pos)
{
	assert(pseq);
	if ((pos >= pseq->size)||(pos < 0))
	{
		printf("error od pos\n");
		return;
	}
	int i = 0;
	for (i = pos; i<pseq->size-1; i++)
	{
		pseq->data[i] = pseq->data[i + 1];
	}
	pseq->size--;
}