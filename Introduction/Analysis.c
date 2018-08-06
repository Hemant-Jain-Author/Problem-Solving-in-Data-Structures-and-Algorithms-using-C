/*
 * Analysis.c
 *
 *  Created on: 03-Aug-2018
 *      Author: hemant
 */

#include <stdio.h>
#include <math.h>

int fun1(int n)
{
	int m = 0;
	for (int i = 0; i < n; i++)
	{
		m += 1;
	}
	return m;
}

int fun2(int n)
{
	int i, j, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m += 1;
		}
	}
	return m;
}

int fun3(int n)
{
	int i, j, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < i; j++)
		{
			m += 1;
		}
	}
	return m;
}

int fun4(int n)
{
	int i, m = 0;
	i = 1;
	while (i < n)
	{
		m += 1;
		i = i * 2;
	}
	return m;
}

int fun5(int n)
{
	int i, m = 0;
	i = n;
	while (i > 0)
	{
		m += 1;
		i = i / 2;
	}
	return m;
}

int fun6(int n)
{
	int i, j, k, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				m += 1;
			}
		}
	}
	return m;
}

int fun7(int n)
{
	int i, j, k, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			m += 1;
		}
	}
	for (i = 0; i < n; i++)
	{
		for (k = 0; k < n; k++)
		{
			m += 1;
		}
	}
	return m;
}

int fun8(int n)
{
	int i, j, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < sqrt(n); j++)
		{
			m += 1;
		}
	}
	return m;
}

int fun9(int n)
{
	int i, j, m = 0;
	for (i = n; i > 0; i /= 2)
	{
		for (j = 0; j < i; j++)
		{
			m += 1;
		}
	}
	return m;
}

int fun10(int n)
{
	int i, j, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i; j > 0; j--)
		{
			m += 1;
		}
	}
	return m;
}

int fun11(int n)
{
	int i, j, k, m = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i; j < n; j++)
		{
			for (k = j + 1; k < n; k++)
			{
				m += 1;
			}
		}
	}
	return m;
}

int fun12(int n)
{
	int i, j = 0, m = 0;
	for (i = 0; i < n; i++)
	{
		for (; j < n; j++)
		{
			m += 1;
		}
	}
	return m;
}

int fun13(int n)
{
	int i, j, m = 0;
	for (i = 1; i <= n; i *= 2)
	{
		for (j = 0; j <= i; j++)
		{
			m += 1;
		}
	}
	return m;
}

int main()
{
	printf("N = 100, Number of instructions O(n):: %d \n" ,fun1(100) );
	printf("N = 100, Number of instructions O(n^2):: %d \n" ,fun2(100) );
	printf("N = 100, Number of instructions O(n^2):: %d \n" ,fun3(100) );
	printf("N = 100, Number of instructions O(log(n)):: %d \n" ,fun4(100) );
	printf("N = 100, Number of instructions O(log(n)):: %d \n" ,fun5(100) );
	printf("N = 100, Number of instructions O(n^3):: %d \n" ,fun6(100) );
	printf("N = 100, Number of instructions O(n^2):: %d \n" ,fun7(100) );
	printf("N = 100, Number of instructions O(n^(3/2)):: %d \n" ,fun8(100) );
	printf("N = 100, Number of instructions O(log(n)):: %d \n" ,fun9(100) );
	printf("N = 100, Number of instructions O(n^2):: %d \n" ,fun10(100) );
	printf("N = 100, Number of instructions O(n^3):: %d \n" ,fun11(100) );
	printf("N = 100, Number of instructions O(n):: %d \n" ,fun12(100) );
	printf("N = 100, Number of instructions O(n):: %d \n" ,fun13(100) );

	return 0;

}
/*
N = 100, Number of instructions O(n):: 100
N = 100, Number of instructions O(n^2):: 10000
N = 100, Number of instructions O(n^2):: 4950
N = 100, Number of instructions O(log(n)):: 7
N = 100, Number of instructions O(log(n)):: 7
N = 100, Number of instructions O(n^3):: 1000000
N = 100, Number of instructions O(n^2):: 20000
N = 100, Number of instructions O(n^(3/2)):: 1000
N = 100, Number of instructions O(log(n)):: 197
N = 100, Number of instructions O(n^2):: 4950
N = 100, Number of instructions O(n^3):: 166650
N = 100, Number of instructions O(n):: 100
N = 100, Number of instructions O(n):: 134
*/
