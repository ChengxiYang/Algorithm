// 分治策略---归并排序.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::cin;

template <class T>
void merge_array(T *p_front, int begin, int mid, int end)
{
	if ((p_front == NULL) || (mid < begin) || (end < mid))
	{
		cout << "Illegl parameters!\n";
		return;
	}
	int num_left = mid - begin + 1;
	int num_right = end - mid;
	T *p_left = new T[num_left];
	T *p_right = new T[num_right];
	if ((p_left == NULL) || (p_right == NULL))
	{
		cout << "Memory allocation failed!\n";
		return;
	}
	for (int i = 0; i < num_left; ++i)
		p_left[i] = p_front[begin + i];
	for (int j = 0; j < num_right; ++j)
		p_right[j] = p_front[mid + 1 + j];
	int l = 0, r = 0;
	for (int k = begin; k <= end; ++k)
	{
		if (l < num_left && r < num_right)
		{
			if (p_left[l] <= p_right[r])
			{
				p_front[k] = p_left[l];
				++l;
			}
			else
			{
				p_front[k] = p_right[r];
				++r;
			}
		}
		else
		{
			if (l == num_left && r < num_right)
			{
				p_front[k] = p_right[r];
				++r;
			}
			if (r == num_right && l < num_left)
			{
				p_front[k] = p_left[l];
				++l;
			}
		}
	}
}

template <class T>
void merge_sort(T *p_front, int begin, int end)
{
	if (p_front == NULL)
	{
		cout << "Illegl parameter!\n";
		return;
	}
	if (begin < end)
	{
		int mid = (begin + end) / 2;
		merge_sort(p_front, begin, mid);
		merge_sort(p_front, mid + 1, end);
		merge_array(p_front, begin, mid, end);
	}
}

int main()
{
	int length;
	cout << "Enter length of array:\n";
	cin >> length;
	int *p_array = new int[length];
	for (int i = 0; i < length; ++i)
	{
		p_array[i] = rand() % 100 ;
		//p_array[i] = length * length - i * i;
		cout << p_array[i] << ", ";
	}
	cout << "\n";
	merge_sort(p_array, 0, length - 1);
	for (int i = 0; i < length; ++i)
		cout << p_array[i] << ", ";
	cout << "\n";
	/*int A[20] = { 1, 13, 24, 57, 69, 74, 79, 83, 92, 97, 20, 25, 27, 28, 30, 34, 39, 46, 51, 55 };
	merge_array(A, 0, 9, 19);
	for (int i = 0; i < 20; ++i)
		cout << A[i] << "\n";*/
    return 0;
}

