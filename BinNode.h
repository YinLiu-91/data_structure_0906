#pragma once
#ifdef BINNODE_H
#define  BINNODE_H
#define  BinNodePosi(T) BinNode<T>*//节点位置
#define stature(p) ((p)?(p)->height:-1)//节点高度（与空树高度为-1的约定相统一
typedef emun{ RB_RED,RB_BLACK }RBColor;//节点颜色

//binnode 状态与性质判断
#define IsRoot(x)		(!((x).parent))
#define IsLChild(x)		(!IsRoot(x)&&(&(x)==(x).parent->lc))
#define IsRChild(x)		(!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x)	(!IsRoot(x))
#define HasLChild(x)	((x).lc)
#define HasRChild(x)	((x).rc)
#define HasCHild(x)		(HasLChild(x)||HasRChild(x))//至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))//同时拥有两个孩子
#define IsLeaf(x)(!HasCHild(x))


//与binnose具有特定关系的节点及指针

#define sibling(p)/*兄弟*/
(IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)

#define uncle(x)/*叔叔*/
(IsLChild(*((x)->parent))?(x)->parent->rc:(x)->parent->parent-lc)

#define  FromParentTo(x)/*来自父亲的引用*/\
(IsRoot(x)?_root:(IsLChild(x)?(x).parent->lc:(x).parent->rc))



template<typename T> struct BinNode{//二叉树节点模板类
	T data;//数值
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc;//父节点及左，右孩子
	int height;//高度（通用）
	int npl;// null path length（左式堆，也可直接用height代替
	RBColor clolor;//颜色（红黑树）
	//构造函数
	BinNode() :parent(nullptr), lc(nullptr), rc(nullptr), height(0), npl(1), clolor(RB_RED) {}
	BinNode(T e, BinNodePosi(T)p = nullptr, BinNodePosi(T)lc = nullptr, BinNodePosi(T)rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), clolor(c) {}
	//操作接口
	int size();//同届当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi(T) insertAsLC(T cont&);//作为当前节点的左孩子插入新节点
	BinNodePosi(T) insertAsRC(T const&);//作为当前节点的右孩子插入新节点
	BinNodePosi(T)succ();//取当前节点的直接后继
	template<typename VST>void travLevel(VST&);//子树层次遍历
	template<typename VST>void travPre(VST&);//子树先序遍历
	template<typename VST>void travIn(VST&);//子树中序遍历
	template<typename VST>void travPost(VST&);//子树后序遍历
	//比较器，判等器（各列其一，其余后面补充）
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }//等于

	

};

template<typename T> BinNodePosi(T) BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this);//将e作为当前节点的左孩子插入二叉树
}
template<typename T>BinNodePosi(T) BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this);//将e当做当前节点的右孩子插入二叉树
}

template<typename T> template<typename VST>//元素类型，操作器
void BinNode<T>::travIn(VST& visit){//二叉树中序遍历统一入口
	switch (rand()%5 )
	{
	case 1:travIn_I1(this, visit);
	break;
	case 2:travIn_I2(this, visit);break;
	case 3:travIn_I3(this, visit); break;
	case 4:travIn_I4(this, visit); break;
	default:
		travIn_R(this, visit);
		break;
	}
}

//子树分离
template<typename T>//二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一个独立子树返回
BinTree<T>*BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;//切断来自父亲的指针
	updateHeightAbove(x->parent);//更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = nullptr;//新树以x为根
	S->_size = x->size(); _size -= S->_size; return S;
}


#endif
