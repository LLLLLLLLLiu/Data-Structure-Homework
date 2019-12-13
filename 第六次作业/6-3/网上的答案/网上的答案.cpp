#include <iostream>
using namespace std;

template <class T>            /********************************节点类*********************************/
class BinaryTreeNode
{
	friend void Visit(BinaryTreeNode<T>*);        //访问某一节点
	friend void LevelOrder(BinaryTreeNode<T>*);    //层遍历
public:
	BinaryTreeNode()                                            //构造函数
	{
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const T& e)                                    //构造函数
	{
		data = e;
		LeftChild = RightChild = 0;
	}
	BinaryTreeNode(const T& e, BinaryTreeNode* l, BinaryTreeNode* r)//构造函数
	{
		data = e;
		LeftChild = l;
		RightChild = r;
	}
private:
	T data;                            //节点的数值
	BinaryTreeNode <T>* LeftChild,    //左子树
		* RightChild;    //右子树
};

template <class T>
class BinaryTree            /********************************二叉树类*******************************/
{
public:
	BinaryTree()                                        //构造函数
	{
		root = 0;
	}
	//    ~BinaryTree() {}                                    //析构函数
	bool IsEmpty()const                                    //判断是否为空
	{
		return ((root) ? false : true);
	}
	bool Root(T& x)const;                                //取根节点的data域，放入x
	void LevelOrder(void (*Visit)(BinaryTreeNode<T>* u));//逐层遍历
//    void CountLeaf(BinaryTree Tree,int &count);//数叶子数目
	void Exchange(BinaryTree& Tree);//交换左右子树
	int TreeWidth(BinaryTree* Tree);//求宽度

	BinaryTreeNode<T>* root;//根节点指针

};

template <class T>            /*********************************队列类*********************************/
class LinkedQueue
{
public:
	LinkedQueue() { front = tear = 0; }            //构造函数
	LinkedQueue<T>& Add(const T& x);        //添加
	LinkedQueue<T>& Delete(T& x);            //删除
	bool IsEmpty() { return !front; }//判断是否为空

	BinaryTreeNode<T>* front;    //队列的头指针
	BinaryTreeNode<T>* tear;    //队列的尾指针
};

template <class T>
void Create(BinaryTreeNode<T>*& Root)        //构造一棵二叉树
{
	T a;
	cin >> a;
	if (a != '#')
	{
		Root = new BinaryTreeNode<T>;
		Root->Node = a;
		Create(Root->LeftChild);
		Create(Root->RightChild);
	}
	else
		Root = NULL;
}

template <class T>
bool BinaryTree<T>::Root(T& x)const        //子函数——取根节点的data域，放入x
{
	if (root)
	{
		x = root->data;
		return true;
	}
	else
		return false;
}

template <class T>
void BinaryTree<T>::LevelOrder(void (*Visit)(BinaryTreeNode<T>* u))//子函数——层遍历
{
	LinkedQueue<BinaryTreeNode<T>*> Q;
	BinaryTreeNode<T>* t;
	t = root;
	while (t)
	{
		Visit(t);
		if (t->LeftChild) Q.Add(t->LeftChild);
		if (t->RightChild) Q.Add(t->RightChild);
		try { Q.Delete(t); }
		catch (OutOfBounds) { return; }
	}
}

//template <class T>                                                //子函数——数叶节点数目
//void BinaryTree<T>::CountLeaf(BinaryTree Tree,int &count)
void CountLeaf(BinaryTree Tree, int& count)
{
	if (Tree)
	{
		CountLeaf(Tree->LeftChild, &count);
		if (Tree->LeftChild == NULL && Tree->RightChild == NULL)
			count++;
		CountLeaf(Tree->RightChild, &count);
	}
}

template <class T>
void BinaryTree<T>::Exchange(BinaryTree& Tree)                    //子函数——交换左右子树
{
	if (Tree)
	{
		Exchange(Tree->LeftChild);
		Exchange(Tree->RightChild);
		BT->lchild < ->BT->rchild;
	}
}

template <class T>
int BinaryTree<T>::TreeWidth(BinaryTree* Tree)                    //子函数——求二叉树宽度
{
	if (Tree->LeftChild == NULL && Tree->RightChild == NULL)
		return 1;
	else
	{
		int k = 0, r = 0;
		if (Tree->LeftChild != NULL)
			k = TreeWidth(Tree->LeftChild);
		if (Tree->RightChild != NULL)
			r = TreeWidth(Tree->RightChild);
		return k + r;
	}
}



int main()                /***************************************测试用主函数***************************/
{
	BinaryTreeNode<char> T;
	LinkedQueue<BinaryTreeNode<char>*> q;
	Create(T);
	int count = 0;

	cout << "测试一：统计二叉树叶节点的数目" << endl;
	CountLeaf(T, count);
	cout << count << endl;

	cout << "测试二&三：交换二叉树的左右子树和逐层遍历" << endl;
	T.Exchange();
	T.LevelOrder(q);

	cout << "测试四：二叉树的宽度" << endl;
	cout << T.TreeWidth() << endl;
	return 0;
}
