#pragma once
#include<iostream>
using namespace std;

#define BinNodePosi(K,E) BinNode<K,E>* //�ڵ�λ��
#define stature(p) ((p) ? (p)->height : -1) //�ڵ�߶ȣ��롰�����߶�Ϊ-1����Լ����ͳһ��
typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
#define IsBlack(p) ( ! (p) || ( RB_BLACK == (p)->color ) ) //�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsRed(p) ( ! IsBlack(p) ) //�Ǻڼ���
/*RedBlack�߶ȸ�������*/
#define BlackHeightUpdated(x) (( stature( (x).lc ) == stature( (x).rc ) ) &&  ( (x).height == ( IsRed(& x) ? stature( (x).lc ) : stature( (x).lc ) + 1 ) ) )
//BinNode״̬�����ʵ��ж�
#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
//��BinNode�����ض���ϵ�Ľڵ㼰ָ��
  /*����*/
#define uncle(x)( IsLChild( * ( (x)->parent ) ) ? (x)->parent->parent->rc : (x)->parent->parent->lc )
  /*���Ը��׵�����*/
#define FromParentTo(x)( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )
//�ڵ�v��������ͨ���ڱ����Ĺؼ������e
#define EQUAL(e, v)  (!(v) || (e) == (v)->data.first) 

//�������ڵ�ģ����
template <class K,class E> 
struct BinNode {
	pair<K, E> data; //�ڵ���һ��key-element pair
	BinNodePosi(K, E) parent;
	BinNodePosi(K, E) lc;
	BinNodePosi(K, E) rc; //���ڵ㼰���Һ���
	int height; //�߶ȣ�ͨ�ã�
	RBColor color; //��ɫ���������
	// ���캯��
	BinNode() :parent(nullptr), lc(nullptr), rc(nullptr), height(0), color(RB_RED) {}
	BinNode(pair<K,E> data, BinNodePosi(K, E) p = nullptr, BinNodePosi(K, E) lc = nullptr, BinNodePosi(K, E) rc = nullptr,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(data), parent(p), lc(lc), rc(rc), height(h), color(c) {}
	// �����ӿ�

	//ȡ��ǰ�ڵ��ֱ�Ӻ��,����key�����������ұ�����ġ�
	BinNodePosi(K, E) succ() { //��λ�ڵ�v��ֱ�Ӻ��
		BinNodePosi(K, E) s = this; //��¼��̵���ʱ����
		if (rc) { //�����Һ��ӣ���ֱ�Ӻ�̱����������У�����ؾ���
			s = rc; //��������
			while (HasLChild(*s)) s = s->lc; //�����С���Ľڵ�
		}
		else { //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�������ؾ���
			while (IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
			s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
		}
		return s;
	}

	//��������������㷨���ݹ�棩
	void travIn(BinNodePosi(K,E) x) {
		if (!x) return;
		travIn(x->lc);
		cout << x->data.first << " " << x->data.second << endl;
		travIn(x->rc);
	}

};

template<class K, class E>
class bsTree {
public:
	virtual ~bsTree() {}
	virtual bool empty() const = 0;
	// return true iff dictionary is empty
	virtual int size() const = 0;
	// return number of pairs in dictionary
	virtual BinNodePosi(K, E)& search(const K&)  = 0;
	// return pointer to matching pair
	virtual bool remove(const K&) = 0;
	// remove matching pair
	virtual BinNodePosi(K, E) insert(const pair<const K, E>&) = 0;
	// insert a (key, value) pair into the dictionary
	virtual void travIn() = 0;//ascend
	// output in ascending order of key
};



template <class K,class E>
class RedBlack:public bsTree<K,E>
{
private:
	int _size;//��ģ
	BinNodePosi(K, E) _root;//���ڵ�
	BinNodePosi(K, E) _hot;//�����С��ڵ�ĸ���

	/******************************************************************************************
	* RedBlack˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⡣��Ϊ�����������
	*    RR-1��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
	*    RR-2��3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
	******************************************************************************************/
	void solveDoubleRed(BinNodePosi(K, E) x) { //x��ǰ��Ϊ��
		if (IsRoot(*x)) //���ѣ��ݹ飩ת������������ת�ڣ������ڸ߶�Ҳ��֮����
		{
			_root->color = RB_BLACK; _root->height++; return;
		} //����x�ĸ���p�ش���
		BinNodePosi(K, E) p = x->parent; if (IsBlack(p)) return; //��pΪ�ڣ������ֹ����������
		BinNodePosi(K, E) g = p->parent; //��ȻpΪ�죬��x���游�ش��ڣ��ұ�Ϊ��ɫ
		BinNodePosi(K, E) u = uncle(x); //���£���x�常u����ɫ�ֱ���
		if (IsBlack(u)) { //uΪ��ɫ����NULL��ʱ //*DSA*/printf("  case RR-1:\n");
			if (IsLChild(*x) == IsLChild(*p)) //��x��pͬ�ࣨ��zIg-zIg��zAg-zAg������
				p->color = RB_BLACK; //p�ɺ�ת�ڣ�x���ֺ�
			else //��x��p��ࣨ��zIg-zAg��zAg-zIg������
				x->color = RB_BLACK; //x�ɺ�ת�ڣ�p���ֺ�
			g->color = RB_RED; //g�ض��ɺ�ת��
	  ///// �����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
	  ///// ����ת�󽫸��úڡ������ú죬��������Ⱦɫ��Ч�ʸ���
			BinNodePosi(K, E) gg = g->parent; //���游��great-grand parent��
			BinNodePosi(K, E) r = FromParentTo(*g) = rotateAt(x); //��������������ڵ�
			r->parent = gg; //��ԭ���游����
		}
		else { //��uΪ��ɫ //*DSA*/printf("  case RR-2:\n");
			p->color = RB_BLACK; p->height++; //p�ɺ�ת��
			u->color = RB_BLACK; u->height++; //u�ɺ�ת��
			if (!IsRoot(*g)) g->color = RB_RED; //g���Ǹ�����ת��
			solveDoubleRed(g); //��������g��������β�ݹ飬���Ż�Ϊ������ʽ��
		}
	}

	/******************************************************************************************
  * RedBlack˫�ڵ����㷨������ڵ�x�뱻������Ľڵ��Ϊ��ɫ������
  * ��Ϊ�����๲���������
  *    BB-1 ��2����ɫ��ת��2�κڸ߶ȸ��£�1~2����ת�����ٵݹ�
  *    BB-2R��2����ɫ��ת��2�κڸ߶ȸ��£�0����ת�����ٵݹ�
  *    BB-2B��1����ɫ��ת��1�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
  *    BB-3 ��2����ɫ��ת��2�κڸ߶ȸ��£�1����ת��תΪBB-1��BB2R
  ******************************************************************************************/
	void solveDoubleBlack(BinNodePosi(K, E) r) {
		BinNodePosi(K, E) p = r ? r->parent : _hot; if (!p) return; //r�ĸ���
		BinNodePosi(K, E) s = (r == p->lc) ? p->rc : p->lc; //r���ֵ�
		if (IsBlack(s)) { //�ֵ�sΪ��
			BinNodePosi(K, E) t = NULL; //s�ĺ캢�ӣ������Һ��ӽԺ죬�������ȣ��Ժ�ʱΪNULL��
			if (IsRed(s->rc)) t = s->rc; //����
			if (IsRed(s->lc)) t = s->lc; //����
			if (t) { //��s�к캢�ӣ�BB-1
			   //*DSA*/printf("  case BB-1: Child ("); print(s->lc); printf(") of BLACK sibling ("); print(s); printf(") is RED\n");
				RBColor oldColor = p->color; //����ԭ�������ڵ�p��ɫ������t���丸�ס��游
			 // ���£�ͨ����ת��ƽ�⣬���������������Һ���Ⱦ��
				BinNodePosi(K, E) b = FromParentTo(*p) = rotateAt(t); //��ת
				if (HasLChild(*b)) { b->lc->color = RB_BLACK; updateHeight(b->lc); } //����
				if (HasRChild(*b)) { b->rc->color = RB_BLACK; updateHeight(b->rc); } //����
				b->color = oldColor; updateHeight(b); //���������ڵ�̳�ԭ���ڵ����ɫ
				//*DSA*/printBinTree(b, 0, 0);
			}
			else { //��s�޺캢��
				s->color = RB_RED; s->height--; //sת��
				if (IsRed(p)) { //BB-2R
				   //*DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is RED\n"); //s���Ӿ��ڣ�p��
					p->color = RB_BLACK; //pת�ڣ����ڸ߶Ȳ���
					//*DSA*/printBinTree(p, 0, 0);
				}
				else { //BB-2B
				//*DSA*/printf("  case BB-2R: Both children ("); print(s->lc); printf(") and ("); print(s->rc); printf(") of BLACK sibling ("); print(s); printf(") are BLACK, and parent ("); print(p); printf(") is BLACK\n"); //s���Ӿ��ڣ�p��
					p->height--; //p���ֺڣ����ڸ߶��½�
					//*DSA*/printBinTree(p, 0, 0);
					solveDoubleBlack(p); //�ݹ�����
				}
			}
		}
		else { //�ֵ�sΪ�죺BB-3
		//*DSA*/printf("  case BB-3: sibling ("); print(s); printf(" is RED\n"); //s�죨˫�Ӿ�ڣ�
			s->color = RB_BLACK; p->color = RB_RED; //sת�ڣ�pת��
			BinNodePosi(K, E) t = IsLChild(*s) ? s->lc : s->rc; //ȡt���丸sͬ��
			_hot = p; FromParentTo(*p) = rotateAt(t); //��t���丸�ס��游��ƽ�����
			//*DSA*/printBinTree<T>(s, 0, 0);
			solveDoubleBlack(r); //��������r��˫�ڡ�����ʱ��p��ת�죬�ʺ���ֻ����BB-1��BB-2R
		}
	}

	//����vΪ����rbTree�в��ҹؼ���e
	BinNodePosi(K, E)& searchIn(BinNodePosi(K, E)& v, const K& key, BinNodePosi(K, E)& hot) {
		if (EQUAL(key, v)) return v; hot = v; //�˻���������������ڵ�v������
		while (1) { //һ��أ��������ϵ�
			BinNodePosi(K, E)& c = (key < hot->data.first) ? hot->lc : hot->rc; //ȷ�����뷽��
			if (EQUAL(key, c)) return c; hot = c; //���з��أ���������һ��
		} //hotʼ��ָ�����һ��ʧ�ܽڵ�
	} //����ʱ������ֵָ�����нڵ㣨������ͨ���ڱ�����hotָ���丸�ף��˻�ʱΪ��ʼֵNULL��

	//���½ڵ�x�ĸ߶�
	int updateHeight(BinNodePosi(K, E) x) { //���½ڵ�߶�
		x->height = __max(stature(x->lc), stature(x->rc)); //����һ��ڸ߶���ȣ����ǳ���˫��
		/*DSA*/// ������и��ڵ����Һ��ӵĺڸ߶�ͨ�����
		/*DSA*/// ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶�
		/*DSA*/// ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶�
		return IsBlack(x) ? x->height++ : x->height; //����ǰ�ڵ�Ϊ�ڣ����������
	} //��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�

	BinNodePosi(K, E) connect34(BinNodePosi(K, E) a, BinNodePosi(K, E) b, BinNodePosi(K, E) c, BinNodePosi(K, E) T0, BinNodePosi(K, E) T1, BinNodePosi(K, E) T2, BinNodePosi(K, E) T3) {
		//*DSA*/print(a); print(b); print(c); printf("\n");
		a->lc = T0; if (T0) T0->parent = a;
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);
		c->lc = T2; if (T2) T2->parent = c;
		c->rc = T3; if (T3) T3->parent = c; updateHeight(c);
		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(b);
		return b; //�������µĸ��ڵ�
	}

	BinNodePosi(K, E) rotateAt(BinNodePosi(K, E) v) { //vΪ�ǿ��ﱲ�ڵ�
		if (!v) {
			cout << "Fail to rotate a null node" << endl;
			exit(-1);
		}
		BinNodePosi(K, E) p = v->parent; BinNodePosi(K, E) g = p->parent; //��v��p��g���λ�÷��������
		if (IsLChild(*p)) /* zig */
			if (IsLChild(*v)) { /* zig-zig */ //*DSA*/printf("\tzIg-zIg: ");
				p->parent = g->parent; //��������
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			}
			else { /* zig-zag */  //*DSA*/printf("\tzIg-zAg: ");
				v->parent = g->parent; //��������
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		else  /* zag */
			if (IsRChild(*v)) { /* zag-zag */ //*DSA*/printf("\tzAg-zAg: ");
				p->parent = g->parent; //��������
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else { /* zag-zig */  //*DSA*/printf("\tzAg-zIg: ");
				v->parent = g->parent; //��������
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}
	}

	BinNodePosi(K, E) removeAt(BinNodePosi(K, E)& x, BinNodePosi(K, E)& hot) {
		BinNodePosi(K, E) w = x; //ʵ�ʱ�ժ���Ľڵ㣬��ֵͬx
		BinNodePosi(K, E) succ = NULL; //ʵ�ʱ�ɾ���ڵ�Ľ�����
		if (!HasLChild(*x)) //��*x��������Ϊ�գ����
			succ = x = x->rc; //ֱ�ӽ�*x�滻Ϊ��������
		else if (!HasRChild(*x)) //��������Ϊ�գ����
			succ = x = x->lc; //�ԳƵش�����ע�⣺��ʱsucc != NULL
		else { //���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
			w = w->succ(); //�����������У��ҵ�*x��ֱ�Ӻ��*w
			swap(x->data, w->data); //����*x��*w������Ԫ��
			BinNodePosi(K, E) u = w->parent;
			((u == x) ? u->rc : u->lc) = succ = w->rc; //����ڵ�*w
		}
		hot = w->parent; //��¼ʵ�ʱ�ɾ���ڵ�ĸ���
		if (succ) succ->parent = hot; //������ɾ���ڵ�Ľ�������hot����
		//release(w->data); release(w); 
		return succ; //�ͷű�ժ���ڵ㣬���ؽ�����
	} //release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ����������


public:
	RedBlack() : _size(0), _root(nullptr) {} //���캯��
	~RedBlack() {} //��������
	int size() const { return _size; } //��ģ
	bool empty() const { return !_root; } //�п�

	//����
	BinNodePosi(K, E) insert(const pair<const K, E>& e) { //��e��������
		BinNodePosi(K, E)& x = search(e.first);
		if (x) return x; //ȷ��Ŀ�겻���ڣ������_hot�����ã�
		x = new BinNode<K, E>(e, _hot, NULL, NULL, -1); _size++; //������ڵ�x����_hotΪ�����ڸ߶�-1
		BinNodePosi(K, E) xOld = x;
		solveDoubleRed(x);
		return xOld; //��˫�������󣬼��ɷ���
	} //����e�Ƿ������ԭ���У�����ʱ����x->data == e

	//ɾ��
	bool remove(const K& key) { //�Ӻ������ɾ���ؼ���e
		BinNodePosi(K, E)& x = search(key);
		if (!x) return false; //ȷ��Ŀ����ڣ�����_hot�����ã�
		BinNodePosi(K, E) r = removeAt(x, _hot);
		if (!(--_size)) return true; //ʵʩɾ��
	 // assert: _hotĳһ���Ӹձ�ɾ�����ұ�r��ָ�ڵ㣨������NULL�����档���¼���Ƿ�ʧ�⣬������Ҫ����
		if (!_hot) //���ձ�ɾ�����Ǹ��ڵ㣬�����úڣ������ºڸ߶�
		{
			_root->color = RB_BLACK; updateHeight(_root); return true;
		}
		// assert: ���£�ԭx����r���طǸ���_hot�طǿ�
		if (BlackHeightUpdated(*_hot)) return true; //���������ȵĺ������Ȼƽ�⣬���������
		if (IsRed(r)) //������rΪ�죬��ֻ������ת��
		{
			r->color = RB_BLACK; r->height++; return true;
		}
		// assert: ���£�ԭx����r����Ϊ��ɫ
		   //*DSA*/printBinTree(_hot, 0, 0);
		solveDoubleBlack(r); return true; //��˫�ڵ����󷵻�
	} //��Ŀ��ڵ�����ұ�ɾ��������true�����򷵻�false



	//����
	BinNodePosi(K, E)& search(const K& key) //��BST�в��ҹؼ���e
	{
		return searchIn(_root, key, _hot = NULL);
	} //����Ŀ��ڵ�λ�õ����ã��Ա�������롢ɾ������

	//�������
	void travIn() { if (_root) _root->travIn(_root); } //�������
};