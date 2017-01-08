#pragma once
/**************��Ŀ��������*************	
�����
***********************************/

#include <iostream>
using namespace std;
#include <cassert>

enum TYPE
{
	HeadType,
	ValueType,
	SubType
};

template <typename T>
struct GeneralTableNode
{
	TYPE _nodeType;
	GeneralTableNode* _next;

	union // ����
	{
		T _value;
		GeneralTableNode* _sub;
	};
	GeneralTableNode()
		:_next(NULL)
	{}
};

template <class T>
class GeneralTable
{
	typedef GeneralTableNode<T> Node;
public:
	GeneralTable()	// Ĭ�Ϲ���	
		:_head(NULL)
	{}
	GeneralTable(const T* str)		// ���� 
		:_head(NULL)
	{
		_head = _CreatGeneralTable(str);
		cout << "1" << endl;
	}
	GeneralTable(const GeneralTable<T>& g)
	{
		Node* tmp = g._head;
		_head = _Copy(tmp);
		cout << "2" << endl;
	}
	~GeneralTable()
	{
		_Destory(_head);
		cout << "3" << endl;
	}

	// �������ܺ���
	void Print()
	{}

	size_t Size()
	{}

	size_t Depth()
	{}
private:
	bool _IsValue(const T& x)
	{
		if ((x >= '0' && x <= '9') || (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		{
			return true;
		}
		else
			return false;
	}

	Node* _CreatGeneralTable(const T*& str)		// �������Ҫ�������ã���ΪҪ�ڵݹ��ͬʱ��һ�����н��з���
	{
		assert(*str == '(');			// ��֤str��Ч
		Node*head = new Node();
		head->_nodeType = HeadType;
		Node* cur = head;
		str++;
		while (*str)
		{
			switch (*str)
			{
			case '(':
				cur->_next = new Node();
				cur->_next->_nodeType = SubType;
				cur->_next->_sub = _CreatGeneralTable(str);	//�ݹ鴴��Sub��
				cur = cur->_next;
				str++;
				break;
			case ')':
				return head;
				break;
			default:
				if (_IsValue(*str))		// ���*str��ֵΪ���ֻ�����ĸ����Ϊ��Чֵ�����Ը���ʵ������Ըú������иı䣬�ﵽɾѡ��Ŀ��
				{
					cur->_next = new Node();
					cur->_next->_nodeType = ValueType;
					cur->_next->_value = *str;
					cur = cur->_next;
				}
				str++;
				break;
			}
		}
		return head;
	}
	
	Node* _Copy(Node* node)
	{
		if (node == NULL)
		{
			return NULL;
		}
		assert(node->_nodeType == HeadType);
		Node* newhead = new Node();
		newhead->_nodeType = HeadType;
		node = node->_next;
		Node* cur = newhead;

		while (node)
		{
			switch (node->_nodeType)
			{
			case ValueType:
				cur->_next = new Node();
				cur->_next->_nodeType = ValueType;
				cur->_next->_value = node->_value;
				cur = cur->_next;
				node = node->_next;
				break;
			case SubType:
				cur->_next = new Node();
				cur->_next->_nodeType = SubType;
				cur->_next->_sub = _Copy(node->_sub);
				cur = cur->_next;
				node = node->_next;
				break;
			default:
				cout << "error for copy" << endl;
				exit(EXIT_FAILURE);
			}
		}
		return newhead;
	}
	
	void _Destory(Node* head)
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->_nodeType == SubType)	// ��ʾ�ý���������ҵĽ��
			{
				_Destory(cur->_sub);
			}
			Node* del = cur;			//  ��ʹ��sub��㣬destory���ҽ��֮����Ȼ��Ҫɾ��������
			cur = cur->_next;
			delete del;
		}
	}
private:
	Node* _head;
};

void TestGeneralTable()
{
	{
		GeneralTable<char> g1("()");
		GeneralTable<char> g2("(a,b)");
		GeneralTable<char> g3("((a,b,(c,d)))");
		GeneralTable<char> g4("((a,b, (a,d) , (e,(f),h)))");

		GeneralTable<char> g5(g1);
		GeneralTable<char> g6(g2);
		GeneralTable<char> g7(g3);
		GeneralTable<char> g8(g4);
	}
}





