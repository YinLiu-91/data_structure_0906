#pragma once
typedef int Rank;//秩
#define  ListNodePosi(T) ListNode<T>*//列表节点位置

template<typename T>struct ListNode
{
	//成员
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;//数值，前驱，后继
	//构造函数
	ListNode(){}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {}//默认构造函数
	//操作接口
	ListNodePosi(T) insertAsPred(T const& e);//紧靠当前节点之前插入新节点
	ListNodePosi(T) insertAsSucc(T const& e);//紧靠当前节点之后插入新节点

};





