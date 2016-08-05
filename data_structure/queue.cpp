#include<iostream>
using namespace std;
#include<assert.h>
template<class T>
struct Node
{
	Node* _next;	//指向下一个节点的指针
	T _data;		//数据

	Node<T>(const T& x)
		:_next(NULL)
		, _data(x)
	{}
};
template<class T>
class Queue
{
	typedef Node<T> Node;
public:
	Queue()
		:_head(NULL)
		, _tail(NULL)
		, _size(0)
	{}

	~Queue()
	{
		Clear();
	}
	void Push(const T& x)
	{
		//队列为空
		if (_head == NULL)
		{
			_head = new Node(x);
			_tail = _head;
		}
		//队列不为空
		else
		{
			_tail->_next = new Node(x);
			_tail = _tail->_next;
		}

		++_size;
	}
	void Pop()
	{
		assert(_head);
		//只有一个结点
		if (_head == _tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
		}
		//有多个结点
		else
		{
			Node* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}
		--_size;
	}
	//返回队列尾的数据
	const T& Back()
	{
		assert(_tail);
		_tail->_data;
	}
	//返回队列头的数据
	const T& Front()
	{
		assert(_head);
		return _head->_data;
	}
	bool Empty()
	{
		return _head == NULL;
	}
	void Print()
	{
		Node* begin = _head;
		while (begin)
		{
			cout << begin->_data << " ";
			begin = begin->_next;
		}
		cout << endl;
	}
	void Clear()
	{
		while (_head)
		{
			Node* tmp = _head;
			_head = _head->_next;
			delete tmp;
		}

		_head = NULL;
		_tail = NULL;
		_size = 0;
	}
	size_t Size()
	{
		return _size;
	}
private:
	Node*  _head;	//指向链表头的指针
	Node*  _tail;	//指向链表尾的指针
	int _size;		//数据的个数
};
void TestQueue()
{
	Queue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);

	q.Print();

	q.Pop();
	q.Pop();
	q.Pop();

	q.Print();
}
int main()
{
	TestQueue();
	return 0;
}