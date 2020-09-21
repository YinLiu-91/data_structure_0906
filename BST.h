#pragma once
#ifndef BST_H
#define BST_H
#include "release.h"
#include "BinTree.h"

template<typename T>
class BST :public BinTree<T> {
	//由bintree派生BST模板类
protected:
	BinNodePosi(T) _hot;//命中节点的父亲
	BinNodePosi(T) connect34(//按照“3+4”结构，联结3个节点及四棵子树
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T)rotateAt(BinNodePosi(T) x);//对x及其父亲，祖父做统一旋转
public:
	//基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
	virtual BinNodePosi(T)& search(const T& e);//查找
	virtual BinNodePosi(T) insert(const T& e);//插入
	virtual bool remove(const T& e);//删除
};

template<typename T>//在以v为根的BST子树中查找关键码
static BinNodePosi(T) & searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data))return v;//递归基：在节点v（或假想的通配节点）处命中
	hot = v;//一般情况：先记下当前节点，然后再
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);//深入一层，递归查找

}
template<typename T> BinNodePosi(T)& BST<T>::search(const T& e)
{
	return searchIn(this->_root, e, _hot = nullptr);
}
template<typename T> BinNodePosi(T) BST<T>::insert(const T& e) {
	BinNodePosi(T)& x = search(e); if (x)return  x;//确认目标不存在
	x = new BinNode<T>(e, _hot);//创建新节点：以e为关键码，以_hot为父
	this->_size;//更新全树规模
	updateHeightAbove(x);//更新x及其历代祖先高度
	return x;
}
template<typename T> bool BST<T>::remove(const T& e) {
	//从BST树中删除关键码e
	BinNodePosi(T)& x = search(e); if (!x)return false;//确认目标存在
	removeAt(x, _hot); this->_size--;//实施删除
	updateHeightAbove(_hot);//更新_hot及其历代祖先的高度
	return true;
}
template<typename T>static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = x;//实施被摘除的节点,初值同x
	BinNodePosi(T) succ = nullptr;//实际被删除节点的接替者
	if (!HasLChild(*x))//若*x的左子树为空，则可
		succ = x = x->rc;//直接将*x替换为其右子树
	else if (!HasRChild(*x))//若右子树为空，则
		succ = x = x->lc;//对称的处理，注意：此时succ!=null;
	else {//若左右子树均存在，则选择x的直接后继作为实际被摘除节点，为此需要
		w = w->succ();//（在右子树中）找到*x的直接后继*w
		swap(x->data, w->data);//交换*x和*w的数据元素
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;//隔离节点*w
	}
	hot = w->parent;//记录实际被删除节点的
	if (succ)succ->parent = hot;//并将被删除节点的接替者与hot相连
	release(w->data); release(w); return succ;//释放被摘除节点，返回接替者

}
#endif