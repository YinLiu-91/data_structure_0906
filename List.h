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

//

#endif // !LIST_H