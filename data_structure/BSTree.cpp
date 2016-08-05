#pragma once
#include<iostream>
using namespace std;
#include<string>

template<class K, class V>
struct BSTreeNode
{
	K key;
	V value;
	BSTreeNode<K, V>* left;
	BSTreeNode<K, V>* right;

	BSTreeNode<K, V>(const K& key, const V& value)
		: key(key)
		, value(value)
		, left(NULL)
		, right(NULL)
	{}
};
template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> node;
public:
	BSTree()
		:_root(NULL)
	{}
	//�����������������������
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->left);
		cout << root->key << " ";
		_InOrder(root->right);
	}
	//�ǵݹ鷽ʽʵ���������������в�������
	bool Insert(const K& key, const V& value)
	{
		node* cur = _root;
		node* parent = NULL;
		if (_root == NULL)
		{
			_root = new node(key, value);
			return true;
		}
		while (cur)
		{
			//Ҫ����Ľ��ȸ�����
			if (cur->key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			//Ҫ����Ľ��ȸ����С
			else if (cur->key > key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
				return false;
		}
		//����parent��key��������������߻����ұ�
		if (parent->key < key)
			parent->right = new node(key, value);
		else if (parent->key>key)
			parent->left = new node(key, value);
		return true;
	}
	//�ǵݹ鷽ʽʵ�ֲ���һ�����
	node* Find(const K& key)
	{
		node* cur = _root;
		if (_root == NULL)
			return NULL;
		while (cur)
		{
			//��������
			if (cur->key < key)
				cur = cur->right;
			//��������
			else if (cur->key>key)
				cur = cur->left;
			//�ҵ�
			else
				return cur;
		}
		return NULL;
	}
	//�ǵݹ鷽ʽʵ��ɾ��һ�����
	bool Remove(const K& key)
	{
		node* cur = _root;
		node* parent = NULL;

		if (_root == NULL)
			return false;
		//���ҵ�Ҫɾ���Ľ��
		while (cur)
		{
			//������
			if (cur->key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			//������
			else if (cur->key>key)
			{
				parent = cur;
				cur = cur->left;
			}
			//�ҵ�
			else
			{
				break;
			}
		}
		if (cur)
		{
			//1��Ҫɾ���Ľ�������Ϊ��
			if (cur->left == NULL)
			{
				//Ҫɾ���Ľ���Ǹ���㣬�Ҹ����û���������������Ҳ���parent
				if (parent == NULL)
				{
					_root = _root->right;
				}
				else
				{
					//���Ҫɾ���Ľ�������������Һ��ӣ�������������Һ���ָ�������Һ���
					if (parent->right == cur)
						parent->right = cur->right;
					//���Ҫɾ���Ľ���������������ӣ����������������ָ�������Һ���
					else if (parent->left == cur)
						parent->left = cur->right;
				}
				delete cur;
			}
			//2��Ҫɾ���Ľ����Һ���Ϊ��
			else if (cur->right == NULL)
			{
				if (parent == NULL)
				{
					_root = _root->left;
				}
				else
				{
					if (parent->right == cur)
						parent->right = cur->left;
					else if (parent->left == cur)
						parent->left = cur->left;
				}
				delete cur;
			}
			//3��Ҫɾ���Ľ������Һ��Ӷ���Ϊ��
			else
			{
				//�ҳ��������������㣨����������С��㣩��������ֵ����Ҫɾ���Ľ�㣬Ȼ��ɾ����������������
				parent = _root;
				node* tmp = _root->right;
				//����������������
				while (tmp->left)
				{
					parent = tmp;
					tmp = tmp->left;
				}
				//���������ֵ����Ҫɾ���Ľ��
				cur->key = tmp->key;
				cur->value = tmp->value;

				//�ж��������Ǹ��������ӻ����Һ���
				if (parent->right == tmp)
					parent->right = tmp->right;
				else if (parent->left == tmp)
					parent->left = tmp->right;

				delete tmp;
			}
			return true;
		}
		//��Ϊ����������д���
	}
	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}
	//�ݹ鷽ʽʵ��������������в����㣨ע�⴫rootʱ���봫���ã����ܰ��½��Ͷ�������������������
	bool _InsertR(node*& root, const K& key, const V& value)
	{
		node* cur = root;
		//�ݹ鷵������
		if (root == NULL)
		{
			root = new node(key, value);
			return true;
		}
		//������
		if (cur->key < key)
			return _InsertR(root->right, key, value);
		//������
		else if (cur->key > key)
			return _InsertR(root->left, key, value);
		//�ý���Ѿ��ڶ�����������
		else
			return false;
	}
	//�ݹ鷽ʽʵ�ֲ���һ�����
	node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}
	node* _FindR(node* root, const K& key)
	{
		node* cur = root;
		if (root == NULL)
			return NULL;
		//�ݹ�������
		if (cur->key < key)
			return _FindR(root->right, key);
		//�ݹ�������
		else if (root->key>key)
			return _FindR(root->left, key);
		else
			return cur;
	}
	//�ݹ鷽ʽʵ��ɾ��һ����㣨ע�⴫root�����ã�����ʹ�������������
	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}
	bool _RemoveR(node*& root, const K& key)
	{
		node* cur = root;
		if (root == NULL)
			return false;
		//�ݹ�������
		if (cur->key < key)
			return _RemoveR(root->right, key);
		//�ݹ�������
		else if (cur->key>key)
			return _RemoveR(root->left, key);
		//�ҵ�Ҫɾ���Ľ��
		else
		{
			//1��Ҫɾ����������Ϊ�գ���Ϊ�Ǵ����ã���������һ����ý����Һ��ӣ�����ֱ�ӽ��ý��ָ�������Һ���
			if (root->left == NULL)
				root = root->right;
			//2��Ҫɾ�������Һ���Ϊ��
			else if (root->right == NULL)
				root = root->left;
			else
			{
				node* tmp = root->right;
				node* parent = root;
				while (tmp->left)
				{
					parent = tmp;
					tmp = tmp->left;
				}
				cur->key = tmp->key;
				cur->value = tmp->value;

				if (parent->right == tmp)
					parent->right = tmp->right;
				if (parent->left == tmp)
					parent->left = tmp->right;

				delete tmp;
			}
		}
	}
private:
	node* _root;
};
void Test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int, int> tree;
	for (int i = 0; i < 10; i++)
	{
		tree.InsertR(a[i], i);
	}
	tree.InOrder();

	tree.RemoveR(8);
	tree.RemoveR(9);
	tree.RemoveR(7);
	tree.RemoveR(5);
	tree.InOrder();

	tree.RemoveR(0);
	tree.RemoveR(1);
	tree.RemoveR(2);
	tree.RemoveR(3);
	tree.RemoveR(4);
	tree.RemoveR(5);
	tree.RemoveR(6);
	tree.RemoveR(7);
	tree.RemoveR(8);
	tree.RemoveR(9);
	tree.InOrder();
}
int main()
{
	Test();
	return 0;
}