#include<iostream>
using namespace std;
#include<assert.h>
#include<vector>

//С�ڣ�������С��
template<class T>
struct Less
{
	bool operator() (const T& l, const T& r)
	{
		return l < r;
	}
};
//���ڣ����������
template<class T>
struct Greater
{
	bool operator() (const T& l, const T& r)
	{
		return l > r;
	}
};

//���÷º���ʵ�ִ�С��
template<class T, class compare>
class Heap
{
public:
	Heap()
	{}
	Heap(const T* arr, size_t size)
	{
		assert(arr);
		//������������������ַ���vector��
		for (size_t i = 0; i < size; i++)
		{
			_arr.push_back(arr[i]);
		}
		//����(�����һ����Ҷ�ӽڵ㿪ʼ���µ���)
		for (int i = (size - 2) / 2; i >= 0; i--)
		{
			_AdjustDown(i, _arr.size());
		}
	}
	//��ȡ�Ѷ�Ԫ��
	T& Top()
	{
		return _arr[0];
	}
	//��ȡ�ѽ�����
	size_t Size()
	{
		return _arr.size();
	}
	//�ж϶��Ƿ�Ϊ��
	bool Empty()
	{
		return _arr.empty();
	}
	//��������һ�����
	void Push(const T& x)
	{
		_arr.push_back(x);
		_AdjustUp(_arr.size() - 1, _arr.size());
	}
	//�Ӷ���ɾ��һ�����
	void Pop()
	{
		//�����һ����㸲�ǶѶ�
		_arr[0] = _arr[_arr.size() - 1];
		//ɾ�����һ�����
		_arr.pop_back();
		//�Ӹ���㿪ʼ���µ���
		_AdjustDown(0, _arr.size());
	}
	//���򣬽������
	void HeapSort()
	{
		int end = _arr.size() - 1;
		while (end > 0)
		{
			//�Ѷ�Ϊ���Ԫ�أ����Ѷ������һ��Ԫ�ؽ���
			swap(_arr[0], _arr[end]);
			//������
			_AdjustDown(0, end);
			--end;
		}
	}
	void Print()
	{
		for (int i = 0; i < 10; i++)
		{
			cout << _arr[i] << " ";
		}
		cout << endl;
	}
protected:
	//���µ����㷨
	void _AdjustDown(int parent, int size)
	{
		compare com;
		//child���������Һ���
		int child = parent * 2 + 1;
		while (child < size)
		{
			//ѡ�����Һ����нϴ��
			if (child + 1<size && com(_arr[child + 1], _arr[child]))
			{
				child = child + 1;
			}
			//�жϸ��������Һ����нϴ�ֵ�ô�С
			if (com(_arr[child], _arr[parent]))
			{
				//���child��parent�󣬽���������ֵ
				swap(_arr[child], _arr[parent]);
				//�����жϸ��º�����Һ����Ƿ������ѻ���С��
				parent = child;
				child = parent * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	//���ϵ����㷨
	void _AdjustUp(int child, int size)
	{
		compare com;
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			//ֻ��ȽϺ��Ӻ͸��ڵ�
			if (com(_arr[child], _arr[parent]))
			{
				swap(_arr[child], _arr[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}
private:
	vector<T> _arr;
};
void Test()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int, Greater<int>> hp(a, 10);
	hp.Push(20);
	hp.Pop();
}
void HeapSortTest()
{
	int a[] = { 10, 11, 13, 12, 16, 18, 15, 17, 14, 19 };
	Heap<int, Greater<int>> hp(a, 10);
	hp.HeapSort();
	hp.Print();
}

int main()
{
	Test();
	//HeapSortTest();
	return 0;
}