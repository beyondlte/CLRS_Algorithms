// StringContaining.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool StringContainingIterate(char *s1, char *s2)
{
	int i, j;
	int status;
	i = 0;
	while (s2[i] != '\0')
	{
		j = 0;
		status = 0;
		while (s1[j] != '\0')
		{
			if (s2[i] == s1[j])
			{
				status = 1;
				break;
			}
			j++;
		}
		if (s1[j] == '\0' && status == 0)
			return false;
		i++;
	}
	if (status == 1)
		return true;
}

// simplified version, we don't need status, as long as s1 goes to '\0', it means we have searched s2[i] in all s1 and 
// couldn't find a match, so s2[i] is not in s1, and we can exit and return false
bool StringContainingIterate2(char *s1, char *s2)
{
	int i, j;
	i = 0;
	while (s2[i] != '\0')
	{
		j = 0;
		// this means as long as s2[i] == s1[j], then while loops will be broken, then we found s2[i] in s1, and 
		// we know s1[j] != '\0' in this case
		while (s1[j] != '\0' && s2[i] != s1[j])
		{
			j++;
		}
		if (s1[j] == '\0')
			return false;
		i++;
	}
	return true;
}

int cmpfunc(const void *a, const void *b)
{
	// (char *)a cast a from void * to char *, the pointer address is still the same
	// printf("%p\n", a);
	// printf("char=%p\n", (char *)a);
	return (*(char *)a - *(char *)b);
}

// algorithm: first sort string s1 and s2, then scan s1 and s2 one char by one char
// sort: O(mlgm) + O(nlogn)
// scan: O(m+n)
//      j
// s1 = AABCDFG 
// s2 = AFGK 
//      i
// if s2[i] == s1[j], increment both i and j
//       j
// s1 = AABCDFG 
// s2 = AFGK 
//       i
// if s2[i] != s1[j], increment just j, until s2[i] == s1[j] 
//        j->j
// s1 = AABCDFG 
// s2 = AFGK 
//       i
// finally we'll always reach s2's last char 
//            j
// s1 = AABCDFG 
// s2 = AFGK 
//        i
//             j
// s1 = AABCDFG'\0' 
// s2 = AFGK 
//         i
// at this time, only when s2[i]==s1[j], it returns true
// has an issue:
//    if len(s2) < len(s1), the while loop stops at s2's end first, it works
//    but if len(s2) > len(s1), the while loop stops at s1's end first, and s2 scanning is not finished yet
bool StringContainingSortedBad(char *s1, char *s2)
{
	qsort(s1, strlen(s1), sizeof(char), cmpfunc);
	qsort(s2, strlen(s2), sizeof(char), cmpfunc);
	// printf("s1 = %s\n", s1);
	// printf("s2 = %s\n", s2);

	unsigned int i = 0, j = 0;

	while (i < strlen(s2) && j < strlen(s1))
	{
		/*
		if (s2[i] == s1[j])
		{
			i++;
			j++;
		}
		else
			j++;
		*/
		// the above can be simplifed to
		if (s2[i] == s1[j])
			i++;
		j++;
	}
	if (s2[i] == s1[j])
		return true;
	else 
		return false;
}

// algorithm: 
// again first sort s1 and s2
// then move j on s1, if s1[j]<s2[i], until s1[j] == s2[i]
// then check if j reaches s1's end, if yes, because s1[j] != s2[i], it returns false 
// or if not, j < strlen(s1), but if s1[j]>s2[i], means s2[i] is impossible to be located in s1[j] or s1[j+1...], so also returns false
// if j not reaches s1's end, and also s1[j] == s2[i], then increment i

bool StringContainingSorted2(char *s1, char *s2)
{
	qsort(s1, strlen(s1), sizeof(char), cmpfunc);
	qsort(s2, strlen(s2), sizeof(char), cmpfunc);

	for (unsigned int j = 0, i = 0; i < strlen(s2);)
	{
		while ((j < strlen(s1)) && (s1[j] < s2[i]))
		{
			++j;
		}
		if ((j >= strlen(s1)) || (s1[j] > s2[i]))
		{
			return false;
		}
		// means s1[j]==s2[i] and j < strlen(s1)
		// can't put if (j<strlen(s1) && s1[j]==s2[i] ahead of while loop
		// because s2[i] may go to the last '\0'
		++i;
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char s1[] = "ABDEK";
	char s2[] = "ABDK";
	// bool ret = StringContainingIterate2(s1, s2);
	bool ret = StringContainingSorted2(s1, s2);
	printf("s1 contains s2? %s\n", ret? "true" : "false");
	return 0;
}

