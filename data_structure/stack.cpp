#include<iostream>
using namespace std;
#include<assert.h>
template<class T>
class Stack
{
public:
	Stack()
		:_capacity(3)
		, _size(0)
		, _array(new T[_capacity])
	{}
	~Stack()
	{
		if (_array)
			delete[] _array;
	}
	void CheckCapacity()
	{
		if (_size == _capacity)
		{
			_capacity = 2 * _capacity + 3;
			T* tmp = new T[_capacity];
			//�����Զ�������ʱ��ע����ǳ��������
			//memcpy(tmp, _array, sizeof(T)*(_topIndex+1));
			for (size_t i = 0; i < _size; i++)
				tmp[i] = _array[i];
			delete[] _array;
			_array = tmp;
		}
	}
	bool IsEmpty()
	{
		return _size == 0;
	}
	void Push(const T& x)
	{
		CheckCapacity();
		_array[_size++] = x;
	}
	void Pop()
	{
		assert(_size > 0);
		--_size;
	}
	const T& Top()
	{
		return _array[_size - 1];
	}
	size_t Size()
	{
		return _size;
	}
	void Print()
	{
		for (size_t i = 0; i < _size; i++)
			cout << _array[i] << " ";
		cout << endl;
	}
private:
	size_t _capacity;	//����
	size_t _size;		//���ݵĸ���
	T*  _array;		//ָ�����ݿ��ָ��
};
void Test()
{
	Stack<int> s1;
	s1.Push(1);
	s1.Push(2);
	s1.Push(3);
	s1.Push(4);
	s1.Print();
	s1.Pop();
	s1.Pop();
	s1.Print();
}
int main()
{
	Test();
	return 0;
}