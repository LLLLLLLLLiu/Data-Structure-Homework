
// max heap with double the space

#ifndef MaxHeap_
#define MaxHeap_

#include <stdlib.h>
#include <iostream>
#include "xcept.h"

using namespace std;
template<class T>
class MaxHeap {
   public:
      MaxHeap(int MaxHeapSize, T maxElement,T minElement);
      ~MaxHeap() {delete [] heap;}
      int Size() const {return CurrentSize;}
      T Max() {if (CurrentSize == 0)
                  throw OutOfBounds();
               return heap[1];}
      MaxHeap<T>& Insert(const T& x);
      MaxHeap<T>& DeleteMax(T& x);
      void Initialize(T a[], int size, int ArraySize,
           int minElement, int maxElement);
      void Deactivate() {heap = 0;}
      void Output() const;
   private:
      int CurrentSize,
          MaxSize;
      T MaxElement,  // all must be <= MaxElement
        MinElement;  // all must be >= MinElement
      T *heap;  // element array
};

//构造函数
template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize,T maxElement, T minElement)
{
   MaxSize = MaxHeapSize;
   MaxElement = maxElement;//创建者提供的maxElement
   MinElement = minElement;//创建者提供的minElement
   heap = new T[2*(MaxSize+1)];//一个n元素的堆需要一个数组heap[0:2n+1]

   //maxElement存储在heap[0]中
   heap[0] = MaxElement;

   // minElement存储在heap[n+1:2n+1]中
   //这里，先是把heap[1:2n+1]都暂时存放了minElement
   for (int i = 1; i <= 2*MaxSize + 1; i++)
      heap[i] = MinElement;

   CurrentSize = 0;
}

//Insert，也是push
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
   if (CurrentSize == MaxSize)
      throw NoMem(); // 当前元素已经达到了最大容量，无法插入（这里需不需要动态扩充容量呢？）
   if (x < MinElement || x > MaxElement)
      throw BadInput();//输入的元素比事前规定的最大元还大或者比最小元还小，报错。

   
   int i = ++CurrentSize;//把i放到合适的位置，也就是当前的位置。
   //下面的循环将i一层一层上移，比较x与其父亲的大小，在最终合适的位置，进行一次交换。
  
   // 不需要再判断是否到达了根节点，因为在原来到达了根节点就一定要终止，然后把x放到heap[1]中。
   // 因为heap[0]一定大于所有的输入的x，之前也比较过了，可以保证这一点。
   while (x > heap[i/2]) {
      
      heap[i] = heap[i/2]; // 把heap[i/2]这个父亲节点的元素copy且下放到heap[i]这个孩子节点处
	  i = i / 2;           // 把“指针”移动到其父亲处
      }
   //在此时，当i=2时，倘若，x>heap[1]这个情况发生（这个情况有可能发生的）
   //那么就把heap[2]=heap[1]；把1处的值下移拷贝到2中，把1这个位置腾出来。
   //i=i/2，让i=1；
   //之后由于x一定不会大于heap[1/2]也就是heap[0]，因此循环必将结束。
   //这样就省掉了每次判断循环是否要进行时，要判断i是否到达了1处。
   //这就省掉了logn次比较操作。
   heap[i] = x;
   
   return *this;//可连等
}

//pop
template<class T>
MaxHeap<T>& MaxHeap<T>::DeleteMax(T& x)
{// Set x to max element and delete
 // max element from heap.
   // check if heap is empty
   if (CurrentSize == 0)
      throw OutOfBounds(); // empty

   x = heap[1]; // max element

   // restructure heap
   T y = heap[CurrentSize]; // last element
   // replace with MinElement
   heap[CurrentSize--] = MinElement;//增加这句，把最后一个点移到开头后，最后一个点位置及时置为极小值，这也是和构造函数呼应，满足了逻辑完整

   // first propagate vacancy to a leaf
   int i = 1,  // 当前的位置，因为删除的是顶元素，肯定是从i=1开始了
       ci = 2; // 用来执行i与i的两个孩子中的最大值的比较，先放在i的左孩子的位置
   while (ci <= CurrentSize) {
      // heap[ci] should be larger child of i
      // no need to check if ci < CurrentSize
      // because heap[CurrentSize] has MinElement
	   //一切都建立在ci <= CurrentSize时
      if (heap[ci] < heap[ci+1]) ci++;
	  //因为刚开始ci是从2开始的,并且ci最多只能+1,所以这句话只能调整左孩子到右孩子
      // move larger child to heap[i]
	  //这里可以省略ci<CurrentSize的判断,因为当之后左子树时,ci+1为min,ci一定>ci+1所指的元素,所以那一句
	  //可以省略
      heap[i] = heap[ci]; // move child up
      i = ci;             // move down a level
	  ci = i * 2;//因为ci是每次都*2,所以可能很快就超出currentSize了
      }
//为什么没有比较y呢?
   //这时候ci已经跑出去了
   i = ci/2;
   //其实我感觉这一句话可要可不要,因为ci = i * 2嘛;

   // vacancy at heap[i], start from here
   // and insert y
   // no need to check if root reached
   // because heap[0] = MaxElement
   while (y > heap[i/2]) {
      // cannot put y in heap[i]
      heap[i] = heap[i/2]; // move element down
      i /= 2;              // move to parent
      }

   heap[i] = y;

   return *this;
}
//因为提上去的元素一定是很小很小的,它之前在最后嘛,所以肯定比它的父亲小.

template<class T>
void MaxHeap<T>::Initialize(T a[], int size,
                 int ArraySize, int minElement, int maxElement)
{// Initialize max heap to array a[0:ArraySize].
   if (ArraySize < 2*size + 1)
      throw BadInput();  // not enough space for
                         // MinElement children of
                         // leaves
   // set private data members of MaxHeap
   delete [] heap;
   heap = a;
   CurrentSize = size;
   MaxElement = maxElement;
   MinElement = minElement;
   heap[0] = MaxElement;
   // fill rest of array with MinElement
   for (int i = size + 1; i <= ArraySize; i++)
      heap[i] = MinElement;
   MaxSize = (ArraySize - 1)/2;

   // make into a max heap
   // by running old method as we do not
   // expect to propagate all the way down
   for (int i = CurrentSize/2; i >= 1; i--) {
      T y = heap[i]; // root of subtree

      // find place to put y
      int c = 2*i; // parent of c is target
                   // location for y
      while (c <= CurrentSize) {
         // heap[c] should be larger sibling
         // no need to check if c < CurrentSize as
         // all unused spots have MinElement
         if (heap[c] < heap[c+1]) c++;

         // can we put y in heap[c/2]?
         if (y >= heap[c]) break;  // yes

         // no
         heap[c/2] = heap[c]; // move child up
         c *= 2; // move down a level
         }
      heap[c/2] = y;
      }
}

template<class T>
void MaxHeap<T>::Output() const
{
   cout << "The " << CurrentSize 
        << " elements are"<< endl;
   for (int i = 1; i <= CurrentSize; i++)
       cout << heap[i] << ' ';
   cout << endl;
}

#endif
