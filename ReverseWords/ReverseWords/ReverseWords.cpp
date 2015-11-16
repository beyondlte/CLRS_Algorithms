// ReverseWords.cpp : Defines the entry point for the console application.
// Question: given a string, reverse each word in the string
// Example: I am a student. ---> .tneduts a ma I

#include "stdafx.h"
#include <string.h>

void ReverseWord(char *s, int m, int n)
{
	char temp;
	while (m < n)
	{
		temp = s[m];
		s[m++] = s[n];
		s[n--] = temp;
	}
}
void ReverseWordsInString(char *s, int n)
{
	int i, j;
	i = 0;
	j = 0;
	while (i < n)
	{
		if (i < j && s[j] == ' ' || j==n)
		{
			ReverseWord(s, i, j - 1);
			i = j + 1;
			j = i;
		}
		else
		{
			j++;
		}

	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "I am a student.";
	int len = strlen(s);
	ReverseWordsInString(s, len-1);
	printf("%s\n", s);
	ReverseWord(s, 0, len-1);
	printf("%s\n", s);
	return 0;
}

