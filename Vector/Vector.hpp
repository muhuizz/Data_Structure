#pragma once

#include <iostream>
#include <cassert>
#include "TypeTraits.hpp"
using namespace std;
//vector�ĵ���������һ��ָ�롣
//new(_finish)T(x);
template<typename T>
class Vector
{
public:
	typedef T* VectorIterator;
	typedef const T* ConstVectorIterator;
	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endofstorage(NULL)
	{}
	//��������
	//��ǳ������������ȡ����Ʒ���
	//������Ŀ��һ��ֻ��Ϊ�˷��ʣ��¿��ٵĿռ�ֻ��Ҫ��ЧԪ�صĿռ伴��
	Vector(const Vector& v)
	{
		size_t size = v.Size();
		T* tmp = new T[size];
		if (TypeTraits<T>::__IsPODType().Get())
		{
			memcpy(tmp, v._start, size* sizeof(T));
		}
		else
		{
			for (size_t i = 0; i < size; i++)
			{
				tmp[i] = *(v._start + i);
			}
		}
		delete[]v._start;
		v._start = tmp;
		v._finish = v._start + size;
		v._endofstorage = v._finish;
	}

	~Vector()
	{
		if (_start != NULL)
		{
			delete[] _start;
		}
	}

	void PushBack(const T& x)
	{
		CheckVector();
		*_finish = x;
		_finish++;
	}

	void PopBack()
	{
		assert(_start);
		_finish--;
	}

	void Insert(VectorIterator pos,const T& x)
	{
		CheckVector();
		VectorIterator tmp = _finish;
		while (tmp != pos)
		{
			*tmp = *(tmp - 1);
			tmp--;
		}
		*pos = x;
		_finish++;
	}

	void Erase(VectorIterator pos)
	{
		assert(_start);
		while (pos != _finish)
		{
			*pos = *(pos + 1);
			pos++;
		}
		--_finish;
	}

	VectorIterator Begin()
	{
		assert(_start);
		return _start;
	}
	VectorIterator End()
	{
		assert(_start);
		return _finish;
	}

	ConstVectorIterator Begin()const 
	{
		assert(_start);
		return _start;
	}
	ConstVectorIterator End()const 
	{
		assert(_start);
		return _finish;
	}

private:
	size_t Size()
	{
		if (_start == NULL)
		{
			return 0;
		}
		return _finish - _start;
	}

	void CheckVector()
	{
		if (_endofstorage == _finish)
		{
			size_t size = Size();
			int newcapacity = size * 2 + 3;
			T* tmp = new T [newcapacity];

			if (TypeTraits<T>::__IsPODType().Get())
			{
				memcpy(tmp, _start, sizeof(T)*size);
			}
			else
			{
				for (size_t i = 0; i < size; i++)
				{
					//tmp[i] = _start[i];
					tmp[i] = *(_start + i);
				}
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + newcapacity;
		}
	}

private:
	VectorIterator _start;
	VectorIterator _finish;
	VectorIterator _endofstorage;
};
template<typename T>
void PrintVector( Vector<T>& v)
{
	Vector<T>::VectorIterator it = v.Begin();
	for (; it != v.End(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void TestVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.Insert(v.Begin(),99);
	v.PushBack(5);
	PrintVector(v);
	v.PopBack();
	v.PopBack();
	v.Erase(v.End());
	PrintVector(v);
}