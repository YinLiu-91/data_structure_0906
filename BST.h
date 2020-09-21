#pragma once
#ifndef BST_H
#define BST_H
#include "release.h"
#include "BinTree.h"

template<typename T>
class BST :public BinTree<T> {
	//��bintree����BSTģ����
protected:
	BinNodePosi(T) _hot;//���нڵ�ĸ���
	BinNodePosi(T) connect34(//���ա�3+4���ṹ������3���ڵ㼰�Ŀ�����
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T)rotateAt(BinNodePosi(T) x);//��x���丸�ף��游��ͳһ��ת
public:
	//�����ӿڣ���virtual���Σ�ǿ��Ҫ�����������ࣨBST���֣����ݸ��ԵĹ��������д
	virtual BinNodePosi(T)& search(const T& e);//����
	virtual BinNodePosi(T) insert(const T& e);//����
	virtual bool remove(const T& e);//ɾ��
};

template<typename T>//����vΪ����BST�����в��ҹؼ���
static BinNodePosi(T) & searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot) {
	if (!v || (e == v->data))return v;//�ݹ�����ڽڵ�v��������ͨ��ڵ㣩������
	hot = v;//һ��������ȼ��µ�ǰ�ڵ㣬Ȼ����
	return searchIn(((e < v->data) ? v->lc : v->rc), e, hot);//����һ�㣬�ݹ����

}
template<typename T> BinNodePosi(T)& BST<T>::search(const T& e)
{
	return searchIn(this->_root, e, _hot = nullptr);
}
template<typename T> BinNodePosi(T) BST<T>::insert(const T& e) {
	BinNodePosi(T)& x = search(e); if (x)return  x;//ȷ��Ŀ�겻����
	x = new BinNode<T>(e, _hot);//�����½ڵ㣺��eΪ�ؼ��룬��_hotΪ��
	this->_size;//����ȫ����ģ
	updateHeightAbove(x);//����x�����������ȸ߶�
	return x;
}
template<typename T> bool BST<T>::remove(const T& e) {
	//��BST����ɾ���ؼ���e
	BinNodePosi(T)& x = search(e); if (!x)return false;//ȷ��Ŀ�����
	removeAt(x, _hot); this->_size--;//ʵʩɾ��
	updateHeightAbove(_hot);//����_hot�����������ȵĸ߶�
	return true;
}
template<typename T>static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot) {
	BinNodePosi(T) w = x;//ʵʩ��ժ���Ľڵ�,��ֵͬx
	BinNodePosi(T) succ = nullptr;//ʵ�ʱ�ɾ���ڵ�Ľ�����
	if (!HasLChild(*x))//��*x��������Ϊ�գ����
		succ = x = x->rc;//ֱ�ӽ�*x�滻Ϊ��������
	else if (!HasRChild(*x))//��������Ϊ�գ���
		succ = x = x->lc;//�ԳƵĴ���ע�⣺��ʱsucc!=null;
	else {//���������������ڣ���ѡ��x��ֱ�Ӻ����Ϊʵ�ʱ�ժ���ڵ㣬Ϊ����Ҫ
		w = w->succ();//�����������У��ҵ�*x��ֱ�Ӻ��*w
		swap(x->data, w->data);//����*x��*w������Ԫ��
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rc : u->lc) = succ = w->rc;//����ڵ�*w
	}
	hot = w->parent;//��¼ʵ�ʱ�ɾ���ڵ��
	if (succ)succ->parent = hot;//������ɾ���ڵ�Ľ�������hot����
	release(w->data); release(w); return succ;//�ͷű�ժ���ڵ㣬���ؽ�����

}
#endif