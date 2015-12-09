// SearchRotatedSortedArray_lc002.cpp : Defines the entry point for the console application.
// {4 5 6 7 8 9 0 1 2 3} -> find 7

#include "stdafx.h"

// my algorithm: find the rotated point, then binary search each part recursively/non-recursively
int BinarySearch(int *s, int h, int t, int val)
{
	if (h == t)
	{
		// while h==t, we need to check if val is s[h] or not
		if (s[h] == val)
			return h;
		else
			return -1;
	}

	int m = (h + t) / 2;
	if (val < s[m])
		return BinarySearch(s, h, m-1, val);
	else if (val > s[m])
		return BinarySearch(s, m + 1, t, val);
	else if (val == s[m])
		return m;
}

int BinarySearchNonRecur(int *s, int h, int t, int val)
{
	while (h != t)
	{
		int m = (h + t) / 2;
		if (val == s[m])
			return m;
		if (val < s[m])
			t = m-1;
		else
			h = m+1;
	}
	if (val == s[h])
		return h;
	else
		return -1;
}

int searchRotatedSortedArray(int *s, int n, int val)
{
	int i;
	int ret;
	for (i = 0; i < n-1; ++i)
	{
		if (s[i] > s[i + 1])
			break;
	}
	if (val >= s[0] && val <= s[i])
	{
		ret = BinarySearch(s, 0, i, val);
	}
	else if (val >= s[i + 1] && val <= s[n - 1])
	{
		ret = BinarySearch(s, i + 1, n - 1, val);
	}
	else
		ret = -1;

	return ret;
}

// algorithm from leetcode solution, just do binary search regardless the rotation
int searchRotatedSortedArrayBinary(int *s, int n, int val)
{
	int i = 0;
	int j = n;
	while (i != j)
	{
		int m = (j+i) / 2;
		if (val == s[m])
			return m;
		if (s[i] < s[m]) // which means s[i,..., m] must be monotonously increasing
		{
			if (val >= s[i] && val <= s[m])
				j = m;
			else
				i = m + 1; // the value may be in s[m+1, ..., n-1] which has the rotation pivot, but we just keep it unchanged and go to next iteration 
						   // we narraow down the range from [i,j] to [m+1,j]
		}
		else // which means s[i]>=s[m], then s[i,...,m] contains the rotation pivot
		{
			if (val >= s[m] && val <= s[j-1]) // s[m+1,...,n-1] is monotonously increasing
				i = m + 1;
			else // then value may be in s[i,...,m], although it contains rotation pivot, we don't care, we narrow down the range from [i,j] to [i,m] 
				j = m;
		}
	}
	return -1;
}

// how about array with duplications?
// only when the duplicates occurs on both the beginning and and end will affect us
// owtherwise, if dups are in the middle, then after cutting the string half, each half will always be monotonously increasing
// so when dup is on the beginning, we just need simply to skip it if s[first] == s[m]
int searchRotatedSortedArrayBinaryDup(int *s, int n, int val)
{
	int i = 0;
	int j = n;
	while (i != j)
	{
		int m = (j+i) / 2;
		if (val == s[m])
			return m;
		if (s[i] < s[m]) // which means s[i,..., m] must be monotonously increasing
		{
			if (val >= s[i] && val <= s[m])
				j = m;
			else
				i = m + 1; // the value may be in s[m+1, ..., n-1] which has the rotation pivot, but we just keep it unchanged and go to next iteration 
						   // we narraow down the range from [i,j] to [m+1,j]
		}
		else if (s[i] >= s[m])
		{
			if (val >= s[m] && val <= s[j - 1]) // s[m+1,...,n-1] is monotonously increasing
				i = m + 1;
			else // then value may be in s[i,...,m], although it contains rotation pivot, we don't care, we narrow down the range from [i,j] to [i,m] 
				j = m;
		}
		else if (s[i] == s[m])
			i++;
	}
	return -1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int str[] = { 3, 4, 5, 6, 7, 8, 0, 1, 2, 3, 3 }; // { 4, 5, 6, 7, 8, 9, 0, 1, 2, 3 };
	int len = sizeof(str) / sizeof(str[0]);
	int val;
	int ret;
	for (val = 0; val <= 9; ++val)
	{
		ret = searchRotatedSortedArrayBinaryDup(str, len, val);
		printf("val = %d, ret = %d\n", val, ret);
	}
	return 0;
}

