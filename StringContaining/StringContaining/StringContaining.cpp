// StringContaining.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// while(a) {
//   if (b)
//      break;
//   c;
// }

// is equivalent to 
// while(a and not b)
// { c; }

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
// then move j on s1, if s1[j]<s2[i], until s1[j] == s2[i], i.e. let j follow i's move until s1[j]==s2[i]
// then check if j reaches s1's end, if yes, because s1[j] != s2[i], it returns false 
// or if not, j < strlen(s1), but if s1[j]>s2[i], means s2[i] is impossible to be located in s1[j] or s1[j+1...], so also returns false
// if j not reaches s1's end, that also implies that s1[j] == s2[i], then increment i
// if j not reaches s1's end, it's impossible that s1[j] < s2[i] because while loop already did this check

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

bool StringContainPrime(char *s1, char *s2)
{
	const int p[26] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101 };
	int f = 1;
	for (unsigned int i = 0; i < strlen(s1); ++i)
	{
		int x = p[s1[i] - 'A'];
		// this is used to detect repeated chars in s1
		if (f % x)
		{
			f *= x;
		}
	}
	for (unsigned int i = 0; i < strlen(s2); ++i)
	{
		int x = p[s2[i] - 'A'];
		// as long as we find a number has remainer, it means it's not in s1
		if (f % x)
		{
			return false;
		}
	}
	return true;
}

bool StringContainBitHash(char *s1, char *s2)
{
	int hash = 0;

	for (unsigned int i = 0; i < strlen(s1); ++i)
	{
		// use bit OR, so repeated char will not be counted again
		hash |= (1 << (s1[i] - 'A'));
		printf("hash & = %d\n", hash);
	}
	// 'KJIHGFEDCBA' corresponds to
	// '10000011011' (hash)   
	// so if we have C in s2, which corresponds to
	// '00000000100' (C)
	// the & of hash and C will = 0 
	for (unsigned int i = 0; i < strlen(s2); ++i)
	{
		printf("hash & = %d\n", hash&(1 << (s2[i] - 'A')));
		if ((hash & (1 << (s2[i] - 'A'))) == 0)
		{
			return false;
		}
	}
	return true;
}

bool BrotherString(char *s1, char *s2)
{
	// hashing may not work, unless we found a unique hash for repeated chars
	// we should sort and compare
	int hash1 = 0, hash2 = 0;
	unsigned int i;
	for (i = 0; i < strlen(s1); ++i)
	{
		hash1 += (1 << (s1[i] - 'A'));
	}
	for (i = 0; i < strlen(s2); ++i)
	{
		hash2 += (1 << (s2[i] - 'A'));
	}
	return (hash1 == hash2);

}

int _tmain(int argc, _TCHAR* s1rgv[])
{
	char s1[] = "ABCDEFG"; // "ABBDEK";
	char s2[] = "BCDEFGA"; // "ABDKI";
	// bool ret = StringContainingIterate2(s1, s2);
	bool ret = StringContainBitHash(s1, s2);
	printf("s1 contains s2? %s\n", ret? "true" : "false");

	ret = BrotherString(s1, s2);
	printf("s1 and s2 are borthers? %s\n", ret? "true" : "false");
	return 0;
}

