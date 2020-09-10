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

template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;//����������
	return x;
}
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);//ȷ����x��ǰ�����̼��� <-x->
	succ->pred = x; succ = x;//������������,��xǰ���ĺ�̣��Լ���̵�ǰ������ ->x<-
	//����˫�����������
	return x;
}



