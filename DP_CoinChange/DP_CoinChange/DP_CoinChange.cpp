// DP_CoinChange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int count(int S[], int m, int n)
{
	// If n is 0 then there is 1 solution (do not include any coin)
	printf("m=%d, n=%d\n", m, n);
	if (n == 0)
		return 1;

	// If n is less than 0 then no solution exists
	if (n < 0)
		return 0;

	// If there are no coins and n is greater than 0, then no solution exist
	if (m <= 0 && n >= 1)
		return 0;

	// count is sum of solutions (i) including S[m-1] (ii) excluding S[m-1]
	return count(S, m - 1, n) + count(S, m, n - S[m - 1]);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int s[] = { 1, 2, 5};
	int m = 2;
	int n = 4;
	int ret = count(s, m, n);
	printf("total solution is %d\n", ret);
	return 0;
}

/*
1 1 1 1 1 1
1 1 2 2
1 5
2 2 2
1 1 1 1 2

3rd coin in or not in

the trick here is:
s(6,3) means use 3 coins to fill 6
s(6,3) = s(6,2) + s(6-5,3)
here, s(6,2) means the 3rd coin not in, so we use first two coins to fill 6, the solution will be 111111,1122,222,11112 = 4
s(6-5,3) means the 3rd coin is in, then we still use three coins to fill 1, then we need to solve s(6-5,3)=s(1,3) which is 1 = 1

so total is 5

how to get s(6,2), repeat it again
consider 2nd coin in or not
s(6,2) = s(6, 1) + s(6-2, 2) = s(6,1) + s(4,2)
S(6,1) means the 2nd coin not in, now only has one 1 coin, so it's 111111 = 1
s(4,2) means 2nd coin is in to fill 4, it is 1111, 121, 22

*/
