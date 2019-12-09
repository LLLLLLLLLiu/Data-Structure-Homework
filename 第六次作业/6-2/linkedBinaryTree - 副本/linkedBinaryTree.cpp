// test linked binary tree class
/*
���ǲ��Ǿ���һЩ�ڵ�ļ���,��Щ�ڵ㱾���ǿ��Թ�������,������ǿ��ֻ�ܴӸ��ڵ����?


*/





#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main(void)
{
	/*binaryTreeNode<int> node1, node2, node3, node4, node5, node6, node7, node8, node9;
	
	node2.rightChild = &node3;
	node1.element = 1;
	node2.element = 2;
	node3.element = 3;
	cout << node1.leftChild->element << endl;
	linkedBinaryTree<string> a, x, y, z;
	x.makeTree("a", a, a);*/


   linkedBinaryTree<int> a,x,y,z;
   y.makeTree(1,a,a);
   z.makeTree(2,a,a);
   x.makeTree(3,y,z);
   y.makeTree(4,x,a);
   cout << "Number of nodes = ";
   cout << y.size() << endl;
   cout << "height = ";
   cout << y.height() << endl;
   cout << "Preorder sequence is ";
   y.preOrderOutput();
   cout << "Inorder sequence is ";
   y.inOrderOutput();
   cout << "Postorder sequence is ";
   y.postOrderOutput();
   cout << "Level order sequence is ";
   y.levelOrderOutput();

   return 0;
}
