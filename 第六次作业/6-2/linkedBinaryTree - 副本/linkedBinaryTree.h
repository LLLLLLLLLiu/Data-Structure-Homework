
// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree
//所有的check if empty都是有问题的,都会报错,因为我不知道该返回什么
#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;


#include <iostream>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "booster.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> >
{
   public:
      linkedBinaryTree() {root = NULL; treeSize = 0;}
      ~linkedBinaryTree(){erase();} 
      bool empty() const {return treeSize == 0;}
      int size() const {return treeSize;}
      E* rootElement() const;
      void makeTree(const E& element,linkedBinaryTree<E>&, linkedBinaryTree<E>&);
      linkedBinaryTree<E>& removeLeftSubtree()
	  {// Remove and return the left subtree.
		  //这里有个疑问：这里是删除之后把LeftSubtree返回了，可不可以不删除，而只是返回LeftSubtree呢？
		  //这个功能是不是很好用?或者写删除函数其实也可以设计成没有返回值的?
		 // check if empty
		  if (treeSize == 0)
		  {
			  cout << "错误，这棵树是空树，无法删除" << endl;
		  }

		  // detach left subtree and save in leftSubtree
		  linkedBinaryTree<E> leftSubtree;
		  leftSubtree.root = root->leftChild;
		  count = 0;
		  leftSubtree.treeSize = countNodes(leftSubtree.root);
		  root->leftChild = NULL;
		  treeSize = treeSize - leftSubtree.treeSize;
		  return leftSubtree;
	  }
      linkedBinaryTree<E>& removeRightSubtree();
      void preOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; preOrder(root);}
      void inOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; inOrder(root);}
      void postOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; postOrder(root);}
      void levelOrder(void(*)(binaryTreeNode<E> *));
      void preOrderOutput() {preOrder(output); cout << endl;}
      void inOrderOutput() {inOrder(output); cout << endl;}
      void postOrderOutput() {postOrder(output); cout << endl;}
      void levelOrderOutput() {levelOrder(output); cout << endl;}
      void erase()
           {
              postOrder(dispose);
              root = NULL;
              treeSize = 0;
           }
      int height() const {return height(root);}
   protected:
      binaryTreeNode<E> *root;                // pointer to root
      int treeSize;                           // number of nodes in tree
      static void (*visit)(binaryTreeNode<E>*);      // visit function
      static int count;         // used to count nodes in a subtree
      static void preOrder(binaryTreeNode<E> *t);
      static void inOrder(binaryTreeNode<E> *t);
      static void postOrder(binaryTreeNode<E> *t);
      static void countNodes(binaryTreeNode<E> *t)
                  {
                     visit = addToCount; 
                     count = 0;
                     preOrder(t);
                  }
      static void dispose(binaryTreeNode<E> *t) {delete t;}
      static void output(binaryTreeNode<E> *t)
                  {cout << t->element << ' ';}
      static void addToCount(binaryTreeNode<E> *t)
                  {count++;}
      static int height(binaryTreeNode<E> *t);
};
// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
void (*linkedBinaryTree<pair<int,int> >::visit)(binaryTreeNode<pair<int,int> >*);
void (*linkedBinaryTree<pair<const int,char> >::visit)(binaryTreeNode<pair<const int,char> >*);
void (*linkedBinaryTree<pair<const int,int> >::visit)(binaryTreeNode<pair<const int,int> >*);

template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// Return NULL if no root. Otherwise, return pointer to root element.
   if (treeSize == 0)
      return NULL;  // no root
   else
      return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,linkedBinaryTree<E>& left,linkedBinaryTree<E>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
   // create combined tree
   root = new binaryTreeNode<E> (element, left.root, right.root);
   treeSize = left.treeSize + right.treeSize + 1;

   // deny access from trees left and right
   //left.root = right.root = NULL;
   //left.treeSize = right.treeSize = 0;
}



template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{// Remove and return the right subtree.
   // check if empty
   if (treeSize == 0)
      cout<<"树大小为0，错误"<<endl;

   // detach right subtree and save in rightSubtree
   linkedBinaryTree<E> rightSubtree;
   rightSubtree.root = root->rightChild;
   count = 0;
   rightSubtree.treeSize = countNodes(rightSubtree.root);
   root->rightChild = NULL;
   treeSize -= rightSubtree.treeSize;
  
   return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{// Preorder traversal.
   if (t != NULL)
   {
      linkedBinaryTree<E>::visit(t);
      preOrder(t->leftChild);
      preOrder(t->rightChild);
   }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{// Inorder traversal.
   if (t != NULL)
   {
      inOrder(t->leftChild);
      linkedBinaryTree<E>::visit(t);
      inOrder(t->rightChild);
   }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{// Postorder traversal.
   if (t != NULL)
   {
      postOrder(t->leftChild);
      postOrder(t->rightChild);
      linkedBinaryTree<E>::visit(t);
   }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// Level-order traversal.
   arrayQueue<binaryTreeNode<E>*> q;
   binaryTreeNode<E> *t = root;
   while (t != NULL)
   {
      theVisit(t);  // visit t

      // put t's children on queue
      if (t->leftChild != NULL)
         q.push(t->leftChild);
      if (t->rightChild != NULL)
         q.push(t->rightChild);

      // get next node to visit
      try {t = q.front();}
      catch (queueEmpty) {return;}
      q.pop();
   }
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{// Return height of tree rooted at *t.
   if (t == NULL)
      return 0;                    // empty tree
   int hl = height(t->leftChild);  // height of left
   int hr = height(t->rightChild); // height of right
   if (hl > hr)
      return ++hl;
   else
      return ++hr;
}

#endif
