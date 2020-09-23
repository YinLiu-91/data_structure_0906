#pragma once
#ifndef AVL_H
#define AVL_H
#define Balanced(x) (stature((x).lc)==stature((x).rc))//����ƽ������
#define BalFac(x)(stature((x).lc)-stature((x).rc))//ƽ������
#define AvlBalanced(x)((-2<BalFac(x))&&(BalFac(x)<2))//AVLƽ������
#include "BinNode.h"
#include "BST.h"
template<typename T> class AVL :public BST<T> {//��BST����avl��ģ����
public:
	using BST<T>::rotateAt;
	BinNodePosi(T) insert(const T& e);//���루��д��
	bool remove(const T& e);//ɾ������д��
};

/*------------------------------------------------------------------------------------
*�����Һ�����ȡ������
*��AVLƽ�����ǰ�����ȷ���ع�����
*/
#define tallerChild(x)(\
stature((x)->lc)>stature((x)->rc)?(x)->lc:(/*���*/\
stature((x)->lc)<stature((x)->rc)?(x)->rc:(/*�Ҹ�*/\
IsLChild(*(x))?(x)->lc:(x)->rc/*�ȸߣ��븸��xͬ����(zIg-zig����zag-zag*/\
)\
)\
)
template<typename T> BinNodePosi(T) AVL<T>::insert(const T& e) {//���ؼ���e����AVL����
	BinNodePosi(T)& x = search(e); if (x)return x;//ȷ��Ŀ��ڵ����
	BinNodePosi(T)xx = x = new BinNode<T>(e, this->_hot); this->_size++;//�����½ڵ�
//��ʱ��x�ĸ���_hot�����ߣ������游�п���ʧ��
	for (BinNodePosi(T)g = this->_hot; g; g = g->parent) {//��x֮���������ϣ�������������g
		if (!AvlBalanced(*g)) {//һ������gʧ�⣬����ã�3+4���㷨ʹ֮ƽ�⣬��������
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//���½���ԭ��
			//auto dddd = rotateAt(tallerChild(tallerChild(g)));//���½���ԭ��
			//FromParentTo(*g) = ddd;
			break;
		}
		else
			updateHeight(g);//������߶ȣ�ע�⣺����gʧ�⣬�߶���������ӣ�
	}//����ֻ��һ�ε�����������������������ȫ���߶ȱ�Ȼ��ԭ
	return xx;//�����½ڵ�λ��

}//����e�Ƿ������ԭ���У�����AVL::insert(e)->data==e

//p200 3+4�ع�
/*----------------------------------------------------------------------------------
*����3+4�ṹ����3���ڵ㼰���Ŀ���������������֮��ľֲ�����������λ�ã���b)
*�������ڵ����ϲ�ڵ�֮���˫�����ᣬ�������ϲ���������
* ������AVL��RedBlack�ľֲ�ƽ�����
-----------------------------------------------------------------------------------*/
template<typename T> BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T)b, BinNodePosi(T)c, BinNodePosi(T)T0, BinNodePosi(T)T1, BinNodePosi(T)T2, BinNodePosi(T)T3)
{
	a->lc = T0; if (T0)T0->parent = a;
	a->rc = T1; if (T1)T1->parent = a; updateHeight(a);
	c->lc = T2; if (T2)T2->parent = c;
	c->rc = T3; if (T3)T3->parent = c; updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateHeight(b);
	return b;//�������µĸ��ڵ�

}
/*-------------------------------------------------------------------------------------
* BST�ڵ�ת���任ͳһ�㷨��3�ڵ�+4�����������ص���֮��ֲ��������ڵ��λ��
* ע�⣺��������������ȷָ���ϲ�ڵ㣨������ڣ��������������������ϲ㺯�����
---------------------------------------------------------------------------------------*/
template<typename T>BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T)v) {
	//vΪ�ǿ��ﱲ�ڵ�
	BinNodePosi(T) p = v->parent; BinNodePosi(T)g = p->parent;//��v��p��g���λ�÷��������
	if (IsLChild(*p))){/*zig*///Ӧ���ж�ΪIsRChild??
	if (IsLChild(*v)) {/*zig-zig*/
		p->parent = g->parent;//�������ӣ�p��ȥ
		return connect34(v, p, g, v->lc, v->rc, p->rc, p->rc);
	}
	else/*zig-zag*/
	{
		v->parent = g->parent;//��������
		return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
	}
	}
	else/*zag*/
	{
		if(IsRChild(*v)){/*zag-zag*/
			p->parent = g->parent;//��������
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}else{/*zag-zig*/
			v->parent = g->parent;//��������
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}

}
#endif