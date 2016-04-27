#include <iostream>
using namespace std;

int Partition(int *array, int p, int r)
{
	int x;
	int i, j;

	// choose the last one as the pivot
	x = array[r]; // pivot
	i = p-1; // initial is -1

	for (j=p; j<r; j++)	
	{
		if (array[j] <= x)
		{
			i++;
			swap(array[i], array[j]);
		}
		// else, do nothing, but just j++
	}
	swap(array[i+1], array[r]);
	return i+1;
}
			


void QuickSort(int *array, int p, int r)
{
	int q;
	if (p<r)
	{
		q = Partition(array, p, r);
		cout<<"2 sort from " << q+1 << " to " << r << "\n";
		QuickSort(array, q+1, r);
		cout<<"1 sort from " << p << " to " << q-1 << "\n";
		QuickSort(array, p, q-1);
	}
	else
		return;
}

void main()
{
	int A[] = {2,8,7,1,3,5,6,4};
	int length = sizeof(A)/sizeof(int);
	QuickSort(A, 0, length-1);
	for (int i=0; i< length; i++)
		cout<<"A[" << i << "]= " << A[i] << "\n";

}
