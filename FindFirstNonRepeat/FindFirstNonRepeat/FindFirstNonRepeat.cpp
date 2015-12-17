// FindFirstNonRepeat.cpp : Defines the entry point for the console application.
// http://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

#if 0
// this will be O(N^2)
int findFirstNonRepeatIntuitive(char *str)
{
	int n = strlen(str);
	int index = -1;
	int i, j;
	int flag;
	for (i = 0; i < n; ++i)
	{
		flag = 0;
		for (j = 0; j < n; ++j)
		{
			if (j!=i && str[j] == str[i])
			{
				flag = 1;
				break;
			}
		}
		if (j == n && flag == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}

// This will be O(N), but need more space
char findFirstNonRepeat(char *str)
{
	char *countArray = (char *)malloc(sizeof(char)*256);
	memset(countArray, 0, strlen(str));

	int i = 0;
	//               a b c,...
	// countArray = [0,0,0,...]
	while (str[i] != '\0')
	{
		countArray[str[i] - 'a']++;
		++i;
	}
	// check countArray
	// this is wrong, if we just check countArray in squence, because the first element in 1 may not be 
	// the first non-repeatable char in the string, for example geeksforgeeksa, it will return a, not f
	// i = 0;
	// while (countArray[i] != 1)
	// {
	// 	++i;
	// }


	// the fix is we still need to check countArray based on the sequence of str
	i = 0;
	while (str[i] != '\0')
	{
		if (countArray[str[i] - 'a'] == 1)
			break;
		++i;
	}
	free(countArray);
	return 'a' + i;

}

// don't forget the hashing method
int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "geeksforgeeks";
	// int ret;
	// ret = findFirstNonRepeatIntuitive(str);
	// if (ret != -1)
	// 	printf("The first non repeat char = %c\n", str[ret]);
	// else
	// 	printf("All chars are repeated\n");
	char ret;
	ret = findFirstNonRepeat(str);
	printf("The first non repeat char = %c\n", ret);
	return 0;
}

#include<stdlib.h>
#include<stdio.h>
#define NO_OF_CHARS 256

/* Returns an array of size 256 containg count
of characters in the passed char array */
int *getCharCountArray(char *str)
{
	int *count = (int *)calloc(sizeof(int), NO_OF_CHARS);
	int i;
	for (i = 0; *(str + i); i++)
		count[*(str + i)]++;
	return count;
}

/* The function returns index of first non-repeating
character in a string. If all characters are repeating
then returns -1 */
int firstNonRepeating(char *str)
{
	int *count = getCharCountArray(str);
	int index = -1, i;

	for (i = 0; *(str + i); i++)
	{
		if (count[*(str + i)] == 1)
		{
			index = i;
			break;
		}
	}

	free(count); // To avoid memory leak
	return index;
}

/* Driver program to test above function */
int main()
{
	char str[] = "geeksforgeeks";
	int index = firstNonRepeating(str);
	if (index == -1)
		printf("Either all characters are repeating or string is empty");
	else
		printf("First non-repeating character is %c", str[index]);
	getchar();
	return 0;
}
#endif

struct countIndex{
	int count;
	int index;
};

struct countIndex * getCountIndexArray(char *s)
{
	struct countIndex * countList = (struct countIndex *)calloc(sizeof(struct countIndex), 256);

	int i = 0;
	while (s[i] != '\0')
	{
		countList[s[i]].count += 1;
		// If it's first occurrence, then store the index
		if (countList[s[i]].count == 1)
			countList[s[i]].index = i;
		++i;
	}
	for (i = 90; i < 256; ++i)
	{
		if (countList[i].count != 0)
			printf("char %c = %d, %d\n", i, countList[i].count, countList[i].index);
	}
	return countList;
}

int findFirstNonRepeating(char *s)
{
	struct countIndex *countList = getCountIndexArray(s);
	int result = 1000;
	for (int i = 0; i < 256; ++i)
	{
		if (countList[i].count == 1 && countList[i].index < result)
		{
			result = countList[i].index;
			printf("result = %d\n", result);
		}
	}
	free(countList);
	return result;
}

int main()
{
	char str[] = "geeksforgeeks";
	int ret = findFirstNonRepeating(str);
	printf("First non-repeating character is %c\n", str[ret]);
	return 0;
}

