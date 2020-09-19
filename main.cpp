/*
 * @Author: your name
 * @Date: 2020-09-06 09:07:12
 * @LastEditTime: 2020-09-06 09:07:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \code20200906\main.cpp
 */
#include"Vector.h"
#include <ctime>
#include <iostream>
#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "BinNode.h"
void convert(Stack<char>& S, __int64 n, int base);



int main(int argc, char** argv) {
/*-----------------------------------------------------------------------*/
	//进制转换例子
	Stack<char> s1;
	__int64 num_to_trans = 13;
	convert(s1, num_to_trans, 2);
	int i_max = s1.size();
	for (int i = 0; i < i_max; ++i)
		std::cout << s1.pop() << "\n";


/*-----------------------------------------------------------------------*/


	List<int> il;
	il.insertAsFirst(1);

	std::clock_t t_start, t_end;
	t_start = std::clock();
	Vector<int> v(1000000000, 1000000000, 5);
	t_end = std::clock();
	std::cout << "构造函数耗时: " << double(t_end - t_start) / 1000.0 << " S" << "\n";
	Vector<int> v1;
	Vector<int> v2;
	
	t_start = std::clock();
	v1 = v;
	t_end = std::clock();
	std::cout << "拷贝赋值运算耗时: " << double(t_end - t_start) / 1000.0 << " S" << "\n";
	

	t_start = std::clock();
	v2 = std::move(v);
	t_end = std::clock();
	std::cout << "移动赋值运算耗时: " << double(t_end - t_start) / 1000.0 << " S" << "\n";



	return 0;
}