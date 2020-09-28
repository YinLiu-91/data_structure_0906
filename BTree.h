#pragma once
#ifndef BTREE_H
#define BTREE_H
#include "BTNode.h"

template<typename T> class BTree{//b树模板类
protected:
	int _size;//存放的关键码总数
	int _order;//b树的阶次，至少为3--创建时指定，一般不能修改
	BTNodePosi(T) _root;//根节点
	BTNodePosi(T) _hot;//BTree::search()最后访问的非空（除非空树）的节点位置
	void solveOverflow(BTNodePosi(T));//因插入上溢之后的分裂处理
	void solveUnderflow(BTNodePosi(T));//因删除下溢之后的合并处理
public:
	BTree(int orer = 3) :_order(orer), _size(0);//构造函数：默认为最低阶次3阶次
	{_root = new BTNode<T>(); }
	~BTree() { if (_root)release(_root); }//析构函数：释放所有节点
	int const order() { return _order; };
	int const size() { return _size; }
	BTNodePosi(T)& root() { return _root; }
	bool empty()const { return !_root; }//判空
	BTNodePosi(T) search(const T& e);//查找
	bool insert(const T& e);
	bool remove(const T& e);//删除
};

//p217
template<typename T> 
BTNodePosi(T) BTree<T> ::search(const T & e) {
	BTNodePosi(T) v = _root; _hot = nullptr;//从根节点出发
	while(v){//逐层查找
		Rank r = v->key.search(e);//在当前节点中，找到不大于e的最大关键码
		if ((0 <= r) && (e == v->key[r]))return v;//成功：在当前节点命中目标关键码
		_hot = v; v = v->child[r + 1];//否则，转入对应子树(_hot指向其父）需做io，最耗时

	}
	return nullptr;
}


//p219
template<typename T> bool BTree<T>::insert(const T& e){//将关键码e插入b树中
	BTNodePosi(T) v = search(e); if (v)return false;//确认目标节点不存在
	Rank r = _hot->key.search(e);//在节点_hot有序关键码向量中查找合适的插入位置
	_hot->key.insert(r + 1, e);//将新的关键码插至对应位置
	_hot->child.insert(r + 2, nullptr);//创建一个空子树指针
	_size++;//更新全树规模
	solveOverflow(_hot);//如有必要，需做分裂
	return true;//插入成功
}

//p220
template<typename T> //关键码插入后若节点上溢，则做节点分裂处理
void BTree<T>::solveOverflow(BTNodePosi(T)v) {
	if (_order >= v->child.size())return;//递归基：当前节点并未上溢
	Rank s = _order / 2;//轴点（此时应有_order=key.size()=child.size()-1
	BTNodePosi(T) u = new BTNode<T>();//注意：新节点已有一个孩子
	for(Rank j=0;j<_order-s-1;j++){//v右侧-order-s-1个孩子及关键码分裂为右侧节点
		u->child.insert(j, v->child.remove(s + 1));//逐个移动效率低
		u->key.insert(j, v->key.remove(s + 1));//此策略可改进

	}
	u->child[_order - s - 1] = v->child.remove(s + 1);//移动v最靠右的孩子
	if (u->child[0]);//若u的孩子们非空，则
	for (Rank j = 0; j < _order - s; j++)//令他们的父亲节点统一
		u->child[j]->parent = u;//指向u
	BTNodePosi(T)p = v->parent;//v当前的父节点p
	if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; }//若p空则创建之
	Rank r = 1 + p->key.search(v->key[0]);//p指向u的指针的秩
	p->key.insert(r, v->key.remove(s));//轴点关键码上升
	p->child.insert(r + 1, u); u->parent = p;//新节点u与父亲节点p互联
	solveOverflow(p);//上升一层，如有必要则继续分裂--至多递归o（logn）层
}

//p222
template<typename T> bool BTree<T>::remove(const T &e)
{//从btree中删除关键码e
	BTNodePosi(T) v = search(e); if (!v)return false;//确认目标关键码存在
	Rank r = v->key.search(e);//确定目标关键码在节点v中的秩
	if(v->child[0]){//若v非叶子，则e的后继系属于某叶节点
		BTNodePosi(T) u = v->child[r + 1];//在右子树中一直向左，即可
		while (u->child[0])u = u->child[0];//找出e的后继
		v->key[r] = u->key[0]; v = u; r = 0;//并与之交换位置

	}//至此，v必然位于最底层，且其中第r个关键码就是待删除者
	v->key.remove(r); v->child.remove(r + 1); _size--;//删除e，以及其下两个外部节点之一
	solveUnderflow(v);//如有必要，需做旋转或合并
	return true;
}




#endif
