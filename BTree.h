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
#endif
