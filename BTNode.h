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
};
#endif
