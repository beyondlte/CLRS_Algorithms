// RotateLinkedList.cpp : Defines the entry point for the console application.
// Question: Given a linked list and a number, rotate the list to the right by the number of places
// Example:  1->2->3->4->5, k = 2 ------> 3->4->5->1->2


#include "stdafx.h"
#include <stdlib.h>

typedef struct Node{
	int val;
	struct Node *next;
}Node;

Node * insertList(Node *H, int key)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->val = key;
	newNode->next = NULL;

	Node *p = H;
	newNode->next = p;
	p = newNode;
	return p;
}

void printList(Node *H)
{
	while (H != NULL)
	{
		printf("%d->", H->val);
		H = H->next;
	}
	printf("\n");
}

// rotate the list
// first link the last node to the head
// then break the list at the kth node
Node * rotateList(Node *H, int k)
{
	Node *p = H;
	int m = 0; 
	while (H->next != NULL)
	{
		H = H->next;
		m++;
	}
	H->next = p;
	// adjust m to be the length of the list
	m++;
	// as we need to move it to right by k, so we move the list from head by (m-k)
	// we first move it by (m-k) - 1, then break the list for next node
	m = m - k - 1;
	while (m--)
	{
		p = p->next;
	}
	// now we can reuse H, no need to use a new pointer
	H = p->next;
	p->next = NULL;
	return H;
}
int _tmain(int argc, _TCHAR* argv[])
{
	Node *L = NULL;
	int A[] = { 1, 2, 3, 4, 5 };
	for (int i = sizeof(A)/sizeof(A[0])-1; i >= 0; --i)
		L = insertList(L, A[i]);

	L = rotateList(L, 2);
	printList(L);
	return 0;
}

