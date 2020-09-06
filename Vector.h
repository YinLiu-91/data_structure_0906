/*
 * @Author: your name
 * @Date: 2020-09-06 09:07:54
 * @LastEditTime: 2020-09-06 18:21:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \code20200906\Vector.h
 */
#ifndef VECTOR_H
#define VECTOR_H//
typedef int Rank;             //using Rank=int;
#define DEFAULT_CAPACITY  3 //默认的初始容量(实际应用中可设置为更大)
#include <memory>

template <typename T>
class Vector
{ //向量模板类
protected:
	Rank _size;                                  //规模
	int _capacity;                               //容量
	T* _elem;                                    //数据区
	void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间;作为一个辅助函数来使用，
												 //构造函数多次用到
	void expand();                               //空间不足时扩容
	void shrink();                               //装填因子过小时压缩
	bool bubble(Rank lo, Rank hi);               //扫描交换
	void bubblesort(Rank lo, Rank hi);           //气泡排序法;
	Rank max(Rank lo, Rank hi);                  //选取最大元素
	void selectionSort(Rank lo, Rank hi);        //选择排序法
	void merge(Rank lo,Rank mi, Rank hi);                //归并算法
	void mergesort(Rank lo, Rank hi);            //归并排序
	Rank partition(Rank lo, Rank hi);            //轴点构造算法
	void quiksort(Rank lo, Rank hi);             //快速排序算法;
	void heapsort(Rank lo, Rank hi);             //堆排序
public:
	//构造函数
	//默认构造函数
	//此默认构造函数我觉着不好，用下面的吧
	//Vector(int c = DEFAULT_CAPACITY,int s , 0,T v = 0) //容量为c，规模为s，所有元素初始为v
	//{
	//	//构建容量大小
	//	_elem = new T[_capacity = c];
	//	for (_size = 0; _size < s; _elem[_size++] = v);
	//}//:_elem(new T[_capacity=c]),_capacity(c),_size(s)
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) :_elem(new T[c]), _capacity(c), _size(s) //容量为c，规模为s，所有元素初始为v
	{
		//构建容量大小

		for (int i = 0; i < _size; ++i)
			_elem[i] = v;
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }//数组整体复制//T const ;const T 都一样，指的是指向常对象的指针
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }//区间整体复制
	//拷贝构造函数
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//向量整体复制

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Vector(Vector<T>&& V);//移动构造函数

	 /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	Vector& operator=(const Vector<T>&);//拷贝赋值
	Vector& operator=(Vector<T>&&);//移动构造赋值
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }//区间复制
	//析构函数
	~Vector() { delete[]_elem; }//释放内部空间，需要析构函数的也需要构造函数和拷贝赋值函数

	//只读访问接口
	Rank size()const { return _size; }//规模
	bool empty()const { return !_size; }//自己写成了_size==0
	int disordered()const;//判断向量是否已排序
	Rank find(T const& e)const { return find(e, 0, _size); }//无序向量整体查找,调用下面的函数
	Rank find(T const& e, Rank lo, Rank hi)const;//无序向量区间查找
	Rank search(T const& e)const//有序向量整体查找
	{
		return (0 >= _size ? -1 : search(e, 0, _size));
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//有序向量区间查找
	//可写访问接口
	T& operator[](Rank r)const;//重载下标运算符
	T remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除区间内的元素
	Rank insert(Rank r, T const& e);//插入元素
	Rank insert(T const& e) { return insert(_size, e); }//默认作为末尾元素插入,类似于stl中的push_back();
	void sort(Rank lo, Rank hi);//对区间内排序
	void sort() { sort(0, _size); }//整体排序
	void unsort(Rank lo, Rank hi);//对区间置乱
	void unsort() { unsort(0, _size); }//整体置乱
	int deduplicate();//无序去重
	int uniquify();//有序去重

	//遍历
	void traverse(void(*)(T&));//遍历
	template<typename VST>void traverse(VST&);//遍历
};

//具体到功能的实现
template<typename T>
void Vector<T> ::copyFrom(T const* A, Rank lo, Rank hi) {//运行时间正比于O(_size)
	//以数组区间A[lo,hi)为蓝本复制对象
	_elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;//分配空间，规模清零,2倍的空间
	while (lo < hi) {
		_elem[_size++] = A[lo++];//复制到_elem[0,hi-lo)
	}
}

template<typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& V) {
	//拷贝赋值的功能类似于析构+构造
	if (_elem)delete[]_elem;
	copyFrom(V._elem, 0, V.size());
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& V) {

	if (this != &V)//注意取V的地址
	{
		delete[]_elem;
		_elem = V._elem;
		_size = V._size;
		_capacity = V._capacity;
		V._elem = nullptr;
	}
	return *this;
}

template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)return;//尚未满员时，无序扩容
	if (_capacity < DEFAULT_CAPACITY)_capacity = DEFAULT_CAPACITY;//不低于最小容量
	T* oldElem = _elem; _elem = new T[_capacity <<= 1];//容量加倍
	for (int i = 0; i < _size; ++i)
		_elem[i] = oldElem[i];
	delete[]oldElem;//释放原有空间
}

template <typename T>
void Vector<T>::shrink() {
	//装填因子过小时压缩向量所占空间
	if (_capacity < DEFAULT_CAPACITY << 1)return;
	if (_size << 2 > _capacity)return;//以25%为界
	T* oldelem = _elem; _elem = new T[_capacity >>= 1];//容量减半
	for (int i = 0; i < _size; ++i)_elem[i] = oldelem[i];
	delete[]oldelem;
}

//下标运算
template<typename T>
T& Vector<T>::operator[](Rank r)const
{
	return _elem[r];
}

template<typename T>
void permute(Vector<T>& V) {
	//随机置乱向量，使得各个元素等概率出现各个位置
	for (int i = V.size(); i > 0; --i)//自后向前
		swap(V[i - 1], V[rand() % i]);
}

template<typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {//等概率的置乱区间
	T* V = _elem + lo;//这里是指针真实位置
	for (Rank i = hi - lo; i >= 0; --i)//自后向前
		swap(V[i - 1], V[rand() % i]);//将V[i-1]与V[0,i)中某一个元素随机交换
}

template<typename T>
static bool lt(T* a, T* b) { return lt(*a, *b); }//less than 
template<typename T>
static bool lt(T& a, T& b) { return a < b; }
template<typename T>
static bool eq(T* a, T* b) { return eq(*a, *b); }
template<typename T>
static bool eq(T& a, T& b) { return a == b; }

template<typename T>//无序向量查找：返回最后一个元素e的位置；失败则返回lo -1
//复杂度：可能为O(1),可能为O(n)，输入敏感
Rank Vector<T>::find(T const& e, Rank lo, Rank hi)const {
	while ((lo < hi--) && (e != _elem[hi]));//从后向前，顺序查找//利用短路特性，在hi=-1时也不会继续执行_elem[hi]
	return hi;//若hi>lo，则意味着失败，否则hi即命中元素的秩
}

template<typename T>//复杂度：输入敏感的
Rank Vector<T>::insert(Rank r, const T& e) {
	expand();//确保_size比capacity至少小1
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];//自前向后，后继元素顺次向后移动位置
	_elem[r] = e; _size++;//置入并更新容量
	return r;//返回秩
}
template<typename T>//输入敏感，仅仅与被删除区间后面的长度有关系
int Vector<T>::remove(Rank lo, Rank hi)
{
	////self
	//for (int i = lo; i > _size-hi; ++i)
	//	_elem[i] = _elem[hi+i-lo];
	//shrink();
	//return hi - lo;

	//课本
	//@@@
	if (lo == hi)return 0;//处于效率考虑，单独考虑退化情况
	while (hi < _size)_elem[lo++] = _elem[hi++];//[hi,_size)顺次前移.利用++更高效
	_size = lo;//更新规模，直接丢弃尾部[lo,_size=hi)的区间
	shrink();
	return hi - lo;
}

template<typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;//返回被删除的元素
}

template<typename T>//复杂度n^2
int Vector<T>::deduplicate(){//删除无序向量中重复的元素
	int oldSize = _size;
	Rank i = 1;//从_elem[i]开始
	while (i < _size) {
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
		return oldSize - _size;
	}
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
	for (int i = 0; i < _size; i++)visit(_elem[i]);//遍历向量
}
template<typename T> template<typename VST>
	void Vector<T>:: traverse(VST& visit)//借助函数对象机制
	{
		for (int i = 0; i < _size; ++i)visit(_elem[i]);//遍历向量
	}
	//p44
	template<typename T>
	struct Increase
	{
		virtual void operator()(T& e) { e++; }
	};
	template<typename T>
	void increase(Vector<T>& V) { V.traverse(Increase<T>()); }//以Increase<T>()为基本操作进行遍历

	template<typename T>//p45
	int Vector<T>::disordered()const {
		//返回向量中逆序相邻的总数
		int n = 0;//计数器
		for (int i = 1; i < _size; ++i)//逐一检查
			if (_elem[i - 1] > _elem[i])n++;//逆序则计数
		return n;
	}
	template<typename T>//p45.复杂度：O(n^2)与无序唯一化相同
	int Vector<T>::uniquify() {
		////有序向量重复元素剔除（低效版）
		//int oldSize = _size;
		//int i = 1;
		//while (i<_size)
		//{
		//	_elem[i - 1] == _elem[i] ? remove(i) : i++;//若雷同则删除后者；否则，转至后一个元素
		//	return oldSize - _size;//返回被删除的数量
		//}

		////有序向量重复元素剔除（高效版）
		Rank i = 0, j = 0;//各对互异“相邻"元素的秩
		//@@@@
		while (++j < _size)
			if (_elem[i] != _elem[j])//跳过雷同者
				_elem[++i] = _elem[j];//发现不同元素时，向前移至紧邻于前者右侧

		_size = ++i;
		shrink();
		return j - i;//返回被删除的元素数量
	}
	//p47
	template<typename T>//在有序向量的区间[lo,hi)内，确定不大于e的最后一个节点的秩
	Rank Vector<T>::search(T const& e, Rank lo, Rank hi)const {
		return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
	}

	//二分查找算法（A）：在有序区间[lo,hi)内查找元素e,0<=lo<=hi<=_size
	/*
	* 二分查找将区间分为三个部分:
	* S[lo,mi)<=S[mi]<=S(mi,hi)
	
	*/
	//template<typename T> static Rank binSearch(T* A, T const& e, Rank lo, Rank hi) {
	//	while(lo<hi){//每步迭代可能要做两次比较判断，有三个分支
	//		Rank mi = (lo + hi) >> 1;//以中轴为轴点
	//		if (e < A[mi])hi = mi;//深入前半段[lo,hi)
	//		else if (A[mi] < e)lo = mi + 1;//深入后半段(mi,hi)继续查找
	//		else return mi;//在mi处命中

	//	
	//	}
	//	return -1;
	//}//有多个元素命中时，并不能保证命中秩最大者；查找失败时，返回-1，而不能指示失败位置

	////二分查找算法B
	//template<typename T>
	//static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
	//{
	//	while(1<hi-lo){//每步迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止
	//		Rank mi = (lo + hi) >> 1;//以中点为轴
	//		(e < A[mi]) ? hi = mi : lo = mi;//经比较深入后确定深入方向

	//	}
	//	return (e == A[lo]) ? lo : -1;//查找成功时返回对应的秩；否则返回-1

	//}
	//二分查找算法C
	template<typename T>
	static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
	{
		while (lo<hi) {//每步迭代仅需做一次比较判断，有两个分支；成功查找不能提前终止
			Rank mi = (lo + hi) >> 1;//以中点为轴
			(e < A[mi]) ? hi = mi : lo = mi+1;//经比较深入后确定深入方向

		}
		return --lo;//循环结束时，lo为大于e的元素的最小的秩，故lo-1即不大于e的元素的最大秩

	}


#include "Fib.h"
	template<typename T>static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi) {
		Fib fib(hi - lo);
		while (lo < hi)
		{
			while (hi - lo < fib.get())fib.prev();//Ran
			Rank mi = lo + fib.get() - 1;//确定轴点
			if (e < A[mi])hi = mi;
			else if (A[mi] < e)lo = mi + 1;
			else return mi;//在mi处命中
		}
		return -1;
	}


	//排序算法
	template<typename T>
	void Vector<T>:: sort(Rank lo,Rank hi){//向量区间排序
		switch (rand()%5)
		{
		case:1
			bubbleSort(lo, hi);
			break;
		case:2
			selectionSort(lo, hi);
			break;
		case:3
			mergeSort(lo, hi);
			break;
		case:4
			heapSort(lo, hi);
			break;
		default:
			quikSort(lo, hi);
			break;
		}
	}

	template<typename T>
	void Vector<T>::bubblesort(Rank lo, Rank hi)
	{
		while (!bubble(lo, hi--));
	}//逐趟扫描交换，直到全序
	template<typename T>
	bool Vector<T>::bubble(Rank lo, Rank hi) {
		bool sorted = true;//整体有序标志
		while(++lo<hi)//自左向右，逐一检查各对相邻元素
			if(_elem[lo-1]>_elem[lo]){//若逆序，则
				sorted = false;//意味着尚未整体有序，需要
				swap(_elem[lo - 1], _elem[lo]);
			}
		return sorted;
	}

	template<typename T>//向量归并排序
	void Vector<T>::mergesort(Rank lo, Rank hi)
	{
		if (hi - lo < 2)return;//
		int mi = (lo + hi) / 2;//以中点为界
		mergesort(lo, mi); mergesort(mi, hi);//分别排序
		merge(lo, mi, hi);//归并
	}

	template<typename T>//有序向量的归并
	void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
		T* A = _elem + lo;//合并后的向量A[0,hi-lo)=_elem[lo,hi)
		int lb = mi - lo; T* B = new T[lb];//前子向量B[0,lb)=_elem[lo,mi)
		for (Rank i = 0; i < lb; B[i] = A[i++]);//复制前子向量
		int lc = hi - mi; T* C = _elem + mi;//后子向量C[0,lc)=_elem[mi,hi)
		for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
			//B[j]和C[k]中的小者续至A末尾

			if ((j < lb) && (!(k < lc) || (B[j] <= C[k])))A[i++] = B[i++];
			if ((k < lc) && (!(j < lb) || (C[k] < B[j])))A[i++] = C[k++];
		}

		delete[]B;
	}
#endif