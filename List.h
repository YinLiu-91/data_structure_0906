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
	header->succ = trailer; header->pred = nullptr;//头的后继是尾巴，头的前驱是nullptr
	trailer->pred = header; trailer->succ = nullptr;//尾巴的前驱是头，尾巴的后继是nullptr

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
template<typename T> void List<T>::traverse(void(*visit)(T&)) {
	for (ListNodePosi(T)p = header->succ; p != trailer; p = p->succ)visit(p->data);
}


//p77
template<typename T> template<typename VST>
void List<T>::traverse(VST& visit) {
	for (ListNodePosi(T)p = header->succ; p != trailer; p = p->succ)visit(p->data);
}

//有序列表唯一化
template<typename T>
int List<T>::uniquify(){//成批剔除元素，效率更高
	if (_size< 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T)q;
	while (trailer != (q = p->succ))//反复考察紧邻的节点对
		if (p->data != q->data)p = q;//若互异，则转向下一区段
		else remove(q);//否则（雷同），删除后者
	return oldSize - _size;//列表规模变化量，即被删除的元素总数
}

template<typename T>
ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p)const {
	//在有序列表内节点p（可能是trailer）的n个（真）前驱中，找到不大于e的最后者
	while (0 <= n--)//对于p的最近的n个前驱，从右向左逐个  比较
		//这里有小于的意义是当没有此值时，返回适当的插入点而插入后不影响整体序列 
		if (((p = p->pred)->data) <= e)break;//直至命中，数值越界或范围越界
	return p;//返回查找终止的位置
}//失败时，返回区间左边界的前驱（可能是header)--调用者可调用valid（）判断成功与否

//排序器p78
template<typename T>
void List<T>::sort(ListNodePosi(T)p,int n){//列表区间排序
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
		//逐一为各节点
		insertA(search(p->data, r, p), p->data);//查找适当的位置插入
		p = p->succ; remove(p->pred);//转向下一节点
		
}
}

template<typename T>
void List<T>::selectionSort(ListNodePosi(T) p, int n) {
	ListNodePosi(T) head = p->pred; ListNodePosi(T) tail = p;
	for (int i = 0; i < n; ++i)tail = tail->succ;//待排序区间为(head,tail)
	while (1<n)
	{
		ListNodePosi(T) max = selectMax(head->succ, n);//找出最大者
		insertB(tail, remove(max));//将其移动至末尾区间
		tail = tail->pred; n--;

	}
}
template<typename T>
ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n) {
	ListNodePosi(T) max = p;//最大值暂定节点p
	for (ListNodePosi(T) cur = p; 1 < n; n--)//从首节点出发，将后续节点逐一于max比较
		if (!lt((cur = cur->succ)->data, max->data))//若当前元素不小于max，则
			max = cur;//跟新最大元素位置记录
	return max;
}


//p82归并排序
template<typename T>
void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T)q, int m)
{
	ListNodePosi(T) pp = p->pred;//借助前驱，以便返回前...
	while(0<m)//在q尚未移出区间之前
		if((0<n)&&(p->data<=q->data))//若p仍在区间内且v(p)<=v(q),则
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
	if (n < 2)return;//若待排序区间已经足够小....递归基
	int m = n >> 1;//以中点为界
	ListNodePosi(T) q = p; for (int i = 0; i < m; ++i)q = q->succ;//均分列表
	mergeSort(p, m); mergeSort(q, n - m);
	merge(p, m, *this, q, n - m);
}
#endif // !LIST_H