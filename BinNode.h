#pragma once
#ifndef BINNODE_H
#define  BINNODE_H
#define  BinNodePosi(T) BinNode<T>*//�ڵ�λ��
#define stature(p) ((p)?(p)->height:-1)//�ڵ�߶ȣ�������߶�Ϊ-1��Լ����ͳһ
typedef enum{ RB_RED,RB_BLACK }RBColor;//�ڵ���ɫ

#include "BinNode_macro_Basic.h"



template<typename T> struct BinNode{//�������ڵ�ģ����
	T data;//��ֵ
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;//���ڵ㼰���Һ���
	int height;//�߶ȣ�ͨ�ã�
	int npl;// null path length����ʽ�ѣ�Ҳ��ֱ����height����
	RBColor clolor;//��ɫ���������
	//���캯��
	BinNode() :parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), clolor(RB_RED) {}
	BinNode(T e, BinNodePosi(T)p = nullptr, BinNodePosi(T)lc = nullptr, BinNodePosi(T)rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), clolor(c) {}
	//�����ӿ�
	int size();//ͬ�쵱ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNodePosi(T) insertAsLC(T const&);//��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi(T) insertAsRC(T const&);//��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T)succ();//ȡ��ǰ�ڵ��ֱ�Ӻ��
	template<typename VST>void travLevel(VST&);//������α���
	template<typename VST>void travPre(VST&);//�����������
	template<typename VST>void travIn(VST&);//�����������
	template<typename VST>void travPost(VST&);//�����������
	//�Ƚ������е�����������һ��������油�䣩
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }//����

	

};

template<typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);//��e��Ϊ��ǰ�ڵ�����Ӳ��������
}
template<typename T>BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);//��e������ǰ�ڵ���Һ��Ӳ��������
}

template<typename T> template<typename VST>//Ԫ�����ͣ�������
void BinNode<T>::travIn(VST& visit){//�������������ͳһ���
	switch (rand()%5 )
	{
	case 1:travIn_I1(this, visit);
	break;
	case 2:travIn_I2(this, visit);break;
	case 3:travIn_I3(this, visit); break;
	case 4:travIn_I4(this, visit); break;
	default:
		travIn_R(this, visit);
		break;
	}
}




#endif
