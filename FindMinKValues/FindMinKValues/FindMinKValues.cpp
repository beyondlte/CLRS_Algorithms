// FindMinKValues.cpp : Defines the entry point for the console application.
// https://github.com/beyondlte/The-Art-Of-Programming-By-July/blob/master/ebook/zh/02.01.md

#include "stdafx.h"
#include <algorithm> // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>

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

void FindMinKValuesHeap(int *ar, int n, int k)
{
	std::vector<int> v(ar, ar+k);
	// vector v(begin, end) same as below, push elements from begin to end
	//for (int i = 0; i < k; ++i)
	//	v.push_back(ar[i]);

	std::vector<int>::iterator it;

	std::make_heap(v.begin(), v.end());

	for (it = v.begin(); it != v.end(); ++it)
		printf("%d,", *it);
	printf("\n");

	printf("\n%d\n", v.front());
	for (int i = k; i < n; ++i)
	{
		if (ar[i] <= v.front())
		{
			std::pop_heap(v.begin(), v.end());
			v.pop_back();
			v.push_back(ar[i]);
			std::push_heap(v.begin(), v.end());
		}
	}

	for (it = v.begin(); it != v.end(); ++it)
		printf("%d,", *it);
	printf("\n");
}
/*
//QuickSelect put the kth min to a[k-1], it's recursive
void QuickSelect(int a[], int k, int left, int right)
{
	int i, j;
	int pivot;

	if (left + k <= right)
	{
		pivot = median3(a, left, right);
		//取三数中值作为枢纽元，可以很大程度上避免最坏情况
		i = left; j = right - 1;
		for (;;)
		{
			while (a[++i] < pivot){}
			while (a[--j] > pivot){}
			if (i < j)
				swap(&a[i], &a[j]);
			else
				break;
		}
		//重置枢纽元
		swap(&a[i], &a[right - 1]);

		if (k <= i)
			QuickSelect(a, k, left, i - 1);
		else if (k > i + 1)
			QuickSelect(a, k, i + 1, right);
	}
	else
		InsertSort(a + left, right - left + 1);
}
*/
int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 6, 7, 8, 3, 4, 2, 1, 9 };
	int len = sizeof(array) / sizeof(array[0]);
	int k = 5;

	//FindMinKValues(array, len, k);
	//for (int i = 0; i < k; ++i)
	//{
	//	printf("%d ", array[i]);
	//}
	printf("\n");

	FindMinKValuesHeap(array, len, k);
	return 0;
}

