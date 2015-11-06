// BFS_adjlist_oop.cpp : Defines the entry point for the console application.
// http://www.geeksforgeeks.org/breadth-first-traversal-for-a-graph/
// Program to print BFS traversal from a given source vertex.BFS(int s)
// traverses vertices reachable from s.

#include "stdafx.h"
#include<iostream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

// This class represents a directed graph using adjacency list representation
// so we don't need to create a linked list by ourselves
class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
public:
	Graph(int V);  // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void BFS(int s);  // prints BFS traversal from a given source s
	void showList();
	void showQueue(queue<int> &q);
};

Graph::Graph(int V)
{
	this->V = V;
	// allocate memory to V lists
	adj = new list<int>[V];
}

void Graph::showList()
{
	// first define an interator
	list<int>::const_iterator it;
	for (int i = 0; i < V; i++)
	{
		cout << "vertex " << i << ": " << i;
		for (it = adj[i].begin(); it != adj[i].end(); ++it) {
			cout << "-" << *it;
		}
		cout << "\n";
	}
}
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v¡¯s list.
}

// recursively show the content of a queue
void Graph::showQueue(queue<int> &q)
{
	queue<int> p;
	stack<int> s;
	cout << "show the current queue (right is front, left is tail): ";
	while (!q.empty())
	{
		int x = q.front();
		p.push(x);
		s.push(x);
		q.pop();
	}

	// show queue in reverse mode using stack
	while (!s.empty())
	{
		int x = s.top();
		cout << x << " ";
		s.pop();
	}

	// push data back to q
	while (!p.empty())
	{
		q.push(p.front());
		p.pop();
	}
	cout << "\n";
}
void Graph::BFS(int s)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;

	// Create a queue for BFS
	// or we can use a list instead
	// diff between queue and list: queue is strictly FIFO, list is like a linked-list
	queue<int> queue;

	// Mark the current node as visited and enqueue it
	visited[s] = true;
	queue.push(s);

	// it will be used to get all adjacent vertices of a vertex
	list<int>::iterator it;

	while (!queue.empty())
	{
		showQueue(queue);
		cout << "\n";

		// show the top vertex of the queue 
		s = queue.front();
		cout << "BFS found vertex " << s << "\n";
		// pop_front() only removes the front element, don't return 
		// so we need to use front() to access it before calling pop_front (using list) or pop (using queue)
		queue.pop();

		// Get all adjacent vertices of the dequeued vertex s
		// If an adjacent has not been visited, then mark it visited
		// and enqueue it
		for (it = adj[s].begin(); it != adj[s].end(); ++it)
		{
			// *it is the vertex in s's adjacent list
			if (!visited[*it]) // not visited yet
			{
				visited[*it] = true;
				cout << "enqueue " << *it << ", ";
				queue.push(*it);
			}
		}
		cout << "\n";
	}
}

// Driver program to test methods of graph class
int main()
{
	// Create a graph given in the above diagram
	Graph g(5);
	g.addEdge(0, 1);
	g.addEdge(0, 2);
	g.addEdge(1, 2);
	g.addEdge(2, 0);
	g.addEdge(2, 3);
	g.addEdge(2, 4);
	g.addEdge(3, 3);
	g.showList();

	int start = 2;
	cout << "Following is Breadth First Traversal (starting from vertex " << start << ") \n";
	g.BFS(start);

	return 0;
}