#include<iostream>
using namespace std;
template<class T>
class DoubleStack
{
public:
	DoubleStack(T* commenArray, size_t topIndex = 0)
		:_array(commenArray)
		, _capacity(3)
		, _topIndex(topIndex)
	{}
	void CheckCapacity()
	{
		if (_topIndex == _capacity)
		{
			_capacity = 2 * _capacity + 3;
			T* tmp = new T[_capacity];
			memcpy(tmp, _array, sizeof(T)*(_topIndex));
			delete _array;
			_array = tmp;
		}
	}
	bool IsEmpty()
	{
		return (_topIndex == 0) || (_topIndex == 1);
	}
	void Push(const T& x)
	{
		CheckCapacity();
		_array[_topIndex] = x;
		_topIndex += 2;
	}
	void Pop()
	{
		--_topIndex;
	}
	T& Top()
	{
		return _array[_topIndex];
	}
private:
	T* & _array;
	size_t _capacity;
	size_t _topIndex;
};
void Test()
{
	int* commonArray1 = 0;
	DoubleStack<int> s1(commonArray1, 0);
	DoubleStack<int> s2(commonArray1, 1);
	s1.Push(1);
	s2.Push(2);
	s1.Push(3);
	s2.Push(4);
	s1.Push(5);
	s2.Push(6);

}
int main()
{
	Test();
	return 0;
}