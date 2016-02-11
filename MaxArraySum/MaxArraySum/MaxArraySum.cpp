// MaxArraySum.cpp : Defines the entry point for the console application.
// http://blog.csdn.net/yusiguyuan/article/details/12877103

#include "stdafx.h"

const int N = 4;
const int ROWS = 4;
const int COLS = 5;

#define MyMin(A,B) (((A)<(B))?(A):(B))
#define MyMax(A,B) (((A)>(B))?(A):(B))

void printP(int p[][COLS]);
int MaxArraySum(int arr[][COLS], int p[][COLS])
{
	int i, j;
	for (i = 0; i < ROWS; ++i)
	{
		for (j = 0; j < COLS; ++j)
		{
			p[i][j] = 0;
		}
	}

	for (i = 1; i < ROWS; ++i)
	{
		for (j = 1; j < COLS; ++j)
		{
			p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + arr[i][j];
		}
	}
	printP(p);

	int max = -1;

	for (int i = 1; i < ROWS; ++i)
	{
		for (int j = i; j < COLS; ++j)
		{
			int sum = 0;
			for (int k = 1; k < COLS; ++k)
			{
				// subarray from [i][k] to [j][m]
				int temp = p[j][k] - p[j][k - 1] - p[i - 1][k] + p[i - 1][k - 1];
				if (sum > 0)
					sum += temp;
				else
					sum = temp;
				if (sum > max)
					max = sum;

				printf("i=%d, j=%d, k=%d, temp = %d, max = %d\n", i,j,k,temp, max);
			}
		}
	}

	return max;
}


void printP(int p[][COLS])
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}

}
/*

int MaxRecSum(int a[][COLS], int p[][COLS], int n)
{
	for (int i = 0; i <= n; ++i)
	{
		p[i][0] = 0;
		p[0][i] = 0;
	}
	printP(p);
	for (int i = 1; i < n; ++i)
	{
		for (int j = 1; j < n; ++j)
			p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + a[i][j];
	}

	printP(p);
	int max = -1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i; j <= n; ++j)
		{
			int sum = 0;
			for (int k = 1; k <= n; ++k)
			{
				// subarray from [i][k] to [j][m]
				int temp = p[j][k] - p[j][k - 1] - p[i - 1][k] + p[i - 1][k - 1];
				if (sum > 0)
					sum += temp;
				else
					sum = temp;
				if (sum > max)
					max = sum;
			}
		}
	}
	return max;
}
*/

int intuitiveMethod(int arr[][COLS])
{
	int i, j, m, n;
	int a, b;
	int sum;
	int minV, maxV;
	int prtFlag = 0;

	int maxMax = 0;
	// a used to track number of rows to include 
	// b used to track number of cols to include
	// (i,j) is the current starting index, traverse them from 0 to end
	// (m,n) is the current index needs to be included

	for (i = 0; i < ROWS; ++i) 
	{
		for (a = 1; a <= ROWS; ++a)
		{
			maxV = MyMax(i - a + 1, 0);
			for (j = 0; j < COLS; ++j)
			{
				for (b = 1; b <= COLS; ++b)
				{
					if ((i - maxV + 1) >= a)
					{
						sum = 0;
						for (m = i; m >= maxV; --m)
						{
							minV = MyMin(j + b - 1, COLS - 1);
							// if < b, we don't have enough colums to calculate
							if ((minV - j + 1) >= b)
							{
								for (n = j; n <= minV; ++n)
								{
									printf("adding a[%d][%d], ", m, n);
									sum += arr[m][n];
								}
								// print flag, only when sum is caculated, we print it out
								prtFlag = 1;
							}
							else
								prtFlag = 0;
						}
						if (prtFlag == 1)
						{
							printf("\n sum = %d\n", sum);
							if (maxMax < sum)
								maxMax = sum;
						}
					}
				}
			}
		}
	}
	return maxMax;
}
int _tmain(int argc, _TCHAR* argv[])
{
	// let first row and col to always be 0, we start from [1][1]
	int array[ROWS][COLS] = { { 1, 2, -1, -4, -20}, 
							  { -8, -3, 4, 2, 1 }, 
							  { 3, 8, 10, 1, 3 },
							  { -4, -1, 1, 7, -6 },
							}; 
	int p[ROWS][COLS] = {};
	// int ret = MaxArraySum(array, p);
	// MaxRecSum(array, p, 3);

	// printf("max sum of subarray is %d\n", ret);
	int ret = intuitiveMethod(array);
	printf("max sum of subarray is %d\n", ret);

	return 0;
}

