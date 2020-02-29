// divide-conquer maximum subarray.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <cmath>
#include <iostream>

using std::cout;

const int NINF = -0x3f3f3f3f;
template <class T>
struct answer
{
	int low;
	int high;
	T value;
};

template <class T>
answer<T> * maximum_subarray(T *p_array, int low, int high)
{
	if (low == high)
	{
		answer<T> *p_base = new answer<T>;
		p_base->low = low; p_base->high = high;
		p_base->value = p_array[low];
		return p_base;
	}
	int mid = (low + high) / 2;
	int left_sum = NINF; int sum = 0; int mid_low = -1;
	for (int i = mid; i >= low; --i)
	{
		sum = sum + p_array[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			mid_low = i;
		}
	}
	int right_sum = NINF; sum = 0; int mid_high = -1;
	for (int i = mid + 1; i <= high; ++i)
	{
		sum = sum + p_array[i];
		if (sum > right_sum)
		{
			right_sum = sum;
			mid_high = i;
		}
	}
	int mid_sum = left_sum + right_sum;
	answer<T> *p_low = maximum_subarray(p_array, low, mid);
	answer<T> *p_high = maximum_subarray(p_array, mid + 1, high);
	answer<T> *p_answer = new answer<T>;
	if (p_low->value > mid_sum && p_low->value > p_high->value)
	{
		p_answer->low = p_low->low; p_answer->high = p_low->high;
		p_answer->value = p_low->value;
	}
	else if (p_high->value > mid_sum && p_high->value > p_low->value)
	{
		p_answer->low = p_high->low; p_answer->high = p_high->high;
		p_answer->value = p_high->value;
	}
	else
	{
		p_answer->low = mid_low; p_answer->high = mid_high;
		p_answer->value = mid_sum;
	}
	return p_answer;
}

int main()
{
	int size = 32, gap = 40, lower_bound = -20;
	int *p_arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		p_arr[i] = rand() % gap + lower_bound;
		cout << p_arr[i] << ", ";
	}
	cout << "\n------\n";
	answer<int> *p_ans = NULL;
	p_ans = maximum_subarray(p_arr, 0, size - 1);
	cout << "(" << p_ans->low << ", " << p_ans->high << ", "
		<< p_ans->value << ")";
	cout << "\n------\n";
    return 0;
}

