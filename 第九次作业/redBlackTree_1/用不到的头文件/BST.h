#pragma once

#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
using namespace std;

template <typename T> struct BinNode { //二叉树节点模板类
// 成员（为简化描述起见统一开放，读者可根据需要进一步封装）
	T data; //数值
	BinNodePosi(T) parent; 
	BinNodePosi(T) lc; 
	BinNodePosi(T) rc; //父节点及左、右孩子
	int height; //高度（通用）
	int npl; //Null Path Length（左式堆，也可直接用height代替）
	RBColor color; //颜色（红黑树）
 // 构造函数
	BinNode():parent(nullptr),lc(nullptr),rc(nullptr),height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) { }
	// 操作接口
	int size(); //统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T const&); //作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const&); //作为当前节点的右孩子插入新节点
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template <typename VST> void travLevel(VST&); //子树层次遍历
	template <typename VST> void travPre(VST&); //子树先序遍历
	template <typename VST> void travIn(VST&); //子树中序遍历
	template <typename VST> void travPost(VST&); //子树后序遍历
 // 比较器、判等器（各列其一，其余自行补充）
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
	bool operator== (BinNode const& bn) { return data == bn.data; } //等于
	/*DSA*/
	/*DSA*/BinNodePosi(T) zig(); //顺时针旋转
	/*DSA*/BinNodePosi(T) zag(); //逆时针旋转
};

template <typename T> class BinTree { //二叉树模板类
protected:
	int _size; BinNodePosi(T) _root; //规模、根节点
	virtual int updateHeight(BinNodePosi(T) x); //更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x); //更新节点x及其祖先的高度
public:
	BinTree() : _size(0), _root(nullptr) { } //构造函数
	~BinTree() { if (0 < _size) remove(_root); } //析构函数
	int size() const { return _size; } //规模
	bool empty() const { return !_root; } //判空
	BinNodePosi(T) root() const { return _root; } //树根
	BinNodePosi(T) insertAsRoot(T const& e); //插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e); //e作为x的左孩子（原无）插入
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e); //e作为x的右孩子（原无）插入
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>*& T); //T作为x左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>*& T); //T作为x右子树接入
	int remove(BinNodePosi(T) x); //删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x); //将子树x从当前树中摘除，并将其转换为一棵独立子树
	template <typename VST> //操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //层次遍历
	template <typename VST> //操作器
	void travPre(VST& visit) { if (_root) _root->travPre(visit); } //先序遍历
	template <typename VST> //操作器
	void travIn(VST& visit) { if (_root) _root->travIn(visit); } //中序遍历
	template <typename VST> //操作器
	void travPost(VST& visit) { if (_root) _root->travPost(visit); } //后序遍历
	bool operator< (BinTree<T> const& t) //比较器（其余自行补充）
	{
		return _root && t._root && lt(_root, t._root);
	}
	bool operator== (BinTree<T> const& t) //判等器
	{
		return _root && t._root && (_root == t._root);
	}
}; //BinTree

template <typename T> 
class BST : public BinTree<T> { //由BinTree派生BST模板类
protected:
   BinNodePosi(T) _hot; //“命中”节点的父亲
   BinNodePosi(T) connect34 ( //按照“3 + 4”结构，联接3个节点及四棵子树
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
      BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T) );
   BinNodePosi(T) rotateAt ( BinNodePosi(T) x ); //对x及其父亲、祖父做统一旋转调整
public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
   virtual BinNodePosi(T) & search ( const T& e ); //查找
   virtual BinNodePosi(T) insert ( const T& e ); //插入
   virtual bool remove ( const T& e ); //删除
   /*DSA*/
   /*DSA*/void stretchToLPath() { stretchByZag ( BinTree<T>::_root ); } //借助zag旋转，转化为左向单链
   /*DSA*/void stretchToRPath() { stretchByZig ( BinTree<T>::_root ); } //借助zig旋转，转化为右向单链
   /*DSA*/void stretch();
   /*DSA*/void imitate ( const BST<T> & ); //临摹
};



