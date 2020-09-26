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
#endif
