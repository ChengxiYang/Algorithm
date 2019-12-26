// 快速排序2---左端主元.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <cmath>

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
int partition(T *p_array, int begin, int end)
{
	if (p_array == NULL)
	{
		cout << "Null Pointer!\n";
		return -1;
	}
	T pivot = p_array[begin];
	int i = begin;
	for (int j = begin + 1; j <= end; ++j) //不变式：[begin + 1 : i] <= pivot, [i + 1 : j - 1] > pivot
		if (p_array[j] <= pivot)
		{
			++i;
			swap(p_array + i, p_array + j);
		}
	swap(p_array + begin, p_array + i);
	return i;
}

template <class T>
void quick_sort(T *p_array, int begin, int end)
{
	if (p_array == NULL)
	{
		cout << "Null Pointer!\n";
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
	cout << "Before sorting:\n";
	for (int i = 0; i < length; ++i)
	{
		p_array[i] = rand() % (length * length) + 1;
		cout << p_array[i] << ", ";
	}
	cout << "\n";
	quick_sort(p_array, 0, length - 1);
	cout << "After sorting:\n";
	for (int i = 0; i < length; ++i)
		cout << p_array[i] << ", ";
	cout << "\n";
    return 0;
}

