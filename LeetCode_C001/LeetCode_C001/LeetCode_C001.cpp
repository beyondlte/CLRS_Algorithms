// LeetCode_C001.cpp : Defines the entry point for the console application.
//

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

void removeDuplicatesInArray(int *s, int n)
{
	int i, j;
	i = 0;
	j = 1; 

	while(j<n)
	{
		printf("before: i = %d, j = %d\n", i, j);
		if(s[j] != s[i])
		{
			s[++i] = s[j];
		}
		++j;
		printf("after: i = %d, j = %d\n", i, j);
	}
}
int _tmain(int argc, _TCHAR* argv[])
{

	int array[]={1,1,2,3,3,4, 5};
	int n = sizeof(array)/sizeof(array[0]);
	removeDuplicatesInArray(array, n);
	for (int i = 0; i<n; ++i)
		printf("%d ", array[i]);

	return 0;
}

