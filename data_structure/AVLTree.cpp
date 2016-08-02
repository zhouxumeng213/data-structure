#pragma once
#include<iostream>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* left;		//����
	AVLTreeNode<K, V>* right;	//�Һ���
	AVLTreeNode<K, V>* parent;	//���׽��

	K key;
	V value;
	int fb;	//ƽ������

	AVLTreeNode<K, V>(const K& key, const V& value)
		: left(NULL)
		, right(NULL)
		, parent(NULL)
		, key(key)
		, value(value)
		, fb(0)
	{}
};
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_root(NULL)
	{}
	//�������ƽ��������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root)
	{
		if (root == NULL)
			return;
		_InOrder(root->left);
		cout << root->key << " ";
		_InOrder(root->right);
	}
	//�ж�һ�����ǲ���ƽ�������
	int Depth(Node* root)
	{
		if (root == NULL)
			return 0;
		int left = Depth(root->left);
		int right = Depth(root->right);
		return left > right ? (left + 1) : (right + 1);
	}
	bool IsBalance()
	{
		return _IsBalance(_root);
	}
	bool _IsBalance(Node* root)
	{
		if (root == NULL)
			return true;
		int left = Depth(root->left);
		int right = Depth(root->right);
		//ƽ����������߶Ȳ����1
		if ((right - left) != root->fb)
		{
			cout << "ƽ�������쳣" << root->key << endl;
			return false;
		}
		if (left - right > 1 || left - right < -1)
			return false;
		else
			return abs(right - left < 2) && _IsBalance(root->left) && _IsBalance(root->right);
	}
	//����
	void RotateL(Node* parent)
	{
		Node* subR = parent->right;
		Node* subLR = subR->left;

		parent->right = subLR;
		if (subLR)
		{
			subLR->parent = parent;
		}
		subR->left = parent;
		Node* ppNode = parent->parent;
		parent->parent = subR;
		if (ppNode == NULL)
		{
			_root = subR;
			subR->parent = NULL;
		}
		else
		{
			if (ppNode->left == parent)
				ppNode->left = subR;
			else if (ppNode->right == parent)
				ppNode->right = subR;
			subR->parent = ppNode;
		}
		parent->fb = subR->fb = 0;
	}
	//�ҵ���
	void RotateR(Node* parent)
	{
		Node* subL = parent->left;
		Node* subLR = subL->right;

		parent->left = subLR;
		if (subLR)
		{
			subLR->parent = parent;
		}
		subL->right = parent;
		Node* ppNode = parent->parent;
		parent->parent = subL;
		if (ppNode == NULL)
		{
			_root = subL;
			subL->parent = NULL;
		}
		else
		{
			if (ppNode->left == parent)
				ppNode->left = subL;
			else if (ppNode->right == parent)
				ppNode->right = subL;
			subL->parent = ppNode;
		}
		subL->fb = parent->fb = 0;
	}
	//����˫��
	void RotateLR(Node* parent)
	{
		//�����ӵ���������subLR�����Һ��ӽ��ʱ��parent��subL��ƽ������Ӱ�첻ͬ
		Node* subL = parent->left;
		Node* subLR = subL->right;

		int fb = subLR->fb;

		RotateL(parent->left);
		RotateR(parent);

		//��subLR����߲�����
		if (fb == -1)
		{
			parent->fb = 1;
			subL->fb = 0;
		}
		//��subLR���ұ߲�����
		else if (fb == 1)
		{
			parent->fb = 0;
			subL->fb = -1;
		}
		else if (fb == 0)
		{
			parent->fb = subL->fb = 0;
		}
	}
	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->right;
		Node* subRL = subR->left;

		int fb = subRL->fb;

		RotateR(parent->right);
		RotateL(parent);

		if (fb == -1)
		{
			parent->fb = 0;
			subR->fb = 1;
		}
		else if (fb == 1)
		{
			parent->fb = -1;
			subR->fb = 0;
		}
		else if (fb == 0)
		{
			parent->fb = subR->fb = 0;
		}
	}
	bool Insert(const K& key, const V& value)
	{
		//��Ϊ��ʱ��newһ����㸳��_root
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		//�ҵ�Ҫ�����λ��
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			else if (cur->key>key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
				return false;
		}
		//����keyֵ�жϲ�����߻����ұ�
		cur = new Node(key, value);
		if (parent->key < key)
		{
			parent->right = cur;
			cur->parent = parent;
		}
		else if (parent->key>key)
		{
			parent->left = cur;
			cur->parent = parent;
		}

		//����ƽ������
		while (parent)
		{
			//���������߲��룬ƽ������-1
			if (parent->left == cur)
				parent->fb--;
			//��������ұ߲��룬ƽ������+1
			else if (parent->right == cur)
				parent->fb++;
			//������º��ƽ������Ϊ0��˵���߶�û�䣬���������ϸ���
			if (parent->fb == 0)
				break;
			//������º��ƽ��������-1����1��˵������0�����ģ���Ҫ���ϸ���
			else if (parent->fb == -1 || parent->fb == 1)
			{
				cur = parent;
				parent = cur->parent;
			}
			//������º��ƽ��������2����-2��˵���Ѿ�������ƽ���������Ҫ������ת
			else//2����-2
			{
				//����ƽ������Ϊ2�����
				if (parent->fb > 1)
				{
					//�������
					if (cur->fb == 1)
						RotateL(parent);
					//����˫�����
					else
						RotateRL(parent);
				}
				//����ƽ������Ϊ-2�����
				else if (parent->fb<-1)
				{
					//�ҵ������
					if (cur->fb == -1)
						RotateR(parent);
					//����˫�����
					else
						RotateLR(parent);
				}
				return true;
			}
		}
		return true;
	}
private:
	Node* _root;
};
void Test()
{
	AVLTree<int, int> tree;
	int arr[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int arr2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (int i = 0; i < 10; i++)
	{
		tree.Insert(arr2[i], i);
	}
	tree.InOrder();
	cout << "IsBalance?" << tree.IsBalance() << endl;
}
int main()
{
	Test();
	return 0;
}