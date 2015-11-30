// AllCombination.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stack>
using namespace std;

#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)

stack<int> ST;
int m = 1;
void Permu(char *s, int h, int t)
{
	if (h==t)
	{
		for (int i = 0; i <= t; i++)
			printf("%c", s[i]);
		printf("\n");
	}
	else
	{
		for (int i = h; i<=t; i++)
		{
			printf("%d..............\n", m); 
			ST.push(m);
			m++;
			printf("swap %c & %c\n", s[h], s[i]);
			SWAP(char, s[h],s[i]);
			Permu(s, h+1, t);
			printf("swap back %c & %c\n", s[h], s[i]);
			SWAP(char, s[h],s[i]); // backtrack
			printf("%d--------------\n", ST.top());
			ST.pop();
			if (ST.empty())
				printf("string is reset to %s\n\n", s);
			//The first swap swaps two characters, e.g. ABC -> ACB

			//Then you recursively call permute on ACB.
			//But then you need to go back to ABC to compute all the other permutations. 
			//That is the purpose of the second swap, merely swapping the same two indices, 
			//canceling the effect of the first swap.
		}
	}

}

int _tmain(int argc, _TCHAR* argv[])
{
	char str[]="abc";
	int n = strlen(str);
	Permu(str, 0, n-1);
	return 0;
}

