#pragma once
#ifndef BTNODE_H
#define BTNODE_H
#include "Vector.h"
#define BTNodePosi(T) BTNode<T>* //b���ڵ�λ��

template<typename T> struct BTNode{//b���ڵ�ģ����
//��Ա��Ϊ���������ͳһ����
	BTNodePosi(T) parent;//���ڵ�
	Vector<T> key;//�ؼ�������
	Vector<BTNodePosi(T)>child;//��������(�䳤���ܱ�key��һ��
	//���캯����ע�⣺btnodeֻ����Ϊ���ڵ㴴�������ҳ�ʼʱ��0���ؼ����1���պ���ָ��
	BTNode() { parent = nullptr; child.insert(0, nullptr); }
	BTNode(T e, BTNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr) {
		parent = nullptr;//��Ϊ���ڵ㣬���ҳ�ʼʱ
		key.insert(0, e);//ֻ��һ���ؼ��룬�Լ�
		child.insert(0, lc); child.insert(1, rc);//��������
		if (lc)lc->parent = this; if (rc)rc->parent = this;
	}
};
#endif
