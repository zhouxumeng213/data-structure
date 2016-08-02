#pragma once
#include<iostream>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* left;		//左孩子
	AVLTreeNode<K, V>* right;	//右孩子
	AVLTreeNode<K, V>* parent;	//父亲结点

	K key;
	V value;
	int fb;	//平衡因子

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
	//中序遍历平衡搜索树
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
	//判断一棵树是不是平衡二叉树
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
		//平衡二叉树：高度差不超过1
		if ((right - left) != root->fb)
		{
			cout << "平衡因子异常" << root->key << endl;
			return false;
		}
		if (left - right > 1 || left - right < -1)
			return false;
		else
			return abs(right - left < 2) && _IsBalance(root->left) && _IsBalance(root->right);
	}
	//左单旋
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
	//右单旋
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
	//左右双旋
	void RotateLR(Node* parent)
	{
		//处理复杂的情况，如果subLR有左右孩子结点时对parent和subL的平衡因子影响不同
		Node* subL = parent->left;
		Node* subLR = subL->right;

		int fb = subLR->fb;

		RotateL(parent->left);
		RotateR(parent);

		//在subLR的左边插入结点
		if (fb == -1)
		{
			parent->fb = 1;
			subL->fb = 0;
		}
		//在subLR的右边插入结点
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
	//右左双旋
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
		//树为空时，new一个结点赋给_root
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		//找到要插入的位置
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
		//根据key值判断插入左边还是右边
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

		//更新平衡因子
		while (parent)
		{
			//如果是在左边插入，平衡因子-1
			if (parent->left == cur)
				parent->fb--;
			//如果是在右边插入，平衡因子+1
			else if (parent->right == cur)
				parent->fb++;
			//如果更新后的平衡因子为0，说明高度没变，不用再向上更新
			if (parent->fb == 0)
				break;
			//如果更新后的平衡因子是-1或者1，说明是由0变来的，需要向上更新
			else if (parent->fb == -1 || parent->fb == 1)
			{
				cur = parent;
				parent = cur->parent;
			}
			//如果更新后的平衡因子是2或者-2，说明已经不满足平衡二叉树，要进行旋转
			else//2或者-2
			{
				//处理平衡因子为2的情况
				if (parent->fb > 1)
				{
					//左单旋情况
					if (cur->fb == 1)
						RotateL(parent);
					//右左双旋情况
					else
						RotateRL(parent);
				}
				//处理平衡因子为-2的情况
				else if (parent->fb<-1)
				{
					//右单旋情况
					if (cur->fb == -1)
						RotateR(parent);
					//左右双旋情况
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