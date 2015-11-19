// StringContaining.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h>

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

int _tmain(int argc, _TCHAR* argv[])
{
	char s1[] = "BDACFG";
	char s2[] = "AGF";
	bool ret = StringContainingIterate2(s1, s2);
	printf("s1 contains s2? %s\n", ret? "true" : "false");
	return 0;
}

