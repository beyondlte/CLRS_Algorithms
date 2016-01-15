// KnapSack.cpp : Defines the entry point for the console application.
// http://www.hawstein.com/posts/dp-knapsack.html

#include "stdafx.h"

// 0-1 knapsack d(i, j)表示前i个物品装到剩余容量为j的背包中的最大重量
#include<cstdio>
using namespace std;
#define MAXN 1000
#define MAXC 100000

#define MyMax(a, b) (((a)>(b))?(a):(b))

// int V[MAXN], W[MAXN], x[MAXN];
int x[MAXN];
int d[MAXN][MAXC];

int main(){
	freopen("data.in", "r", stdin);//重定向输入流
	// freopen("data.out", "w", stdout);//重定向输出流
	int n, C, V=0, W=0;
	while (scanf("%d %d", &n, &C) != EOF){
		
		// for (int i = 0; i<n; ++i)   
		// 	scanf("%d %d", &V[i], &W[i]);
		//	

		for (int i = 0; i<n; ++i)   
			x[i] = 0; //初始化打印方案

		for (int i = 0; i <= n; ++i){
			// don't use V[i] and W[i], but use V and W instead
			// dont' read in V&W at the same time when we do the DP, read them one sequence later
			// do d[i][j] update first, then read V&W
			// previously, read V[i]&W[i], then update d[i][j] using V[i-1] and W[i-1]
			if (i>0)
				scanf("%d %d", &V, &W);
			for (int j = C; j >= 0; --j){
				if (i==0)
					d[i][j] = i;

				// d[i][j] = i == 0 ? 0 : d[i - 1][j];

				// if j>= V[i-1], then we can put i-1 thing in the bag or not, so we have the Max(d[i-1][j], d[i-1][j-V[i-1]]+W[i-1]
				if (i>0 && j >= V)
				{
					d[i][j] = MyMax(d[i-1][j], d[i - 1][j - V] + W);
				}
				// if j< V[i-1], then we don't put i-1 thing in the bag, so we have d[i][j] = d[i-1][j]
				// if we use d[i][j] = i == 0 ? 0 : d[i - 1][j]; before, then we don't need this else if block 
				else if (i>0 && j< V)
					d[i][j] = d[i - 1][j];
				printf("d[%d][%d] = %d\n", i, j, d[i][j]);
			}
		}
		printf("%d\n", d[n][C]);//最终求解的最大价值

		//输出打印方案
		int j = C;
		for (int i = n; i>0; --i){
			if (d[i][j] > d[i - 1][j]){
				x[i - 1] = 1;
				j = j - V;
			}
		}
		for (int i = 0; i<n; ++i)   printf("%d ", x[i]);
		printf("\n");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

/*
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define MyMax(a, b) (((a)>(b))?(a):(b))

int main(){
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
	int n, C, V = 0, W = 0;
	while (scanf("%d %d", &n, &C) != EOF){
		int* d = (int*)malloc((C + 1)*sizeof(int));
		memset(d, 0, (C + 1)*sizeof(int));

		for (int i = 0; i <= n; ++i){
			if (i>0)   
				scanf("%d %d", &V, &W);
			// 由上面那一小段优化过后的代码可知，状态转移方程为：d(i, j)=max{ d(i-1, j), d(i-1, j-V)+W }，
			// 也就是在计算d(i, j)时我们用到了d(i-1,j)和d(i-1, j-V)的值。 如果我们只用一个一维数组d(0)～d(C)来保存状态值可以么？
			// 将i方向的维数去掉， 我们可以将原来二维数组表示为一维数据：d(i-1, j-V)变为d(j-V)， d(i-1, j)变为d(j)。
			// 当我们要计算d(i, j)时，只需要比较d(j)和d(j-V)+W的大小， 用较大的数更新d(j)即可。
			// 等等，如果我们按j递增的顺序来计算下一个d(i, j+1)，而它可能要用到d(i-1, j)的值， 那么问题就出来了，因为你刚刚才把它更新为d(i, j)了。
			// because d(i, j+1)=max{ d(i-1, j+1), d(i-1, j+1-V)+W } 
			//	---->		d(i-1, j) | d(i-1, j+1)
			//	---->		d(i,   j) | d(i,   j+1)
			// if V=1, then d(i-1, j+1) needs d(i-1,j+1-V)=d(i-1,j) 
			// however, d(i-1,j) has been replaced by d(i,j) when we cal d(i,j)
			// 那么，怎么办呢？ 按照j递减的顺序即可避免这种问题。比如，你计算完d(i, j)， 接下来要计算的是d(i,j-1)，
			// 而它的状态转移方程为d(i, j-1)=max{ d(i-1, j-1), d(i-1, j-1-V)+W }，它不会再用到d(i-1,j)的值！
			// it only needds d(i-1,j-1) and d(i-1, j-1-V), even when V=0, it can't be d(i-1, j)
			// 所以， 即使d(i-1,j)的值被更新了也无所谓。
			// d(i-1,j-1)  d(i-1, j) <------- i-1
			// d(i,  j-1)  d(i,   j) <------- i

			// for (int j = 0; j <= C; ++j)
			// {
			// 	if (j >= V && i> 0)
			// 		d[j] = MyMax(d[j], d[j - V] + W);
			// }
			
			for (int j = C; j >= 0; --j){
				if (j >= V && i>0)    
					d[j] = MyMax(d[j], d[j - V] + W);
			}
		}
		printf("%d\n", d[C]);
		free(d);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
*/