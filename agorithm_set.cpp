// agorithm_set.cpp : 定义控制台应用程序的入口点。
//

#include "DumpFile.h"
#include "order.h"
#include "cpp11.h"
//extern template void print(vector<int> &vec);
//
//extern template void InsertOrder(vector<int> &vec);
int main()
{
	//DeclareDumpFile();
	//vector<int> vec{ 12,3,44,67,32,2,1,343,65,22,32,878,0,232,45,22,54,76,544,76,43,224,655,773,656,87,323};
	//print<int>(vec);
	//MergeSort(vec);
	//print<int>(vec);
	//tt<int, float, char,int> t;
	//t.set(8,1.2, 'a',6);
	//t.print();
	testF(1);
	int b;
	int &a = b;
	testF(a);
	//testF(std::move(a));
	//testF(std::forward<int>(a));
	system("pause");
    return 0;
}

