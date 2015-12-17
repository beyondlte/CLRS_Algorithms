// FindMinKValues.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// intuitive algorithm is sort array, and get the first k, is O(n*lgn)
// improved algorithm
// n*O(k) = O(nk), O(k) is to find max in ar[0...k-1]
void FindMinKValues(int *ar, int n, int k)
{
	int i;
	i = k;
	while (i < n)
	{
		// find the max in ar[0...k-1]
		int maxIx = 0;
		int maxVal = ar[0];
		for (int j = 1; j < k; ++j)
		{
			if (ar[j]>maxVal)
			{
				maxVal = ar[j];
				maxIx = j;
			}
		}

		// swap ar[i] if ar[i] > max of ar[0...k-1], where i is [k...n-1]
		if (ar[i] < maxVal)
		{
			ar[i] ^= ar[maxIx];
			ar[maxIx] ^= ar[i];
			ar[i] ^= ar[maxIx];
		}
		++i;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 8, 7, 6, 3, 2, 4, 1, 9 };
	int len = sizeof(array) / sizeof(array[0]);
	int k = 7;
	FindMinKValues(array, len, k);
	for (int i = 0; i < k; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}

