// divide-conquer maximum subarray.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>

using std::cout;
using std::setprecision;
using std::time;

const int NINF = -0x3f3f3f3f;

template <class T>
struct solution
{
	int low;
	int high;
	T value;
};

template <class T>
solution<T> * find_max_crossing_subarr(T *p_array, int low, int high)
{
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
	solution<T> *p_ret = new solution<T>;
	p_ret->low = mid_low; p_ret->high = mid_high;
	p_ret->value = left_sum + right_sum;
	return p_ret;
}

template <class T>
solution<T> * recur_max_subarr(T *p_array, int low, int high)
{ //time complexity: O(N * lgN)
	if (low == high)
	{
		solution<T> *p_base = new solution<T>;
		p_base->low = low; p_base->high = high;
		p_base->value = p_array[low];
		return p_base;
	}
	int mid = (low + high) / 2;
	solution<T> *p_low = recur_max_subarr(p_array, low, mid);
	solution<T> *p_high = recur_max_subarr(p_array, mid + 1, high);
	solution<T> *p_mid = find_max_crossing_subarr(p_array, low, high);
	solution<T> *p_ret = new solution<T>;
	if (p_low->value > p_mid->value && p_low->value > p_high->value)
	{
		p_ret->low = p_low->low; p_ret->high = p_low->high;
		p_ret->value = p_low->value;
	}
	else if (p_high->value > p_mid->value && p_high->value > p_low->value)
	{
		p_ret->low = p_high->low; p_ret->high = p_high->high;
		p_ret->value = p_high->value;
	}
	else
	{
		p_ret->low = p_mid->low; p_ret->high = p_mid->high;
		p_ret->value = p_mid->value;
	}
	return p_ret;
}

template <class T>
solution<T> * dynamic_max_subarr(T *p_array, int size)
{ //time complexity: O(N)
	solution<T> *p_solus = new solution<T>[size];
	p_solus[0].low = p_solus[0].high = 0;
	p_solus[0].value = p_array[0];
	int *p_low = new int[size]; p_low[0] = 0;
	T *p_value = new T[size]; p_value[0] = p_array[0];
	for (int j = 1; j < size; ++j)
	{
		if (p_value[j - 1] > 0)
		{
			p_value[j] = p_array[j] + p_value[j - 1];
			p_low[j] = p_low[j - 1];
		}
		else
		{
			p_value[j] = p_array[j];
			p_low[j] = j;
		}
		if (p_value[j] > p_solus[j - 1].value)
		{
			p_solus[j].low = p_low[j];
			p_solus[j].high = j;
			p_solus[j].value = p_value[j];
		}
		else
		{
			p_solus[j].low = p_solus[j - 1].low;
			p_solus[j].high = p_solus[j - 1].high;
			p_solus[j].value = p_solus[j - 1].value;

		}
	}
	solution<T> *p_ret = new solution<T>;
	p_ret->low = p_solus[size - 1].low;
	p_ret->high = p_solus[size - 1].high;
	p_ret->value = p_solus[size - 1].value;
	delete[]p_solus; delete[]p_low; delete[]p_value;
	return p_ret;
}

template <class T>
solution<T> * violent_solution(T *p_array, int size)
{ //time complexity: O(N^2)
	int low = -1, high = -1;
	T value = NINF, sum = 0;
	T **p_sum = new T *[size + 1]; p_sum[0] = NULL;
	for (int len = 1; len <= size; ++len)
	{
		int upper_bound = size - len + 1;
		p_sum[len] = new T[upper_bound];
		//for (int i = 0; i < upper_bound; ++i)
	}
	for (int i = 0; i < size; ++i)
	{
		p_sum[1][i] = p_array[i];
		sum = p_sum[1][i];
		if (sum > value)
		{
			value = sum;
			low = i;
			high = i;
		}
	}
	for (int len = 2; len <= size; ++len)
	{
		int upper_bound = size - len + 1;
		for (int i = 0; i < upper_bound; ++i)
		{ //sum[i:j] = sum[i:j-1] + A[j], j = i + len - 1
			p_sum[len][i] = p_sum[len - 1][i] + p_array[i + len - 1]; 
			sum = p_sum[len][i];
			if (sum > value)
			{
				value = sum;
				low = i;
				high = i + len - 1;
			}
		}
	}
	solution<T> *p_ret = new solution<T>;
	p_ret->low = low; p_ret->high = high; p_ret->value = value;
	for (int len = 1; len <= size; ++len)
	{
		delete[]p_sum[len];
		p_sum[len] = NULL;
	}
	delete[]p_sum; p_sum = NULL;
	return p_ret;
}

int main()
{
	int nums = 0x00005000, gap = 100, lower_bound = -50;
	int *p_arr = new int[nums];
	for (int i = 0; i < nums; ++i)
	{
		p_arr[i] = rand() % gap + lower_bound;
		cout << p_arr[i] << ", ";
	}
	cout << "\n------\n";

	solution<int> *p_recur_answer = NULL;
	clock_t start_1, finish_1; double duration_1;
	start_1 = clock();
	p_recur_answer = recur_max_subarr(p_arr, 0, nums - 1);
	finish_1 = clock();
	duration_1 = (double)(finish_1 - start_1) / CLOCKS_PER_SEC;
	cout << "(" << p_recur_answer->low << ", " << p_recur_answer->high << ", "
		<< p_recur_answer->value << ")";
	cout << " time of recursive solution: " << setprecision(12) << duration_1;
	cout << "\n------\n";

	solution<int> *p_dynam_answer = NULL;
	clock_t start_2, finish_2; double duration_2;
	start_2 = clock();
	p_dynam_answer = dynamic_max_subarr(p_arr, nums);
	finish_2 = clock();
	duration_2 = (double)(finish_2 - start_2) / CLOCKS_PER_SEC;
	cout << "(" << p_dynam_answer->low << ", " << p_dynam_answer->high << ", "
		<< p_dynam_answer->value << ")";
	cout << " time of dynamic programming solution: " << setprecision(12) << duration_2;
	cout << "\n------\n";

	clock_t start_3, finish_3; double duration_3;
	start_3 = clock();
	solution<int> *p_viole_answer = violent_solution(p_arr, nums);
	finish_3 = clock();
	duration_3 = (double)(finish_3 - start_3) / CLOCKS_PER_SEC;
	cout << "(" << p_viole_answer->low << ", " << p_viole_answer->high << ", "
		<< p_viole_answer->value << ")";
	cout << " time of violent solution: " << setprecision(12) <<duration_3;
	cout << "\n------\n";

    return 0;
}

