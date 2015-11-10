// BmF_CLRS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

typedef struct _Edge{
	char src, dest;
	int weight;
}Edge;

template <class T> class Graph
{
	int V;
	int E;
	T *parent;
	int *key;
	std::vector<Edge> *edge;
public:
	Graph(int v, int e);
	void addEdge(T src, T dest, int weight);
	void showEdge();
	void BellmanFordShortestPath();
	int mapVertexToIndex(T s);
};

template <class T> Graph<T>::Graph(int v, int e)
{
	this->V = v;
	this->E = e;
	parent = new T[this->V];
	key = new int[this->V];
	for (int v = 0; v < this->V; ++v)
		key[v] = 100000;
	// V vectors, each vector is for one vertex
	edge = new std::vector<Edge>[V];
}

template <class T> void Graph<T>::addEdge(T src, T dest, int weight)
{
	std::vector<Edge>::iterator it;
	int v;
	v = mapVertexToIndex(src);

	it = edge[v].begin();

	Edge newE;
	newE.src = src;
	newE.dest = dest;
	newE.weight = weight;

	it = edge[v].insert(it, newE);
}

template <class T> void Graph<T>::showEdge()
{
	std::vector<Edge>::iterator it;

	for (int v = 0; v < V; ++v)
	{
		std::cout << "vertex " << v << ":";
		for (it = edge[v].begin(); it != edge[v].end(); ++it)
			std::cout << "-" << (*it).dest;

		std::cout << "\n";
	}
}

template <class T> void Graph<T>::BellmanFordShortestPath()
{
	std::vector<Edge>::iterator it;

	/*
	for (int v; v < V; ++v)
	{
		for (it = edge[v].begin(); it != edge[v].end(); ++it)
		{
			if (key[v] > key[u] + (*it).weight)
			{
				key[v] = key[u] + (*it).weight);
				parent[v] = u;
			}
		}
	}
	*/
}

template <class T> int Graph<T>::mapVertexToIndex(T src)
{
	int v;
	if (src == 's')
		v = 0;
	else if (src == 't')
		v = 1;
	else if (src == 'x')
		v = 2;
	else if (src == 'y')
		v = 3;
	else if (src == 'z')
		v = 4;
	return v;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Graph<char> g(5, 10);
	g.addEdge('s', 't', 6);
	g.addEdge('s', 'y', 7);
	g.addEdge('t', 'x', 5);
	g.addEdge('t', 'y', 8);
	g.addEdge('t', 'z', 2);
	g.addEdge('x', 't', -2);
	g.addEdge('y', 'x', -3);
	g.addEdge('y', 'z', 9);
	g.addEdge('z', 's', 2);
	g.addEdge('z', 'x', 7);
	g.showEdge();
	return 0;
}

