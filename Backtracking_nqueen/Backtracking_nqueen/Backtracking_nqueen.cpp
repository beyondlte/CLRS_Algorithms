// Backtracking_nqueen.cpp : Defines the entry point for the console application.
// http://zephiruswt.blog.51cto.com/5193151/895797

#include "stdafx.h"

/*
//�˻ʺ�����

// Queen.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

class Queen{    //��Queen��¼��ռ��еĽڵ���Ϣ
	friend int nQueen(int);
private:
	bool Place(int k);    //��֦����
	void Backtrack(int t);    //�ݹ麯��
	int n;    //�ʺ����
	int *x;    //��ǰ��
	long sum;    //��ǰ���еķ�����
};

int abs(int ab)//�����ֵ
{
	return ab>0 ? ab : -ab;
}

bool Queen::Place(int k)    //��֦����
{
	for (int j = 1; j<k; j++)
	{
		//��֦�����������ͬһ�У�ͬһ�л���ͬб����
		if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
			return false;
	}
	return true;
}

void Queen::Backtrack(int t)    //�ݹ���ݺ���
{
	if (t>n) 
		sum++;    //���������Ҷ�ӣ�˵�������һ����
	else
	for (int i = 1; i <= n; i++)
	{
		x[t] = i;
		if (Place(t)) 
			Backtrack(t + 1); //����PlaceΪ��֦����
	}
}

int nQueen(int n)//��ʼ������
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
	printf("%d", nQueen(8));//�������8�����˻ʺ�����
	return 0;
}
*/


#include <stdlib.h> 
#include <stdio.h> 

int m[8][8] = { 0 };//��ʾ���̣���ʼΪ0����ʾδ���ûʺ� 
int num = 0;//����Ŀ 
int search = 0; // in each solution, the number of searches

//��������ǰrow-1���ѷ��úûʺ� 
//����ڵ�row�С���column�з���һö�ʺ��Ƿ���� 
bool check(int row, int column)
{
	if (row == 1) 
		return true;
	int i, j;
	//����ֻ����һö�ʺ� 
	// only checks m[0][col-1] to m[row-2][col-1], on vertical direction
	// we don't check rows larger than m[row-1], we only check preceeding rows
	for (i = 0; i <= row - 2; i++)
	{
		if (m[i][column - 1] == 1) 
			return false;
	}
	//����������ֻ����һö�ʺ�, only to m[row-2]
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
	//����������ֻ����һö�ʺ�, only to m[row-2]
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

//���ѷ���8ö�ʺ�Ϊ���н�ʱ��������� 
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

//���õݹ麯��ʵ�ְ˻ʺ�����㷨 
//�ú�����⵱����ǰrow-1���ѷ��úûʺ��ڵ�row�з��ûʺ� 
void solve(int row)
{
	int j;
	//�����ڵ�row�еĸ��з��ûʺ� 
	for (j = 0; j<8; j++)
	{
		//������һ�з��ûʺ� 
		m[row - 1][j] = 1;
		output(2);
		//����ڸ��з��ûʺ��Ƿ����, m[row-1][j] corresponds to row:row and column:j+1 
		if (check(row, j + 1) == true)
		{
			//�����пɷ��ûʺ��Ҹ���Ϊ���һ�У����ҵ�һ���н⣬��� 
			if (row == 8) 
				output(1);
			//�����пɷ��ûʺ�������һ�У�������������� 
			else
			{
				solve(row + 1);
			}
		}
		//ȡ�����еĻʺ󣬽��л��ݣ��������з��ûʺ� 
		m[row - 1][j] = 0;
		output(0);
	}
}

//������ 
int main()
{
	//���˻ʺ����� 
	freopen("data.out", "w", stdout);//�ض��������
	solve(1);
	return 0;
}