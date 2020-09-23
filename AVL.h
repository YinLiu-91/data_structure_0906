#pragma once
#ifndef AVL_H
#define AVL_H
#define Balanced(x) (stature((x).lc)==stature((x).rc))//理想平衡条件
#define BalFac(x)(stature((x).lc)-stature((x).rc))//平衡因子
#define AvlBalanced(x)((-2<BalFac(x))&&(BalFac(x)<2))//AVL平衡条件
#include "BinNode.h"
#include "BST.h"
template<typename T> class AVL :public BST<T> {//由BST派生avl树模板类
public:
	using BST<T>::rotateAt;
	BinNodePosi(T) insert(const T& e);//插入（重写）
	bool remove(const T& e);//删除（重写）
};

/*------------------------------------------------------------------------------------
*在左，右孩子中取更高者
*在AVL平衡调整前，借此确定重构方案
*/
#define tallerChild(x)(\
stature((x)->lc)>stature((x)->rc)?(x)->lc:(/*左高*/\
stature((x)->lc)<stature((x)->rc)?(x)->rc:(/*右高*/\
IsLChild(*(x))?(x)->lc:(x)->rc/*等高：与父亲x同侧者(zIg-zig或则zag-zag*/\
)\
)\
)
template<typename T> BinNodePosi(T) AVL<T>::insert(const T& e) {//将关键码e插入AVL树中
	BinNodePosi(T)& x = search(e); if (x)return x;//确认目标节点存在
	BinNodePosi(T)xx = x = new BinNode<T>(e, this->_hot); this->_size++;//创建新节点
//此时，x的父亲_hot若增高，则其祖父有可能失衡
	for (BinNodePosi(T)g = this->_hot; g; g = g->parent) {//从x之父出发向上，逐层检查各代祖先g
		if (!AvlBalanced(*g)) {//一旦发现g失衡，则采用（3+4）算法使之平衡，并将子树
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//重新接入原树
			//auto dddd = rotateAt(tallerChild(tallerChild(g)));//重新接入原树
			//FromParentTo(*g) = ddd;
			break;
		}
		else
			updateHeight(g);//更新其高度（注意：几遍g失衡，高度亦可能增加）
	}//至多只需一次调整；若果真做过调整，则全树高度必然复原
	return xx;//返回新节点位置

}//无论e是否存在于原树中，总有AVL::insert(e)->data==e

//p200 3+4重构
/*----------------------------------------------------------------------------------
*按照3+4结构联结3个节点及其四棵子树，返回重组之后的局部子树根几点位置（即b)
*子树根节点与上层节点之间的双向联结，均需由上层调用者完成
* 可用于AVL和RedBlack的局部平衡调整
-----------------------------------------------------------------------------------*/
template<typename T> BinNodePosi(T) BST<T>::connect34(BinNodePosi(T) a, BinNodePosi(T)b, BinNodePosi(T)c, BinNodePosi(T)T0, BinNodePosi(T)T1, BinNodePosi(T)T2, BinNodePosi(T)T3)
{
	a->lc = T0; if (T0)T0->parent = a;
	a->rc = T1; if (T1)T1->parent = a; updateHeight(a);
	c->lc = T2; if (T2)T2->parent = c;
	c->rc = T3; if (T3)T3->parent = c; updateHeight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateHeight(b);
	return b;//该子树新的根节点

}
/*-------------------------------------------------------------------------------------
* BST节点转换变换统一算法（3节点+4子树），返回调整之后局部子树根节点的位置
* 注意：尽管子树根会正确指向上层节点（如果存在），单反向的联结必须由上层函数完成
---------------------------------------------------------------------------------------*/
template<typename T>BinNodePosi(T)BST<T>::rotateAt(BinNodePosi(T)v) {
	//v为非空孙辈节点
	BinNodePosi(T) p = v->parent; BinNodePosi(T)g = p->parent;//视v，p和g相对位置分四种情况
	if (IsLChild(*p))){/*zig*///应当判断为IsRChild??
	if (IsLChild(*v)) {/*zig-zig*/
		p->parent = g->parent;//向上链接，p上去
		return connect34(v, p, g, v->lc, v->rc, p->rc, p->rc);
	}
	else/*zig-zag*/
	{
		v->parent = g->parent;//向上联结
		return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
	}
	}
	else/*zag*/
	{
		if(IsRChild(*v)){/*zag-zag*/
			p->parent = g->parent;//向上联结
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}else{/*zag-zig*/
			v->parent = g->parent;//向上联结
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
	}

}
#endif