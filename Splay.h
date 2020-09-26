#pragma once
#ifndef SPLAY_H
#define SPLAY_H
#include "BST.h"
template<typename T> class Splay:public BST<T>{//��bst������splay��ģ����
protected:
	BinNodePosi(T)splay(BinNodePosi(T)v);//���ڵ�v��չ������
public:
	using BST<T>::_root;
	using BST<T>::_hot;
	using BST<T>::_size;
	BinNodePosi(T)& search(const T& e);//���ң���д��
	BinNodePosi(T)insert(const T& e);//���루��д��
	bool remove(const T& e);//ɾ������д��
};

template<typename NodePosi> inline
void attachAsLChild(NodePosi p, NodePosi lc) { p->lc = lc; if (lc)lc->parent = p; }

template<typename NodePosi>inline
void attachAsRChild(NodePosi p, NodePosi rc) { p->rc = rc; if (rc)rc->parent = p; }

template<typename T> //splay����չ�㷨���ӽڵ�v���������չ
BinNodePosi(T)Splay<T>::splay(BinNodePosi(T)v) {
	//vΪ������ʶ���Ҫ��չ�Ľڵ�λ��
	if (!v)return nullptr; BinNodePosi(T)p; BinNodePosi(T)g;//*v�ĸ������游
	while ((p = v->parent) && (g = p->parent)) {
		//���¶��ϣ�������*v��˫����չ
		BinNodePosi(T)gg = g->parent;//ÿ��֮��*v����ԭ���游Ϊ��
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
		if (!gg)v->parent = nullptr;//��*v��ԭ�ȵ����游�����ڣ���*����ӦΪ����
		else
			//����*gg�˺�Ӧ����*v��Ϊ����Һ���
			(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);
		BinTree<T>::updateHeight(g); BinTree<T>::updateHeight(p); BinTree<T>::updateHeight(v);
	}//˫����չ����������g==null,��p���ܷǿ�
	if(p=v->parent){//��p����ǿգ����������һ����ת
		if (IsLChild(*v)) { attachAsRChild(p, v->rc); attachAsRChild(v, p); }
		else { attachAsRChild(p, v->lc); attachAsLChild(v, p); }
		BinTree<T>::updateHeight(p); BinTree<T>::updateHeight(v);
	}
	v->parent = nullptr; return v;
	
}

template<typename T>
BinNodePosi(T) & Splay<T>::search(const T&e){//����չ���в���e
	//using BinTree<T>::_root;
	BinNodePosi(T)p = searchIn(_root, e, _hot = nullptr);
	_root = splay(p ? p : this->_hot);//�����һ�������ʵĽڵ���չ������
	return _root;
	
}
template<typename T> BinNodePosi(T) Splay<T>::insert(const T& e)
{
	if (!BinTree<T>::_root) { _size++; return this->_root = new BinNode<T>(e); }//����ԭ��Ϊ�յ��˻����
	if (e == search(e)->data)return this->_root;//ȷ��Ŀ��ڵ㲻����
	_size++; BinNodePosi(T)t = _root;//�����½ڵ㡣���µ���<=7��ָ������ɾֲ��ع�
	if(this->_root->data<e){//�����¸�����t��t->rcΪ���Һ���
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t, t->rc);//2+3��
		if (HasRChild(*t)) { t->rc->parent = BinTree<T>::_root; t->rc = nullptr; }//<=2��
	}else
	{//�����¸�,��t->lc��tΪ���Һ���
		t->parent = BinTree<T>::_root = new BinNode<T>(e, nullptr, t->lc, t);//2+3��
		if (HasLChild(*t)) { t->lc->parent = BinTree<T>::_root; t->lc = nullptr; }//<=2��
	
	}
	BinTree<T>::updateHeightAbove(t);//����t�������ȣ�ʵ��ֻ��һ��_rootһ�����ĸ߶�
	return BinTree<T>::_root;//�½ڵ��Ȼ��������������
}
template<typename T> 
bool Splay<T>::remove(const T& e)
{
	//����չ����ɾ���ؼ���e
	if (!BinTree<T>::_root || (e != search(e)->data))return false;//�����ջ���Ŀ�겻���ڣ����޷�ɾ��
	BinNodePosi(T) w = BinTree<T>::_root;//assert:��search������ڵ�e�ѱ���չ������
	if(!HasLChild(*BinTree<T>::_root)){//��������������ֱ��ɾ��
		BinTree<T>::_root = BinTree<T>::_root->rc; if (BinTree<T>::_root)BinTree<T>::_root->parent = nullptr;

	}else if(!HasRChild(*BinTree<T>::_root)){//������������Ҳ��ֱ��ɾ��
		BinTree<T>::_root = BinTree<T>::_root->lc; if (BinTree<T>::_root)BinTree<T>::_root->parent = nullptr;
	}else {//����������ͬʱ���ڣ���
		BinNodePosi(T) lTree = _root->lc;
		lTree->parent = nullptr; _root->lc = nullptr;//��ʱ��������ɾ��
		_root = _root->rc; _root->parent = nullptr;//ֻ����������
		search(w->data);//��ԭ����ΪĿ�꣬��һ�Σ��ض�ʧ�ܵģ�����
		/////assert�����ˣ�����������С�ڵ����չ������������������Ϊ�գ�����
		_root->lc = lTree; lTree->parent = _root;//ֻ�轫ԭ���ӻؼ���
	

	}
	release(w->data); release(w); _size--;//�ͷŽڵ㣬���¹�ģ
	if (_root)BinTree<T>::updateHeight(_root);//�˺������ǿգ��������ĸ߶���Ҫ����
	return true;//���سɹ���־
}


#endif
