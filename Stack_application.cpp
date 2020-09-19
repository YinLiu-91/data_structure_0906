#include "Stack.h"
#include <ctype.h>
//ջ�ĵ���Ӧ��
//�������p90
	//����ת��

//void convert(Stack<char>& S, __int64 n, int base) {
//	//ʮ��������n��base���Ƶ�ת��(�ݹ�棩
//	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
//	if (0 < n) {
//		//����������ǰ��������
//		S.push(digit[n % base]);//�����¼��ǰ���λ����
//		convert(S, n / base, base);//ͨ���ݹ�õ����и���λ
//
//	}
//
//}

void convert(Stack<char>& S, __int64 n, int base) {
	//ʮ��������n��base���Ƶ�ת��(ѭ����
	static char digit[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	while (n > 0)
	{
		S.push(digit[n % base]);
		n /= base;
	}
}

void trim(const char exp[], int& lo, int& hi)
{//ɾ��exp[lo,hi]�������ŵ��ǰ׺����׺
	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')'))lo++;//���ҵ�һ������
	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')'))hi--;//���һ������
}

int divide(const char exp[], int lo, int hi) {//�з�exp[lo,hi],ʹexpƥ������ӱ��ʽƥ��
	int mi = lo; int crc = 1;//crcΪ[lo,hi]�ķ�Χ������������Ŀ֮��
	while ((0 < crc) && (++mi < hi))//��������ַ���ֱ������������Ŀ��ȣ�����Խ��
	{
		if (exp[mi] == ')')crc--; if (exp[mi] == '(')crc++;
	}//�������ŷֱ����
	return mi;//��mi<=hi����Ϊ�Ϸ��зֵ㣻������ζ�žֲ�������ƥ��
}

bool paren(const char exp[], int lo, int hi) {//�����ʽexp[lo,hi]�Ƿ�����ƥ��
	trim(exp, lo, hi); if (lo > hi)return true;
	if (exp[lo] != '(')return false;
	if (exp[hi] != ')')return false;//ĩ�ַ��������ţ���ز�ƥ��
	int mi = divide(exp, lo, hi);//ȷ���ʵ����зֵ�
	if (mi > hi)return false;
	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);//�ֱ��������ӱ��ʽ
}



/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2003-2020. All rights reserved.
 ******************************************************************************************/

#define N_OPTR 9 //���������
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //���������
//�ӡ������ˡ������˷����׳ˡ������š������š���ʼ������ֹ��

const char pri[N_OPTR][N_OPTR] = { //��������ȵȼ� [ջ��] [��ǰ]
   /*              |-------------------- �� ǰ �� �� �� --------------------| */
   /*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* ջ  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* ��  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* ��  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* ��  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};


//float evaluate(char* S, char*& RPN) {//�ԣ��Ѿ��޳��׿ո�ģ����ʽS��ֵ����ת��Ϊ�沨��ʽ
//	Stack<float> opnd;
//	Stack<char>optr;//�������������ջ
//	optr.push('\0');//β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
//	while (!optr.empty()) {//�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
//		if (isdigit(*S)) {//����ǰ�ַ�Ϊ��������
//			readNumber(S, opnd); append(RPN, opnd.top());//��������������������RPNĩβ
//		}
//		else
//			switch (orderBetween(optr.top(), *S)) {//������ջ������֮������ȼ��ֱ���
//			case '<'://ջ����������ȼ�����ʱ
//				optr.push((*S)); S++;
//				break;//�����ӳ٣���ǰ�������ջ
//			case '='://���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'ʱ
//				optr.pop(); S++;//�����Ų�������һ���ַ�
//				break;
//
//			case '>': {
//				//ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
//				char op = optr.pop(); append(RPN, op);//ջ���������ջ��������RPNĩβ
//				if ('!' == op) {//������һԪ�����
//					float p0pnd = opnd.pop();//ֻ��ȡ��һ��������
//					opnd.push(calcu(op, p0pnd));//ʵʩһԪ���㣬�����ջ
//				}
//				else {
//					float p0pnd2 = opnd.pop(), p0pnd1 = opnd.pop();//ȡ����ǰ������
//					opnd.push(calcu(p0pnd1, op, p0pnd2));//ʵʩ��Ԫ���㣬�����ջ
//				}
//				break;
//			}
//			default: exit(-1);//���﷨���󣬲�������ֱ���˳�
//			}//switch
//	}//while
//	return opnd.pop();
//}
//}