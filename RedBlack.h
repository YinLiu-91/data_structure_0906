#pragma once
#ifndef REDBLACK_H
#define REDBLACK_H
#include "BST.h"
template<typename T> class RedBlack:public BST<T>{//RedBlack��ģ����
protected:
	void solveDoubleRed(BinNodePosi(T)x);//˫������
	void solveDoubleBlack(BinNodePosi(T)x);//˫������
	int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
public:
	using BinTree<T>::_size;
	using BinTree<T>::_root;
	using BST<T>::_hot;
	BinNodePosi(T) insert(const T& e);//������д
	bool remove(const T& e);//ɾ������д��
};


#define IsBlack(p)(!(p)||(RB_BLACK==(p)->color))//�ⲿ�ڵ�Ҳ�����ڽڵ�
#define IsRed(p)(!IsBlack(p))//�Ǻڼ���
#define BlackHeightUpdated(x)(/*redblack�߶ȸ�������*/\
(stature((x).lc)==stature((x).rc))&&\
((x).height==(IsRed(&x)?stature((x).lc):stature((x).rc)+1))\
)


//p230
template<typename T> int RedBlack<T>::updateHeight(BinNodePosi(T) x){//���½ڵ�߶�
	x->height = max(stature(x->lc), stature(x->rc));//����һ��ڸ߶���ȣ����ǳ���˫��
	return IsBlack(x) ? x->height++ : x->height;//����ǰ�ڵ�Ϊ�ڣ����������

}

template<typename T> BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e); if (x)return x;//ȷ��Ŀ�겻����
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); _size++;//������ڵ㣺��_hotΪ�����ڸ߶�-1
	solveDoubleRed(x); return x ? x : _hot->parent;//��˫�������󣬼��ɷ���
}


//p233
/*
* RedBlack ˫������㷨������ڵ�x���丸��Ϊ��ɫ�����⣬��Ϊ�����ࣺ
* RR-1:2����ɫ��ת��3�κڸ߶ȸ��£�1-2����ת�����ٵݹ�
* RR-2:3����ɫ��ת��3�κڸ߶ȸ��£�0����ת����Ҫ�ݹ�
*/
template<typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T)x){//x��ǰ����Ϊ��
if(IsRoot(*x))//���ѣ��ݹ飩������������ת�ڣ������ڸ߶�Ҳ���ŵ���
{
	this->_root->color = RB_BLACK; _root->height++; return;
}
BinNodePosi(T) p = x->parent; if (IsBlack(p))return;//��pΪ�ڣ������ֹ����������
BinNodePosi(T)g = p->parent;//��ȻpΪ�죬��x���游��Ȼ���ڣ���Ϊ��ɫ
BinNodePosi(T) u = uncle(x);//���£���x����u����ɫ�ֱ���
if(IsBlack(u)){//uΪ��ɫ��x���ֺ�
	if (IsLChild(*x) == IsLChild(*p))//��x��pͬ�ࣨ��zig-zig��zag-zag������
		p->clolor = RB_BLACK;//p�ɺ�ת�ڣ�x���ֺ죨ͼ8.25a)
	else //��x��p��ࣨ��zig-zag����zag-zig��
		x->clolor = RB_BLACK;//x�ɺ�ת��,p���ֺ�
	g->clolor = RB_RED;//g�ض��ɺ�ת��
////�����䱣֤�ܹ�����Ⱦɫ�������������ж϶��ò���ʧ
//////////////////////////////////////////////////////////////////////////������Ⱦɫ����Ч�ʸ���
	BinNodePosi(T)gg = g->parent;//���游
	BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);//��������������ڵ�
	r->parent = gg;//��ԭ���游����

}else {//��uΪ��ɫ
	p->clolor = RB_BLACK; p->height++;//p�ɺ�ת��
	u->clolor = RB_BLACK; u->height++;//u�ɺ�ת��
	if (!IsRoot(*g))g->clolor = RB_RED;//g���Ǹ�����ת��
	solveDoubleRed(g);//����������������β�ݹ飬���Ż�Ϊ������ʽ��
}

}

#endif