// MST_Kruskal.cpp : Defines the entry point for the console application.
// Kruskal's algortihm to find Minimum Spanning Tree of a given connected,
// undirected and weighted graph

/* ----------------        Plain C program, see url below
 * // http://www.geeksforgeeks.org/greedy-algorithms-set-2-kruskals-minimum-spanning-tree-mst/
 * ----------------
 */

/*****************************************************
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

// a structure to represent a weighted edge in graph
struct Edge
{
	int src, dest, weight;
};

// a structure to represent a connected, undirected and weighted graph
struct Graph
{
	// V-> Number of vertices, E-> Number of edges
	int V, E;

	// graph is represented as an array of edges. Since the graph is
	// undirected, the edge from src to dest is also edge from dest
	// to src. Both are counted as 1 edge here.
	struct Edge* edge;
};

// Creates a graph with V vertices and E edges
struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
	graph->V = V;
	graph->E = E;

	graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));

	return graph;
}

// A structure to represent a subset for union-find
struct subset
{
	int parent;
	int rank;
};

// A utility function to find set of an element i
// (uses path compression technique)
int find(struct subset subsets[], int i)
{
	// find root and make root as parent of i (path compression)
	if (subsets[i].parent != i)
		subsets[i].parent = find(subsets, subsets[i].parent);

	return subsets[i].parent;
}

// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], int x, int y)
{
	int xroot = find(subsets, x);
	int yroot = find(subsets, y);

	// Attach smaller rank tree under root of high rank tree
	// (Union by Rank)
	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;

	// If ranks are same, then make one as root and increment
	// its rank by one
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

// Compare two edges according to their weights.
// Used in qsort() for sorting an array of edges
int myComp(const void* a, const void* b)
{
	struct Edge* a1 = (struct Edge*)a;
	struct Edge* b1 = (struct Edge*)b;
	return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(struct Graph* graph)
{
	int V = graph->V;
	// struct Edge result[V];
	struct Edge *result = (struct Edge*)malloc(sizeof(struct Edge)*V);  // Tnis will store the resultant MST
	int e = 0;  // An index variable, used for result[]
	int i = 0;  // An index variable, used for sorted edges

	// Step 1:  Sort all the edges in non-decreasing order of their weight
	// If we are not allowed to change the given graph, we can create a copy of
	// array of edges
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

	// Allocate memory for creating V ssubsets
	struct subset *subsets =
		(struct subset*) malloc(V * sizeof(struct subset));

	// Create V subsets with single elements
	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
	}

	// Number of edges to be taken is equal to V-1
	while (e < V - 1)
	{
		// Step 2: Pick the smallest edge. And increment the index
		// for next iteration
		struct Edge next_edge = graph->edge[i++];

		int x = find(subsets, next_edge.src);
		int y = find(subsets, next_edge.dest);

		// If including this edge does't cause cycle, include it
		// in result and increment the index of result for next edge
		if (x != y)
		{
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}

	// print the contents of result[] to display the built MST
	printf("Following are the edges in the constructed MST\n");
	for (i = 0; i < e; ++i)
		printf("%d -- %d == %d\n", result[i].src, result[i].dest,
		result[i].weight);
	return;
}

// Driver program to test above functions
int main()
{
	// Let us create following weighted graph
	// 10
	// 0--------1
	// |  \     |
	// 6|   5\   |15
	// |      \ |
	// 2--------3
	// 4       
	int V = 4;  // Number of vertices in graph
	int E = 5;  // Number of edges in graph
	struct Graph* graph = createGraph(V, E);


	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 10;

	// add edge 0-2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	// add edge 0-3
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	// add edge 1-3
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	// add edge 2-3
	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;

	KruskalMST(graph);

	return 0;
}
*******************************************************/

/******************************************************
 * C++ version 
 * Two classes: Graph and Subset
 *****************************************************/
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

template <class T_Type> struct Edge
{
	T_Type src, dest;
	int weight;
};

typedef struct _subset
{
	int parent;
	int rank;
}subset;

class Subset
{
	subset *sb;
	int size;
public:
	Subset(int size);
	void showSets();
	int find(int node);
	void Union(int x, int y);
	~Subset();
};

Subset::Subset(int size)
{
	this->size = size;
	sb = new subset[this->size];
	for (int s = 0; s < this->size; s++)
	{
		sb[s].parent = s;
		sb[s].rank = 0;
	}
}

Subset::~Subset()
{
	delete sb;
}

void Subset::showSets()
{
	for (int s = 0; s < this->size; s++)
	{
		cout << sb[s].parent << " " << sb[s].rank << "\n";
	}
}

int Subset::find(int node)
{
	if (sb[node].parent != node)
	{
		sb[node].parent = find(sb[node].parent);
	}

	return sb[node].parent;
}

void Subset::Union(int x, int y)
{
	int xroot = find(x);
	int yroot = find(y);

	if (sb[xroot].rank < sb[yroot].rank)
	{
		sb[xroot].parent = yroot;
	}
	else if (sb[xroot].rank > sb[yroot].rank)
	{
		sb[yroot].parent = xroot;
	}
	else
	{
		sb[yroot].parent = xroot;
		sb[xroot].rank++;
	}

}


template <class T_Type> class Graph
{
	int V, E;
	// define a pointer to a vector, whose element is a struct Edge*
	vector<struct Edge<T_Type>> *edge;

public:
	Graph(int V, int E);
	void addEdge(T_Type s, T_Type d, int w);
	void showEdge();
	void KruskalMST();
	static int myComp(const void* a, const void* b);
	~Graph();
};

template <class T_Type> Graph<T_Type>::Graph(int V, int E)
{
	this->V = V;
	this->E = E;
	// first initialize the edge pointer
	edge = new vector<struct Edge<T_Type>>();
}

template <class T_Type> Graph<T_Type>::~Graph()
{
	delete edge;
}

template <class T_Type> void Graph<T_Type>::addEdge(T_Type s, T_Type d, int w)
{
	vector<struct Edge<T_Type>>::iterator it;
	// find the begin(), then insert
	it = edge->begin();

	// make a new struct Edge* element
	struct Edge<T_Type> e;
	e.src = s;
	e.dest = d;
	e.weight = w;

	//insert it to the vector
	it = edge->insert(it, e);
}

template <class T_Type> void Graph<T_Type>::showEdge()
{
	vector<struct Edge<T_Type>>::iterator it;

	for (it = edge->begin(); it < edge->end(); it++)
	{
		cout << (*it).src << "\t";
		cout << (*it).dest << "\t";
		cout << (*it).weight << "\n";
	}
}

// used for qsort
template <class T_Type> int Graph<T_Type>::myComp(const void* a, const void* b)
{
	// cast to (struct Edge*)
	struct Edge<T_Type>* a1 = (struct Edge<T_Type>*)a;
	struct Edge<T_Type>* b1 = (struct Edge<T_Type>*)b;
	return a1->weight > b1->weight;
}

template <class T_Type> void Graph<T_Type>::KruskalMST()
{ 
	// vector result is used to save the MST result
	vector<struct Edge<T_Type>> result;

	// sort all edges
	// qsort is a pure c function, in order to call it, need to define myComp as static member function
	// they say to use std::sort instead
	// the real solution is this, using callback function...
	// http://p-nand-q.com/programming/cplusplus/using_member_functions_with_c_function_pointers.html
	qsort(&(*edge)[0], edge->size(), sizeof(struct Edge<T_Type>), &Graph::myComp);

	// define V subsets
	Subset SBs(V);

	int e = 0;
	int i = 0;
	// only V-1 edge is needed to be considered
	while (e < V-1)
	{
		// get the edge with min weight 
		struct Edge<T_Type> next_edge = (*edge)[i++];

		// find each edge's vertices' set
		int x = SBs.find(next_edge.src);
		int y = SBs.find(next_edge.dest);

		// if they are not in the sam set, union them into one set
		if (x != y)
		{
			result.push_back(next_edge);
			SBs.Union(x, y);
			// e++ is here, not outside of this if() statement
			// because if x==y, eg. here for edge (0-2)=6, root of 0 == root of 2, they are in the same set
			// so edge 6 won't be added into the result vector
			e++;
		}
	}

	vector<struct Edge<T_Type>>::iterator it;
	cout << "MST is:" << "\n";
	for (it = result.begin(); it < result.end(); it++)
	{
		cout << (*it).src << "\t";
		cout << (*it).dest << "\t";
		cout << (*it).weight << "\n";
	}

}
int main()
{
	Graph<int> g(4, 5);
	g.addEdge(0, 1, 10);
	g.addEdge(0, 2, 6);
	g.addEdge(0, 3, 5);
	g.addEdge(1, 3, 15);
	g.addEdge(2, 3, 4);

	/* to-do-list: support char vertex
	Graph<char> g(4, 4);
	g.addEdge('a', 'b', 10);
	g.addEdge('a', 'c', 30);
	g.addEdge('b', 'd', 20);
	g.addEdge('a', 'd', 25);
	*/

	g.showEdge();
	g.KruskalMST();
	// g.showEdge();
	return 0;
}
