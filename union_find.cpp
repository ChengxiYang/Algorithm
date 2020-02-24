// union_find.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include "union_find.h"

class UnionFind
{
public:
	UnionFind(int vertex_num);
	int find(int p); //find component id of p
	void union_component(int p, int q); //add connection between p and q
	bool is_connected(int p, int q); //return true if p and q in same component
protected:
	int vertex_num;
	int *p_index;
	int *p_size;
	int component_num;
};

UnionFind::UnionFind(int vertex_num)
{
	this->vertex_num = vertex_num;
	component_num = vertex_num;
	p_index = new int[vertex_num + 1];
	p_size = new int[vertex_num + 1];
	p_index[0] = -1; p_size[0] = 0;
	for (int i = 1; i <= vertex_num; ++i)
	{
		p_index[i] = i;
		p_size[i] = 1;
	}
}

int UnionFind::find(int p)
{
	while (p != p_index[p])
	{
		p_index[p] = p_index[p_index[p]]; //path-compression
		p = p_index[p];
	}
	return p;
}

bool UnionFind::is_connected(int p, int q)
{
	return find(p) == find(q);
}

void UnionFind::union_component(int p, int q)
{
	int root_p = find(p);
	int root_q = find(q);
	if (root_p == root_q)
		return;
	if (p_size[p] < p_size[q])
	{
		p_index[root_p] = root_q;
		p_size[root_q] += p_size[root_p];
	}
	else
	{
		p_index[root_q] = root_p;
		p_size[root_p] += p_size[root_q];
	}
	--component_num;
}

int main()
{
    return 0;
}

