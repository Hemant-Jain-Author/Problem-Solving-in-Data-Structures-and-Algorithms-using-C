#include <stdio.h>
#include <stdlib.h>
int INFINITE = 99999 ;

int greater(int a, int b) {
	return (a > b);
}

int min(int a, int b) {
	return (a < b)? a : b;
}

void sort(int arr[], int size, int (*comp)(int p1, int p2)) {
	int temp;
    for (int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (comp(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int minCoins(int d[], int n, int val) {// Greedy may be wrong.
	if (val <= 0)
		return 0;

	int count = 0;
	sort(d, n, greater);
	for (int i = n - 1; i >= 0 && val > 0;) {
		if (d[i] <= val) {
			count++;
			val -= d[i];
		} else {
			i--;
		}
	}
	return (val == 0)? count : -1;
}

int minCoins2(int d[], int n, int val) // Brute force.
{
	if (val == 0)
		return 0;

	int count = INFINITE ;
	for (int i = 0; i < n ; i++) {
		if (d[i] <= val) {
			int subCount = minCoins2(d, n, val - d[i]);
			if (subCount != -1) {
				count = min(count, subCount + 1);
			}
		}
	}
	return (count != INFINITE )? count : -1;
}


int minCoinsTDUtil(int coins[], int d[], int n, int val) {
	// Base case
	if (coins[val] != INFINITE )
		return coins[val];

	// Recursion
	for (int i = 0; i < n; i++) {
		if (d[i] <= val) { // check validity of a sub-problem
			int subCount = minCoinsTDUtil(coins, d, n, val - d[i]);

			if (subCount != INFINITE && coins[val] > (subCount + 1)) {
				coins[val] = subCount + 1;
			}
		}
	}
	return coins[val];
}


int minCoinsTD(int d[], int n, int val) {
	int coins[val + 1];
	for(int i = 0; i< val + 1; i++)
		coins[i] = INFINITE ;

	coins[0] = 0; // zero val need zero coins.
	return minCoinsTDUtil(coins, d, n, val);
}

int minCoinsBU(int d[], int n, int val) { // DP bottom up approach.
	int coins[val + 1];
	for(int i = 0; i< val + 1; i++)
		coins[i] = INFINITE ;

	coins[0] = 0; // Base value.

	for (int i = 1; i <= val; i++) {
		for (int j = 0; j < n; j++) {
			// For all coins smaller than or equal to i.

			if (d[j] <= i && 
			coins[i - d[j]] != INFINITE ) {
				coins[i] = min(coins[i], coins[i - d[j]] + 1);
			}
		}
	}

	return (coins[val] != INFINITE )? coins[val] : -1;
}


void printCoinsUtil(int deno[], int val) {
    if (val > 0){
        printCoinsUtil(deno, val - deno[val]);
        printf("%d ", deno[val]);
	}
}

void printCoins(int deno[], int val) {
    printf("Coins are : ");
    printCoinsUtil(deno, val);
    printf("\n");
}

int minCoinsBU2(int d[], int n, int val) { // DP bottom up approach.
	int coins[val + 1];
	int deno[val + 1];

	for(int i = 0; i< val + 1; i++){
		coins[i] = INFINITE ;
		deno[i] = INFINITE ;
	}

	coins[0] = 0; // Base value.

	for (int i = 1; i <= val; i++) {
		for (int j = 0; j < n; j++) {
			// For all coins smaller than or equal to i.
			if (d[j] <= i 
			&& coins[i - d[j]] != INFINITE && coins[i] > (coins[i - d[j]] + 1)) {
				coins[i] = coins[i - d[j]] + 1;
				deno[i] = d[j];
			}
		}
	}
	
	printCoins(deno, val);
	return (coins[val] != INFINITE )? coins[val] : -1;
}

int main() {
	int  d[] = {1, 4, 6, 9, 12};
	int value = 15;
	int n = 5;
	printf("Count is : %d\n" , minCoins(d, n, value));
	printf("Count is : %d\n" , minCoins2(d, n, value));
	printf("Count is : %d\n" , minCoinsBU(d, n, value));
	printf("Count is : %d\n" , minCoinsTD(d, n, value));
	printf("Count is : %d\n" , minCoinsBU2(d, n, value));
}

/*
Count is : 4
Count is : 2
Count is : 2
Count is : 2
Coins are : 9 6 
Count is : 2
*/
