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

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;//设置正向链
	return x;
}
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);//确定了x的前驱与后继即： <-x->
	succ->pred = x; succ = x;//设置逆向链接,即x前驱的后继，以及后继的前驱即： ->x<-
	//这样双向链表即告完成
	return x;
}



