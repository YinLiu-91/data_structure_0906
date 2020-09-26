#pragma once
#ifndef SPLAY_H
#define SPLAY_H
#include "BST.h"
template<typename T> class Splay:public BST<T>{//由bst派生的splay树模板类
protected:
	BinNodePosi(T)splay(BinNodePosi(T)v);//将节点v伸展至树根
public:
	using BST<T>::_root;
	using BST<T>::_hot;
	using BST<T>::_size;
	BinNodePosi(T)& search(const T& e);//查找（重写）
	BinNodePosi(T)insert(const T& e);//插入（从写）
	bool remove(const T& e);//删除（重写）
};

template<typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc) { p->lc = lc; if (lc)lc->parent = p; }

template<typename NodePosi>inline
void attachAsRChild(NodePosi p, NodePosi rc) { p->rc = rc; if (rc)rc->parent = p; }

template<typename T> //splay树伸展算法：从节点v出发逐层伸展
BinNodePosi(T)Splay<T>::splay(BinNodePosi(T)v) {
	//v为最近访问而需要伸展的节点位置
	if (!v)return nullptr; BinNodePosi(T)p; BinNodePosi(T)g;//*v的父亲与祖父
	while ((p = v->parent) && (g = p->parent)) {
		//自下而上，反复对*v做双层伸展
		BinNodePosi(T)gg = g->parent;//每轮之后，*v都以原曾祖父为父
		if(IsLChild(*v))
			if(IsLChild(*p)){//zig-zig
				attachAsLChild(g, p->rc); attachAsLChild(p, v->rc);
				attachAsRChild(p, g); attachAsRChild(v, p);
			}
			else
			{
				//zig-zag
				attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
				attachAsLChild(p, g); attachAsLChild(v, p);
			}
		else if(IsRChild(*p)){//zag-zag
			attachAsRChild(g, p->lc); attachAsLChild(p, v->lc);
			attachAsLChild(p, g); attachAsLChild(v, p);

		}
		else {
			//zag-zig
			attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
			attachAsRChild(v, g); attachAsLChild(v, p);

		}
		if (!gg)v->parent = nullptr;//若*v的原先的曾祖父不存在，则*现在应为树根
		else
			//否则*gg此后应该以*v作为左或右孩子
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		BinTree<T>::updateHeight(g); BinTree<T>::updateHeight(p); BinTree<T>::updateHeight(v);
	}//双层伸展结束，必有g==null,但p可能非空
	if(p=v->parent){//若p果真非空，则额外再做一次旋转
		if (IsLChild(*v)) { attachAsRChild(p, v->rc); attachAsRChild(v, p); }
		else { attachAsRChild(p, v->lc); attachAsLChild(v, p); }
		BinTree<T>::updateHeight(p); BinTree<T>::updateHeight(v);
	}
	v->parent = nullptr; return v;
	
}

template<typename T>
BinNodePosi(T) & Splay<T>::search(const T&e){//在伸展树中查找e
	//using BinTree<T>::_root;
	BinNodePosi(T)p = searchIn(_root, e, _hot = nullptr);
	_root = splay(p ? p : this->_hot);//将最后一个被访问的节点伸展至树根
	return _root;
	
}
template<typename T> BinNodePosi(T) Splay<T>::insert(const T& e)
{
	if (!BinTree<T>::_root) { _size++; return this->_root = new BinNode<T>(e); }//处理原树为空的退化情况
	if (e == search(e)->data)return this->_root;//确认目标节点不存在
	_size++; BinNodePosi(T)t = _root;//创建新节点。以下调整<=7个指针以完成局部重构
	if(this->_root->data<e){//插入新根，以t和t->rc为左右孩子
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t, t->rc);//2+3个
		if (HasRChild(*t)) { t->rc->parent = BinTree<T>::_root; t->rc = nullptr; }//<=2个
	}else
	{//插入新根,以t->lc和t为左，右孩子
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t->lc, t);//2+3个
		if (HasLChild(*t)) { t->lc->parent = BinTree<T>::_root; t->lc = nullptr; }//<=2个
	
	}
	BinTree<T>::updateHeightAbove(t);//更新t及其祖先（实际只有一个_root一个）的高度
	return BinTree<T>::_root;//新节点必然置于树根，返回
}
template<typename T> 
bool Splay<T>::remove(const T& e)
{
	//从伸展树中删除关键码e
	if (!BinTree<T>::_root || (e != search(e)->data))return false;//若树空或者目标不存在，则无法删除
	BinNodePosi(T) w = BinTree<T>::_root;//assert:经search（）后节点e已被伸展至树根
	if(!HasLChild(*BinTree<T>::_root)){//若无左子树，则直接删除
		BinTree<T>::_root = BinTree<T>::_root->rc; if (BinTree<T>::_root)BinTree<T>::_root->parent = nullptr;

	}else if(!HasRChild(*BinTree<T>::_root)){//若无右子树，也被直接删除
		BinTree<T>::_root = BinTree<T>::_root->lc; if (BinTree<T>::_root)BinTree<T>::_root->parent = nullptr;
	}else {//若左右子树同时存在，则
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = nullptr; _root->lc = nullptr;//暂时将左子树删除
		_root = _root->rc; _root->parent = nullptr;//只保留右子树
		search(w->data);//以原树根为目标，做一次（必定失败的）查找
		/////assert：至此，右子树中最小节点必伸展至根，且其左子树必为空，于是
		_root->lc = lTree; lTree->parent = _root;//只需将原树接回即可
	

	}
	release(w->data); release(w); _size--;//释放节点，更新规模
	if (_root)BinTree<T>::updateHeight(_root);//此后，若树非空，则树根的高度需要更新
	return true;//返回成功标志
}


#endif
