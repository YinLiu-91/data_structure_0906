#pragma once
#ifndef LIST_H
#define LIST_H


#include "ListNode.h"
template<typename T> 
class List {

private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//��ģ��ͷ�ڱ���β�ڱ�
protected:
	void init();//�б���ʱ��ʼ��
	int clear();//������е�
	void copyNodes(ListNodePosi(T), int);//�����б�����λ��p���n��
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);//�鲢
	void mergeSort(ListNodePosi(T)&, int);//�Դ�p��ʼ������n���ڵ���й鲢����
	void selectionSort(ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int);//��������
public:
	//���캯��
	List() { init(); };//Ĭ��
	List(List<T>const& L);//��������
	List(List<T>const& L, Rank r, int n);//�����б�L����r����ĵ�n��
	List(ListNodePosi(T)p, int n);//�����б�����λ��p���n��

	//��������
	~List();//�ͷţ�����ͷ��β�ڱ����ڵģ������ڵ�

	//ֻ�����ʽӿ�
	Rank size()const { return  _size; };
	bool empty()const { return  _size <= 0; };
	T& operator[](Rank r)const;//֧��ѭ�ȷ���(Ч�ʵ�ѽ��
	ListNodePosi(T) first()const { return header->succ; }//�׽ڵ�λ��
	ListNodePosi(T) last()const { return trailer->pred; }//�׽ڵ�λ��

	bool valid(ListNodePosi(T) p)//�ж�λ��p�Ƿ�Ϸ�
	{
		return p && (trailer != p) && (header != p);//��ͷβ�ڵ��ͬ��null
	}
	int disordered()const;//�ж��б��Ƿ�������
	ListNodePosi(T) find(T const& e)const//�����б����
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T)p)const;//�����������
	ListNodePosi(T)search(T const& e) {
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p)const;


	ListNodePosi(T)selectMax(ListNodePosi(T)p, int n);//��p����n-1�������ѡ�������
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }

	//��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const& e);//��e�����׽ڵ����
	ListNodePosi(T) insertAsLast(T const& e);//��e����ĩ�ڵ����
	ListNodePosi(T) insertA(ListNodePosi(T) p, const T& e);//��e����p�ĺ�̲���
	ListNodePosi(T) insertB(ListNodePosi(T) p, const T& e);//��e����p��ǰ������
	T remove(ListNodePosi(T) p);//ɾ���Ϸ�λ��p���Ľڵ㣬���ر�ɾ���ڵ�
	void merge(List<T>& L) { merge(first(), size(), L, L.first(), L._size); }//ȫ�б�鲢
	void sort(ListNodePosi(T) p, int n);//�б���������
	void sort() { sort(first(), _size); }
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
	void reverse();//ǰ����

	//����
	void traverse(void(*)(T&));//����,����ʵʩvisit����
	template<typename VST>//������
	void traverse(VST&);//����������ʵʩvisit����
};

template<typename T> 
void List<T>::init() {
	header = new ListNode<T>;//����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>;//����β�ڱ��ڵ�
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;

	_size = 0;//��ģ
}

template<typename T>//�����±�������������ͨ����ֱ�ӷ����б�ڵ㣨���㣬��Ч�ʵͣ���Ҫ���ã�
T& List<T>:: operator[](Rank r)const {
	ListNodePosi(T) p = first();//���׽ڵ����
	while (0 < r--)p = p->succ;//˳����r���ڵ㼴��
	return p->data;//Ŀ��ڵ�
}

//���ң�p72
template<typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p)const {
	while (0 < n--)
		if (e == (p = p->pred)->data)return p;//����ȶԣ�ֱ�����л�ΧԽ��
	return nullptr;
}

//����
template<typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const& e)
{
	++_size; return header->insertAsSucc(e);
}

template<typename T>
ListNodePosi(T) List<T>::insertAsLast(T const& e)
{
	++_size; return trailer->insertAsPred(e);
}

template<typename T	> ListNodePosi(T) List<T>::insertA(ListNodePosi(T)p, T const& e)
{
	_size++; return p->insertAsSucc(e);
}
template<typename T> ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
{
	_size++; return p->insertAsPred(e);
}
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsPred(T const& e) {
	ListNodePosi(T) x = new ListNode(e, pred, this);
	pred->succ = x; pred = x;//����������
	return x;
}
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;//������������
	return x;
}

//p74
template<typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n)
{
	init();
	while (n--) { insertAsLast(p->data); p = p->succ; }
}

template<typename T>
List<T>::List(ListNodePosi(T) p, int n) { copyNodes(p, n); }
template<typename T>//��������
List<T>::List(List<T>const& L) { copyNodes(L.first(), L._size); }
template<typename T>
List<T>::List(List<T> const& L, int r, int n) { copyNodes(L[r], n); }


//ɾ��
//p75
template<typename T>T List<T>::remove(ListNodePosi(T) P){//ɾ���Ϸ��ڵ�p����������ֵ

	T e = P->data;
	P->pred->succ = P->succ; P->succ->pred = P->pred;
	delete P;
	_size--;
	return e;

}


//����
template<typename T>
List<T>::~List()
{
	clear(); delete header; delete trailer;
}

template<typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (0 < _size)remove(header->succ);//����ɾ���׽ڵ㣬ֱ���б���
	return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
	if (_size < 2)return 0;
	int oldSize = _size;
	ListNodePosi(T) p = header; Rank r = 0;
	while(trailer!=(p=p->succ)){//����ֱ��ĩ�ڵ�
		ListNodePosi(T)q = find(p->data, r, p);//��p��r�����棩ǰ���в�����ͬ��
		q ? remove(q) : r++;//����ȷ���ڣ���ɾ��֮�������ȼ�һ
	}
	return oldSize - _size;
}





#endif // !LIST_H