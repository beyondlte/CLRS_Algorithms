// KnapSack.cpp : Defines the entry point for the console application.
// http://www.hawstein.com/posts/dp-knapsack.html

#include "stdafx.h"

// 0-1 knapsack d(i, j)��ʾǰi����Ʒװ��ʣ������Ϊj�ı����е��������
#include<cstdio>
using namespace std;
#define MAXN 1000
#define MAXC 100000

#define MyMax(a, b) (((a)>(b))?(a):(b))

// int V[MAXN], W[MAXN], x[MAXN];
int x[MAXN];
int d[MAXN][MAXC];

int main(){
	freopen("data.in", "r", stdin);//�ض���������
	// freopen("data.out", "w", stdout);//�ض��������
	int n, C, V=0, W=0;
	while (scanf("%d %d", &n, &C) != EOF){
		
		// for (int i = 0; i<n; ++i)   
		// 	scanf("%d %d", &V[i], &W[i]);
		//	

		for (int i = 0; i<n; ++i)   
			x[i] = 0; //��ʼ����ӡ����

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
		printf("%d\n", d[n][C]);//������������ֵ

		//�����ӡ����
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
			// ��������һС���Ż�����Ĵ����֪��״̬ת�Ʒ���Ϊ��d(i, j)=max{ d(i-1, j), d(i-1, j-V)+W }��
			// Ҳ�����ڼ���d(i, j)ʱ�����õ���d(i-1,j)��d(i-1, j-V)��ֵ�� �������ֻ��һ��һά����d(0)��d(C)������״ֵ̬����ô��
			// ��i�����ά��ȥ���� ���ǿ��Խ�ԭ����ά�����ʾΪһά���ݣ�d(i-1, j-V)��Ϊd(j-V)�� d(i-1, j)��Ϊd(j)��
			// ������Ҫ����d(i, j)ʱ��ֻ��Ҫ�Ƚ�d(j)��d(j-V)+W�Ĵ�С�� �ýϴ��������d(j)���ɡ�
			// �ȵȣ�������ǰ�j������˳����������һ��d(i, j+1)����������Ҫ�õ�d(i-1, j)��ֵ�� ��ô����ͳ����ˣ���Ϊ��ողŰ�������Ϊd(i, j)�ˡ�
			// because d(i, j+1)=max{ d(i-1, j+1), d(i-1, j+1-V)+W } 
			//	---->		d(i-1, j) | d(i-1, j+1)
			//	---->		d(i,   j) | d(i,   j+1)
			// if V=1, then d(i-1, j+1) needs d(i-1,j+1-V)=d(i-1,j) 
			// however, d(i-1,j) has been replaced by d(i,j) when we cal d(i,j)
			// ��ô����ô���أ� ����j�ݼ���˳�򼴿ɱ����������⡣���磬�������d(i, j)�� ������Ҫ�������d(i,j-1)��
			// ������״̬ת�Ʒ���Ϊd(i, j-1)=max{ d(i-1, j-1), d(i-1, j-1-V)+W }�����������õ�d(i-1,j)��ֵ��
			// it only needds d(i-1,j-1) and d(i-1, j-1-V), even when V=0, it can't be d(i-1, j)
			// ���ԣ� ��ʹd(i-1,j)��ֵ��������Ҳ����ν��
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