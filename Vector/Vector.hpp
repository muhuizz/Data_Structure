#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>
using namespace std;
#include <cstring>
#include "TypeTraits.hpp"

template <typename T>
class Vector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;
	
	Vector()
		:_start(NULL)
		 ,_finish(NULL)
		 ,_endOfStorage(NULL)
	{}
	~Vector()
	{}
public:
	Iterator Begin() const
	{
		return _start;
	}
	Iterator End() const
	{
		return _finish;
	}
//	ConstIterator Begin() const
//	{
//		return _start;
//	}
//	Iterator End() const
//	{
//		return _finish;
//	}
	size_t Size() const
	{
		return (End() - Begin());
	}
	size_t Capacity() const
	{
		return (_endOfStorage - Begin());
	}
	bool Empty() const
	{
		return (Begin() == End());
	}
	T& Front()
	{
		return (*Begin());
	}
	T& Back()
	{
		return (*(End()-1));
	}

	T& operator[](size_t pos)
	{
		return *(Begin()+pos);
	}
	void PushBack(const T& x)
	{
		CheckVector();
		*_finish = x;
		_finish++;
	}
	void PopBack()
	{
		if(!Empty())
			_finish--;
	}
	void Insert(Iterator pos, const T& x)
	{
		Iterator tmp = End();
		while(tmp != pos)
		{
			*tmp = *(tmp-1);
			tmp--;
		}
		*pos = x;
		_finish++;
	}
	void Erase(Iterator pos)
	{
		while((pos+1) != End())
		{
			*pos = *(pos+1);
			pos++;
		}
		--_finish;
	}
protected:
	void CheckVector()
	{
		if(_endOfStorage == End())
		{
			size_t size=Size();
			int newCapacity = (size==0?1:(size*2));
			T* tmp = new T[newCapacity];
			//
			if(typename TypeTraits<T>::__IsPODType().Get())
			{
				memcpy(tmp, _start, sizeof(T)*Size());
			}
			else
			{
				for(size_t i=0; i < Size(); i++)
				{
					tmp[i] = *(_start+i);
				}
			}
			delete[] _start;
			_start=tmp;
			_finish=_start+size;	// can't use Size()
			_endOfStorage=_start+newCapacity;
		}
	}
protected:
	Iterator _start;		// the head of used_space
	Iterator _finish;		// the tail of used_space
	Iterator _endOfStorage;	// the tail of all_space
};

#endif// __VECTOR_HPP__

