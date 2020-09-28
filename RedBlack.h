#pragma once
#ifndef REDBLACK_H
#define REDBLACK_H
#include "BST.h"
template<typename T> class RedBlack:public BST<T>{//RedBlack树模板类
protected:
	void solveDoubleRed(BinNodePosi(T)x);//双红修正
	void solveDoubleBlack(BinNodePosi(T)x);//双黑修正
	int updateHeight(BinNodePosi(T) x);//更新节点x的高度
public:
	using BinTree<T>::_size;
	using BinTree<T>::_root;
	using BST<T>::_hot;
	BinNodePosi(T) insert(const T& e);//插入重写
	bool remove(const T& e);//删除（重写）
};


#define IsBlack(p)(!(p)||(RB_BLACK==(p)->color))//外部节点也视作黑节点
#define IsRed(p)(!IsBlack(p))//非黑即红
#define BlackHeightUpdated(x)(/*redblack高度更新条件*/\
(stature((x).lc)==stature((x).rc))&&\
((x).height==(IsRed(&x)?stature((x).lc):stature((x).rc)+1))\
)


//p230
template<typename T> int RedBlack<T>::updateHeight(BinNodePosi(T) x){//更新节点高度
	x->height = max(stature(x->lc), stature(x->rc));//孩子一般黑高度相等，除非出现双黑
	return IsBlack(x) ? x->height++ : x->height;//若当前节点为黑，则计入黑深度

}

template<typename T> BinNodePosi(T) RedBlack<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e); if (x)return x;//确认目标不存在
	x = new BinNode<T>(e, this->_hot, nullptr, nullptr, -1); _size++;//创建红节点：以_hot为父，黑高度-1
	solveDoubleRed(x); return x ? x : _hot->parent;//经双红修正后，即可返回
}


//p233
/*
* RedBlack 双红调整算法：解决节点x与其父亲为红色的问题，分为两大类：
* RR-1:2此颜色翻转，3次黑高度更新，1-2次旋转，不再递归
* RR-2:3次颜色翻转，3次黑高度更新，0次旋转，需要递归
*/
template<typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T)x){//x当前必须为红
if(IsRoot(*x))//若已（递归）至树根，则将其转黑，整树黑高度也随着递增
{
	this->_root->color = RB_BLACK; _root->height++; return;
}
BinNodePosi(T) p = x->parent; if (IsBlack(p))return;//若p为黑，则可终止调整。否则
BinNodePosi(T)g = p->parent;//既然p为红，则x的祖父必然存在，且为黑色
BinNodePosi(T) u = uncle(x);//以下，视x输入u的颜色分别处理
if(IsBlack(u)){//u为黑色，x保持红
	if (IsLChild(*x) == IsLChild(*p))//若x与p同侧（即zig-zig或zag-zag），则
		p->clolor = RB_BLACK;//p由红转黑，x保持红（图8.25a)
	else //若x与p异侧（即zig-zag或者zag-zig）
		x->clolor = RB_BLACK;//x由红转黑,p保持红
	g->clolor = RB_RED;//g必定由黑转红
////以上虽保证总共两次染色，但因增加了判断而得不偿失
//////////////////////////////////////////////////////////////////////////需三次染色，但效率更高
	BinNodePosi(T)gg = g->parent;//曾祖父
	BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);//调整后的子树根节点
	r->parent = gg;//与原曾祖父相连

}else {//若u为红色
	p->clolor = RB_BLACK; p->height++;//p由红转黑
	u->clolor = RB_BLACK; u->height++;//u由红转黑
	if (!IsRoot(*g))g->clolor = RB_RED;//g若非根，则转红
	solveDoubleRed(g);//继续调整（类似于尾递归，可优化为迭代形式）
}

}

#endif