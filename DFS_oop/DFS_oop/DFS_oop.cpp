// DFS_oop.cpp : Defines the entry point for the console application.
// see http://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/

// C++ program to print DFS traversal for a given graph, covering all vertices 
#include "stdafx.h"
#include<iostream>
#include <list>
using namespace std;

class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
	void DFSUtil(int v, bool visited[]);  // A function used by DFS
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void DFS();    // prints DFS traversal of the complete graph
	void listAdj();
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v��s list.
}

void Graph::listAdj()
{
	list<int>::iterator it;
	cout << "Adjacent list:\n";
	for (int v = 0; v < V; ++v)
	{
		cout << v;
		for (it = adj[v].begin(); it != adj[v].end(); ++it)
		{
			cout << "-" << (*it);
		}
		cout << "\n";
	}
}
void Graph::DFSUtil(int v, bool visited[])
{
	// Mark the current node as visited and print it
	visited[v] = true;
	cout << v << " ";

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end(); ++it)
	{
		if (!visited[*it])
			DFSUtil(*it, visited);
	}
}

// The function to do DFS traversal. It uses recursive DFSUtil()
void Graph::DFS()
{
	// Extra array to mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Call the recursive helper function to print DFS traversal
	// starting from all vertices one by one, so for disconnected graph, this algorithm also works
	for (int i = 0; i < V; i++)
	{
		cout << "from vertex " << i << ": ";
		if (visited[i] == false) // it's like u.color == WHITE
			DFSUtil(i, visited);
		cout << "\n";
	}
}

int main()
{
	// Create a graph given in the above diagram
	Graph g(6);
	g.addEdge(0, 1);
	g.addEdge(0, 3);
	g.addEdge(2, 5);
	g.addEdge(3, 4);
	g.addEdge(4, 0);
	g.addEdge(5, 2);
	// show the adj list for each vertex
	g.listAdj();

	// output is: 0,1,3; 2, 5; 4, three disconnected trees

	cout << "Following is Depth First Traversal\n";
	g.DFS();

	return 0;
}

/*
// C++ program to print DFS traversal from a given vertex in a given graph
#include<iostream>
#include <list>

using namespace std;

// Graph class represents a directed graph using adjacency list representation
class Graph
{
int V;    // No. of vertices
list<int> *adj;    // Pointer to an array containing adjacency lists
void DFSUtil(int v, bool visited[]);  // A function used by DFS
public:
Graph(int V);   // Constructor
void addEdge(int v, int w);   // function to add an edge to graph
void DFS(int v);    // DFS traversal of the vertices reachable from v
};

Graph::Graph(int N)
{
V = N; // if Graph(int V), then we need to use this->V = V to distinguish those two Vs
adj = new list<int>[N];
}

void Graph::addEdge(int v, int w)
{
adj[v].push_back(w); // Add vertex w to v��s list.
}

void Graph::DFSUtil(int v, bool visited[])
{
// Mark the current node as visited and print it
visited[v] = true;
cout << v << " ";

// Recur for all the vertices adjacent to this vertex
// check each vertex's adjacent list
list<int>::iterator i;
for (i = adj[v].begin(); i != adj[v].end(); ++i)
{
if (!visited[*i])
DFSUtil(*i, visited);
}
}

// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void Graph::DFS(int v)
{
// Mark all the vertices as not visited
// make a new array to save this
bool *visited = new bool[V];
for (int i = 0; i < V; i++)
visited[i] = false;

// Call the recursive helper function to print DFS traversal
DFSUtil(v, visited);
}

int main()
{
// Create a graph given in the above diagram
Graph g(4);
g.addEdge(0, 1);
g.addEdge(0, 2);
g.addEdge(1, 2);
g.addEdge(2, 0);
g.addEdge(2, 3);
g.addEdge(3, 3);

cout << "Following is Depth First Traversal (starting from vertex 2) \n";
g.DFS(3);

return 0;
}
*/