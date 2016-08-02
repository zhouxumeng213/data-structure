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
	//中序遍历红黑树
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
	//根据以下三条来判断是否满足红黑树
	// 1、根结点是黑色的
	// 2、没有连续的红色结点
	// 3、任意一条路径的黑色结点数量相等
	bool IsBalance()
	{
		//保证根结点是黑色的
		if (_root && _root->_col == RED)
			return false;

		//求出最左路径的黑色结点个数，判断其他路径求出来的和k是否相等
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
		//保证不会有连续的红色结点
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "有连续的红结点" << root->_key << endl;
			return false;
		}
		//计算任意一条路径的黑色结点数量
		if (root->_col == BLACK)
			count++;
		//如果到叶子节点，判断与给的黑色结点数量是否相等
		if (root->_left == NULL && root->_right == NULL)
		{
			if (count == k)
				return true;
			else
			{
				cout << "黑色结点数量不相等" << root->_key << endl;
				return false;
			}
		}

		return _IsBalance(root->_left, k, count) && _IsBalance(root->_right, k, count);
	}
	//左旋
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
	//右旋
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
		//没有结点时new一个结点赋给_root
		if (_root == NULL)
		{
			_root = new Node(key, value);
			_root->_col = BLACK;
			return true;
		}
		//找出要插入的位置
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
		//根据key值判断插入左边还是右边
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
		//调整红黑树的颜色
		while (cur != _root && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//处理parent是grandfather的左孩子的情况
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//uncle存在且颜色是红色，即第一种情况
				if (uncle && uncle->_col == RED)
				{
					//改变parent、uncle、grandfather的颜色
					parent->_col = BLACK;
					uncle->_col = BLACK;

					grandfather->_col = RED;

					//继续向上调整
					cur = grandfather;
					parent = cur->_parent;
				}
				//uncle为空或者uncle的颜色是黑色
				else
				{
					//处理第三种情况：左单旋以后转换成第二种情况
					if (cur == parent->_right)
					{
						//先以parent为轴进行左单旋
						RotateL(parent);
						//注意：：左单旋以后parent和cur的位置发生改变，但是转换成第二种情况
						//处理时，是基于没有改变时进行处理，所以必须交换它们的位置
						swap(parent, cur);
					}
					//第二种情况：改变颜色，然后进行右单旋
					parent->_col = BLACK;
					grandfather->_col = RED;
					RotateR(grandfather);
					break;
				}
			}
			//处理parent是grandfather右孩子的情况
			else if (grandfather->_right == parent)
			{
				Node* uncle = grandfather->_left;
				//uncle存在并且颜色是红色
				if (uncle && uncle->_col == RED)
				{
					uncle->_col = BLACK;
					parent->_col = BLACK;
					grandfather->_col = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				//uncle不存在或者颜色是黑色
				else
				{
					//处理第三种情况
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					//第二种情况
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