#pragma once
//ģ�庯������������붨����Ҫ����һ��
#include <vector>
using namespace std;
using uint = unsigned int;
template<typename T>
void print(vector<T> &vec) {
	for (auto v : vec)
		cout << v << " ";
	cout << endl;
}

template<typename T>
void sswap(vector<T> &vec, int i, int j) {
	auto temp = vec[i];
	vec[i] = vec[j];
	vec[j] = temp;
}

//ֱ�Ӳ��� n*n �ȶ�
template<typename T>
void InsertOrder(vector<T> &vec) {
	for (uint i = 1; i < vec.size(); i++) {
		for (int j = i; j > 0 && vec[j] < vec[j - 1]; j--)
			sswap(vec, j, j - 1);
	}
}

//ϣ������ ���ݲ��� ���ȶ�
template<typename T>
void ShellOrder(vector<T> &vec,int gap) {
	while (gap > 1) {
		for (uint i = 0; i < vec.size() - gap;i++) {
			if(vec[i+gap]<vec[i])
				sswap(vec, i + gap, i);
		}

		gap = gap / 2 - 1;
	}

	InsertOrder(vec);
}

//ֱ��ѡ�� n*n ���ȶ�
template<typename T>
void SelOrder(vector<T> &vec) {
	int min;
	for (uint i = 0; i < vec.size() - 1; i++) {
		min = i;
		for (int j = i; j < vec.size(); j++) {
			if (vec[j]<vec[i]) {
				min = j;
			}
		}
		sswap(vec, i, min);
	}
}

//������ nlogn ���ȶ�
template<typename T>
void HeadAdjust(vector<T> &vec, int nNode, int end) {
	int left = 2 * nNode + 1;
	int right = 2 * nNode + 2;
	if (left > end) {
		return;
	}
	if (vec[left]>vec[nNode]) {
		sswap(vec, nNode, left);
	}
	if (right <= end && vec[left] > vec[nNode]) {
		sswap(vec, nNode, right);
	}
	HeadAdjust(vec, left, end);
	HeadAdjust(vec, right, end);
}
template<typename T>
void HeapSort(vector<T> &vec) {
	for (int i = vec.size() / 2 - 1; i >= 0; i--) {
		HeadAdjust(vec, i, vec.size() - 1);
	}
	for (int i = vec.size()-1; i >0; i--) {
		sswap(vec, 0, i);
		HeadAdjust(vec, 0, i-1);
	}
}

//ð������ n*n �ȶ�
template<typename T>
void BubbleSort(vector<T> &vec) {
	for (int i = vec.size() - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (vec[j] > vec[j + 1])
				sswap(vec, j, j + 1);
		}
	}
}

//�������� nlogn ���ȶ�
template <typename T>
void QuickSort(vector<T> &vec, int start=-1, int end=-1){
	if (start < 0 && end < 0) {
		start = 0;
		end = vec.size()-1;
	}
	if (start >= end) {
		return;
	}
	int s = start;
	int n = end;
	int gap = vec[start];
	while (s < n) {
		while (s<n && vec[n]>gap)
			n--;
		vec[s] = vec[n];

		while (s < n && vec[s] < gap)
			s++;
		vec[n] = vec[s];
	}
	vec[s] = gap;
	QuickSort(vec, start, s - 1);
	QuickSort(vec, s + 1, end);
}

//�鲢���� nlogn �ȶ�
template <typename T>
void Merge(vector<T> &vec, vector<T> &temp,int start,int end) {
	if (start >= end)
		return;
	int middle = (end - start) / 2 + start;
	Merge(vec, temp, start, middle);
	Merge(vec, temp, middle+1,end);
	int f = start;
	int s = middle + 1;
	for (int i = start; i <= end; i++) {
		if (f <= middle && ( s > end || vec[f] < vec[s]))
		{
			temp[i] = vec[f];
			f++;
		}
		else
		{
			temp[i] = vec[s];
			s++;
		}
	}
	for (int i = start; i <= end; i++) {
		vec[i] = temp[i];
	}
}

template <typename T>
void MergeSort(vector<T> &vec) {
	if (vec.size() > 1) {
		vector<T> temp(vec.size(), 0);
		Merge(vec, temp,0,vec.size()-1);
	}
}