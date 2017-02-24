// 1.逆序打印代码
	// 方法一
	void PrintReverse_1()
	{
		assert(_head);
		stack<T> mysta;
		Node* cur = _head->_next;
		while (cur != NULL)
		{
			mysta.push(cur->_data);
			cur = cur->_next;
		}
		while (!mysta.empty())
		{
			cout << mysta.top() << "---";
			mysta.pop();
		}
		cout << endl;
	}
	// 方法二
	void _printReverse_R(Node* node)
	{
		if (node == NULL)
			return;
		_printReverse_R(node->_next);
		cout << node->_data << "--->";
	}
	void PrintReverse_2()
	{
		assert(_head);
		Node* node = _head->_next;
		_printReverse_R(node);
		cout << endl;
	}
// 2.删除无头单链表的非尾节点
	void DeleteNode_withoutHead(Node* node)
	{
		assert(node);
		Node* del = node->_next;
		node->_data = node->_next->_data;
		node->_next = del->_next;
		destory_node(del);
	}

// 3.在无头单链表的非头结点前插入一个结点
	void Insert_IsNotHead(Node* node, const T& x)
	{
		assert(node);
		Node* tmp = new Node(node->_data);
		tmp->_next = node->_next;
		node->_data = x;
		node->_next = tmp;
	}
	
// 4. 单链表的逆置
	// 方法一
	void Reverse_1(Node* head)
	{
		if(head == NULL || head->_next == NULL)
			return;
		Node* cur = head;
		Node* prev = NULL;		
		Node* tmp = NULL;
		while (cur)
		{
			tmp = cur->_next;
			cur->_next = prev;
			prev = cur;
			cur = tmp;
		}
	}
	// 方法二
	LinkNode<int>* _reverseR(LinkNode<int>* node, LinkNode<int>* prev)
	{
		if (node == NULL)
			return prev;
		LinkNode<int>* tmp = node->_next;
		node->_next = prev;
		return _reverseR(tmp, node);
	}
	void Reverse_2(LinkList<T> list)
	{
		Node* head = list->_head;
		if(head == NULL || head->_next == NULL)
			return;
		LinkNode<int>* ret =  _reverseR(list->_head, NULL);
	}

//5、合并有序链表
	Node* MergeLinkList(LinkList<T>* l1, LinkList<T>* l2)
	{
		assert(l1);
		assert(l2);
		Node* node1 = l1->_head;
		Node* node2 = l2->_head;
		return _Merge(node1, node2);
	}
	Node* _Merge(Node* node1, Node* node2)
	{
		if (node1 == NULL)
			return node2;
		if (node2 == NULL)
			return node1;
		Node*  cur = NULL;
		if (node1->_data < node2->_data){
			cur = node1;
			cur->_next = _Merge(node1->_next, node2);
		}
		else{
			cur = node2;
			cur->_next = _Merge(node1, node2->_next);
		}
		return cur;
	}
	
	
	
	
	
	
	
	
	
	
	