// LongestPalindrome.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stdlib.h>

// for C++
#include <iostream>
#include <string>
using namespace std;
// end of for C++

#define MIN(a,b) (a)>(b)?(b):(a)

// this is O(N^2)
char * longestPalindrome(const char *s)
{
	int i, j;
	int len = strlen(s);
	int maxLen = 0;
	int pIndex;
	char *r;
	for (i = 0; i < len; ++i)
	{
		// because we don't know it's in format of abccba or abcba
		// so we need to check both cases
		// case 1: for abcba
		for (j = 0; j < MIN(i, len - i); ++j)
		{
			if (s[i - j] != s[i + j])
				break;
		}
		if (j>maxLen)
		{
			pIndex = i;
			maxLen = j-1;
		}
		// case 2: for abccba
		for (j = 0; j < MIN(i, len - i-1); ++j)
		{
			if (s[i - j] != s[i + j + 1])
				break;
		}
		if (j>maxLen)
		{
			pIndex = i;
			maxLen = j;
		}
	}
	printf("pIndex = %d\n", pIndex);
	printf("maxlen = %d\n", maxLen);

	int newLen;
	int startPos;
	if (s[pIndex] == s[pIndex + 1])
	{
		newLen = maxLen * 2;
		startPos = pIndex - maxLen + 1;
	}
	else
	{
		newLen = maxLen * 2 + 1;
		startPos = pIndex - maxLen;
	}
	printf("newLen = %d\n", newLen);
		
	r = (char *)malloc(sizeof(char)* newLen);
	strncpy(r, s+startPos, newLen);
	return r;
}

char * preProcess(const char *s)
{
	unsigned int len = strlen(s);
	if (len == 0)
		return "^$";
	char *ret = (char *)malloc(sizeof(char)*len * 2 + 3);

	unsigned int i;
	unsigned int retLen = len * 2 + 3;

	ret[0] = '^';
	for (i = 1; i < retLen; ++i)
	{
		if (i % 2 == 1)
			ret[i] = '#';
		else
		{
			ret[i] = s[i / 2 - 1]; 
		}
	}
	// retLen is variable, although it's allocated with len*2+3 chars
	ret[retLen-1] = '$';
	ret[retLen] = '\0';
	return ret;
}

string preProcessStr(string s)
{
	string t;
	t = "^";
	for (unsigned int i = 0; i < s.length(); ++i)
	{
		t += '#' + s.substr(i, 1);
	}
	t += "#$";
	return t;
}


int longestPalindromeLinearity(char *s)
{
	// 12212321 change to 
	// S # 1 # 2 # 2 # 1 # 2 # 3 # 2 # 1 #
	// P 1 2 1 2 5 2 1 4 1 2 1 6 1 2 1 2 1

	// mx -i > P[j]
	// mx    j         Id        i     mx
	// 0 2 3 4 3 2 1 0 3 0 1 2 3 4 3 2 0
	//   2 3 4 3 2 
	// 0 2 3 4 3 2 1 0 3 0 1 2 3 4 3 2 0

	// mx -i <= P[j]
	//   mx  j         Id        i   mx
	// 1 2 3 4 3 2 1 0 3 0 1 2 3 4 3 2 5
	// 1 2 3 4 3 2 1
	//   2 3 4 3 2 1 0 3 0 1 2 3 4 3 2 
	
	// see http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
	//           R                 C                 R
	//           |         i'      |       i         | 
	// T = ^ # b # a # b # c # b # a # b # c # b # a # c # c # b # a #
	//     0 1 2 3 4 5 6 7 8 9 10111213141516
	// P = 0 0 1 0 3 0 1 0 7 0 1 0 9 0 1 0 ?
	// for i = 13, as P[i'] = 1, so P[i] = 1
	// but for i=15, P[i']=7, P[i]!=7
	// which means:
	// if P[i'] <= L-i' = R-i
	//    P[i] = P[i']
	// else P[i] <= P[i']

	// This algorithm is definitely non-trivial and you won¡¯t be expected to come up with such algorithm 
	// during an interview setting. However, I do hope that you enjoy reading this article and hopefully 
	// it helps you in understanding this interesting algorithm. You deserve a pat if you have gone this far!

	// Leetcode explanation is wrong, if P[i] = P[i'], P[i] can still be increased!!!
	// if P[i] == R-i, then it is R-i and no need to expand panlidrome centered at i

	return 1;

}

string longestPalindromeStr(string s) {
	string T = preProcessStr(s);
	int n = T.length();
	int *P = new int[n];

	// initialize P to all zeros, must use sizeof(int)*n, not n
	memset(P, -1, sizeof(int)*n);
	int C = 0, R = 0;
	for (int i = 0; i < n - 1; i++) {
		int i_mirror = 2 * C - i; // equals to i' = C - (i-C)

		// if i < R, then we check R-i vs P[i']
		P[i] = (R > i) ? MIN(R - i, P[i_mirror]) : 0;
		// if R-i >= P[i'], then P[i] = P[i']
		// if R-i < P[i'], then P[i] = R-i
		// here for debug printing
		if (R - i < P[i_mirror] && (R > i))
			cout << P[i] << "\n"; // now P[i] = R-i;
		else if ((R > i) && (R-i >= P[i_mirror]))
			cout << P[i] << "\n"; // now P[i] = P[i']; 
		else if (R <= i)
			cout << P[i] << "\n"; // now P[i] = 0; 
 


		// Attempt to expand palindrome centered at i when R<=i or R>i&&R-i>=P[i']
		// now T[i+1+P[i]] actually is T[i+1+R-i] = T[R+1]
		//     T[i-1-P[i]] actually is T[i-1-R+i] = T[2i-1-R] 
		while ((i - 1 - P[i] > 0) && T[i + 1 + P[i]] == T[i - 1 - P[i]]) 
			P[i]++;

		// If palindrome centered at i expand past R,
		// adjust center based on expanded palindrome.
		if (i + P[i] > R) {
			C = i;
			R = i + P[i];
		}
		for (int m = 0; m < 20; ++m)
			cout << P[m] << " ";
		cout << "\n";
	}

	// Find the maximum element in P.
	int maxLen = 0;
	int centerIndex = 0;
	for (int i = 1; i < n - 1; i++) {
		if (P[i] > maxLen) {
			maxLen = P[i];
			centerIndex = i;
		}
	}
	delete[] P;

	return s.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// char s[] = "112345676543210";
	char s[] = "babcbabcbaccba";
	char *ret;
	ret = longestPalindrome(s);
	ret = preProcess(s);
	printf("%s\n", ret);

	string x = "babcbabcbaccba";
	x = longestPalindromeStr(x);
	cout << x << "\n";

	return 0;
}

