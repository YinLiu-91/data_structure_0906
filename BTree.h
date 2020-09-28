#pragma once
#ifndef BTREE_H
#define BTREE_H
#include "BTNode.h"

template<typename T> class BTree{//b��ģ����
protected:
	int _size;//��ŵĹؼ�������
	int _order;//b���Ľ״Σ�����Ϊ3--����ʱָ����һ�㲻���޸�
	BTNodePosi(T) _root;//���ڵ�
	BTNodePosi(T) _hot;//BTree::search()�����ʵķǿգ����ǿ������Ľڵ�λ��
	void solveOverflow(BTNodePosi(T));//���������֮��ķ��Ѵ���
	void solveUnderflow(BTNodePosi(T));//��ɾ������֮��ĺϲ�����
public:
	BTree(int orer = 3) :_order(orer), _size(0);//���캯����Ĭ��Ϊ��ͽ״�3�״�
	{_root = new BTNode<T>(); }
	~BTree() { if (_root)release(_root); }//�����������ͷ����нڵ�
	int const order() { return _order; };
	int const size() { return _size; }
	BTNodePosi(T)& root() { return _root; }
	bool empty()const { return !_root; }//�п�
	BTNodePosi(T) search(const T& e);//����
	bool insert(const T& e);
	bool remove(const T& e);//ɾ��
};

//p217
template<typename T> 
BTNodePosi(T) BTree<T> ::search(const T & e) {
	BTNodePosi(T) v = _root; _hot = nullptr;//�Ӹ��ڵ����
	while(v){//������
		Rank r = v->key.search(e);//�ڵ�ǰ�ڵ��У��ҵ�������e�����ؼ���
		if ((0 <= r) && (e == v->key[r]))return v;//�ɹ����ڵ�ǰ�ڵ�����Ŀ��ؼ���
		_hot = v; v = v->child[r + 1];//����ת���Ӧ����(_hotָ���丸������io�����ʱ

	}
	return nullptr;
}


//p219
template<typename T> bool BTree<T>::insert(const T& e){//���ؼ���e����b����
	BTNodePosi(T) v = search(e); if (v)return false;//ȷ��Ŀ��ڵ㲻����
	Rank r = _hot->key.search(e);//�ڽڵ�_hot����ؼ��������в��Һ��ʵĲ���λ��
	_hot->key.insert(r + 1, e);//���µĹؼ��������Ӧλ��
	_hot->child.insert(r + 2, nullptr);//����һ��������ָ��
	_size++;//����ȫ����ģ
	solveOverflow(_hot);//���б�Ҫ����������
	return true;//����ɹ�
}

//p220
template<typename T> //�ؼ����������ڵ����磬�����ڵ���Ѵ���
void BTree<T>::solveOverflow(BTNodePosi(T)v) {
	if (_order >= v->child.size())return;//�ݹ������ǰ�ڵ㲢δ����
	Rank s = _order / 2;//��㣨��ʱӦ��_order=key.size()=child.size()-1
	BTNodePosi(T) u = new BTNode<T>();//ע�⣺�½ڵ�����һ������
	for(Rank j=0;j<_order-s-1;j++){//v�Ҳ�-order-s-1�����Ӽ��ؼ������Ϊ�Ҳ�ڵ�
		u->child.insert(j, v->child.remove(s + 1));//����ƶ�Ч�ʵ�
		u->key.insert(j, v->key.remove(s + 1));//�˲��ԿɸĽ�

	}
	u->child[_order - s - 1] = v->child.remove(s + 1);//�ƶ�v��ҵĺ���
	if (u->child[0]);//��u�ĺ����Ƿǿգ���
	for (Rank j = 0; j < _order - s; j++)//�����ǵĸ��׽ڵ�ͳһ
		u->child[j]->parent = u;//ָ��u
	BTNodePosi(T)p = v->parent;//v��ǰ�ĸ��ڵ�p
	if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; }//��p���򴴽�֮
	Rank r = 1 + p->key.search(v->key[0]);//pָ��u��ָ�����
	p->key.insert(r, v->key.remove(s));//���ؼ�������
	p->child.insert(r + 1, u); u->parent = p;//�½ڵ�u�븸�׽ڵ�p����
	solveOverflow(p);//����һ�㣬���б�Ҫ���������--����ݹ�o��logn����
}

//p222
template<typename T> bool BTree<T>::remove(const T &e)
{//��btree��ɾ���ؼ���e
	BTNodePosi(T) v = search(e); if (!v)return false;//ȷ��Ŀ��ؼ������
	Rank r = v->key.search(e);//ȷ��Ŀ��ؼ����ڽڵ�v�е���
	if(v->child[0]){//��v��Ҷ�ӣ���e�ĺ��ϵ����ĳҶ�ڵ�
		BTNodePosi(T) u = v->child[r + 1];//����������һֱ���󣬼���
		while (u->child[0])u = u->child[0];//�ҳ�e�ĺ��
		v->key[r] = u->key[0]; v = u; r = 0;//����֮����λ��

	}//���ˣ�v��Ȼλ����ײ㣬�����е�r���ؼ�����Ǵ�ɾ����
	v->key.remove(r); v->child.remove(r + 1); _size--;//ɾ��e���Լ����������ⲿ�ڵ�֮һ
	solveUnderflow(v);//���б�Ҫ��������ת��ϲ�
	return true;
}




#endif
