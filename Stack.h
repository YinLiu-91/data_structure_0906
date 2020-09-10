#pragma once
#ifndef STACK_H
#define STACK_H
#include "Vector.h"
template<typename T> class Stack :public Vector<T> {
	//将向量的首/末端作为栈底/顶
public:
	
	void push(T const& e) { Vector<T>::insert(Vector<T>::size(), e); }//入栈：等于将新元素作为向量的末尾元素插入
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); }
	T& top() { return (*this)[Vector<T>::size() - 1]; }//取顶：直接返回向量的末元素
};
#endif