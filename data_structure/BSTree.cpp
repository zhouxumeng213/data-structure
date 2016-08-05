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
	//中序遍历，遍历结果是有序的
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
	//非递归方式实现向搜索二叉树中插入数据
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
			//要插入的结点比根结点大
			if (cur->key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			//要插入的结点比根结点小
			else if (cur->key > key)
			{
				parent = cur;
				cur = cur->left;
			}
			else
				return false;
		}
		//根据parent的key决定插入它的左边还是右边
		if (parent->key < key)
			parent->right = new node(key, value);
		else if (parent->key>key)
			parent->left = new node(key, value);
		return true;
	}
	//非递归方式实现查找一个结点
	node* Find(const K& key)
	{
		node* cur = _root;
		if (_root == NULL)
			return NULL;
		while (cur)
		{
			//右子树中
			if (cur->key < key)
				cur = cur->right;
			//左子树中
			else if (cur->key>key)
				cur = cur->left;
			//找到
			else
				return cur;
		}
		return NULL;
	}
	//非递归方式实现删除一个结点
	bool Remove(const K& key)
	{
		node* cur = _root;
		node* parent = NULL;

		if (_root == NULL)
			return false;
		//先找到要删除的结点
		while (cur)
		{
			//右子树
			if (cur->key < key)
			{
				parent = cur;
				cur = cur->right;
			}
			//左子树
			else if (cur->key>key)
			{
				parent = cur;
				cur = cur->left;
			}
			//找到
			else
			{
				break;
			}
		}
		if (cur)
		{
			//1、要删除的结点的左孩子为空
			if (cur->left == NULL)
			{
				//要删除的结点是根结点，且根结点没有左子树，所以找不到parent
				if (parent == NULL)
				{
					_root = _root->right;
				}
				else
				{
					//如果要删除的结点是它父结点的右孩子，则把它父结点的右孩子指向它的右孩子
					if (parent->right == cur)
						parent->right = cur->right;
					//如果要删除的结点是它父结点的左孩子，则把它父结点的左孩子指向它的右孩子
					else if (parent->left == cur)
						parent->left = cur->right;
				}
				delete cur;
			}
			//2、要删除的结点的右孩子为空
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
			//3、要删除的结点的左右孩子都不为空
			else
			{
				//找出右子树的最左结点（右子树的最小结点），将它的值赋给要删除的结点，然后删除右子树的最左结点
				parent = _root;
				node* tmp = _root->right;
				//找右子树的最左结点
				while (tmp->left)
				{
					parent = tmp;
					tmp = tmp->left;
				}
				//将最左结点的值赋给要删除的结点
				cur->key = tmp->key;
				cur->value = tmp->value;

				//判断最左结点是父结点的左孩子还是右孩子
				if (parent->right == tmp)
					parent->right = tmp->right;
				else if (parent->left == tmp)
					parent->left = tmp->right;

				delete tmp;
			}
			return true;
		}
		//分为三种情况进行处理
	}
	bool InsertR(const K& key, const V& value)
	{
		return _InsertR(_root, key, value);
	}
	//递归方式实现向二叉搜索树中插入结点（注意传root时必须传引用，才能把新结点和二叉搜索树链接起来）
	bool _InsertR(node*& root, const K& key, const V& value)
	{
		node* cur = root;
		//递归返回条件
		if (root == NULL)
		{
			root = new node(key, value);
			return true;
		}
		//右子树
		if (cur->key < key)
			return _InsertR(root->right, key, value);
		//左子树
		else if (cur->key > key)
			return _InsertR(root->left, key, value);
		//该结点已经在二叉搜索树中
		else
			return false;
	}
	//递归方式实现查找一个结点
	node* FindR(const K& key)
	{
		return _FindR(_root, key);
	}
	node* _FindR(node* root, const K& key)
	{
		node* cur = root;
		if (root == NULL)
			return NULL;
		//递归右子树
		if (cur->key < key)
			return _FindR(root->right, key);
		//递归左子树
		else if (root->key>key)
			return _FindR(root->left, key);
		else
			return cur;
	}
	//递归方式实现删除一个结点（注意传root的引用，才能使结点链接起来）
	bool RemoveR(const K& key)
	{
		return _RemoveR(_root, key);
	}
	bool _RemoveR(node*& root, const K& key)
	{
		node* cur = root;
		if (root == NULL)
			return false;
		//递归右子树
		if (cur->key < key)
			return _RemoveR(root->right, key);
		//递归左子树
		else if (cur->key>key)
			return _RemoveR(root->left, key);
		//找到要删除的结点
		else
		{
			//1、要删除结点的左孩子为空，因为是传引用，，它是上一层调用结点的右孩子，所以直接将该结点指向它的右孩子
			if (root->left == NULL)
				root = root->right;
			//2、要删除结点的右孩子为空
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