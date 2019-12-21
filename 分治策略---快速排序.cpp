// 分治策略---快速排序.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::cin;

template <class T>
void swap(T *p_a, T *p_b)
{
	T tmp = *p_a;
	*p_a = *p_b;
	*p_b = tmp;
}

template <class T>
int partition(T *p_array, int begin, int end)
{
	if (p_array == NULL || begin > end)
	{
		cout << "Empty array!\n";
		return -1;
	}
	if (begin < 0 || end < 0)
	{
		cout << "Wrong parameter!\n";
		return -1;
	}
	T pivot = p_array[end];
	int i = begin - 1;
	for (int j = begin; j < end; ++j)
		if (p_array[j] <= pivot)
		{
			++i;
			swap(p_array + i, p_array + j);
		}
	swap(p_array + i + 1, p_array + end);
	return i + 1;
}

template <class T>
void quick_sort(T *p_array, int begin, int end)
{
	if (p_array == NULL)
	{
		cout << "Empty array!\n";
		return;
	}
	if (begin < end)
	{
		int partition_num = partition(p_array, begin, end);
		quick_sort(p_array, begin, partition_num - 1);
		quick_sort(p_array, partition_num + 1, end);
	}
	else
		return;
}

int main()
{
	int length;
	cout << "Enter size of array to be sorted:\n";
	cin >> length;
	int *p_array = new int[length];
	for (int i = 0; i < length; ++i)
	{
		//p_array[i] = length * length - i * i;
		p_array[i] = rand() % (length * length) + 1;
		cout << p_array[i] << ", ";
	}
	cout << "\n";
	quick_sort(p_array, 0, length - 1);
	for (int i = 0; i < length; ++i)
		cout << p_array[i] << ", ";
	cout << "\n";
    return 0;
}

