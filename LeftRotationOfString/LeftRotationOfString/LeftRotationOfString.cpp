// LeftRotationOfString.cpp : Defines the entry point for the console application.
// Question:
// Left rotation of a string is to move some leading characters to its tail. Please implement a function to rotate a string.
// For example, if the input string is ¡°abcdefg¡± and a number 2, the rotated result is ¡°cdefgab¡±.
// Time: O(N), Space: O(1)

#include "stdafx.h"
#include <string.h>

// s[0] = a, s[5=n-1] = f

void leftMoveOneChar(char *str, int n)
{
	char c;
	c = str[0];
	int i = 1;
	while (i < n )
	{
		str[i-1] = str[i];
		// printf("str[%d]=%c\n", i, str[i]);
		i++;
	}
	str[n - 1] = c;
	// the terminating char doesn't change, so this line is not necessary
	// str[n] = '\0';
}
void leftRotateString(char *str, int m, int n)
{
	int i = 1;
	while (i <= m)
	{
		leftMoveOneChar(str, n);
		i++;
	}
}

void modifyStr(char *str)
{
	// str is a new pointer created in the function, it points to the original s
	// str ---> s
	// if we change str[i], it's equivalent to change s's content
	str[0] = 'x';

	// assign pointer to point to another value, the assignment itself is ok
	// but the original str is not changed 
	// str ---> s, then is changed to str ---> "xyzbcd", the link str ---> s does not exist any more
	// str = "xyzbcd";

	// if str="syzbcd" (const string) is called before strcpy, then strcpy will fail because can't write to a const string
	strcpy(str, "xyzbcd");
}

void swapStr(char *str, int m, int n)
{
	char temp;
	for (int i = m; i < (n+m)/2; ++i)
	{
		temp = str[i];
		str[i] = str[n - 1 - i + m ];
		str[n - 1 - i + m] = temp;
	}
}
int _tmain(int argc, _TCHAR* argv[])
{
	char s[] = "abcdef";
	printf("%p\n", s);
	// modifyStr(s);
	// printf("%s\n", s);

	int len = strlen(s); // return 6
	// int len = sizeof(s) / sizeof(s[0]); 
	// sizeof returns 7 for string literal as the terminated null is counted
	printf("%d\n", len);
	// r = leftMoveOneChar(s, len);
	leftRotateString(s, 2, len);
	printf("%s\n", s);

	swapStr(s, 0, 4);
	swapStr(s, 4, 6);
	swapStr(s, 0, 6);
	printf("%s\n", s);

	return 0;
}

