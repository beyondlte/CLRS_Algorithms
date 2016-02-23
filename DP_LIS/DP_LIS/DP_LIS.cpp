// DP_LIS.cpp : Defines the entry point for the console application.
// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/

// illustration:
// {3, 4, 7, 2, 5, 10}
// L[i] = 1 + Max(L[j]), if j<i && a[j] < a[i]
//      = 1, otherwise
// L[0] = 1
// L[1] = 1+ Max(L[0]) as 0<i and a[0]<a[1]
// L[1] = 2
// L[2] = 1 + Max(L[0], L[1]) as 0,1 <2, a[0], a[1] < a[2]
// L[2] = 1 + Max(1, 2) = 3
// L[3] = 1, as a[0], a[1], a[2] > a[3]
// L[4] = 1 + Max(L[0], L[1], L[3])
// L[4] = 1 + Max(1,2,1) = 1+2 = 3
#include "stdafx.h"

/* A Naive C/C++ recursive implementation of LIS problem */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* To make use of recursive calls, this function must return
two things:
1) Length of LIS ending WITH element arr[n-1]. We use max_ending_here for this purpose
for n = 1, max_ending_here = 1
for n = 2, length of LIS ending with arr[n-1]=arr[1] = 22, is 2, i.e. {10,22}
for n = 3, length of LIS ending with arr[n-1]=arr[2] = 9, is 1 (res=1), i.e. {9}
for n = 4, length of LIS ending with arr[n-1]=arr[3] = 33, is 3, i.e. {10,22,33}

2) Overall maximum as the LIS may end with an element before arr[n-1], max_ref is used this purpose.
The value of LIS of full array of size n is stored in *max_ref which is our final result */
int _lis(int arr[], int n, int *max_ref)
{
	/* Base case */
	if (n == 1)
		return 1;

	// 'max_ending_here' is length of LIS ending with arr[n-1]
	int res, max_ending_here = 1;

	// Recursively get all LIS ending with arr[0], arr[1] ... arr[n-2]. 
	// If arr[i-1] is smaller than arr[n-1], and max ending with arr[n-1] needs to be updated, then update it 
	for (int i = 1; i < n; i++)
	{
		res = _lis(arr, i, max_ref);
		printf("i=%d: res=%d\n", i, res);
		printf("i=%d: max_ref =%d\n", i, *max_ref);
		// for arr[i], we check if arr[i-1] is < arr[n-1] (why?), if so, it means arr[i-1] can be included into LIS
		// so res (ending with arr[i-1]) will be increased by 1, then we check if res+1 is larger than the max length so far
		if (arr[i - 1] < arr[n - 1] && res + 1 > max_ending_here)
			max_ending_here = res + 1;
	}

	// Compare max_ending_here with the overall max. And 
	// update the overall max if needed
	if (*max_ref < max_ending_here)
		*max_ref = max_ending_here;

	// Return length of LIS ending with arr[n-1]
	return max_ending_here;
}

// The wrapper function for _lis()
int lis(int arr[], int n)
{
	// The max variable holds the result
	int max = 1;

	// The function _lis() stores its result in max
	_lis(arr, n, &max);

	// returns max
	return max;
}

void DP_lis(int arr[], int n)
{
	int *L = (int *)malloc(sizeof(int)*n);
	int *P = (int *)malloc(sizeof(int)*n);

	int i, j, max;

	for (i = 0; i < n; ++i)
	{
		L[i] = 1;
		P[i] = 0;
		for (j = 0; j < i; ++j)
		{
			if (arr[j] < arr[i] && L[i] < L[j] + 1)
			{
				P[i] = j;
				L[i] = L[j] + 1;
			}
		}
	}
	/* pick maximum of all LIS values*/
	max = 0;
	for (i = 0; i < n; i++)
	{
		printf("L[%d] = %d\n", i, L[i]);
		if (max < L[i])
			max = L[i];
	}
	for (i = 0; i < n; i++)
		printf("%d ", P[i]);
	printf("\nMax length of LIS = %d\n", max);
}

/*
O(NlogN) algorithm: http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/
{0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15}

A[0] = 0. Case 1. There are no active lists, create one.
0.
-----------------------------------------------------------------------------
A[1] = 8. Case 2. Clone and extend.
0.
0, 8.
-----------------------------------------------------------------------------
A[2] = 4. Case 3. Clone, extend and discard.
0.
0, 4.
0, 8. Discarded
-----------------------------------------------------------------------------
A[3] = 12. Case 2. Clone and extend.
0.
0, 4.
0, 4, 12.
-----------------------------------------------------------------------------
A[4] = 2. Case 3. Clone, extend and discard.
0.
0, 2.
0, 4. Discarded.
0, 4, 12.
here tailtable is 0 2 12, but the active & valid lists are 0,2 and 0,4,12
so here only the length is correct, the tailTable's content is not
if we have {0,8,4,12,2,13}, then the final tailTable will be {0,2,12,13}
the length=4 is correct, but {0,2,12,13} is not
-----------------------------------------------------------------------------
A[5] = 10. Case 3. Clone, extend and discard.
0.
0, 2.
0, 2, 10.
0, 4, 12. Discarded.
-----------------------------------------------------------------------------
A[6] = 6. Case 3. Clone, extend and discard.
0.
0, 2.
0, 2, 6.
0, 2, 10. Discarded.
-----------------------------------------------------------------------------
A[7] = 14. Case 2. Clone and extend.
0.
0, 2.
0, 2, 6.
0, 2, 6, 14.
-----------------------------------------------------------------------------
A[8] = 1. Case 3. Clone, extend and discard.
0.
0, 1.
0, 2. Discarded.
0, 2, 6.
0, 2, 6, 14.
-----------------------------------------------------------------------------
A[9] = 9. Case 3. Clone, extend and discard.
0.
0, 1.
0, 2, 6.
0, 2, 6, 9.
0, 2, 6, 14. Discarded.
-----------------------------------------------------------------------------
A[10] = 5. Case 3. Clone, extend and discard.
0.
0, 1.
0, 1, 5.
0, 2, 6. Discarded.
0, 2, 6, 9.
-----------------------------------------------------------------------------
A[11] = 13. Case 2. Clone and extend.
0.
0, 1.
0, 1, 5.
0, 2, 6, 9.
0, 2, 6, 9, 13.
-----------------------------------------------------------------------------
A[12] = 3. Case 3. Clone, extend and discard.
0.
0, 1.
0, 1, 3.
0, 1, 5. Discarded.
0, 2, 6, 9.
0, 2, 6, 9, 13.
-----------------------------------------------------------------------------
A[13] = 11. Case 3. Clone, extend and discard.
0.
0, 1.
0, 1, 3.
0, 2, 6, 9.
0, 2, 6, 9, 11.
0, 2, 6, 9, 13. Discarded.
-----------------------------------------------------------------------------
A[14] = 7. Case 3. Clone, extend and discard.
0.
0, 1.
0, 1, 3.
0, 1, 3, 7.
0, 2, 6, 9. Discarded.
0, 2, 6, 9, 11.
----------------------------------------------------------------------------
A[15] = 15. Case 2. Clone and extend.
0.
0, 1.
0, 1, 3.
0, 1, 3, 7.
0, 2, 6, 9, 11.
0, 2, 6, 9, 11, 15. <-- LIS List
----------------------------------------------------------------------------
*/

#define ARRAY_SIZE(A) sizeof(A)/sizeof(A[0])

// Binary search (note boundaries in the caller)
// A[] is ceilIndex in the caller
int CeilIndex(int A[], int l, int r, int key)
{
	while (r - l > 1)
	{
		int m = l + (r - l) / 2;
		if (A[m] >= key)
			r = m;
		else
			l = m;
	}
	return r;
}

void printTable(int A[], int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", A[i]);
	printf("\n");
}
int LongestIncreasingSubsequenceLength(int A[], int size)
{
	// Add boundary case, when array size is one

	int *tailTable = (int *)malloc(sizeof(int)*size);
	int len; // always points empty slot

	memset(tailTable, 0, sizeof(tailTable[0])*size);

	tailTable[0] = A[0];
	len = 1;
	for (int i = 1; i < size; i++)
	{
		if (A[i] < tailTable[0])
			// new smallest value
			tailTable[0] = A[i];

		else if (A[i] > tailTable[len - 1])
			// A[i] wants to extend largest subsequence
			tailTable[len++] = A[i];

		else
			// A[i] wants to be current end candidate of an existing
			// subsequence. It will replace ceil value in tailTable
			// CeilIndex is using Binary search, it's O(lgN)
			tailTable[CeilIndex(tailTable, -1, len - 1, A[i])] = A[i];
		printTable(tailTable, len);
	}

	free(tailTable);
	return len;
}

/* Driver program to test above function */
int main()
{
	// int arr[] = { 10, 22, 9, 33, 21, 50 }; // , 41, 60, 12, 61
	// int arr[] = { 10, 20, 30, 33, 7, 8, 35}; // , 41, 60, 12, 61
	// int arr[] = { 2, 5, 3, 7, 11, 8, 9 };
	// int arr[] = { 0, 8, 4, 12, 2, 10};
	int arr[] = { 0, 8, 4, 6, 2, 5, 6, 7, 8};
	int n = sizeof(arr) / sizeof(arr[0]);
	// printf("Length of LIS is %d\n", lis(arr, n));
	// DP_lis(arr, n);
	int ret = LongestIncreasingSubsequenceLength(arr, n);
	printf("length of LIS = %d\n", ret);
	return 0;
}