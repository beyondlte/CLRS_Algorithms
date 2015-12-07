// RemovDupInSortedArray_lc001.cpp : Defines the entry point for the console application.
// Remove duplicates in a sorted array: {1,1,2,3,4,4,5} -> {1,2,3,4,5}
// Remove duplicates in a sorted array and duplicates are allowed twice: {1,1,2,3,4,4,5} -> {1,1,2,3,4,4,5}


#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

// i j
// 1 1 2 3 3 4 5

// i   j
// 1 1 2 3 3 4 5
//    /
//   i   j
// 1 2 2 3 3 4 5
//      /
//     i   j
// 1 2 3 3 3 4 5
//     i     j
// 1 2 3 3 3 4 5
//          /
//         /
//        /
//       i     j 
// 1 2 3 4 3 4 5

// i starts from 0, j starts from 1
int removeDuplicatesInArray(int *s, int n)
{
	int i, j;
	i = 0;
	j = 1;

	while (j<n)
	{
		printf("before: i = %d, j = %d\n", i, j);
		if (s[j] != s[i])
		{
			// increase i first, then assign
			s[++i] = s[j];
		}
		++j;
		printf("after: i = %d, j = %d\n", i, j);
	}
	return i;
}



// duplicates are allowed at most twice
//     i = 2
//     j = 2

// only two cases:

// if s[j] == s[i-2], ++j only
//     i j
// 1 1 1 

// if s[j] != s[i-2], s[i] = s[j], then i++, ++j
//     i
//     j
// 1 1 2
int removeDuplicatesInArray2(int *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (s[j] != s[i - 2] || i < 2)
			// more generic, add one more condition i<2 here, it's like in removeDuplicatesInArray3 using else if{i<2} 
			// see removeDuplicatesInArray2Mine 
		{
			// simplified version is s[i++] = s[j];
			// but this is more clear
			if (i != j)
				s[i] = s[j];
			i++;
			// this ++j can be simpilied to outside of if{}
			++j;
		}
		else
			++j;
	}
	return i;
}

// duplicates are allowed at most triple times 
// again, only two cases: 1. s[j] = s[i-2] or s[i-3], then increase j only
//                        2. not 1, then s[i] = s[j], and i++, j++
//       i/j
// 1 1 1 1 (only j++), this also means only when s[j] == s[i-3] == s[i-2], we let j++ only
// 1 1 1 2 (s[i]=s[j], then i++, j++) -> change to 1 1 2 2 or 1 1 2 3
// 1 1 2 2 (s[i]=s[j], then i++, j++) -> change to 1 2 2 2/3
// 1 1 2 3 (s[i]=s[j], then i++, j++) -> change to 1 2 3 3/4
// 1 2 2 2 (s[i]=s[j], then i++, j++) -> change to 2 2 2 2 (same as 1 1 1 1) or 2 2 2 3 (same as 1 1 1 2) 
// 1 2 2 3
// 1 2 3 3
// 1 3 3 3 same as 1 2 2 2 
// 1 2 3 4 same as 1 2 2 2 
int removeDuplicatesInArray3(int *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (s[j] != s[i - 3] || s[j] != s[i - 2])
		{
			// simplified version is s[i++] = s[j];
			// but this is more clear
			if (i != j)
				s[i] = s[j];
			i++;
			// this ++j can be simpilied to outside of if{}
			++j;
		}
		else if (i < 3 && j < 3)
		{
			++i; ++j;
		}
		else
			++j;
	}
	return i;
}

// this generic version is just for illustration
// becasue we need to list all from s[i-dupNo], s[i-(dupNo-1)], ..., to s[i-2]
int removeDuplicatesInArrayGeneric(int *s, int n, int dupNo)
{
	int i, j;
	i = dupNo;
	j = dupNo;
	while (j < n)
	{
		if (s[j] != s[i - dupNo] || s[j] != s[i - 3] || s[j] != s[i - 2])
		{
			// simplified version is s[i++] = s[j];
			// but this is more clear
			if (i != j)
				s[i] = s[j];
			i++;
			// this ++j can be simpilied to outside of if{}
			++j;
		}
		else
			++j;
	}
	return i;
}
// so if duplicate is allowed only once, the generic version is
int removeDuplicatesInArray1(int *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (s[j] != s[i - 1] || i < 1)
		{
			// simplified version is s[i++] = s[j];
			// but this is more clear
			if (i != j)
				s[i] = s[j];
			i++;
			// this ++j can be simpilied to outside of if{}
			++j;
		}
		else
			++j;
	}
	return i;
}

// the version in the ebook 
int removeDuplicatesInArray2Book(int *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (j<n)
	{
		if (j>0 && j < n - 1 && s[j] == s[j - 1] && s[j] == s[j + 1])
			j++;
		else
		{
			s[i++] = s[j];
			j++;
		}
	}
	return i;
}

// The similar algorithm to removeDuplicatesInArray2Book
int removeDuplicatesInArray2Mine(int *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (j < n)
	{
		if (i >= 2 && s[j] == s[i - 2])
		{
			++j;
		}
		else
		{
			if (i != j)
				s[i] = s[j];
			i++;
			++j;
		}
	}
	return i;
}

int _tmain(int argc, _TCHAR* argv[])
{

	int array[] = { 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5 };
	int n = sizeof(array) / sizeof(array[0]);
	// removeDuplicatesInArray(array, n);
	int endPos = removeDuplicatesInArray3(array, n);
	for (int i = 0; i<endPos; ++i)
		printf("%d ", array[i]);

	return 0;
}

