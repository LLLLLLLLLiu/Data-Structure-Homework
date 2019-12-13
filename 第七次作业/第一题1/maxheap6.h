
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

//���캯��
template<class T>
MaxHeap<T>::MaxHeap(int MaxHeapSize,T maxElement, T minElement)
{
   MaxSize = MaxHeapSize;
   MaxElement = maxElement;//�������ṩ��maxElement
   MinElement = minElement;//�������ṩ��minElement
   heap = new T[2*(MaxSize+1)];//һ��nԪ�صĶ���Ҫһ������heap[0:2n+1]

   //maxElement�洢��heap[0]��
   heap[0] = MaxElement;

   // minElement�洢��heap[n+1:2n+1]��
   //������ǰ�heap[1:2n+1]����ʱ�����minElement
   for (int i = 1; i <= 2*MaxSize + 1; i++)
      heap[i] = MinElement;

   CurrentSize = 0;
}

//Insert��Ҳ��push
template<class T>
MaxHeap<T>& MaxHeap<T>::Insert(const T& x)
{
   if (CurrentSize == MaxSize)
      throw NoMem(); // ��ǰԪ���Ѿ��ﵽ������������޷����루�����費��Ҫ��̬���������أ���
   if (x < MinElement || x > MaxElement)
      throw BadInput();//�����Ԫ�ر���ǰ�涨�����Ԫ������߱���СԪ��С������

   
   int i = ++CurrentSize;//��i�ŵ����ʵ�λ�ã�Ҳ���ǵ�ǰ��λ�á�
   //�����ѭ����iһ��һ�����ƣ��Ƚ�x���丸�׵Ĵ�С�������պ��ʵ�λ�ã�����һ�ν�����
  
   // ����Ҫ���ж��Ƿ񵽴��˸��ڵ㣬��Ϊ��ԭ�������˸��ڵ��һ��Ҫ��ֹ��Ȼ���x�ŵ�heap[1]�С�
   // ��Ϊheap[0]һ���������е������x��֮ǰҲ�ȽϹ��ˣ����Ա�֤��һ�㡣
   while (x > heap[i/2]) {
      
      heap[i] = heap[i/2]; // ��heap[i/2]������׽ڵ��Ԫ��copy���·ŵ�heap[i]������ӽڵ㴦
	  i = i / 2;           // �ѡ�ָ�롱�ƶ����丸�״�
      }
   //�ڴ�ʱ����i=2ʱ��������x>heap[1]�������������������п��ܷ����ģ�
   //��ô�Ͱ�heap[2]=heap[1]����1����ֵ���ƿ�����2�У���1���λ���ڳ�����
   //i=i/2����i=1��
   //֮������xһ���������heap[1/2]Ҳ����heap[0]�����ѭ���ؽ�������
   //������ʡ����ÿ���ж�ѭ���Ƿ�Ҫ����ʱ��Ҫ�ж�i�Ƿ񵽴���1����
   //���ʡ����logn�αȽϲ�����
   heap[i] = x;
   
   return *this;//������
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
   heap[CurrentSize--] = MinElement;//������䣬�����һ�����Ƶ���ͷ�����һ����λ�ü�ʱ��Ϊ��Сֵ����Ҳ�Ǻ͹��캯����Ӧ���������߼�����

   // first propagate vacancy to a leaf
   int i = 1,  // ��ǰ��λ�ã���Ϊɾ�����Ƕ�Ԫ�أ��϶��Ǵ�i=1��ʼ��
       ci = 2; // ����ִ��i��i�����������е����ֵ�ıȽϣ��ȷ���i�����ӵ�λ��
   while (ci <= CurrentSize) {
      // heap[ci] should be larger child of i
      // no need to check if ci < CurrentSize
      // because heap[CurrentSize] has MinElement
	   //һ�ж�������ci <= CurrentSizeʱ
      if (heap[ci] < heap[ci+1]) ci++;
	  //��Ϊ�տ�ʼci�Ǵ�2��ʼ��,����ci���ֻ��+1,������仰ֻ�ܵ������ӵ��Һ���
      // move larger child to heap[i]
	  //�������ʡ��ci<CurrentSize���ж�,��Ϊ��֮��������ʱ,ci+1Ϊmin,ciһ��>ci+1��ָ��Ԫ��,������һ��
	  //����ʡ��
      heap[i] = heap[ci]; // move child up
      i = ci;             // move down a level
	  ci = i * 2;//��Ϊci��ÿ�ζ�*2,���Կ��ܺܿ�ͳ���currentSize��
      }
//Ϊʲôû�бȽ�y��?
   //��ʱ��ci�Ѿ��ܳ�ȥ��
   i = ci/2;
   //��ʵ�Ҹо���һ�仰��Ҫ�ɲ�Ҫ,��Ϊci = i * 2��;

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
//��Ϊ����ȥ��Ԫ��һ���Ǻ�С��С��,��֮ǰ�������,���Կ϶������ĸ���С.

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
