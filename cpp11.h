#pragma once
//�º���
//�ڲ���ӵ��״̬�����ñȺ���ָ���
#include <iostream>
#include "cpp11.h"
#include <vector>
//extern template void print(vector<int> &vec);
//
//extern template void InsertOrder(vector<int> &vec);
using namespace std;
template<typename T>
struct comp {
	bool operator()(T a, T b) {
		return (a > b);
	}
};
#include<stdarg.h>
//�ɱ��������
int add(int num, ...) {
	va_list ap;
	int r=0;
	va_start(ap, num);
	for (int i = 0; i < num; i++) {
		r += va_arg(ap, int);
	}
	va_end(ap);
	return r;
}
//��ģ�塢ȫ�ػ���ƫ�ػ�
//����ģ��ֻ��ȫ�ػ�
template<typename T1,typename T2>
class A{
public:
	void print(T1 a, T2 b) {
		printf("1-------");
	}
};
template<>
class A<int,char>{
public:
	void print(int a, char b) {
		printf("2-------");
	}
};
template<typename T>
class A<T,float> {
public:
	void print(T a, float b) {
		printf("3-------");
	}
};

//�ɱ����ģ�庯��
//�ݹ�չ��������չ��
template<typename T>
void pfun(T a) {
	cout << a << "--"<<endl;
}
template<typename T,typename ...arg>
void pfun(T head, arg... rest) {
	cout << head << " ";
	pfun(rest...);
}

template<typename T>
void ff(T a) {
	cout << a << "--";
}
template<typename ...arg>
void pfun1(arg... rest) {
	initializer_list<int>{(ff(rest), 0)...};
}

//�ɱ����ģ����
//ƫ�ػ����ݹ�չ��

//����
template<class ...arge>
struct tt;
//����
template<>
struct tt<>{
	void set(){}
	void  print() {}
};
//�̳еݹ����
template<class first,class ...rest>
struct tt<first,rest...>:tt<rest...>{
	typedef tt<rest...> base_type;
	void set(first b, rest... others){
		a = b;
		base_type::set(others...);
	}
	void print() {
		cout << a << endl;
		base_type::print();
	}
	first a;
};
//std::move ������ת��Ϊ��ֵ 
//std::forward ������ת��Ϊ��ֵ
//�۵�����
/*
X& . &.X& &&.X&& &�����۵�ΪX&
X&& && �۵�ΪX &&
���������۵�����֮�⣬c++��׼���涨��һ������ֵת�����Ĺ���
��ֵת���ĺ����ǣ�
����funRef(T && arg)�����ֲ���Ϊ��ֵ���õ�ģ�壬��ʵ��Ϊһ����ֵʱ��������Ȼ�ɹ���
��ʱ�������ƶ�ģ�������Ҳ����T��Ϊ��ֵ�����á��������funRef(i), ��ôT��int&����int��
չ����֪funRef(int & && arg)�ٲ��������������۵����򣬿�֪���arg��int&

��������ת��:һ���ܸı�������ԣ����ǲ��ܲ�������Ŀ��������ģ���ܹ��������������͵Ĳ������ܰ�������Ҫ�����ת��
*/
template<typename T>
void pp(T& a) {
	cout << "left" << endl;
}
template<typename T>
void pp(T&& a) {
	cout << "right" << endl;
}
template<typename T>
void testF(T&& a) {
	//pp(a);
	pp(std::forward<T>(a));
}
//�÷���������ֵ���ɰ󶨵���ֵ����
void test(int && a) {
	cout << a << endl;
}