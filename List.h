#pragma once
#ifndef LIST_H
#define LIST_H


#include "ListNode.h"
template<typename T> 
class List {

private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//规模，头哨兵，尾哨兵
protected:
	void init();//列表创建时初始化
	int clear();//清楚所有点
	void copyNodes(ListNodePosi(T), int);//复制列表中自位置p起的n项
	void merge(ListNodePosi(T)&, int, List<T>&, ListNodePosi(T), int);//归并
	void mergeSort(ListNodePosi(T)&, int);//对从p开始的连续n个节点进行归并排序
	void selectionSort(ListNodePosi(T), int);
	void insertionSort(ListNodePosi(T), int);//插入排序
public:
	//构造函数
	List() { init(); };//默认
	List(List<T>const& L);//拷贝构造
	List(List<T>const& L, Rank r, int n);//复制列表L中自r项起的第n项
	List(ListNodePosi(T)p, int n);//复制列表中自位置p起的n项

	//析构函数
	~List();//释放（包含头，尾哨兵在内的）所欲节点

	//只读访问接口
	Rank size()const { return  _size; };
	bool empty()const { return  _size <= 0; };
	T& operator[](Rank r)const;//支持循秩访问(效率低呀）
	ListNodePosi(T) first()const { return header->succ; }//首节点位置
	ListNodePosi(T) last()const { return trailer->pred; }//首节点位置

	bool valid(ListNodePosi(T) p)//判断位置p是否合法
	{
		return p && (trailer != p) && (header != p);//将头尾节点等同于null
	}
	int disordered()const;//判断列表是否已排序
	ListNodePosi(T) find(T const& e)const//无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T)p)const;//无序区间查找
	ListNodePosi(T)search(T const& e) {
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const& e, int n, ListNodePosi(T) p)const;


	ListNodePosi(T)selectMax(ListNodePosi(T)p, int n);//在p及其n-1个后继中选出最大者
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }

	//可写访问接口
	ListNodePosi(T) insertAsFirst(T const& e);//将e当做首节点插入
	ListNodePosi(T) insertAsLast(T const& e);//将e当做末节点插入
	ListNodePosi(T) insertA(ListNodePosi(T) p, const T& e);//将e当做p的后继插入
	ListNodePosi(T) insertB(ListNodePosi(T) p, const T& e);//将e当做p的前驱插入
	T remove(ListNodePosi(T) p);//删除合法位置p处的节点，返回被删除节点
	void merge(List<T>& L) { merge(first(), size(), L, L.first(), L._size); }//全列表归并
	void sort(ListNodePosi(T) p, int n);//列表区间排序
	void sort() { sort(first(), _size); }
	int deduplicate();//无序去重
	int uniquify();//有序去重
	void reverse();//前后倒置

	//遍历
	void traverse(void(*)(T&));//遍历,依次实施visit操作
	template<typename VST>//操作器
	void traverse(VST&);//遍历，依次实施visit操作
};

template<typename T> 
void List<T>::init() {
	header = new ListNode<T>;//创建头哨兵节点
	trailer = new ListNode<T>;//创建尾哨兵节点
	header->succ = trailer; header->pred = nullptr;
	trailer->pred = header; trailer->succ = nullptr;

	_size = 0;//规模
}

template<typename T>//重载下标操作运算符，以通过秩直接访问列表节点（方便，但效率低，需要慎用）
T& List<T>:: operator[](Rank r)const {
	ListNodePosi(T) p = first();//从首节点出发
	while (0 < r--)p = p->succ;//顺数第r个节点即是
	return p->data;//目标节点
}

//查找，p72
template<typename T>
ListNodePosi(T) List<T>::find(T const& e, int n, ListNodePosi(T) p)const {
	while (0 < n--)
		if (e == (p = p->pred)->data)return p;//逐个比对，直至命中或范围越界
	return nullptr;
}

//插入
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
	pred->succ = x; pred = x;//设置正向链
	return x;
}
template<typename T>
ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ->pred = x; succ = x;//设置逆向链接
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
template<typename T>//拷贝构造
List<T>::List(List<T>const& L) { copyNodes(L.first(), L._size); }
template<typename T>
List<T>::List(List<T> const& L, int r, int n) { copyNodes(L[r], n); }


//删除
//p75
template<typename T>T List<T>::remove(ListNodePosi(T) P){//删除合法节点p，返回其数值

	T e = P->data;
	P->pred->succ = P->succ; P->succ->pred = P->pred;
	delete P;
	_size--;
	return e;

}


//析构
template<typename T>
List<T>::~List()
{
	clear(); delete header; delete trailer;
}

template<typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (0 < _size)remove(header->succ);//反复删除首节点，直至列表变空
	return oldSize;
}

template<typename T>
int List<T>::deduplicate() {
	if (_size < 2)return 0;
	int oldSize = _size;
	ListNodePosi(T) p = header; Rank r = 0;
	while(trailer!=(p=p->succ)){//依次直到末节点
		ListNodePosi(T)q = find(p->data, r, p);//在p的r个（真）前驱中查找雷同者
		q ? remove(q) : r++;//若的确存在，则删除之；否则秩加一
	}
	return oldSize - _size;
}





#endif // !LIST_H