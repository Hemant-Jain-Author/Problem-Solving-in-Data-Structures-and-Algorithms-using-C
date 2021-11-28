
#include <stdio.h>
#include<stdlib.h>

int isPrime(int n)
{
	int answer = (n > 1) ? 1 : 0;
	for (int i = 2; i * i <= n; ++i)
	{
		if (n % i == 0)
		{
			answer = 0;
			break;
		}
	}
	return answer;
}

int main()
{
	printf("7 is prime: %d", isPrime(7));
	return 0;
}

/*
7 is prime: 1
*/