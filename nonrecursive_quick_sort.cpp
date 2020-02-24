// nonrecursive_quick_sort.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <stack>

using std::cout;
using std::cin;
using std::stack;

template <class T>
void swap(T *p_a, T *p_b)
{
	T temp = *p_a;
	*p_a = *p_b;
	*p_b = temp;
}

template <class T>
int partite(T *p_array, int begin, int end)
{
	if (p_array == NULL || begin > end)
	{
		cout << "empty array!\n";
		return -1;
	}
	if (begin < 0 || end < 0)
	{
		cout << "wrong parameter!\n";
		return -1;
	}
	int i = begin - 1, j = begin;
	T pivot = p_array[end];
	for (; j < end; ++j) //loop-invariant: [begin, i] <= pivot, [i + 1, j] > pivot
		if (p_array[j] <= pivot)
		{
			++i;
			swap(p_array + i, p_array + j);
		}
	swap(p_array + i + 1, p_array + end);
	return i + 1;
}

template <class T>
void quick_sort(T *p_array, int size)
{
	/*if (begin < end)
	{
		int mid = partite(p_array, begin, end);
		quick_sort(p_array, begin, mid - 1);
		quick_sort(p_array, mid + 1, end);
	}
	else
		return;*/
	stack<int> arg_stack;
	if (size > 1)
	{ //initialize arg_stack with patitition of p_array[0:size-1]
		int low = 0, high = size - 1;
		int mid = partite(p_array, low, high);
		if (low < (mid - 1))
		{
			arg_stack.push(low);
			arg_stack.push(mid - 1);
		}
		if ((mid + 1) < high)
		{
			arg_stack.push(mid + 1);
			arg_stack.push(high);
		}
		while (!arg_stack.empty())
		{
			high = arg_stack.top();
			arg_stack.pop();
			int low = arg_stack.top();
			arg_stack.pop();
			mid = partite(p_array, low, high);
			if (low < (mid - 1))
			{
				arg_stack.push(low);
				arg_stack.push(mid - 1);
			}
			if ((mid + 1) < high)
			{
				arg_stack.push(mid + 1);
				arg_stack.push(high);
			}
		}
	}
}

int main()
{
	int array_size;
	cout << "enter size of array to be sorted:\n";
	cin >> array_size;
	double *p_array = new double[array_size];
	for (int k = 0; k < array_size; ++k)
	{
		p_array[k] = (rand() % array_size + 1.0) / array_size;
		cout << p_array[k] << ", ";
	}
	cout << "\n------\n";
	quick_sort(p_array, array_size);
	for (int k = 0; k < array_size; ++k)
		cout << p_array[k] << ", ";
	cout << "\n------\n";
    return 0;
}

