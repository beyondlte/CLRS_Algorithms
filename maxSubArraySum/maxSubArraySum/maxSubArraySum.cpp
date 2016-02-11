// maxSubArraySum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <limits.h>

int max(int a, int b) { return (a > b) ? a : b; }
int max(int a, int b, int c) { return max(max(a, b), c); }

int maxCrossSubArray(int *arr, int lo, int m, int hi)
{
	int sum = 0;
	int left_sum = INT_MIN;
	for (int i = m; i >= lo; i--)
	{
		sum = sum + arr[i];
		if (sum > left_sum)
			left_sum = sum;
	}

	sum = 0;
	int right_sum = INT_MIN;
	for (int i = m+1; i <= hi; i++)
	{
		sum = sum + arr[i];
		if (sum > right_sum)
			right_sum = sum;
	}
	return left_sum + right_sum;


}
int maxSubArraySum(int *arr, int lo, int hi)
{
	if (lo == hi)
		return arr[lo];

	int m = (lo + hi) / 2;

	return max(maxSubArraySum(arr, lo, m),
			   maxSubArraySum(arr, m + 1, hi),
	  		   maxCrossSubArray(arr, lo, m, hi));
}

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { -1, 3, 2, -1, 0, 5, 7, -3, -1 };
	int len = sizeof(array) / sizeof(array[0]);
	int max_sum = maxSubArraySum(array, 0, len-1);
	printf("max sum of subarray is %d\n", max_sum);
	return 0;
}

