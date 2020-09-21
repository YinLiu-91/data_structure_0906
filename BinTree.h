#pragma once
#ifndef BINTREE_H
#define BINTREE_H
#include "BinNode.h"
#include "Stack.h"
template<typename T>class BinTree {//二叉树模板类
protected:
	int _size; BinNodePosi(T) _root;//规模，根节点
	virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新节点x及其祖先的高度
public:
	BinTree() :_size(0), _root(nullptr) {}//构造函数
	~BinTree() { if (0 < _size)remove(_root); }//析构函数
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNodePosi(T) root()const { return _root; }//树根
	BinNodePosi(T) insertAdRoot(T const& e);//插入根节点
	BinNodePosi(T) insertAsLc(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRc(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLc(BinNodePosi(T) x, BinTree<T>*& T);//T作为左子树插入
	BinNodePosi(T) attachAsRc(BinNodePosi(T) x, BinTree<T>*& T);//T作为右子树插入
	int remove(BinNodePosi(T) x);//删除以位置节点x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x);//将子树x从当前树中摘除，并将其转换为一棵独立子树
	template<typename VST>
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }//层次遍历
	template<typename VST>//操作器
	void travPre(VST& visit) { if (_root)_root->travPre(visit); }//先序遍历
	template<typename VST>//操作器
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }//中序遍历
	template<typename VST>//操作器
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }//中序遍历
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) {
		return _root && t._root && (_root == t._root);
	}
};
template<typename T>int BinTree<T>::updateHeight(BinNodePosi(T) x)//更新节点x的高度
{
	return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}
template<typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)//更新高度
{
	while (x) { updateHeight(x); x = x->height; }
}
template<typename T> BinNodePosi(T) BinTree<T>::insertAdRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);
}//将e当做根节点插入空的二叉树
template<typename T> BinNodePosi(T) BinTree<T>::insertAsLc(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}//e作为x的左孩子

template<typename T> BinNodePosi(T) BinTree<T>::insertAsRc(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e);
	updateHeightAbove(x); return x->rc;
}

template<typename T>//二叉树子树接入算法：将s当做节点x的左子树插入，s本身为空
BinNodePosi(T) BinTree<T>::attachAsLc(BinNodePosi(T) x, BinTree<T>*& S) {
	if (x->lc = S->_root)x->lc->parent = x;//接入
	_size += S->_size; updateHeightAbove(x);//更新全树规模与x所有祖先的高度
	S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;//释放原树，返回接入位置
}
template<typename T>//二叉树接入算法：将S当做节点x的右子树插入，S本身置空
BinNodePosi(T) BinTree<T>::attachAsRc(BinNodePosi(T) x, BinTree<T>*& S) {
	if (x->rc = S->_root)x->rc->parent = x;//接入
	_size += S->_size; updateHeightAbove(x);//更新全树规模与x所有祖先的高度
	S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;//释放原树，返回接入位置
}
//p123
template<typename T>//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
int BinTree<T>::remove(BinNodePosi(T)x) {//
	FromParentTo(*x) = nullptr;//切断来自父节点的指针
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x); _size - n = n; return n;
}
template<typename T>//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi(T)x) {
	if (!x)return 0;//递归基,空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//递归释放左右子树
	release(x->data); release(x); return n;//释放被摘除节点，并返回删除节点总数
}

//p124先序遍历
template<typename T, typename VST>//元素类型，操作器
void travPre_R(BinNodePosi(T) x, VST& visit) {//二叉树先序遍历算法（递归版)
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

//后序遍历
template<typename T, typename VST>//元素类型，操作器
void travPost_R(BinNodePosi(T)x, VST& visit) {
	if (!x)return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

//中序遍历
template<typename T, typename VST>
void travIn_R(BinNodePosi(T)x, VST& visit) {
	if (!x)return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

//p127//迭代版先序遍历方法
template<typename T, typename VST>//元素类型，操作器
static void visitAlongLeftBranch(BinNodePosi(T)x, VST& visit, Stack<BinNodePosi(T)>& S) {
	while (x) {
		visit(x->data);//访问当前节点
		S.push(x->rc);//右孩子入栈暂存
		x = x->lc;//沿左侧深入一支
	}
}

template<typename T, typename VST>//元素类型，操作器
void travPre_I2(BinNodePosi(T)x, VST& visit) {
	//迭代版先序
	Stack<BinNodePosi(T)>S;//辅助栈
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.empty())break;
		x = S.pop();//弹出下一批的起点
	}
}

//迭代版中序遍历
//p128
template<typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x) { S.push(x); x = x->lc; }//当前节点入栈后随即向左侧深入，迭代到直到无左孩子

}
template<typename T, typename VST> //元素类型，操作器
void travIn_I1(BinNodePosi(T)x, VST& visit) {
	//二叉树中序遍历方法
	Stack<BinNodePosi(T)>S;//辅助栈
	while (true) {
		goAlongLeftBranch(x, S);//从当前节点出发，逐批入栈
		if (S.empty())break;
		x = S.pop(); visit(x->data);//弹出栈顶节点并访问
		x = x->rc;//转向右子树


	}
}

//
template<typename	 T>BinNodePosi(T)BinNode<T>::succ() {//定位节点v的直接后继
	BinNodePosi(T) s = this;//记录后继的临时变量
	if (rc) {//若有右孩子，则直接后继必在右子树
		s = rc;//右子树
		while (HasLChild(*s))s = s->lc;//最靠左（最小的节点)
	}
	else {
		//否则，直接后继是“将当前节点包含于其左子树中的最低祖先”
		while (IsRChild(*s))s = s->parent;//逆向的沿右向分支，不断朝左上方移动
		s = s->parent;//最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}
//p130
template<typename T, typename VST> //元素类型，操作器
void travIn_I2(BinNodePosi(T)x, VST& visit) {
	//二叉树中序遍历方法
	Stack<BinNodePosi(T)>S;//辅助栈
	while (true) {
		if (x) {
			S.push(x);//根节点入栈
			x = x->lc;//深入遍历左子树
		}
		else if (!S.empty()) {
			x = S.pop();//尚未访问的最低祖先
			visit(x->data);
			x = x->rc;//遍历祖先的右子树
		}
		else
			break;
	}

}


template<typename T,typename VST>//元素类型，操作器
void travIn_I3(BinNodePosi(T)x,VST&visit){//二叉树中序遍历算法
	bool backtrack = false;//前一步是否刚从右子树回溯--省去栈，进o(1)辅助空间
	while (true)
		if (!backtrack && HasLChild(*x))//若有左子树且不是刚刚回溯，则
			x = x->lc;//深入遍历左子树
		else {
			//否则，无左子树或刚刚回溯（相当于无左子树)
			visit(x->data);
			if (HasRChild(*x)) {
				x = x->rc;//深入右子树继续遍历
				backtrack = false;
			}
			else {
				if (!(x = x->succ()))break;//回溯
				backtrack = true;
			}
		}
}

//p132
template<typename T>//在以S栈顶节点为根的子树中，找到最左侧可见叶节点
static void gotoHLVFL(Stack<BinNodePosi(T)>&S){//沿途所遇节点依次入栈
while(BinNodePosi(T)x=S.top())//自顶而下，反复检查当前节点
if(HasLChild(*x)){//可能向左
	if (HasRChild(*x))S.push(x->rc);//若有右孩子，优先入栈
	S.push(x->lc);//然后左孩子入栈
}
else//实不得已
S.push(x->rc);//才向右
S.pop();//返回之前，弹出栈顶的空节点
}

template<typename T,typename VST>
void travPost_I(BinNodePosi(T)x,VST&visit){//二叉树的后序遍历
	Stack<BinNodePosi(T)>S;//辅助栈
	if (x)S.push(x);
	while (!S.empty()) {
		if (S.top != x->parent)//若栈顶非当前节点支付（则必为其右兄），此时需
			gotoHLVFL(S);//在以其右兄为根之子树中，站到HLVFL（相当于递归的深入）
		x = S.pop(); visit(x->data);//弹出栈顶（即前一节点之后继），并访问
	}
}

//p134层次遍历
#include "Queue.h"
template<typename T>template<typename VST>//元素类型，操作器
void BinNode<T>::travLevel(VST& visit){//二叉树层次遍历
	Queue<BinNodePosi(T)>Q;//辅助队列
	Q.enqueue(this);//根节点入队
	while(!Q.empty()){//在队列再次变空前，反复迭代
		BinNodePosi(T) x = Q.dequeue(); visit(x->data);//取出队首节点并访问
		if (HasLChild(*x))Q.enqueue(x->lc);//左孩子入队
		if (HasRChild(*x))Q.enqueue(x->rc);//右孩子入队
	}
}

//子树分离
template<typename T>//二叉树子树分离算法：将子树x从当前树中摘除，将其封装为一个独立子树返回
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;//切断来自父亲的指针
	updateHeightAbove(x->parent);//更新原树中所有祖先的高度
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = nullptr;//新树以x为根
	S->_size = x->size(); _size -= S->_size; return S;
}





#endif

