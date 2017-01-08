#pragma once

#include <iostream>
#include <cassert>
using namespace std;

enum Type
{
	VALUE_TYPE,// next、type、方峙
	HEAD_TYPE,//next、type
	SUB_TYPE//next、type、_sublink
};

template<typename T>
struct GeneralizeNode
{
	Type _type;
	GeneralizeNode*  _next;
	union 
	{
		char _value;
		GeneralizeNode*  _sublink;
	};
	GeneralizeNode()
		:_next(NULL)
	{}
};

template<typename T>
class GeneralizeTable
{
	typedef GeneralizeNode<T> Node;
public:
	GeneralizeTable()
		:_head(NULL)
	{}
	GeneralizeTable(const char* str )
		:_head(NULL)
	{
		_head = _CreatGeneralize(str);
	}
	GeneralizeTable(const GeneralizeTable& g)
	{
		_head = _Copy(g._head);
	}
	~GeneralizeTable()
	{
		 _destory(_head);
	}
	void Print()
	{
		_print(_head);
		cout << endl;

	}
	size_t Size()
	{
		return __size(_head);
	}
	size_t Depth()
	{
		return __depth(_head);
	}
protected:
	void _print(Node* node)
	{
		Node* cur = node;
		while (cur)
		{
			if (cur->_type == HEAD_TYPE)
			{
				cout << "(";
			}
			else if (cur->_type == SUB_TYPE)
			{
				_print(cur->_sublink);
			}
			else if (cur->_type == VALUE_TYPE)
			{
				cout << cur->_value;
				if (cur->_next != NULL)
				{
					cout << ",";
				}
			}
				cur = cur->_next;
		}
		cout << ")";
	}

	bool is_value(const char& c)
	{
		if ((c >= '1' && c <= '9') || (c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z')))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Node* _CreatGeneralize(const char*& str)
	{
		assert(*str == '(');
		Node *head = new Node();
		head->_type = HEAD_TYPE;
		Node* cur = head;
		str++;
		while (str)
		{
			if (*str == '(')
			{
				Node * newnode = new Node();
				newnode->_type = SUB_TYPE;
				cur->_next = newnode;
				cur=cur->_next;
				newnode->_sublink = _CreatGeneralize(str);
				str++;
			}
			else if (is_value(*str))
			{
				Node* newnode = new Node();
				newnode->_type = VALUE_TYPE;
				newnode->_value = *str;
				cur->_next = newnode;
				cur = cur->_next;
				str++;
			}
			else if (*str == ')')
			{
				return head;
			}
			else
			{
				str++;
			}
		}
		return head;
	}

	Node* _Copy(Node* node)
	{
		Node* head = new Node();
		head->_type = HEAD_TYPE;
		Node* cur = node;
		Node* newcur = head;

		while (cur)
		{
			if (cur->_type == SUB_TYPE)
			{
				Node* newnode = new Node();
				newnode->_type = SUB_TYPE;
				newcur->_next = newnode;
				newcur = newcur->_next;
				newnode->_sublink = _Copy(cur->_sublink);
			}
			else if (cur->_type == VALUE_TYPE)
			{
				Node* newnode = new Node();
				newnode->_type = VALUE_TYPE;
				newnode->_value = cur->_value;
				newcur->_next = newnode;
				newcur = newcur->_next;
			}
			cur = cur->_next;
		}
		return head;
	}

	void _destory(Node* head)
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->_type == SUB_TYPE)
			{
				_destory(cur->_sublink);
			}
			Node* del = cur;
			cur = cur->_next;
			delete del;
			del = NULL;
		}
	}
	size_t __size(Node* head)
	{
		Node* cur = head;
		size_t count = 0;
		while (cur != NULL)
		{
			if (cur->_type == VALUE_TYPE)
			{
				count++;
			}
			else if (cur->_type == SUB_TYPE)
			{
				count += __size(cur->_sublink);
			}
			cur = cur->_next;
		}
		return count;
	}

	size_t __depth(Node*  head)
	{
		Node* cur = head;
		size_t max_depth = 1;
		while (cur)
		{
			size_t depth = 1;
			if (cur->_type == SUB_TYPE)
			{
				depth += __depth(cur->_sublink);
				if (depth > max_depth)
				{
					max_depth = depth;
				}
			}
			cur = cur->_next;
		}
		return max_depth;
	}

protected:
	Node* _head;
};

void TestGeneralizeTable()
{
	GeneralizeTable<int> g1("()");
	GeneralizeTable<int> g2("(a,b)");
	GeneralizeTable<int> g3("((a,b,(c,d)))");
	GeneralizeTable<int> g4("((    a,b, (a,d) , (e,(f),h)    ))");

	g1.Print();
	cout << g1.Size() << endl;
	cout << "max_depth is "<<g1.Depth() << endl;

	g2.Print();
	cout << g2.Size() << endl;
	cout << "max_depth is " << g2.Depth() << endl;

	g3.Print();
	cout << g3.Size() << endl;
	cout << "max_depth is " << g3.Depth() << endl;

	g4.Print();
	cout << g4.Size() << endl;
	cout << "max_depth is " << g4.Depth() << endl;

	//GeneralizeTable<int >g5(g4);
	//g5.Print();
}
