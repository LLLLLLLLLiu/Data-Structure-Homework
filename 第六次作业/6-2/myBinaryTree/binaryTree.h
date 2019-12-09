#pragma once
#include<iostream>
#include"arrayQueue.h"
using namespace std;

template<class T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T>* leftChild, * rightChild;
	binaryTreeNode() { leftChild = NULL; rightChild = NULL; }
	binaryTreeNode(const T& theElement) :element(theElement) {
		leftChild = NULL; rightChild = NULL;
	}
	binaryTreeNode(const T& theElement, binaryTreeNode* theLeftChild, binaryTreeNode* theRightChild) :element(theElement) {
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};
//只有三个数据成员，和各种初始化一个节点的方法。如果要删除或者改变
//一个节点，恐怕就只有去动用数据成员来操作了。

template<class E>
class binaryTree
{
public:
	binaryTree() { root = NULL; treeSize = 0;}
	~binaryTree() { erase(); }
	bool empty()const { return treeSize == 0;}
	int size()const { return treeSize; }
	E* rootElement()const {
		if (treeSize == 0) {
			return NULL;
		}
		else {
			return &root->element;
		}
	}
	void makeTree(const E& element, binaryTree<E>& left, binaryTree<E>& right) {
		//left,right,and this must be different trees.
		root = new binaryTreeNode<E>(element, left.root, right.root);//这句话真是非常非常关键
		treeSize = left.treeSize + right.treeSize + 1;
		//deny access from trees left and right
		left.root = NULL;
		right.root = NULL;
		left.treeSize = 0;
		right.treeSize = 0;
	}
	binaryTree<E>& removeLeftSubtree() {
		if (treeSize == 0) {
			cout << "错误，这棵树是空树，无法删除" << endl;
		}
		binaryTree<E> leftSubtree;
		leftSubtree.root = root->leftChild;
		count = 0;
		leftSubtree.treeSize = countNodes(leftSubtree.root);
		root->leftChild = NULL;
		treeSize = treeSize - leftSubtree.treeSize;
		return leftSubtree;
		//一个疑问，这个removeLeftSubtree平时似乎用不着啊。
		//因为这个是对于树来说的，一下子就砍掉了一半啊
	}
	binaryTree<E>& removeRightSubtree() {
		if (treeSize == 0) {
			cout << "错误，这棵树是空树，无法删除" << endl;
		}
		binaryTree<E> rightSubtree;
		rightSubtree.root = root->rightChild;
		count = 0;
		rightSubtree.treeSize = countNode(rightSubtree.root);
		root->rightChild = NULL;
		treeSize = treeSize - rightSubtree.treeSize;
		return rightSubtree;
	}
	//这个外部的和private里的区别是，这个可以给赋予一个visit函数
	void preOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; preOrder(root);
	}
	void inOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; inOrder(root);
	}
	void postOrder(void(*theVisit)(binaryTreeNode<E>*))
	{
		visit = theVisit; postOrder(root);
	}
	void levelOrder(void(*theVisit)(binaryTreeNode<E>*)) {
		arrayQueue<binaryTreeNode<E>*> q;
		binaryTreeNode<E>* t = root;
		while (t != NULL) {
			theVisit(t);
			if (t->leftChild != NULL)
				q.push(t->leftChild);
			if (t->rightChild != NULL)
				q.push(t->rightChild);

			t = q.front();
			if (q.empty()) {
				return;
			}
			q.pop();
		}
	}
	void preOrderOutput() { preOrder(output); cout << endl; }
	void inOrderOutput() { inOrder(output); cout << endl; }
	void postOrderOutput() { postOrder(output); cout << endl; }
	void levelOrderOutput() { levelOrder(output); cout << endl; }
	void erase() {
		postOrder(dispose);
		root = NULL;
		treeSize = 0;
	}
	int height()const { return height(root); }
private:
	binaryTreeNode<E>* root;
	int treeSize;
	static void (*visit)(binaryTreeNode<E>*);//visit function
	static int count;//used to count nodes in a subtree
	static void preOrder(binaryTreeNode<E>* t) {
		if (t != NULL) {
			binaryTree<E>::visit(t);
			preOrder(t->leftChild);
			preOrder(t->rightChild);
		}
	}
	//是用visit作用到了每一个节点上了，这是递归，从给定的t开始，一直到最后
	static void inOrder(binaryTreeNode<E>* t) {
		if (t != NULL) {
			inOrder(t->leftChild);
			binaryTree<E>::visit(t);
			inOrder(t->rightChild);
		}
	}
	static void postOrder(binaryTreeNode<E>* t) {
		if (t != NULL)
		{
			postOrder(t->leftChild);
			postOrder(t->rightChild);
			binaryTree<E>::visit(t);
		}
	}
	static void countNodes(binaryTreeNode<E>* t) {
		visit = addToCount;
		count = 0;
		preOrder(t);
	}

	static void dispose(binaryTreeNode<E>* t) { delete t; }
	static void output(binaryTreeNode<E>* t) {
		cout << t->element << ' ';
	}
	static void addToCount(binaryTreeNode<E>* t) {
		count++;
	}
	static int height(binaryTreeNode<E>* t) {
		if (t == NULL) {
			return 0;
		}
		int hl = height(t->leftChild);
		int hr = height(t->rightChild);
		if (hl > hr) {
			hl++;
			return hl;
		}
		else {
			hr++;
			return hr;
		}
	}
};