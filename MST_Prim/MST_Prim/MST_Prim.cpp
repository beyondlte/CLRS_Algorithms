// MST_Prim.cpp : Defines the entry point for the console application.
// C++ version with OOP for Minimum Spanning Tree using Prim's algorithm 
// http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

// structure of edge of graph
template <class T> struct Edge
{
	T src, dest;
	int weight;
};

// class of Graph
// member variables:
//		V: num of vertices
//		E: num of edges
//		parent: array to save each vertex's parent for MST display
//		key: array to save minimum weight of any edge connecting v to MST   
//			using array, we can map index(vertex) to key
//			we can also use vector or priority queue, but we need to get the index using it-vector.begin(), or std::distance(vec.begin(), it)
//		mstSet: bool array to indicate if a vertex is in the MST or not, 
//			we call "vertices in false" as set Q
//			"vertices in true" as set V
//		edge: array of edges in the graph
// member functions:
//		addEdge: adding edge to the graph, here we don't use adjacent array
//		primMST: Prism's algorithm
//		minKey: utility to find vertex in Q, whose key is the minimum
//		printMST: print out the MST
template <class T> class Graph
{
	int V, E;
	int *parent;
	int *key;
	bool *mstSet;
	vector<struct Edge<T>> *edge;
public:
	Graph(int V, int E);
	void addEdge(T src, T dest, int w);
	void primMST();
	T minKey();
	void printMST();
};

template <class T> Graph<T>::Graph(int V, int E)
{
	this->V = V;
	this->E = E;
	edge = new vector<struct Edge<T>>();
	parent = new int[V];
	key = new int[V];
	mstSet = new bool[V];
	for (int i = 0; i < V; i++)
	{
		// initialize parent, key and mstSet
		parent[i] = -1;
		key[i] = 1000;
		mstSet[i] = false;
	}
	// initialize starting vertex's key to 0
	key[0] = 0;
}

template <class T> void Graph<T>::addEdge(T src, T dest, int w)
{
	vector<struct Edge<T>>::iterator it;
	it = edge->begin();
	struct Edge<T> e; 
	e.src = src;
	e.dest = dest;
	e.weight = w;
	it = edge->insert(it, e);
}

template <class T> T Graph<T>::minKey()
{
	int min = 100000;
	T minIndex=0;
	for (int v = 0; v < V; v++)
	{
		// only check v in Q ("vertices in false")
		// find the min key
		if (mstSet[v] == false && key[v] < min)
		{
			min = key[v];
			minIndex = v;
		}
	}
	return minIndex;
}

template <class T> void Graph<T>::primMST()
{
	// set v to -1 (here we cast it to type T)
	T v= (T)-1;
	for (int count = 0; count < V; count++)
	{
		// find the vertex u with min key
		T u = minKey();
		cout << "u = " << u << "\n";
		// set u to MST
		mstSet[u] = true;

		// search all edges, check each edge's src or dest, 
		// if it is u, then the other vertex on the edge is v (adjacent of u) 
		vector<struct Edge<T>>::iterator it;
		for (it = edge->begin(); it != edge->end(); it++)
		{
			// find if u has an adjacent vertex, if so, set it to v
			if ((*it).src == u)
				v = (*it).dest;
			else if ((*it).dest == u)
				v = (*it).src;
			// only for valid v (!=-1), compare the edge's weigt with its key
			// if weight is smaller, update the key to the weight
			// then set v's parent to u, means u-v belongs to MST
			if (v!= (T)-1 && (*it).weight < key[v] && mstSet[v] == false)
			{
				parent[v] = u;
				key[v] = (*it).weight;
			}
		}
	}
}

template <class T> void Graph<T>::printMST()
{
	cout << "MST is: \n";
	// because the starting node i 0, so we print MST from vertex 1
	for (int v = 1; v < V; v++)
	{
		cout << v << "-" << parent[v] << " ";
	}
	cout << "\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	Graph<int> g(4, 5);
	g.addEdge(0, 1, 10);
	g.addEdge(0, 2, 6);
	g.addEdge(0, 3, 5);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 4);
	*/
	Graph<int> g(5, 7);
	g.addEdge(0, 1, 2);
	g.addEdge(1, 2, 3);
	g.addEdge(0, 3, 6);
	g.addEdge(1, 3, 8);
	g.addEdge(1, 4, 5);
	g.addEdge(2, 4, 7);
	g.addEdge(3, 4, 9);
	g.primMST();
	g.printMST();
	return 0;
}

