#pragma once
#include"RedBlack.h"
template <typename T> int RedBlack<T>::updateHeight ( BinNodePosi(T) x ) { //���½ڵ�߶�
   x->height = __max ( stature ( x->lc ), stature ( x->rc ) ); //����һ��ڸ߶���ȣ����ǳ���˫��
   /*DSA*/// ������и��ڵ����Һ��ӵĺڸ߶�ͨ�����
   /*DSA*/// ����֮����ȡ����ֵ���Ǳ�����ɾ���ڵ���ƽ����������У���ȷ���±�ɾ���ڵ㸸�׵ĺڸ߶�
   /*DSA*/// ����rotateAt()����ݱ�ɾ���ڵ������ߣ��߶�Сһ�����ø��ڵ�ĺڸ߶�
   return IsBlack ( x ) ? x->height++ : x->height; //����ǰ�ڵ�Ϊ�ڣ����������
} //��ͳһ����stature(NULL) = -1����height�Ⱥڸ߶���һ�����ڲ���Ӱ�쵽�����㷨�еıȽ��ж�
