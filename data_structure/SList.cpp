#include<iostream>
using namespace std;

typedef int DataType;
struct LinkNode
{
	DataType _date;
	LinkNode* _next;
	LinkNode(const DataType& x)
	{
		_date = x;
		_next = NULL;
	}
};
class SList
{
public:
	//构造函数
	SList()
		:_head(NULL)
		, _tail(NULL)
	{}
	//拷贝构造函数
	SList(const SList& s)
		:_head(NULL)
		, _tail(NULL)
	{
		if (s._head == NULL)
		{
			return;
		}
		else
		{
			LinkNode* begin = s._head;
			do
			{
				this->PushBack(begin->_date);
				begin = begin->_next;
			} while (begin != s._head);
		}
	}
	//交换函数
	void Swap(SList& s)
	{
		swap(_head, s._head);
		swap(_tail, s._tail);
	}
	//析构函数
	~SList()
	{
		Destory();
	}
	//销毁链表
	void Destory()
	{
		if (_head == NULL)
		{
			return;
		}
		else
		{
			LinkNode* begin = _head;
			while (begin != _tail)
			{
				LinkNode*del = _head;
				begin = begin->_next;
				_head = begin;
				delete del;
			}
			delete _tail;
			_head = NULL;
			_tail = NULL;
		}
	}
	//赋值操作符的重载
	SList& operator=(const SList& s)
	{
		if (this != &s)
		{
			SList tmp(s);
			Swap(tmp);
		}
		return *this;
	}
public:
	void Print()
	{
		if (_head == NULL)
		{
			cout << "此链表无值打印!" << endl;
			return;
		}
		LinkNode* begin = _head;
		do
		{
			cout << begin->_date << "->";
			begin = begin->_next;
		} while (begin != _head);
		cout << endl;
	}
	void PushBack(const DataType& x)//尾插
	{
		//1.没有节点
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.有两个以上节点
		else
		{
			_tail->_next = new LinkNode(x);
			_tail = _tail->_next;
			_tail->_next = _head;
		}
	}
	void PopBack()//尾删
	{
		//1.没有节点
		if (_head == NULL)
		{
			cout << "链表为空！" << endl;
		}
		//2.只有一个节点
		else if (_head == _tail)
		{
			delete[] _head;
			_head = NULL;
			_tail = NULL;
		}
		//3.有两个以上节点
		else
		{
			LinkNode* begin = _head;
			while (begin->_next != _tail)
			{
				begin = begin->_next;
			}
			delete[] _tail;
			begin->_next = _head;
			_tail = begin;
		}
	}
	void PushFront(const DataType& x)//头插
	{
		//1.链表为空
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.有两个以上节点
		else
		{
			LinkNode* tmp = new LinkNode(x);
			tmp->_next = _head;
			_head = tmp;
			_tail->_next = _head;
		}
	}
	void PopFront()//头删
	{
		//1.链表为空
		if (_head == NULL)
		{
			cout << "此链表为空链表！" << endl;
		}
		//2.只有一个节点
		else if (_head == _tail)
		{
			delete[] _head;
			_head = NULL;
			_tail = NULL;
		}
		//3.有两个以上节点
		else
		{
			LinkNode* tmp = _head;
			_head = _head->_next;
			delete[] tmp;
			_tail->_next = _head;
		}
	}
	void Insert(LinkNode* n, const DataType& x)//在所给节点的后面插入
	{
		//1.链表为空
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.链表不为空
		else
		{
			LinkNode* tmp = new LinkNode(x);
			tmp->_next = n->_next;
			n->_next = tmp;
		}
	}
	LinkNode* Find(const DataType& x)//查找某个节点
	{
		//1.链表为空
		if (_head == NULL)
		{
			cout << "链表为空!" << endl;
			return NULL;
		}
		//2.链表不为空
		else
		{
			LinkNode* begin = _head;
			do
			{
				if (begin->_date == x)
				{
					return begin;
				}
				begin = begin->_next;
			} while (begin != _head);
		}
		return NULL;
	}
	bool Remove(LinkNode* n)//删除节点
	{	//1.空链表
		if (_head == NULL)
		{
			cout << "链表为空!" << endl;
			return 0;
		}
		//2.只有一个节点
		else if (_head == _tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
			return 1;
		}
		//3.有两个以上节点
		else
		{
			LinkNode* begin = _head;
			LinkNode* prev = begin;
			do
			{
				//删除的节点是头节点
				if (_head == n)
				{
					begin = begin->_next;
					delete _head;
					_head = begin;
					_tail->_next = _head;
					return 1;
				}
				//删除的是中间节点或者尾节点
				else
				{
					prev = begin;
					begin = begin->_next;
					if (begin == n)
					{
						prev->_next = begin->_next;
						delete begin;
						return 1;
					}
				}

			} while (begin != _head);
		}
		return 0;
	}
private:
	LinkNode* _head;//指向链表头的指针
	LinkNode* _tail;//指向链表尾的指针
};
void Test1()//测试尾插、尾删
{
	SList s1;
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.Print();
	s1.PopBack();
	s1.Print();
	s1.PopBack();
	s1.Print();
	s1.PopBack();
	s1.Print();
	s1.PopBack();
}
void Test2()//测试头插、头删
{
	SList s2;
	s2.PushFront(1);
	s2.PushFront(2);
	s2.PushFront(3);
	s2.PushFront(4);
	s2.Print();
	s2.PopFront();
	s2.Print();
	s2.PopFront();
	s2.Print();
	s2.PopFront();
	s2.Print();
	s2.PopFront();
	s2.Print();
	s2.PopFront();
}
void Test3()//测试查找函数
{
	SList s3;
	s3.PushBack(1);
	s3.PushBack(2);
	s3.PushBack(3);
	s3.PushBack(4);
	s3.Print();
	LinkNode* ret1 = s3.Find(1);
	cout << ret1->_date << endl;
	LinkNode* ret2 = s3.Find(4);
	cout << ret2->_date << endl;
	LinkNode* ret3 = s3.Find(5);
	cout << ret3 << endl;

}
void Test4()//测试删除函数
{
	SList s4;
	s4.PushBack(1);
	s4.PushBack(2);
	s4.PushBack(3);
	s4.PushBack(4);
	s4.Print();
	LinkNode* ret1 = s4.Find(1);
	s4.Remove(ret1);
	s4.Print();
	LinkNode* ret2 = s4.Find(2);
	s4.Remove(ret2);
	s4.Print();
	LinkNode* ret3 = s4.Find(3);
	s4.Remove(ret3);
	s4.Print();
	LinkNode* ret4 = s4.Find(4);
	s4.Remove(ret4);
	s4.Print();
}
void Test5()//测试插入函数
{
	SList s5;
	s5.PushBack(1);
	s5.PushBack(2);
	s5.PushBack(3);
	s5.PushBack(4);
	s5.Print();
	LinkNode* ret1 = s5.Find(1);
	s5.Insert(ret1, 8);
	s5.Print();
	LinkNode* ret2 = s5.Find(2);
	s5.Insert(ret2, 8);
	s5.Print();
	LinkNode* ret3 = s5.Find(4);
	s5.Insert(ret3, 8);
	s5.Print();
}
void Test6()//测试拷贝构造函数和赋值操作符的重载
{
	SList s6;
	s6.PushBack(1);
	s6.PushBack(2);
	s6.PushBack(3);
	s6.PushBack(4);
	s6.Print();
	SList s7(s6);
	s7.Print();
	SList s8;
	s8 = s6;
	s8.Print();
}
int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	return 0;
}
