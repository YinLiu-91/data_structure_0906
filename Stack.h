#pragma once
#ifndef STACK_H
#define STACK_H
#include "Vector.h"
template<typename T> class Stack :public Vector<T> {
	//����������/ĩ����Ϊջ��/��
public:
	
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); }//��ջ�����ڽ���Ԫ����Ϊ������ĩβԪ�ز���
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }
	T& top() { return (*this)[Vector<T>::size() - 1]; }//ȡ����ֱ�ӷ���������ĩԪ��
};
#endif