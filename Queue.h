#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include "List.h"
template<typename T>class Queue :public List<T>
{
	//队列模板类
	using List<T>::insertAsLast;
	using List<T>::remove;
	using List<T>::first;
public:
	void enqueue(T const& e) { insertAsLast(e); }//入队
	T dequeue() { return remove(first()); }//出队，首部删除
	T& front() { return first()->data; }
};


#endif
