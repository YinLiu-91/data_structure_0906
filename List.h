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
	header->succ = trailer; header->pred = nullptr;//ͷ�ĺ����β�ͣ�ͷ��ǰ����nullptr
	trailer->pred = header; trailer->succ = nullptr;//β�͵�ǰ����ͷ��β�͵ĺ����nullptr

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
template<typename T> void List<T>::traverse(void(*visit)(T&)) {
	for (ListNodePosi(T)p = header->succ; p != trailer; p = p->succ)visit(p->data);
}


//p77
template<typename T> template<typename VST>
void List<T>::traverse(VST& visit) {
	for (ListNodePosi(T)p = header->succ; p != trailer; p = p->succ)visit(p->data);
}

//�����б�Ψһ��
template<typename T>
int List<T>::uniquify(){//�����޳�Ԫ�أ�Ч�ʸ���
	if (_size< 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T)q;
	while (trailer != (q = p->succ))//����������ڵĽڵ��
		if (p->data != q->data)p = q;//�����죬��ת����һ����
		else remove(q);//������ͬ����ɾ������
	return oldSize - _size;//�б��ģ�仯��������ɾ����Ԫ������
}

template<typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p)const {
	//�������б��ڽڵ�p��������trailer����n�����棩ǰ���У��ҵ�������e�������
	while (0 <= n--)//����p�������n��ǰ���������������  �Ƚ�
		//������С�ڵ������ǵ�û�д�ֵʱ�������ʵ��Ĳ����������Ӱ���������� 
		if (((p = p->pred)->data) <= e)break;//ֱ�����У���ֵԽ���ΧԽ��
	return p;//���ز�����ֹ��λ��
}//ʧ��ʱ������������߽��ǰ����������header)--�����߿ɵ���valid�����жϳɹ����

//������p78
template<typename T>
void List<T>::sort(ListNodePosi(T)p,int n){//�б���������
	switch (rand()%3)
	{
	case 1:insertionSort(p, n); break;
	case 2:selectionSort(p, n); break;
	default:mergeSort(p, n);
		break;
	}

}
template<typename T>
void List<T>::insertionSort(ListNodePosi(T)p, int n){//valid(p)&& rank(p)+n<=size;
	for (int r = 0; r < n; r++) {
		//��һΪ���ڵ�
		insertA(search(p->data, r, p), p->data);//�����ʵ���λ�ò���
		p = p->succ; remove(p->pred);//ת����һ�ڵ�
		
}
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; ++i)tail = tail->succ;//����������Ϊ(head,tail)
	while (1<n)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);//�ҳ������
		insertB(tail, remove(max));//�����ƶ���ĩβ����
		tail = tail->pred; n--;

	}
}
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;//���ֵ�ݶ��ڵ�p
	for (ListNodePosi(T) cur = p; 1 < n; n--)//���׽ڵ�������������ڵ���һ��max�Ƚ�
		if (!lt((cur = cur->succ)->data, max->data))//����ǰԪ�ز�С��max����
			max = cur;//�������Ԫ��λ�ü�¼
	return max;
}


//p82�鲢����
template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)q, int m)
{
	ListNodePosi(T) pp = p->pred;//����ǰ�����Ա㷵��ǰ...
	while(0<m)//��q��δ�Ƴ�����֮ǰ
		if((0<n)&&(p->data<=q->data))//��p������������v(p)<=v(q),��
		{
			if (q == (p = p->succ))break; n--;
		}
		else 
		{
			insertB(p, L.remove((q = q->succ)->pred)); m--;
		}
	p = pp->succ;
}

template<typename T>
void List<T>::mergeSort(ListNodePosi(T)& p, int n)
{
	if (n < 2)return;//�������������Ѿ��㹻С....�ݹ��
	int m = n >> 1;//���е�Ϊ��
	ListNodePosi(T) q = p; for (int i = 0; i < m; ++i)q = q->succ;//�����б�
	mergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}
#endif // !LIST_H