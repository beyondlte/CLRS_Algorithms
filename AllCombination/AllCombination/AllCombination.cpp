// AllCombination.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#include <stack>
using namespace std;

char * reverseArray(char *s, int m, int n);
#define SWAP(T, a, b) do { T tmp = a; a = b; b = tmp; } while (0)

// ------------ functions
// permutation without repeatition
void Permu(char *s, int h, int t);
// next_permutation using lexicographic ordering
char * NextPermutation(char *s);
// permutation with/without repeatition
void allPerm(char* result, char *str, int size, int resPos, int repeat);

// all possible combinations of r elements in a given array of size n
void combinationUtil(char arr[], char data[], int start, int end, int index, int r);
void printCombination(char arr[], int n, int r);

// --------- global variables
stack<int> ST;
int m = 1;

// permutation without repeatition
void Permu(char *s, int h, int t)
{
	printf("call permu(s, %d, %d)\n", h, t);
	if (h==t)
	{
		printf("s = %s, try to swap %c & %c, but no need, just print it, s = ", s, s[h], s[t]);
		for (int i = 0; i <= t; i++)
			printf("%c", s[i]);
		printf("\n");
	}
	else
	{
		for (int i = h; i<=t; i++)
		{
			// for debug purpose, we push the number into a stack
			ST.push(m);
			printf("%d ....... swap %c & %c\n", m, s[h], s[i]);
			m++;

			SWAP(char, s[h],s[i]);
			Permu(s, h+1, t);
			printf("%d ------- swap back %c & %c: s=%s --> ", ST.top(), s[h], s[i], s);
			SWAP(char, s[h],s[i]); // backtrack

			// for debug, we pop the m out of stack when the recursive call returns 
			printf("%s\n", s);
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

// next_permutation using lexicographic ordering
// first find x, from end to start, as long as s[i]<=s[i+1]
// then find y, the last larger value than x on right of x
//       x y  
// 4 1 3 2 5 ->
// 4 1 3 5 2

//     x y
// 4 1 3 5 2 ->
// 4 1 5 3 2
// swap 3 2 to 2 3
// 4 1 5 2 3

//       x y
// 4 1 5 2 3
// 4 1 5 3 2

//   x     y
// 4 1 5 3 2
// 4 2 5 3 1
// swap 5 3 1 to 1 3 5
// 4 2 1 3 5
char * NextPermutation(char *s)
{
	int i;
	// first find x
	int len = (int)strlen(s);
	for (i = len - 1; (i >= 0 && s[i] > s[i + 1]); --i)
	{
		;
	}
	// printf("i=%d, x=%c\n", i, s[i]);

	// find y, the last larger value on the right of s[i]
	int j;
	for (j = len - 1; (j > i&&s[j] <= s[i]); --j)
		;

	// printf("j=%d, y=%c\n", j, s[j]);

	// swap x & y
	char temp = s[i];
	s[i] = s[j];
	s[j] = temp;

	// printf("s = %s\n", s);

	// reverse s[i+1... len-1] in place
	reverseArray(s, i + 1, len - 1);
	/*
	int m = i + 1;
	int n = len-1;
	while (m <= n)
	{
		temp = s[m];
		s[m] = s[n];
		s[n] = temp;
		++m;
		--n;
	}
	*/

	// printf("s = %s\n", s);
	return s;
}

// reverse the string in place
char * reverseArray(char *s, int m, int n)
{
	char *ret = s;
	char temp;
	while (m <= n)
	{
		temp = ret[m];
		ret[m] = ret[n];
		ret[n] = temp;
		++m;
		--n;
	}
	return ret;
}

// permutatin with repeatition
void allPerm(char* result, char *str, int size, int resPos, int repeat)
{
	// basic idea is when resPos doesn't reach size, it will assign value to result[resPos] and recursively call allPerm(resPos+1)
	// when it reaches size, it will not call allPerm(resPos+1), it will call the block (resPos==size) instead to print it out
	// so first result[0] = a -> call allPerm(0+1)
	//    then  result[1] = a -> call allPerm(1+1)
	//          result[2] = a ->, don't call allPerm(2+1), will print result = aaa
	//    then back to result[2], which is assigned to 'a', but there's a for loop, 'b' and 'c' not assigned yet
	//    so    result[2] = b -> print aab
	//		    result[3] = c -> print aac
	//    then back to result[1], assign 'b' and 'c' to it
	//			result[1] = b
	//			result[2] = a -> print aba
	//			result[2] = b -> print abb
	//			result[2] = c -> print abc
	//    then change result[1] again	
	//			result[1] = c

	if (resPos == size)
	{
		printf("%d: ", m);
		for (int i = 0; i < size; ++i)
			printf("%c", result[i]);
		m++;
		printf("\n");
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			// adding this line can get all permutations without repeatition
			// the idea is check if the new allocation is the repeatition of all previous 
			if (repeat == 0)
			{
				// now only works for size = 3
				// if size = 4, we need one more condition, !=result[resPos-3]
				if (resPos >= 0 && (str[i] != result[resPos - 1]) && (str[i] != result[resPos - 2]))
				{
					result[resPos] = str[i];
					printf("result[%d] = %c\n", resPos, result[resPos]);
					allPerm(result, str, size, resPos + 1, repeat);
				}
			}
			else
			{
				result[resPos] = str[i];
				printf("result[%d] = %c\n", resPos, result[resPos]);
				allPerm(result, str, size, resPos + 1, repeat);
			}
		}
	}
}


// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil()
void printCombination(char arr[], int n, int r)
{
	// A temporary array to store all combination one by one
	char *data = (char *)malloc(sizeof(char)*r);

	// Print all combination using temprary array 'data[]'
	combinationUtil(arr, data, 0, n - 1, 0, r);
}

/* arr[]  ---> Input Array
data[] ---> Temporary array to store current combination
start & end ---> Staring and Ending indexes in arr[]
index  ---> Current index in data[]
r ---> Size of a combination to be printed */
void combinationUtil(char arr[], char data[], int start, int end, int index, int r)
{
	// Current combination is ready to be printed, print it
	if (index == r)
	{
		for (int j = 0; j<r; j++)
			printf("%c", data[j]);
		printf("\n");
		return;
	}

	// replace index with all possible elements. The condition
	// "end-i+1 >= r-index" makes sure that including one element
	// at index will make a combination with remaining elements
	// at remaining positions

	// More clear explanation:
	// Its pretty confusing..Instead of i <= end && end - i + 1 >= r - index you could understand that 
	// as i <= end - (r - index) + 1 which means the following :
	// Lets take[1, 2, 3, 4, 5] and r = 3. While picking up the first element(index = 0) we dont need to 
	// go through 4 and 5. lets suppose we considered the 1st element as 1. 
	// Then, we dont want to pick the 2nd element as 5 at any case ([1, 5, ? ] not possible).
	// So the picking up a digit is really depending on end, r and index.We are excluding 
	// last r - index elements at the end.So it becomes i <= end - (r - index) + 1.
	// for example: 123456
	// when index = 1, we have x,?,?, x can be 1, 2, 3, 4, and ? will not be 5 and 6 ,i.e. 6-(3-1)+1 = 6-2+1 = 5 and above
	// when index = 2, we have x,y,?, y can be 2, 3, 4, 5, won't be 1 again, and ? will not be 6 ,i.e. 6-(3-2)+1 = 6-1+1 = 6 and above
	// this is similar to the allPerm, but start is differnt, in allPerm, start pos is always 0, but here it's varying as i+1
	for (int i = start; i <= end && i <= end - (r - index) + 1; i++)
	{
		data[index] = arr[i];
		combinationUtil(arr, data, i + 1, end, index + 1, r);
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "abc"; // "abcd";
	unsigned int n = strlen(str);

	// permunation without repeatition: n!
	Permu(str, 0, n-1);

	// permunation with/without repeatition
	// with repeatition: n^n
	// without repeatition: n!
	/*
	char *result = (char *)malloc(sizeof(char)*n);
	int repeat;
	allPerm(result, str, n, 0, repeat=0);
	*/

	// all combinations of r elements: C(n, r)
	printCombination(str, n, 1);
	printCombination(str, n, 2);
	printCombination(str, n, 3);

	// next_permutation using lexicographic ordering
	/*
	// first get the target string, i.e. the reverse of str
	// need to allocate a new pointer and copy the reverse of str to it
	char *target = (char *)malloc(sizeof(char)*n);
	reverseArray(str, 0, n - 1);
	strcpy(target, str);

	// reverse it back, as in reverseArray, str has been reversed
	char *origin = str;
	origin = reverseArray(str, 0, n - 1);
	int i = 1;
	while (strcmp(origin, target))
	{
		printf("str %d = %s\n", i, str);
		origin = NextPermutation(str);
		++i;
	}
	printf("str %d = %s\n", i, str);
	// end of calling NextPermutation
	*/

	return 0;
}

