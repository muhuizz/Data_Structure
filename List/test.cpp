#include "List.hpp"

struct A
{
	int a;
	char c;
	A()
		:a(1)
		 ,c('c')
	{}
};

int main()
{
	List<A> l2;
	l2.PushBack(A());
	List<A>::Iterator it = l2.Begin();
	cout<<it->a<<endl;
	cout<<it->c<<endl;


//	List<int> l1;
//	l1.PushFront(1);
//	l1.PushFront(2);
//	l1.PushFront(3);
//	l1.PushFront(4);
////	l1.PushBack(1);
////	l1.PushBack(2);
////	l1.PushBack(3);
////	l1.PushBack(4);
//	List<int>::Iterator it = l1.Begin();
//	while(it != l1.End())
//	{
//		cout<<*it<<endl;
//		it++;
//	}
//	cout<<endl;
//	l1.PopFront();
//	l1.PopFront();
//	l1.PopFront();
//	l1.PopFront();
//	l1.PopFront();
//	l1.PopFront();
////	l1.PopBack();
////	l1.PopBack();
////	l1.PopBack();
////	l1.PopBack();
////	l1.PopBack();
////	l1.PopBack();
//	while(it != l1.End())
//	{
//		cout<<*it<<endl;
//		it++;
//	}
	return 0;
}
