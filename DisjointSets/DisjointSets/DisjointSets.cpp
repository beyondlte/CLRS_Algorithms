// DisjointSets.cpp : Defines the entry point for the console application.
// This is the linked-list representation, not efficient
// The first part is struct version, the second part is class version
// One improvement is: weighted-union heuristic
// Always merge short set to long set, assuming each set maintains the number of objects in the set

/*  Struct version in plain C */
/*
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

// NodeAddress is used to save each node's address
long NodeAddress[10] = {0};
int n = 0;
struct DSETs;

// data structure of the element node
// each node has value, next pointer, and a pointer linked back to its set
typedef struct Node{
	Node *next;
	char val;
	DSETs *setPtr;
}Node;

// data structure of disjoint sets: each set has a head, and a tail, which points to a node
typedef struct DSETs{
	Node *head;
	Node *tail;
} DSETs;

DSETs *MakeSet(char s)
{
	// first allocate memory for a new set
	DSETs *newSet = (DSETs *)malloc(sizeof(DSETs));
	// then allocate memory for a new node, and link it to set's head and tail
	newSet->head = (Node *)malloc(sizeof(Node));
	newSet->tail = newSet->head;

	// assign value to head, and link it to set
	Node *nHead = newSet->head;
	NodeAddress[n++] = (long)nHead;
	nHead->val = s;
	nHead->setPtr = newSet;
	nHead->next = NULL;

	return newSet;
}

void PrintSet(DSETs *s)
{
	Node *p = s->head;
	printf("Printing set with pointer %x, and elemetns are: ", p);
	while (p != NULL)
	{
		printf("%c\t", p->val);
		p = p->next;
	}
	printf("\n");
}

void UnionSets(DSETs *ds1, DSETs *ds2)
{
	Node *curN = ds2->head;

	while (curN != NULL)
	{
		// first search ds1, check if curN is already in ds1
		Node *n1 = ds1->head;
		while (n1 != NULL)
		{
			if (n1->val != curN->val)
				n1 = n1->next;
			else
				break;
		}

		// this means curN is not in ds1, so append curN to ds1
		if (n1 == NULL)
		{
			ds1->tail->next = curN;
			ds1->tail = curN;
			curN->setPtr = ds1;
			curN = curN->next;
		}
		// otherwise, skip curN
		// this is not necessary, can be combined with curN=curN->next above
		else if (n1 != NULL)
			curN = curN->next;
	}
	// finally set ds1's new tail->next
	ds1->tail->next = NULL;
}

int _tmain(int argc, _TCHAR* argv[])
{

	DSETs *s1 = MakeSet('a');
	DSETs *s2 = MakeSet('b');
	DSETs *s3 = MakeSet('c');
	DSETs *s4 = MakeSet('b');
	PrintSet(s1);
	PrintSet(s2);
	UnionSets(s1, s2);
	UnionSets(s3, s4);
	PrintSet(s1);
	UnionSets(s1, s3);
	PrintSet(s1);

	for (int i = 0; i < 10; i++)
	{
		printf("%p\t", NodeAddress[i]);
	}
	printf("\n");
	return 0;
}
*/

/* Object oriented version*/
#include "stdafx.h"
#include <iostream>
using namespace std;

long NodeAddress[10] = {0};
int n = 0;

template <class T> class DisjSetClass {
public:
	struct DSETs;
	struct Node{
		T val;
		Node *next;
		DSETs *setPtr;
	};
	struct DSETs{
		Node *head;
		Node *tail;
	};
	DisjSetClass(){}
	DSETs* MakeSet(T a);
	void PrintSet(DSETs *s);
	void UnionSet(DSETs *ds1, DSETs *ds2);
};

template<class T> typename DisjSetClass<T>::DSETs* DisjSetClass<T>::MakeSet(T a)
{
	DSETs *newSet = new DSETs;
	newSet->head = new Node;
	newSet->tail = newSet->head;

	Node *np = newSet->head;
	NodeAddress[n++] = (long)np;
	np->val = a;
	np->setPtr = newSet;
	np->next = NULL;

	return newSet;
}

template<class T> void DisjSetClass<T>::PrintSet(DSETs *s)
{
	Node *p = s->head;
	cout << "Printing set with pointer " << p << " and elemetns are: ";
	while (p != NULL)
	{
		cout << p->val << "\t";
		p = p->next;
	}
	cout << "\n";
}

template<class T> void DisjSetClass<T>::UnionSet(DSETs *ds1, DSETs *ds2)
{

}

int main()
{
	DisjSetClass<char> ds;
	DisjSetClass<char>::DSETs *s1 = ds.MakeSet('a');
	DisjSetClass<char>::DSETs *s2 = ds.MakeSet('b');
	DisjSetClass<char>::DSETs *s3 = ds.MakeSet('c');
	DisjSetClass<char>::DSETs *s4 = ds.MakeSet('d');
	ds.PrintSet(s1);
	ds.PrintSet(s3);
	return 1;
}