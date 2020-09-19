#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"
template<typename T>class Queue :public List<T>
{
	//����ģ����
	using List<T>::insertAsLast;
	using List<T>::remove;
	using List<T>::first;
public:
	void enqueue(T const& e) { insertAsLast(e); }//���
	T dequeue() { return remove(first()); }//���ӣ��ײ�ɾ��
	T& front() { return first()->data; }
};


#endif
