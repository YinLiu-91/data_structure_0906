#include "Stack.h"
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

