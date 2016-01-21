// Backtracking_nqueen.cpp : Defines the entry point for the console application.
// http://zephiruswt.blog.51cto.com/5193151/895797

#include "stdafx.h"

/*
//八皇后问题

// Queen.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class Queen{    //类Queen记录解空间中的节点信息
	friend int nQueen(int);
private:
	bool Place(int k);    //剪枝函数
	void Backtrack(int t);    //递归函数
	int n;    //皇后个数
	int *x;    //当前解
	long sum;    //当前可行的方案数
};

int abs(int ab)//求绝对值
{
	return ab>0 ? ab : -ab;
}

bool Queen::Place(int k)    //剪枝函数
{
	for (int j = 1; j<k; j++)
	{
		//剪枝条件：如果在同一行，同一列或者同斜线上
		if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
			return false;
	}
	return true;
}

void Queen::Backtrack(int t)    //递归回溯核心
{
	if (t>n) 
		sum++;    //如果遍历到叶子，说明求出了一个解
	else
	for (int i = 1; i <= n; i++)
	{
		x[t] = i;
		if (Place(t)) 
			Backtrack(t + 1); //函数Place为剪枝函数
	}
}

int nQueen(int n)//初始化数据
{
	Queen X;
	X.n = n;
	X.sum = 0;
	int *p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	for (int i = 0; i <= n; i++)
		printf("%d\n", X.x[i]);
	delete[]p;
	return X.sum;
}


int _tmain(int argc, _TCHAR* argv[])
{
	printf("%d", nQueen(8));//传入参数8，即八皇后问题
	return 0;
}
*/


#include <stdlib.h> 
#include <stdio.h> 

int m[8][8] = { 0 };//表示棋盘，初始为0，表示未放置皇后 
int num = 0;//解数目 
int search = 0; // in each solution, the number of searches

//对于棋盘前row-1行已放置好皇后 
//检查在第row行、第column列放置一枚皇后是否可行 
bool check(int row, int column)
{
	if (row == 1) 
		return true;
	int i, j;
	//纵向只能有一枚皇后 
	// only checks m[0][col-1] to m[row-2][col-1], on vertical direction
	// we don't check rows larger than m[row-1], we only check preceeding rows
	for (i = 0; i <= row - 2; i++)
	{
		if (m[i][column - 1] == 1) 
			return false;
	}
	//左上至右下只能有一枚皇后, only to m[row-2]
	// current is m[row-1][col-1], just need to check starting from row-1-1 = row-2 and col-1-1 = col-2
	i = row - 2;
	// j = i - (row - column); // indeed it's the same as j = column - 2; 
	// the idea here is: the diff between row and col, is the same as the diff between i and j
	// i = row-2, so j = row-2-(row-col) = col - 2
	// another way to think is: cur = row-1, col-1, so left up diagnal item is row-1-1, col-1-1 
	// or: (i+1) = row-1, (j+1) = col-1 => (i+1)+(j+1) = row-1 +col-1 => i+j+2 = row+col-2 => j = row+col-i-4
	// the best is i+1=row-1 => i = row-2, j+1=col-1 => j=col-2
	j = column - 2;
	while (i >= 0 && j >= 0)
	{
		if (m[i][j] == 1) 
			return false;
		i--;
		j--;
	}
	//右上至左下只能有一枚皇后, only to m[row-2]
	i = row - 2;
	// j = row + column - i - 2; // j = row + col - (row-2) - 2 = row + col -row + 2 -2 = col
	// j = (row-1) + (col-1) -i, i.e. j+i = (row-1)+(col-1)
	// the best is i+1 = row-1 => i=row-2; j-1=col-1 => j = col
	j = column;
	while (i >= 0 && j <= 7)
	{
		if (m[i][j] == 1) 
			return false;
		i--;
		j++;
	}
	return true;
}

//当已放置8枚皇后，为可行解时，输出棋盘 
void output(int mode)
{
	int i, j;
	if (mode == 1)
	{
		num++;
		printf("answer %d:\n", num);
		search = 0;
	}
	else if (mode == 0)
	{
		printf("backtracking..........\n");
	}
	else
	{
		search++;
		printf("Searching %d:\n", search);
	}
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<8; j++) printf("%d ", m[i][j]);
		printf("\n");
	}
}

//采用递归函数实现八皇后回溯算法 
//该函数求解当棋盘前row-1行已放置好皇后，在第row行放置皇后 
void solve(int row)
{
	int j;
	//考虑在第row行的各列放置皇后 
	for (j = 0; j<8; j++)
	{
		//在其中一列放置皇后 
		m[row - 1][j] = 1;
		output(2);
		//检查在该列放置皇后是否可行, m[row-1][j] corresponds to row:row and column:j+1 
		if (check(row, j + 1) == true)
		{
			//若该列可放置皇后，且该行为最后一行，则找到一可行解，输出 
			if (row == 8) 
				output(1);
			//若该列可放置皇后，则向下一行，继续搜索、求解 
			else
			{
				solve(row + 1);
			}
		}
		//取出该列的皇后，进行回溯，在其他列放置皇后 
		m[row - 1][j] = 0;
		output(0);
	}
}

//主函数 
int main()
{
	//求解八皇后问题 
	freopen("data.out", "w", stdout);//重定向输出流
	solve(1);
	return 0;
}