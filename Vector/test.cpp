#include "Vector.hpp"

int main()
{
	Vector<int> vec;
	vec.PushBack(1);
	vec.PushBack(2);
	vec.PushBack(3);
	vec.PushBack(4);
	vec.PushBack(5);
	vec.PushBack(6);
	Vector<int>::Iterator it = vec.Begin();
	vec.Erase(++it);
//	it++;
//	vec.Insert(it, 99);
	cout<<"Size#"<<vec.Size()<<endl;
	cout<<"Capacity#"<<vec.Capacity()<<endl;
	for(size_t i = 0;i<vec.Size(); i++)
	{
		cout<<vec[i]<<"--";
	}
//	cout<<endl;
//	vec.PopBack();
//	vec.PopBack();
//	vec.PopBack();
//	vec.PopBack();
//	vec.PopBack();
//	cout<<"Size#"<<vec.Size()<<endl;
//	cout<<"Capacity#"<<vec.Capacity()<<endl;
//	for(size_t i = 0;i<vec.Size(); i++)
//	{
//		cout<<vec[i]<<"--";
//	}
	cout<<endl;
	return 0;
}
