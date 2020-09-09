#pragma once
typedef int Rank;//��
#define  ListNodePosi(T) ListNode<T>*//�б�ڵ�λ��

template<typename T>struct ListNode
{
	//��Ա
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ;//��ֵ��ǰ�������
	//���캯��
	ListNode(){}
	ListNode(T e, ListNodePosi(T) p = nullptr, ListNodePosi(T) s = nullptr) :data(e), pred(p), succ(s) {}//Ĭ�Ϲ��캯��
	//�����ӿ�
	ListNodePosi(T) insertAsPred(T const& e);//������ǰ�ڵ�֮ǰ�����½ڵ�
	ListNodePosi(T) insertAsSucc(T const& e);//������ǰ�ڵ�֮������½ڵ�

};





