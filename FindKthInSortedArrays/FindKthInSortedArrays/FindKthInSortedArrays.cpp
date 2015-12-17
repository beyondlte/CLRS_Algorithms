// FindKthInSortedArrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#define min(a,b) (a)<(b)?(a):(b)

// O(M+N)
int FindKthInSortedArrayMerge(int *ar1, int m, int *ar2, int n, int k)
{
	int *ar3 = (int *)calloc((m + n), sizeof(int));

	int i = 0, j = 0;
	int t;
	for (t = 0; t < (m + n); ++t)
	{
		if (i >= m || j >= n)
			break;
		if (ar1[i] < ar2[j]) 
		{
			ar3[t] = ar1[i];
			++i;
		}
		else if (ar1[i] > ar2[j])
		{
			ar3[t] = ar2[j];
			++j;
		}
		else
		{
			ar3[t] = ar1[i];
			while (ar1[i] == ar3[t])
				i++;
			while (ar2[j] == ar3[t])
				j++;
		}
	}
	if (i >= m)
	{
		while (j < n)
		{
			ar3[t] = ar2[j];
			j++;
			t++;
		}
	}
	if (j >= n)
	{
		while (i < m)
		{
			ar3[t] = ar1[i];
			i++;
			t++;
		}
	}

	for (t = 0; t < m + n; ++t)
	{
		printf("ar3[%d] = %d ", t, ar3[t]);
	}
	printf("\n");
	return ar3[k-1];

	/*
	// using sentinel
	int *s1 = (int *)calloc((m + 1), sizeof(int));
	int *s2 = (int *)calloc((n + 1), sizeof(int));
	int i, j;
	for (i = 0; i < m; ++i)
		s1[i] = ar1[i];
	for (j = 0; j < n; ++j)
		s2[j] = ar2[j];
	s1[m] = 10000; // sentinel 
	s2[n] = 10000;

	int *ar3 = (int *)calloc((m + n), sizeof(int));

	i = 0;
	j = 0;

	for (int t = 0; t < m + n; ++t)
	{
		if (s1[i] < s2[j])
		{
			ar3[t] = s1[i];
			i++;
		}
		else if (s1[i] > s2[j])
		{
			ar3[t] = s2[j];
			j++;
		}
		else
		{
			ar3[t] = s1[i];
			// taking care of duplicates
			while (ar3[t] == s1[i])
				i++;
			while (ar3[t] == s2[j])
				j++;
		}
		printf("ar3[%d] = %d ", t, ar3[t]);
	}

	printf("\n");
	return ar3[k-1];
	*/
}

// recursive version
// this doesn't support duplicates
int FindKthInSortedArrayBinary(int *a1, int m, int *a2, int n, int k)
{
	if (m > n)
		return FindKthInSortedArrayBinary(a2, n, a1, m, k);
	if (m == 0)
		return a2[k - 1];
	if (k == 1)
		return min(a1[0], a2[0]);

	int ia = min(k / 2, m);
	int ib = k - ia;

	if (a1[ia - 1] < a2[ib - 1])
		return FindKthInSortedArrayBinary(a1 + ia, m - ia, a2, n, k - ia);
	else if (a1[ia - 1] > a2[ib - 1])
		return FindKthInSortedArrayBinary(a1, m, a2 + ib, n - ib, k - ib);
	else
		return a1[ia - 1];
}

int _tmain(int argc, _TCHAR* argv[])
{
	int ar1[] = { 1, 2, 3, 5, 9 };
	int ar2[] = { 5, 6, 7, 8, 10 };
	int len1, len2;
	len1 = sizeof(ar1) / sizeof(ar1[0]);
	len2 = sizeof(ar2) / sizeof(ar2[0]);
	// int ret = FindKthInSortedArrayMerge(ar1, len1, ar2, len2, 6);
	for (int i = 1; i <= 10; ++i)
	{
		int ret = FindKthInSortedArrayBinary(ar1, len1, ar2, len2, i);
		printf("check %d, ret = %d\n", i, ret);
	}
	return 0;
}

