通过理解cpp文件，和写出6.2,6.3，来加深对linkedBinaryTree这个文件的理解。

首先，这个构造函数是形同虚设的，只能把root置为NULL，把treeSize置为0；
所以在写cpp时，先`linkedBinaryTree<int> a,x,y,z;`

```
y.makeTree(1,a,a);
z.makeTree(2,a,a);
x.makeTree(3,y,z);
y.makeTree(4,x,a);
```
这个很重要,就是用makeTree这个成员函数
makeTree需要输入一个E类型的数据,毫无疑问,就是这个根节点元素的数据.
除此之外,还要有两个linkedBinaryTree类型的实参
对于新建的树来说,root的内容域就是这个E类型的数据,而root作为一个binaryTreeNode类型的对象,它的左子树域和右子树域分别为输入这个函数的left.root,和right.root,
并且,不允许再从之前的地方来访问了.

也就是所有访问只能从根节点出发,或者用提供的那四种遍历方式

我们都知道,在进行树的操作时,可以进行像把一个节点摘下来放到某一个位置上,旋转操作等等,但是这些操作具体用代码如何实现,这是我们现在需要思考的.

哪些是外部可见的,外部可以做哪些操作?
root:返回根节点的元素值
但是返回某一个特定节点的元素值呢?就是所谓随机查找呢?

首先来看建树,如果只用makeTree来建树,是不是太麻烦了,bst应当有更简单方便的建树方法?
这个之所以麻烦,是因为对树的限定太少了,可以搭建的树的形态很多,所以没法给予规定.
