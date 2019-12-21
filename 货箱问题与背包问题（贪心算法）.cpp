// 货箱问题与背包问题（贪心算法）.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <queue>
#include <vector>

using std::cin;
using std::cout;
using std::iterator;
using std::priority_queue;
using std::vector;

template <class W, class V>
struct box
{
	W weight;
	V value;
	int index;
	box(W weight, V value, int index) 
	{ this->weight = weight; this->value = value; this->index = index; }
	bool operator<(const box<W, V> &the_box) const
	{ return (value / weight) < (the_box.value / the_box.weight); } //定义优先级规则
};

template <class W, class V>
void heapSort(vector<box<W, V> > &vec)
{
	if (vec.empty())
	{
		cout << "The vector to be sorted is empty!\n";
		return;
	}
	priority_queue<box<W, V> > max_heap; //默认声明大根堆
	vector<box<W, V> >::iterator iter = vec.begin();
	while (!vec.empty())
	{
		max_heap.push(vec.front());
		vec.erase(iter);
		iter = vec.begin();
	}
	while (!max_heap.empty())
	{
		vec.push_back(max_heap.top());
		max_heap.pop();
	}
}

template <class W, class V>
void boxLoading(const double max_weight, vector<box<W, V> > &box_vec)
{
	if (max_weight < 0 || box_vec.empty())
	{
		cout << "Invalid situation!\n";
		return;
	}
	heapSort(box_vec);
	vector<box<W, V> >::iterator iter = box_vec.begin();
	vector<int> box_index;
	double remain_weight = max_weight;
	while (iter != box_vec.end())
	{
		if (remain_weight < iter->weight)
			break;
		box_index.push_back(iter->index);
		remain_weight -= iter->weight;
		++iter;
	}
	if (box_index.empty())
	{
		cout << "This algorithm does not find a solution!\n";
		return;
	}
	for (int i : box_index)
		cout << "box " << i << ", ";
	cout << "\n";
}

int main()
{
	const double MAX_WEIGHT = 50.0;
	vector<box<double, double> > ship;
	int total_box = 30;
	for (int i = 0; i < total_box; ++i)
	{
		double w = (rand() % 100 + 10) / 10.0;
		double v = (rand() % 1000 + 100) / 1.0;
		box<double, double> the_box(w, v, i + 1);
		ship.push_back(the_box);
	}
	vector<box<double, double> >::iterator box_iter = ship.begin();
	for (; box_iter != ship.end(); ++box_iter)
		cout << "box " << box_iter->index << ": "
		<< box_iter->weight << ", " << box_iter->value << "\n";
	boxLoading(MAX_WEIGHT, ship);
	return 0;
}

