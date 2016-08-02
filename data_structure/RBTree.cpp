#include<iostream>
using namespace std;
enum Color
{
	RED,
	BLACK,
};
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	K _key;
	V _value;
	Color _col;

	RBTreeNode<K, V>(const K& key, const V& value)
		: _left(NULL)
		, _right(NULL)
		, _parent(NULL)
		, _key(key)
		, _value(value)
		, _col(RED)
	{}
};
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		:_root(NULL)
	{}
	//������������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}
	//���������������ж��Ƿ���������
	// 1��������Ǻ�ɫ��
	// 2��û�������ĺ�ɫ���
	// 3������һ��·���ĺ�ɫ����������
	bool IsBalance()
	{
		//��֤������Ǻ�ɫ��
		if (_root && _root->_col == RED)
			return false;

		//�������·���ĺ�ɫ���������ж�����·��������ĺ�k�Ƿ����
		int k = 0;
		int count = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				k++;
			cur = cur->_left;
		}

		return _IsBalance(_root, k, count);
	}
	bool _IsBalance(Node* root, const int k, int count)
	{
		if (root == NULL)
			return true;
		//��֤�����������ĺ�ɫ���
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "�������ĺ���" << root->_key << endl;
			return false;
		}
		//��������һ��·���ĺ�ɫ�������
		if (root->_col == BLACK)
			count++;
		//�����Ҷ�ӽڵ㣬�ж�����ĺ�ɫ��������Ƿ����
		if (root->_left == NULL && root->_right == NULL)
		{
			if (count == k)
				return true;
			else
			{
				cout << "��ɫ������������" << root->_key << endl;
				return false;
			}
		}

		return _IsBalance(root->_left, k, count) && _IsBalance(root->_right, k, count);
	}
	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;
		if (ppNode == NULL)
		{
			_root = subR;
			subR->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else if (ppNode->_right == parent)
				ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}
	//����
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->_parent = NULL;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else if (ppNode->_right == parent)
				ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}
	bool Insert(const K& key, const V& value)
	{
		//û�н��ʱnewһ����㸳��_root
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		//�ҳ�Ҫ�����λ��
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		//����keyֵ�жϲ�����߻����ұ�
		cur = new Node(key, value);
		if (parent->_key < key)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else if (parent->_key>key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//�������������ɫ
		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//����parent��grandfather�����ӵ����
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//uncle��������ɫ�Ǻ�ɫ������һ�����
				if (uncle && uncle->_col == RED)
				{
					//�ı�parent��uncle��grandfather����ɫ
					parent->_col = BLACK;
					uncle->_col = BLACK;

					grandfather->_col = RED;

					//�������ϵ���
					cur = grandfather;
					parent = cur->_parent;
				}
				//uncleΪ�ջ���uncle����ɫ�Ǻ�ɫ
				else
				{
					//�������������������Ժ�ת���ɵڶ������
					if (cur == parent->_right)
					{
						//����parentΪ���������
						RotateL(parent);
						//ע�⣺�������Ժ�parent��cur��λ�÷����ı䣬����ת���ɵڶ������
						//����ʱ���ǻ���û�иı�ʱ���д������Ա��뽻�����ǵ�λ��
						swap(parent, cur);
					}
					//�ڶ���������ı���ɫ��Ȼ������ҵ���
					parent->_col = BLACK;
					grandfather->_col = RED;
					RotateR(grandfather);
					break;
				}
			}
			//����parent��grandfather�Һ��ӵ����
			else if (grandfather->_right == parent)
			{
				Node* uncle = grandfather->_left;
				//uncle���ڲ�����ɫ�Ǻ�ɫ
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//uncle�����ڻ�����ɫ�Ǻ�ɫ
				else
				{
					//������������
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					//�ڶ������
					parent->_col = BLACK;
					grandfather->_col = RED;
					RotateL(grandfather);
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}
private:
	Node* _root;
};
void Test()
{
	RBTree<int, int> tree;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < 9; i++)
	{
		tree.Insert(arr[i], i);
	}
	tree.InOrder();
	cout << "IsBalance?" << tree.IsBalance() << endl;
}
int main()
{
	Test();
	return 0;
}