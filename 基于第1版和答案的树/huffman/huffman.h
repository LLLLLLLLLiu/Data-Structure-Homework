#ifndef Huffman_
#define Huffman_
#include"binary.h"
template<class T>
class  Huffman {
   friend BinaryTree<int> HuffmanTree(T [], int);
   public:
      operator T () const {return weight;}
	  BinaryTree<int> tree;
      T weight;
};

#endif
