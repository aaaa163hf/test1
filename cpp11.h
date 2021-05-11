#pragma once
//仿函数
//内部可拥有状态，调用比函数指针快
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
//可变参数函数
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
//类模板、全特化、偏特化
//函数模板只可全特化
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

//可变参数模板函数
//递归展开、逗号展开
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

//可变参数模板类
//偏特化、递归展开

//声明
template<class ...arge>
struct tt;
//基类
template<>
struct tt<>{
	void set(){}
	void  print() {}
};
//继承递归调用
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
//std::move 无条件转化为右值 
//std::forward 有条件转化为右值
//折叠引用
/*
X& . &.X& &&.X&& &都被折叠为X&
X&& && 折叠为X &&
除了引用折叠规则之外，c++标准还规定了一个“右值转换”的规则。
右值转换的含义是：
形容funRef(T && arg)的这种参数为右值引用的模板，当实参为一个左值时，调用仍然成功，
此时编译器推断模板参数（也就是T）为左值的引用。例如调用funRef(i), 那么T是int&而非int，
展开可知funRef(int & && arg)再采用上述的引用折叠规则，可知最后arg是int&

完美参数转发:一不能改变参数特性，二是不能产生额外的开销。如果模板能够把所有数据类型的参数都能按照上述要求进行转发
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
//该方法错误，左值不可绑定到右值当中
void test(int && a) {
	cout << a << endl;
}