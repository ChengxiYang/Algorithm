// optimization of bubble sort.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <iostream>
#include <math.h>

using std::cout;
using std::cin;

template <class T>
void swap(T *p_a, T *p_b)
{
	T temp = *p_a;
	*p_a = *p_b;
	*p_b = temp;
}

template <class T>
void optimal_bubble_sort(T *p_array, int size)
{
	int i, j = size - 1, k = 0;
	bool flag = true;
	while (flag && j >= 1)
	{
		flag = false;
		for (i = 0; i < j; ++i)
			if (p_array[i] > p_array[i + 1])
			{
				flag = true;
				k = i;
				swap(p_array + i, p_array + i + 1);
			}
		j = k;
	}
}

int main()
{
	int array_num;
	cout << "enter size of array to be sorted:\n";
	cin >> array_num;
	int *p_array_1 = new int[array_num];
	for (int k = 0; k < array_num; ++k)
	{
		p_array_1[k] = rand() % array_num + 1;
		cout << p_array_1[k] << ", ";
	}
	cout << "\n------\n";
	optimal_bubble_sort(p_array_1, array_num);
	for (int k = 0; k < array_num; ++k)
		cout << p_array_1[k] << ", ";
	cout << "\n------\n";
    return 0;
}

