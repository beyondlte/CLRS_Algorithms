// MaxArraySum.cpp : Defines the entry point for the console application.
// http://blog.csdn.net/yusiguyuan/article/details/12877103
// http://www.geeksforgeeks.org/dynamic-programming-set-27-max-sum-rectangle-in-a-2d-matrix/

#include "stdafx.h"
#include "limits.h"
#include "string.h"

const int N = 4;
const int ROW = 4;
const int COL = 4;

#define MyMin(A,B) (((A)<(B))?(A):(B))
#define MyMax(A,B) (((A)>(B))?(A):(B))

void printP(int p[][COL]);
int MaxArraySum(int arr[][COL], int p[][COL])
{
	int i, j;
	for (i = 0; i < ROW; ++i)
	{
		for (j = 0; j < COL; ++j)
		{
			p[i][j] = 0;
		}
	}

	for (i = 1; i < ROW; ++i)
	{
		for (j = 1; j < COL; ++j)
		{
			p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + arr[i][j];
		}
	}
	printP(p);

	int max = -1;

	for (int i = 1; i < ROW; ++i)
	{
		for (int j = i; j < COL; ++j)
		{
			int sum = 0;
			for (int k = 1; k < COL; ++k)
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


void printP(int p[][COL])
{
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			printf("%d ", p[i][j]);
		}
		printf("\n");
	}

}
/*

int MaxRecSum(int a[][COL], int p[][COL], int n)
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

int intuitiveMethod(int arr[][COL])
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

	for (i = 0; i < ROW; ++i) 
	{
		for (a = 1; a <= ROW; ++a)
		{
			maxV = MyMax(i - a + 1, 0);
			for (j = 0; j < COL; ++j)
			{
				for (b = 1; b <= COL; ++b)
				{
					if ((i - maxV + 1) >= a)
					{
						sum = 0;
						for (m = i; m >= maxV; --m)
						{
							minV = MyMin(j + b - 1, COL - 1);
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

// Implementation of Kadane's algorithm for 1D array. The function returns the
// maximum sum and stores starting and ending indexes of the maximum sum subarray
// at addresses pointed by start and finish pointers respectively.
int kadane(int* arr, int* start, int* finish, int n)
{
	// initialize sum, maxSum and
	int sum = 0, maxSum = INT_MIN, i;

	// Just some initial value to check for all negative values case
	*finish = -1;

	// local variable
	int local_start = 0;

	for (i = 0; i < n; ++i)
	{
		sum += arr[i];
		if (sum < 0)
		{
			sum = 0;
			local_start = i + 1;
		}
		else if (sum > maxSum)
		{
			maxSum = sum;
			*start = local_start;
			*finish = i;
		}
	}

	// There is at-least one non-negative number
	if (*finish != -1)
		return maxSum;

	// Special Case: When all numbers in arr[] are negative
	maxSum = arr[0];
	*start = *finish = 0;

	// Find the maximum element in array
	for (i = 1; i < n; i++)
	{
		if (arr[i] > maxSum)
		{
			maxSum = arr[i];
			*start = *finish = i;
		}
	}
	return maxSum;
}

void printTemp(int temp[ROW])
{
	for (int i = 0; i < ROW; ++i)
		printf("%d ", temp[i]);
	printf("\n");
}
// The main function that finds maximum sum rectangle in M[][]
void findMaxSum(int M[][COL])
{
	// Variables to store the final output
	int maxSum = INT_MIN, finalLeft, finalRight, finalTop, finalBottom;

	int left, right, i;
	int temp[ROW], sum, start, finish;

	// Set the left column
	for (left = 0; left < COL; ++left)
	{
		// Initialize all elements of temp as 0
		memset(temp, 0, sizeof(temp));

		// Set the right column for the left column set by outer loop
		for (right = left; right < COL; ++right)
		{
			// Calculate sum between current left and right for every row 'i'
			for (i = 0; i < ROW; ++i)
				temp[i] += M[i][right];
			printf("left = %d, right = %d\n", left, right);
			printTemp(temp);

			// Find the maximum sum subarray in temp[]. The kadane() function
			// also sets values of start and finish.  So 'sum' is sum of
			// rectangle between (start, left) and (finish, right) which is the
			//  maximum sum with boundary columns strictly as left and right.
			sum = kadane(temp, &start, &finish, ROW);

			// Compare sum with maximum sum so far. If sum is more, then update
			// maxSum and other output values
			if (sum > maxSum)
			{
				maxSum = sum;
				finalLeft = left;
				finalRight = right;
				finalTop = start;
				finalBottom = finish;
			}
		}
	}

	// Print final values
	printf("(Top, Left) (%d, %d)\n", finalTop, finalLeft);
	printf("(Bottom, Right) (%d, %d)\n", finalBottom, finalRight);
	printf("Max sum is: %d\n", maxSum);
}

// see the MaxArraySub_Naive.ccd file for illustration
int naiveMethod(int arr[][COL])
{
	int R = ROW, C = COL;
	int sum = 0, maxSum = -1;
	int RS = 0, RE = 0, CS = 0, CE = 0;
	int rowEnd, rowStart, colEnd, colStart;

	for (rowEnd = 0; rowEnd<R; rowEnd++)
	{
		for (rowStart = 0; rowStart <= rowEnd; rowStart++)
		{
			for (colEnd = 0; colEnd<C; colEnd++)
			{
				for (colStart = 0; colStart <= colEnd; colStart++)
				{
					sum = 0;
					for (int i = rowStart; i <= rowEnd; i++)
					{
						for (int j = colStart; j <= colEnd; j++)
						{
							printf("adding a[%d][%d], ", i, j);
							sum += arr[i][j];
						}
					}
					printf("\n");
					if (sum>maxSum)
					{
						maxSum = sum;
						RS = rowStart;
						RE = rowEnd;
						CS = colStart;
						CE = colEnd;
					}
					printf("--------------------- colStart = %d, colEnd = %d, rowStart = %d, rowEnd = %d\n", colStart, colEnd, rowStart, rowEnd);
				}
				printf("--------------------- colEnd = %d, rowStart = %d, rowEnd = %d\n", colEnd, rowStart, rowEnd);
			}
			printf("--------------------- rowStart = %d, rowEnd = %d\n", rowStart, rowEnd);
		}
		printf("--------------------- rowEnd = %d\n", rowEnd);
	}
	return maxSum;
}
int _tmain(int argc, _TCHAR* argv[])
{
	// let first row and col to always be 0, we start from [1][1]
	// int array[ROW][COL] = { { -1, -2, -10, -4, -20}, 
	// 						{  0,  3, -4, -3,  1 }, 
	//						{ -3,  8, -3,  1,  -3 },
	//						{ -4,  1,  1, -7, -6 },
	//						}; 
	int array[ROW][COL] = { { -1, -1, 3, 3 },
							{ -1, -1, 3, 3 },
							{ 10, -1, -1, -1 },
							{ -1, -1, -1, -1 } };
	// int p[ROW][COL] = {};
	// int ret = MaxArraySum(array, p);
	// MaxRecSum(array, p, 3);

	
	// int ret = intuitiveMethod(array);
	// printf("max sum of subarray is %d\n", ret);

	// findMaxSum(array);
	int ret = naiveMethod(array);
	printf("max sum of subarray is %d\n", ret);


	return 0;
}

