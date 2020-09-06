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
int main(int argc, char** argv) {
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