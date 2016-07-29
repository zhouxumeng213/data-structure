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
	//���캯��
	SList()
		:_head(NULL)
		, _tail(NULL)
	{}
	//�������캯��
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
	//��������
	void Swap(SList& s)
	{
		swap(_head, s._head);
		swap(_tail, s._tail);
	}
	//��������
	~SList()
	{
		Destory();
	}
	//��������
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
	//��ֵ������������
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
			cout << "��������ֵ��ӡ!" << endl;
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
	void PushBack(const DataType& x)//β��
	{
		//1.û�нڵ�
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.���������Ͻڵ�
		else
		{
			_tail->_next = new LinkNode(x);
			_tail = _tail->_next;
			_tail->_next = _head;
		}
	}
	void PopBack()//βɾ
	{
		//1.û�нڵ�
		if (_head == NULL)
		{
			cout << "����Ϊ�գ�" << endl;
		}
		//2.ֻ��һ���ڵ�
		else if (_head == _tail)
		{
			delete[] _head;
			_head = NULL;
			_tail = NULL;
		}
		//3.���������Ͻڵ�
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
	void PushFront(const DataType& x)//ͷ��
	{
		//1.����Ϊ��
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.���������Ͻڵ�
		else
		{
			LinkNode* tmp = new LinkNode(x);
			tmp->_next = _head;
			_head = tmp;
			_tail->_next = _head;
		}
	}
	void PopFront()//ͷɾ
	{
		//1.����Ϊ��
		if (_head == NULL)
		{
			cout << "������Ϊ������" << endl;
		}
		//2.ֻ��һ���ڵ�
		else if (_head == _tail)
		{
			delete[] _head;
			_head = NULL;
			_tail = NULL;
		}
		//3.���������Ͻڵ�
		else
		{
			LinkNode* tmp = _head;
			_head = _head->_next;
			delete[] tmp;
			_tail->_next = _head;
		}
	}
	void Insert(LinkNode* n, const DataType& x)//�������ڵ�ĺ������
	{
		//1.����Ϊ��
		if (_head == NULL)
		{
			_head = new LinkNode(x);
			_tail = _head;
			_tail->_next = _head;
		}
		//2.����Ϊ��
		else
		{
			LinkNode* tmp = new LinkNode(x);
			tmp->_next = n->_next;
			n->_next = tmp;
		}
	}
	LinkNode* Find(const DataType& x)//����ĳ���ڵ�
	{
		//1.����Ϊ��
		if (_head == NULL)
		{
			cout << "����Ϊ��!" << endl;
			return NULL;
		}
		//2.����Ϊ��
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
	bool Remove(LinkNode* n)//ɾ���ڵ�
	{	//1.������
		if (_head == NULL)
		{
			cout << "����Ϊ��!" << endl;
			return 0;
		}
		//2.ֻ��һ���ڵ�
		else if (_head == _tail)
		{
			delete _head;
			_head = NULL;
			_tail = NULL;
			return 1;
		}
		//3.���������Ͻڵ�
		else
		{
			LinkNode* begin = _head;
			LinkNode* prev = begin;
			do
			{
				//ɾ���Ľڵ���ͷ�ڵ�
				if (_head == n)
				{
					begin = begin->_next;
					delete _head;
					_head = begin;
					_tail->_next = _head;
					return 1;
				}
				//ɾ�������м�ڵ����β�ڵ�
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
	LinkNode* _head;//ָ������ͷ��ָ��
	LinkNode* _tail;//ָ������β��ָ��
};
void Test1()//����β�塢βɾ
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
void Test2()//����ͷ�塢ͷɾ
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
void Test3()//���Բ��Һ���
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
void Test4()//����ɾ������
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
void Test5()//���Բ��뺯��
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
void Test6()//���Կ������캯���͸�ֵ������������
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
