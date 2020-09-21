#pragma once
#ifndef BINTREE_H
#define BINTREE_H
#include "BinNode.h"
#include "Stack.h"
template<typename T>class BinTree {//������ģ����
protected:
	int _size; BinNodePosi(T) _root;//��ģ�����ڵ�
	virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�������ȵĸ߶�
public:
	BinTree() :_size(0), _root(nullptr) {}//���캯��
	~BinTree() { if (0 < _size)remove(_root); }//��������
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNodePosi(T) root()const { return _root; }//����
	BinNodePosi(T) insertAdRoot(T const& e);//������ڵ�
	BinNodePosi(T) insertAsLc(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRc(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLc(BinNodePosi(T) x, BinTree<T>*& T);//T��Ϊ����������
	BinNodePosi(T) attachAsRc(BinNodePosi(T) x, BinTree<T>*& T);//T��Ϊ����������
	int remove(BinNodePosi(T) x);//ɾ����λ�ýڵ�x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x);//������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
	template<typename VST>
	void travLevel(VST& visit) { if (_root)_root->travLevel(visit); }//��α���
	template<typename VST>//������
	void travPre(VST& visit) { if (_root)_root->travPre(visit); }//�������
	template<typename VST>//������
	void travIn(VST& visit) { if (_root)_root->travIn(visit); }//�������
	template<typename VST>//������
	void travPost(VST& visit) { if (_root)_root->travPost(visit); }//�������
	bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root); }
	bool operator==(BinTree<T> const& t) {
		return _root && t._root && (_root == t._root);
	}
};
template<typename T>int BinTree<T>::updateHeight(BinNodePosi(T) x)//���½ڵ�x�ĸ߶�
{
	return x->height = 1 + std::max(stature(x->lc), stature(x->rc));
}
template<typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)//���¸߶�
{
	while (x) { updateHeight(x); x = x->height; }
}
template<typename T> BinNodePosi(T) BinTree<T>::insertAdRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);
}//��e�������ڵ����յĶ�����
template<typename T> BinNodePosi(T) BinTree<T>::insertAsLc(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;
}//e��Ϊx������

template<typename T> BinNodePosi(T) BinTree<T>::insertAsRc(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e);
	updateHeightAbove(x); return x->rc;
}

template<typename T>//���������������㷨����s�����ڵ�x�����������룬s����Ϊ��
BinNodePosi(T) BinTree<T>::attachAsLc(BinNodePosi(T) x, BinTree<T>*& S) {
	if (x->lc = S->_root)x->lc->parent = x;//����
	_size += S->_size; updateHeightAbove(x);//����ȫ����ģ��x�������ȵĸ߶�
	S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;//�ͷ�ԭ�������ؽ���λ��
}
template<typename T>//�����������㷨����S�����ڵ�x�����������룬S�����ÿ�
BinNodePosi(T) BinTree<T>::attachAsRc(BinNodePosi(T) x, BinTree<T>*& S) {
	if (x->rc = S->_root)x->rc->parent = x;//����
	_size += S->_size; updateHeightAbove(x);//����ȫ����ģ��x�������ȵĸ߶�
	S->_root = nullptr; S->_size = 0; release(S); S = nullptr; return x;//�ͷ�ԭ�������ؽ���λ��
}
//p123
template<typename T>//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
int BinTree<T>::remove(BinNodePosi(T)x) {//
	FromParentTo(*x) = nullptr;//�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent);//�������ȸ߶�
	int n = removeAt(x); _size - n = n; return n;
}
template<typename T>//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static int removeAt(BinNodePosi(T)x) {
	if (!x)return 0;//�ݹ��,����
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//�ݹ��ͷ���������
	release(x->data); release(x); return n;//�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
}

//p124�������
template<typename T, typename VST>//Ԫ�����ͣ�������
void travPre_R(BinNodePosi(T) x, VST& visit) {//��������������㷨���ݹ��)
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

//�������
template<typename T, typename VST>//Ԫ�����ͣ�������
void travPost_R(BinNodePosi(T)x, VST& visit) {
	if (!x)return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

//�������
template<typename T, typename VST>
void travIn_R(BinNodePosi(T)x, VST& visit) {
	if (!x)return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

//p127//�����������������
template<typename T, typename VST>//Ԫ�����ͣ�������
static void visitAlongLeftBranch(BinNodePosi(T)x, VST& visit, Stack<BinNodePosi(T)>& S) {
	while (x) {
		visit(x->data);//���ʵ�ǰ�ڵ�
		S.push(x->rc);//�Һ�����ջ�ݴ�
		x = x->lc;//���������һ֧
	}
}

template<typename T, typename VST>//Ԫ�����ͣ�������
void travPre_I2(BinNodePosi(T)x, VST& visit) {
	//����������
	Stack<BinNodePosi(T)>S;//����ջ
	while (true) {
		visitAlongLeftBranch(x, visit, S);
		if (S.empty())break;
		x = S.pop();//������һ�������
	}
}

//�������������
//p128
template<typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)>& S) {
	while (x) { S.push(x); x = x->lc; }//��ǰ�ڵ���ջ���漴��������룬������ֱ��������

}
template<typename T, typename VST> //Ԫ�����ͣ�������
void travIn_I1(BinNodePosi(T)x, VST& visit) {
	//�����������������
	Stack<BinNodePosi(T)>S;//����ջ
	while (true) {
		goAlongLeftBranch(x, S);//�ӵ�ǰ�ڵ������������ջ
		if (S.empty())break;
		x = S.pop(); visit(x->data);//����ջ���ڵ㲢����
		x = x->rc;//ת��������


	}
}

//
template<typename	 T>BinNodePosi(T)BinNode<T>::succ() {//��λ�ڵ�v��ֱ�Ӻ��
	BinNodePosi(T) s = this;//��¼��̵���ʱ����
	if (rc) {//�����Һ��ӣ���ֱ�Ӻ�̱���������
		s = rc;//������
		while (HasLChild(*s))s = s->lc;//�����С�Ľڵ�)
	}
	else {
		//����ֱ�Ӻ���ǡ�����ǰ�ڵ���������������е�������ȡ�
		while (IsRChild(*s))s = s->parent;//������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent;//����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}
//p130
template<typename T, typename VST> //Ԫ�����ͣ�������
void travIn_I2(BinNodePosi(T)x, VST& visit) {
	//�����������������
	Stack<BinNodePosi(T)>S;//����ջ
	while (true) {
		if (x) {
			S.push(x);//���ڵ���ջ
			x = x->lc;//�������������
		}
		else if (!S.empty()) {
			x = S.pop();//��δ���ʵ��������
			visit(x->data);
			x = x->rc;//�������ȵ�������
		}
		else
			break;
	}

}


template<typename T,typename VST>//Ԫ�����ͣ�������
void travIn_I3(BinNodePosi(T)x,VST&visit){//��������������㷨
	bool backtrack = false;//ǰһ���Ƿ�մ�����������--ʡȥջ����o(1)�����ռ�
	while (true)
		if (!backtrack && HasLChild(*x))//�����������Ҳ��Ǹոջ��ݣ���
			x = x->lc;//�������������
		else {
			//��������������ոջ��ݣ��൱����������)
			visit(x->data);
			if (HasRChild(*x)) {
				x = x->rc;//������������������
				backtrack = false;
			}
			else {
				if (!(x = x->succ()))break;//����
				backtrack = true;
			}
		}
}

//p132
template<typename T>//����Sջ���ڵ�Ϊ���������У��ҵ������ɼ�Ҷ�ڵ�
static void gotoHLVFL(Stack<BinNodePosi(T)>&S){//��;�����ڵ�������ջ
while(BinNodePosi(T)x=S.top())//�Զ����£�������鵱ǰ�ڵ�
if(HasLChild(*x)){//��������
	if (HasRChild(*x))S.push(x->rc);//�����Һ��ӣ�������ջ
	S.push(x->lc);//Ȼ��������ջ
}
else//ʵ������
S.push(x->rc);//������
S.pop();//����֮ǰ������ջ���Ŀսڵ�
}

template<typename T,typename VST>
void travPost_I(BinNodePosi(T)x,VST&visit){//�������ĺ������
	Stack<BinNodePosi(T)>S;//����ջ
	if (x)S.push(x);
	while (!S.empty()) {
		if (S.top != x->parent)//��ջ���ǵ�ǰ�ڵ�֧�������Ϊ�����֣�����ʱ��
			gotoHLVFL(S);//����������Ϊ��֮�����У�վ��HLVFL���൱�ڵݹ�����룩
		x = S.pop(); visit(x->data);//����ջ������ǰһ�ڵ�֮��̣���������
	}
}

//p134��α���
#include "Queue.h"
template<typename T>template<typename VST>//Ԫ�����ͣ�������
void BinNode<T>::travLevel(VST& visit){//��������α���
	Queue<BinNodePosi(T)>Q;//��������
	Q.enqueue(this);//���ڵ����
	while(!Q.empty()){//�ڶ����ٴα��ǰ����������
		BinNodePosi(T) x = Q.dequeue(); visit(x->data);//ȡ�����׽ڵ㲢����
		if (HasLChild(*x))Q.enqueue(x->lc);//�������
		if (HasRChild(*x))Q.enqueue(x->rc);//�Һ������
	}
}

//��������
template<typename T>//���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ��������������
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x)
{
	FromParentTo(*x) = nullptr;//�ж����Ը��׵�ָ��
	updateHeightAbove(x->parent);//����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = nullptr;//������xΪ��
	S->_size = x->size(); _size -= S->_size; return S;
}





#endif

