#include "Stack.h"
#include <ctype.h>
//栈的典型应用
//逆序输出p90
	//进制转换

//void convert(Stack<char>& S, __int64 n, int base) {
//	//十进制整数n到base进制的转换(递归版）
//	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
//	if (0 < n) {
//		//在尚有余数前，反复的
//		S.push(digit[n % base]);//逆向记录当前最低位，再
//		convert(S, n / base, base);//通过递归得到所有更高位
//
//	}
//
//}

void convert(Stack<char>& S, __int64 n, int base) {
	//十进制整数n到base进制的转换(循环）
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		S.push(digit[n % base]);
		n /= base;
	}
}

void trim(const char exp[], int& lo, int& hi)
{//删除exp[lo,hi]不含括号的最长前缀，后缀
	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))lo++;//查找第一个括号
	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))hi--;//最后一个括号
}

int divide(const char exp[], int lo, int hi) {//切分exp[lo,hi],使exp匹配仅当子表达式匹配
	int mi = lo; int crc = 1;//crc为[lo,hi]的范围内左，右括号数目之差
	while ((0 < crc) && (++mi < hi))//逐个检查各字符，直到左右括号数目相等，或者越界
	{
		if (exp[mi] == ')')crc--; if (exp[mi] == '(')crc++;
	}//左，右括号分别计数
	return mi;//若mi<=hi；则为合法切分点；否则，意味着局部不可能匹配
}

bool paren(const char exp[], int lo, int hi) {//检查表达式exp[lo,hi]是否括号匹配
	trim(exp, lo, hi); if (lo > hi)return true;
	if (exp[lo] != '(')return false;
	if (exp[hi] != ')')return false;//末字符非右括号，则必不匹配
	int mi = divide(exp, lo, hi);//确定适当的切分点
	if (mi > hi)return false;
	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);//分别检查左右子表达式
}



/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/

#define N_OPTR 9 //运算符总数
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = { //运算符优先等级 [栈顶] [当前]
   /*              |-------------------- 当 前 运 算 符 --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};


//float evaluate(char* S, char*& RPN) {//对（已经剔除白空格的）表达式S求值，并转换为逆波兰式
//	Stack<float> opnd;
//	Stack<char>optr;//运算数，运算符栈
//	optr.push('\0');//尾哨兵'\0'也作为头哨兵首先入栈
//	while (!optr.empty()) {//在运算符栈非空之前，逐个处理表达式中各字符
//		if (isdigit(*S)) {//若当前字符为操作数则
//			readNumber(S, opnd); append(RPN, opnd.top());//读入操作数，并将其接至RPN末尾
//		}
//		else
//			switch (orderBetween(optr.top(), *S)) {//视其与栈顶运算之间的优先级分别处理
//			case '<'://栈顶运算符优先级更低时
//				optr.push((*S)); S++;
//				break;//计算延迟，当前运算符进栈
//			case '='://优先级相等（当前运算符为右括号或者尾部哨兵'\0'时
//				optr.pop(); S++;//脱括号并接收下一个字符
//				break;
//
//			case '>': {
//				//栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
//				char op = optr.pop(); append(RPN, op);//栈顶运算符出栈并续接至RPN末尾
//				if ('!' == op) {//若属于一元运算符
//					float p0pnd = opnd.pop();//只需取出一个数，并
//					opnd.push(calcu(op, p0pnd));//实施一元计算，结果入栈
//				}
//				else {
//					float p0pnd2 = opnd.pop(), p0pnd1 = opnd.pop();//取出后，前操作数
//					opnd.push(calcu(p0pnd1, op, p0pnd2));//实施二元计算，结果入栈
//				}
//				break;
//			}
//			default: exit(-1);//逢语法错误，不做处理直接退出
//			}//switch
//	}//while
//	return opnd.pop();
//}
//}