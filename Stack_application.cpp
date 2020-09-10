#include "Stack.h"
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

