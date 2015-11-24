// Palindrome.cpp : Defines the entry point for the console application.
// Algorithm 1: search from start and end to the middle
// Algorithm 2: search from the middle
// For linked list: first go to the middle, then reverse the second half of the linked list, then scan from start and middle

#include "stdafx.h"
#include <stdbool.h>
#include <string.h>

// Time: O(n)
// Space: O(1)
bool isPalindrome(const char *s)
{
	unsigned int i, j;
	i = 0;
	j = strlen(s)-1;
	while (i < j)
	{
		if (s[i] != s[j])
			return false;
		++i;
		--j;
	}
	return true;
}

bool isPalindrome2(char *str)
{
	char *s;
	char *t;
	int n = strlen(str);
	int mid = ((n >> 1) - 1) >= 0 ? ((n >> 1) - 1) : 0;


	s = str + mid;
	t = str + n - 1 - mid;

	while (s >= str)
	{
		if (*(s--) != *(t++))
			return false;
	}
	return true;


}

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "woainiiniaow";
	bool ret;
	ret = isPalindrome2(s);
	printf("Is %s palindrome: %s\n", s, ret ? "Yes": "No");

	return 0;
}

