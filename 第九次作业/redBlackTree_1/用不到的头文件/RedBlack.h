#pragma once

#include<iostream>
#include<memory>
#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度（与“空树高度为-1”的约定相统一）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //外部节点也视作黑节点
#define IsRed(p) ( ! IsBlack(p) ) //非黑即红
#define BlackHeightUpdated(x) ( /*RedBlack高度更新条件*/ \
   ( stature( (x).lc ) == stature( (x).rc ) ) && \
   ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) \
)
/******************************************************************************************
 * BinNode状态与性质的判断
 ******************************************************************************************/
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )

 /******************************************************************************************
  * 与BinNode具有特定关系的节点及指针
  ******************************************************************************************/
#define sibling(p) /*兄弟*/ \
   ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc )
#define uncle(x) /*叔叔*/ \
   ( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
#define FromParentTo(x) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )


#define EQUAL(e, v)  (!(v) || (e) == (v)->data) //节点v（或假想的通配哨兵）的关键码等于e


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
	BinNode() :parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), color(RB_RED) {}
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

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //定位节点v的直接后继
	BinNodePosi(T) s = this; //记录后继的临时变量
	if (rc) { //若有右孩子，则直接后继必在右子树中，具体地就是
		s = rc; //右子树中
		while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
	}
	else { //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
		while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
		s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}


template <typename T> 
class RedBlack { //RedBlack树模板类
public:
	//规模
	int _size; 
	//根节点
	BinNodePosi(T) _root;
	//“命中”节点的父亲
	BinNodePosi(T) _hot;

	BinNodePosi(T) connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3) {
		//*DSA*/print(a); print(b); print(c); printf("\n");
		a->lc = T0; if (T0) T0->parent = a;
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
		c->lc = T2; if (T2) T2->parent = c;
		c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(b);
		return b; //该子树新的根节点
	}
 /******************************************************************************************
 * RedBlack双红调整算法：解决节点x与其父均为红色的问题。分为两大类情况：
 *    RR-1：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    RR-2：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
 ******************************************************************************************/
   void solveDoubleRed(BinNodePosi(T) x) { //x当前必为红
	   if (IsRoot(*x)) //若已（递归）转至树根，则将其转黑，整树黑高度也随之递增
	   {
		   _root->color = RB_BLACK; _root->height++; return;
	   } //否则，x的父亲p必存在
	   BinNodePosi(T) p = x->parent; if (IsBlack(p)) return; //若p为黑，则可终止调整。否则
	   BinNodePosi(T) g = p->parent; //既然p为红，则x的祖父必存在，且必为黑色
	   BinNodePosi(T) u = uncle(x); //以下，视x叔父u的颜色分别处理
	   if (IsBlack(u)) { //u为黑色（含NULL）时 //*DSA*/printf("  case RR-1:\n");
		   if (IsLChild(*x) == IsLChild(*p)) //若x与p同侧（即zIg-zIg或zAg-zAg），则
			   p->color = RB_BLACK; //p由红转黑，x保持红
		   else //若x与p异侧（即zIg-zAg或zAg-zIg），则
			   x->color = RB_BLACK; //x由红转黑，p保持红
		   g->color = RB_RED; //g必定由黑转红
	 ///// 以上虽保证总共两次染色，但因增加了判断而得不偿失
	 ///// 在旋转后将根置黑、孩子置红，虽需三次染色但效率更高
		   BinNodePosi(T) gg = g->parent; //曾祖父（great-grand parent）
		   BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x); //调整后的子树根节点
		   r->parent = gg; //与原曾祖父联接
	   }
	   else { //若u为红色 //*DSA*/printf("  case RR-2:\n");
		   p->color = RB_BLACK; p->height++; //p由红转黑
		   u->color = RB_BLACK; u->height++; //u由红转黑
		   if (!IsRoot(*g)) g->color = RB_RED; //g若非根，则转红
		   solveDoubleRed(g); //继续调整g（类似于尾递归，可优化为迭代形式）
	   }
   }

   /******************************************************************************************
 * RedBlack双黑调整算法：解决节点x与被其替代的节点均为黑色的问题
 * 分为三大类共四种情况：
 *    BB-1 ：2次颜色翻转，2次黑高度更新，1~2次旋转，不再递归
 *    BB-2R：2次颜色翻转，2次黑高度更新，0次旋转，不再递归
 *    BB-2B：1次颜色翻转，1次黑高度更新，0次旋转，需要递归
 *    BB-3 ：2次颜色翻转，2次黑高度更新，1次旋转，转为BB-1或BB2R
 ******************************************************************************************/
   void solveDoubleBlack(BinNodePosi(T) r) {
	   BinNodePosi(T) p = r ? r->parent : _hot; if (!p) return; //r的父亲
	   BinNodePosi(T) s = (r == p->lc) ? p->rc : p->lc; //r的兄弟
	   if (IsBlack(s)) { //兄弟s为黑
		   BinNodePosi(T) t = NULL; //s的红孩子（若左、右孩子皆红，左者优先；皆黑时为NULL）
		   if (IsRed(s->rc)) t = s->rc; //右子
		   if (IsRed(s->lc)) t = s->lc; //左子
		   if (t) { //黑s有红孩子：BB-1
			  //*DSA*/printf("  case BB-1: Child ("); print(s->lc); printf(") of BLACK sibling ("); print(s); printf(") is RED\n");
			   RBColor oldColor = p->color; //备份原子树根节点p颜色，并对t及其父亲、祖父
			// 以下，通过旋转重平衡，并将新子树的左、右孩子染黑
			   BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t); //旋转
			   if (HasLChild(*b)) { b->lc->color = RB_BLACK; updateHeight(b->lc); } //左子
			   if (HasRChild(*b)) { b->rc->color = RB_BLACK; updateHeight(b->rc); } //右子
			   b->color = oldColor; updateHeight(b); //新子树根节点继承原根节点的颜色
			   //*DSA*/printBinTree(b, 0, 0);
		   }
		   else { //黑s无红孩子
			   s->color = RB_RED; s->height--; //s转红
			   if (IsRed(p)) { //BB-2R
				  //*DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is RED\n"); //s孩子均黑，p红
				   p->color = RB_BLACK; //p转黑，但黑高度不变
				   //*DSA*/printBinTree(p, 0, 0);
			   }
			   else { //BB-2B
			   //*DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is BLACK\n"); //s孩子均黑，p黑
				   p->height--; //p保持黑，但黑高度下降
				   //*DSA*/printBinTree(p, 0, 0);
				   solveDoubleBlack(p); //递归上溯
			   }
		   }
	   }
	   else { //兄弟s为红：BB-3
	   //*DSA*/printf("  case BB-3: sibling ("); print(s); printf(" is RED\n"); //s红（双子俱黑）
		   s->color = RB_BLACK; p->color = RB_RED; //s转黑，p转红
		   BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc; //取t与其父s同侧
		   _hot = p; FromParentTo(*p) = rotateAt(t); //对t及其父亲、祖父做平衡调整
		   //*DSA*/printBinTree<T>(s, 0, 0);
		   solveDoubleBlack(r); //继续修正r处双黑——此时的p已转红，故后续只能是BB-1或BB-2R
	   }
   }

   //更新节点x的高度
   int updateHeight(BinNodePosi(T) x) { //更新节点高度
	   x->height = __max(stature(x->lc), stature(x->rc)); //孩子一般黑高度相等，除非出现双黑
	   /*DSA*/// 红黑树中各节点左、右孩子的黑高度通常相等
	   /*DSA*/// 这里之所以取更大值，是便于在删除节点后的平衡调整过程中，正确更新被删除节点父亲的黑高度
	   /*DSA*/// 否则，rotateAt()会根据被删除节点的替代者（高度小一）设置父节点的黑高度
	   return IsBlack(x) ? x->height++ : x->height; //若当前节点为黑，则计入黑深度
   } //因统一定义stature(NULL) = -1，故height比黑高度少一，好在不致影响到各种算法中的比较判断


public:
	int size() const { return _size; } //规模
	bool empty() const { return !_root; } //判空
	RedBlack() : _size(0), _root(nullptr) { } //构造函数
	~RedBlack() {} //析构函数

	BinNodePosi(T) rotateAt(BinNodePosi(T) v) { //v为非空孙辈节点
		if (!v) {
			cout << "Fail to rotate a null node" << endl;
			exit(-1);
		}
		BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
		if (IsLChild(*p)) /* zig */
			if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
				p->parent = g->parent; //向上联接
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			}
			else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
				v->parent = g->parent; //向上联接
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		else  /* zag */
			if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
				p->parent = g->parent; //向上联接
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
				v->parent = g->parent; //向上联接
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}




	BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
		BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
		BinNodePosi(T) succ = NULL; //实际被删除节点的接替者
		if (!HasLChild(*x)) //若*x的左子树为空，则可
			succ = x = x->rc; //直接将*x替换为其右子树
		else if (!HasRChild(*x)) //若右子树为空，则可
			succ = x = x->lc; //对称地处理——注意：此时succ != NULL
		else { //若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
			w = w->succ(); //（在右子树中）找到*x的直接后继*w
			swap(x->data, w->data); //交换*x和*w的数据元素
			BinNodePosi(T) u = w->parent;
			((u == x) ? u->rc : u->lc) = succ = w->rc; //隔离节点*w
		}
		hot = w->parent; //记录实际被删除节点的父亲
		if (succ) succ->parent = hot; //并将被删除节点的接替者与hot相联
		//release(w->data); release(w); 
		return succ; //释放被摘除节点，返回接替者
	} //release()负责释放复杂结构，与算法无直接关系，具体实现详见代码包
	//插入（重写）


   BinNodePosi(T) insert(const T& e) { //将e插入红黑树
	   BinNodePosi(T)& x = search(e);
	   if (x) return x; //确认目标不存在（留意对_hot的设置）
	   x = new BinNode<T>(e, _hot, NULL, NULL, -1); _size++; //创建红节点x：以_hot为父，黑高度-1
	   BinNodePosi(T) xOld = x;
	   solveDoubleRed(x);
	   return xOld; //经双红修正后，即可返回
   } //无论e是否存在于原树中，返回时总有x->data == e

    //删除（重写）
   bool remove(const T& e) { //从红黑树中删除关键码e
	   BinNodePosi(T)& x = search(e); 
	   if (!x) return false; //确认目标存在（留意_hot的设置）
	   BinNodePosi(T) r = removeAt(x, _hot); 
	   if (!(--_size)) return true; //实施删除
	// assert: _hot某一孩子刚被删除，且被r所指节点（可能是NULL）接替。以下检查是否失衡，并做必要调整
	   if (!_hot) //若刚被删除的是根节点，则将其置黑，并更新黑高度
	   {
		   _root->color = RB_BLACK; updateHeight(_root); return true;
	   }
	   // assert: 以下，原x（现r）必非根，_hot必非空
	   if (BlackHeightUpdated(*_hot)) return true; //若所有祖先的黑深度依然平衡，则无需调整
	   if (IsRed(r)) //否则，若r为红，则只需令其转黑
	   {
		   r->color = RB_BLACK; r->height++; return true;
	   }
	   // assert: 以下，原x（现r）均为黑色
		  //*DSA*/printBinTree(_hot, 0, 0);
	   solveDoubleBlack(r); return true; //经双黑调整后返回
   } //若目标节点存在且被删除，返回true；否则返回false


   BinNodePosi(T)& search(const T& e) //在BST中查找关键码e
   {
	   return searchIn(_root, e, _hot = NULL);
   } //返回目标节点位置的引用，以便后续插入、删除操作

//在以v为根的rbTree中查找关键码e
   BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
	   if (EQUAL(e, v)) return v; hot = v; //退化情况：在子树根节点v处命中
	   while (1) { //一般地，反复不断地
		   BinNodePosi(T)& c = (e < hot->data) ? hot->lc : hot->rc; //确定深入方向
		   if (EQUAL(e, c)) return c; hot = c; //命中返回，或者深入一层
	   } //hot始终指向最后一个失败节点
   } //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲（退化时为初始值NULL）
  

};

