// ConvertStringToInteger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>

int ConvertString2Int(char *s)
{
	unsigned int i;
	int ret = 0;
	int negFlag = 1;
	int start = 0;

	if (s == NULL)
		return -1;

	if (s[0] == '-')
	{
		negFlag = -1;
		start = 1;
	}

	for (i = start; i < strlen(s); ++i)
	{
		if (s[i] > '9' || s[i] < '0')
			return -1;
		ret = ret * 10 + s[i] - '0';
	}
	return ret*negFlag;
}

int ConvertString2IntPointer(const char *str)
{
	static const int MAX_INT = (int)((unsigned)~0 >> 1);
	static const int MIN_INT = -(int)((unsigned)~0 >> 1) - 1;
	unsigned int n = 0;

	//check if the pointer is NULL
	if (str == NULL)
		return 0;

	// handling spaces
	while (*str == ' ')
		++str;

	// sign
	int sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		++str;
	}

	while ( *str > '0' && *str < '9')
	{
		//overflow
		int c = *str - '0';
		// user n> MAX_INT/10 instead of n*10 > MAX_INT
		if (sign > 0 && (n > MAX_INT / 10 || (n == MAX_INT / 10 && c > MAX_INT % 10)))
		{
			n = MAX_INT;
			break;
		}
		else if (sign < 0 && (n >(unsigned)MIN_INT / 10 || (n == (unsigned)MIN_INT / 10 && c > (unsigned)MIN_INT % 10)))
		{
			n = MIN_INT;
			break;
		}

		n = n * 10 + c;
		++str;
	}
	return sign > 0 ? n : -n;
}

int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "2147483658";
	int ret = ConvertString2IntPointer(s);
	printf("Convert of %s = %d\n", s, ret);
	return 0;
}

