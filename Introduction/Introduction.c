#include <stdio.h>
#include <stdlib.h>

void swap(int arr[], int x, int y) {
	int temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
	return;
}

int max(int X, int Y) {
	return (X > Y) ? X : Y;
}

int main1() {
	int var;
	int *ptr;
	var = 10;
	ptr = &var;

	printf("Value stored at variable var is %d\n", var);
	printf("Value stored at variable var is %d\n", *ptr);

	printf("The address of variable var is %p \n", &var);
	printf("The address of variable var is %p \n", ptr);
	return 0;
}

/*
 Value stored at variable var is 10
 Value stored at variable var is 10
 The address of variable var is 0x7ffff15a41bc
 The address of variable var is 0x7ffff15a41bc
 */

void printArray(int *arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("]\n");
}

int main2() {
	int arr[10];
	for (int i = 0; i < 10; i++)
		arr[i] = i;

	int size = sizeof(arr) / sizeof(int);
	printArray(arr, size);
	return 0;
}

/*
 [ 0 1 2 3 4 5 6 7 8 9 ]
 */

void print2DArray(int row, int col, int arr[row][col]) {
	printf("[");
	for (int i = 0; i < row; i++) {
		printf("[ ");
		for (int j = 0; j < col; j++)
			printf("%d ", arr[i][j]);
		printf("]");
	}
	printf("]\n\n");
}

int main3() {
	int arr[4][2];
	int count = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 2; j++)
			arr[i][j] = count++;

	print2DArray(4, 2, arr);
}

/*
 [[ 0 1 ][ 2 3 ][ 4 5 ][ 6 7 ]]
 */

int sumArray(int arr[], int size) {
	int total = 0;
	int index = 0;
	for (index = 0; index < size; index++) {
		total = total + arr[index];
	}
	return total;
}

/* Testing code */
int main4() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("Sum of values in array: %d\n",
			sumArray(arr, sizeof(arr) / sizeof(int)));
}

/*
 Sum of values in array: 45
 */

int sequentialSearch(int arr[], int size, int value) {
	for (int i = 0; i < size; i++) {
		if (value == arr[i])
			return i;
	}
	return -1;
}
/* Binary Search Algorithm : Iterative Way */
int binarySearch(int arr[], int size, int value) {
	int low = 0, mid;
	int high = size - 1;
	while (low <= high) {
		mid = low + (high - low) / 2; /* To avoid the overflow */
		if (arr[mid] == value)
			return mid;
		else if (arr[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

void reverseArray(int *a, int n) {
	int temp;
	for (int i = 0, j = n - 1; i < j; i++, j--) {
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}
}

void rotateArray(int *a, int n, int k) {
	reverseArray(a, k);
	reverseArray(&a[k], n - k);
	reverseArray(a, n);
}

/* Testing code */
int main5() {
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	rotateArray(arr, sizeof(arr) / sizeof(int), 2);
	printArray(arr, sizeof(arr) / sizeof(int));
}

/*
 [ 3 4 5 6 1 2 ]
 */

int maxSubArraySum(int a[], int size) {
	int maxSoFar = 0, maxEndingHere = 0;

	for (int i = 0; i < size; i++) {
		maxEndingHere = maxEndingHere + a[i];
		if (maxEndingHere < 0)
			maxEndingHere = 0;
		if (maxSoFar < maxEndingHere)
			maxSoFar = maxEndingHere;
	}
	return maxSoFar;
}

/* Testing code */
int main6() {
	int arr[] = { 1, -2, 3, 4, -4, 6, -4, 3, 2 };
	printf("Max sub array sum : %d\n", maxSubArraySum(arr, 9));
}

/*
 Max sub array sum : 10
 */

struct coord {
	int x;
	int y;
};

int main7() {
	struct coord point;
	point.x = 10;
	point.y = 10;
	printf("X axis coord value is %d \n", point.x);
	printf("Y axis coord value is %d \n", point.y);
	printf("Size of structure is %ld bytes\n", sizeof(point));
	return 0;
}

/*
 X axis coord value is 10
 Y axis coord value is 10
 Size of structure is 8 bytes
 */

struct student {
	int rollNo;
	char *firstName;
	char *lastName;
};

int main8() {
	int i = 0;
	struct student stud;
	struct student *ptrStud;
	ptrStud = &stud;
	ptrStud->rollNo = 1;
	ptrStud->firstName = "john";
	ptrStud->lastName = "smith";
	printf("Roll No: %d  Student Name: %s %s ", ptrStud->rollNo,
			ptrStud->firstName, ptrStud->lastName);

	return 0;
}

/*
 Roll No: 1  Student Name: john smith
 */

int sum(int num1, int num2);

int main9() {
	/* local variable definition */
	int x = 10;
	int y = 20;
	/* calling a function to find sum */
	printf("Sum is : %d\n", sum(x, y));
	return 0;
}

/*
 Sum is : 30
 */

/* function returning the sum of two numbers */
int sum(int num1, int num2) {
	/* local variable declaration */
	int result;
	result = num1 + num2;
	return result;
}

void function2() {
	printf("fun2 line 1\n");
}

void function1() {
	printf("fun1 line 1\n");
	function2();
	printf("fun1 line 2\n");
}

int main10() {
	printf("main line 1\n");
	function1();
	printf("main line 2\n");
}

/*
 main line 1
 fun1 line 1
 fun2 line 1
 fun1 line 2
 main line 2
 */

void increment(int var) {
	var++;
}

int main11() {
	int i = 10;
	printf("Value of i before increment is : %d \n", i);
	increment(i);
	printf("Value of i before increment is : %d \n", i);
}

/*
 Value of i before increment is : 10
 Value of i before increment is : 10
 */

void incrementP(int *ptr) {
	(*ptr)++;
}
int main12() {
	int i = 10;
	printf("Value of i before increment is : %d \n", i);
	incrementP(&i);
	printf("Value of i before increment is : %d \n", i);
}

/*
 Value of i before increment is : 10
 Value of i before increment is : 11
 */

void quickSortUtil(int arr[], int lower, int upper) {
	if (upper <= lower)
		return;

	int pivot = arr[lower];

	int start = lower;
	int stop = upper;

	while (lower < upper) {
		while (arr[lower] <= pivot) {
			lower++;
		}
		while (arr[upper] > pivot) {
			upper--;
		}
		if (lower < upper) {
			swap(arr, upper, lower);
		}
	}
	swap(arr, upper, start); //upper is the pivot position
	quickSortUtil(arr, start, upper - 1); //pivot -1 is the upper for left sub array.
	quickSortUtil(arr, upper + 1, stop); // pivot + 1 is the lower for right sub array.
}
void quickSort(int arr[], int size) {
	quickSortUtil(arr, 0, size - 1);
}
int main13() {
	int arr[10] = { 4, 5, 3, 2, 6, 7, 1, 8, 9, 10 };
	int size = sizeof(arr) / sizeof(int);
	printArray(arr, size);
	quickSort(arr, size);
	printArray(arr, size);
}

/*
 [ 4 5 3 2 6 7 1 8 9 10 ]
 [ 1 2 3 4 5 6 7 8 9 10 ]
 */

void waveArray2(int arr[], int size) {
	/* Odd elements are lesser then even elements. */
	for (int i = 1; i < size; i += 2) {
		if ((i - 1) >= 0 && arr[i] > arr[i - 1]) {
			swap(arr, i, i - 1);
		}
		if ((i + 1) < size && arr[i] > arr[i + 1]) {
			swap(arr, i, i + 1);
		}
	}
}

void waveArray(int arr[], int size) {
	quickSort(arr, size);
	/* Swap adjacent elements in array */
	for (int i = 0; i < size - 1; i += 2) {
		swap(arr, i, i + 1);
	}
}

/* Testing code*/
int main14() {
	int arr[] = { 8, 1, 2, 3, 4, 5, 6, 4, 2 };
	int size = sizeof(arr) / sizeof(int);
	waveArray(arr, size);
	printArray(arr, size);
	return 0;
}

/*
 [ 2 1 3 2 4 4 6 5 8 ]
 */

void indexArray(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		int curr = i;
		int value = -1;

		/* swaps to move elements in proper position. */
		while (arr[curr] != -1 && arr[curr] != curr) {
			int temp = arr[curr];
			arr[curr] = value;
			value = curr = temp;
		}
		/* check if some swaps happened.*/
		if (value != -1) {
			arr[curr] = value;
		}
	}
}

void indexArray2(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		while (arr[i] != -1 && arr[i] != i) {
			/* swap arr[i] and arr[arr[i]] */
			int temp = arr[i];
			arr[i] = arr[temp];
			arr[temp] = temp;
		}
	}
}

/* Testing code */
int main15() {
	int arr[] = { 8, -1, 6, 1, 9, 3, 2, 7, 4, -1 };
	int size = sizeof(arr) / sizeof(int);
	indexArray2(arr, size);
	printArray(arr, size);
	return 0;
}

/*
 [ -1 1 2 3 4 -1 6 7 8 9 ]
 */

void sort1toN(int arr[], int size) {
	int curr, value, next;
	for (int i = 0; i < size; i++) {
		curr = i;
		value = -1;
		/* swaps to move elements in proper position.*/
		while (curr >= 0 && curr < size && arr[curr] != curr + 1) {
			next = arr[curr];
			arr[curr] = value;
			value = next;
			curr = next - 1;
		}
	}
}

void sort1toN2(int arr[], int size) {
	int temp;
	for (int i = 0; i < size; i++) {
		while (arr[i] != i + 1 && arr[i] > 1) {
			temp = arr[i];
			arr[i] = arr[temp - 1];
			arr[temp - 1] = temp;
		}
	}
}

/* Testing code */
int main16() {
	int arr[] = { 8, 5, 6, 1, 9, 3, 2, 7, 4, 10 };
	int size = sizeof(arr) / sizeof(int);
	sort1toN(arr, size);
	printArray(arr, size);

	int arr2[] = { 8, 5, 6, 1, 9, 3, 2, 7, 4, 10 };
	sort1toN2(arr2, size);
	printArray(arr2, size);
	return 0;
}

/*
 [ 1 2 3 4 5 6 7 8 9 10 ]
 [ 1 2 3 4 5 6 7 8 9 10 ]
 */

int smallestPositiveMissingNumber(int arr[], int size) {
	int found;
	for (int i = 1; i < size + 1; 1) {
		found = 0;
		for (int j = 0; j < size; j++) {
			if (arr[j] == i) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			return i;
		}
	}
	return -1;
}
/*
 int smallestPositiveMissingNumber2(int arr[], int size){
 HashTable hs;
 for(int i = 0;i< size; i++) {
 HashAdd(hs, arr[i], 1);
 }
 for(int i=1;i< size+1; i++) {
 if (HashFind(hs, i)) {
 return i;
 }
 }
 return -1;
 }
 */
int smallestPositiveMissingNumber3(int arr[], int size) {
	int *aux = (int*) malloc(size * sizeof(int));
	/* aux = [-1]*size; */
	for (int i = 0; i < size; i++) {
		if (arr[i] > 0 && arr[i] <= size) {
			aux[arr[i] - 1] = arr[i];
		}
	}
	for (int i = 0; i < size; i++) {
		if (aux[i] != i + 1) {
			return i + 1;
		}
	}
	return -1;
}

int smallestPositiveMissingNumber5(int arr[], int size) {
	int temp;
	for (int i = 0; i < size; i++) {
		while (arr[i] != i + 1 && arr[i] > 0 && arr[i] <= size) {
			temp = arr[i];
			arr[i] = arr[temp - 1];
			arr[temp - 1] = temp;
		}
	}
	for (int i = 0; i < size; i++) {
		if (arr[i] != i + 1) {
			return i + 1;
		}
	}
	return -1;
}

void maxMinArr(int arr[], int size) {
	int *aux = (int*) malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		aux[i] = arr[i];
	}

	int start = 0;
	int stop = size - 1;
	for (int i = 0; i < size; i++) {
		if (i % 2 == 0) {
			arr[i] = aux[stop];
			stop -= 1;
		} else {
			arr[i] = aux[start];
			start += 1;
		}
	}
}

/* Testing code */
int main17() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 };
	int size = sizeof(arr) / sizeof(int);
	maxMinArr(arr, size);
	printArray(arr, size);
	return 0;
}

/*
 [ 7 1 6 2 5 3 4 ]
 */

int maxCircularSum(int arr[], int n) {
	int sumAll = 0;
	int currVal = 0;
	int maxVal;

	for (int i = 0; i < n; i++) {
		sumAll += arr[i];
		currVal += (i * arr[i]);
	}
	maxVal = currVal;
	for (int i = 1; i < n; i++) {
		currVal = (currVal + sumAll) - (n * arr[n - i]);
		if (currVal > maxVal) {
			maxVal = currVal;
		}
	}
	return maxVal;
}

/* Testing code */
int main18() {
	int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	printf("MaxCircularSm : %d\n",
			maxCircularSum(arr, sizeof(arr) / sizeof(int)));
}

/*
 MaxCircularSm : 290
 */

int arrayIndexMaxDiff(int arr[], int size) {
	int maxDiff = -1;
	int j;
	for (int i = 0; i < size; i++) {
		j = size - 1;
		while (j > i) {
			if (arr[j] > arr[i]) {
				maxDiff = max(maxDiff, j - i);
				break;
			}
			j -= 1;
		}
	}
	return maxDiff;
}

int arrayIndexMaxDiff2(int arr[], int size) {
	int *leftMin = (int*) malloc(sizeof(int) * size);
	int *rightMax = (int*) malloc(sizeof(int) * size);
	leftMin[0] = arr[0];
	int i, j;
	int maxDiff;
	for (i = 1; i < size; i++) {
		if (leftMin[i - 1] < arr[i]) {
			leftMin[i] = leftMin[i - 1];
		} else {
			leftMin[i] = arr[i];
		}
	}
	rightMax[size - 1] = arr[size - 1];
	for (i = size - 2; i >= 0; i--) {
		if (rightMax[i + 1] > arr[i]) {
			rightMax[i] = rightMax[i + 1];
		} else {
			rightMax[i] = arr[i];
		}
	}
	i = 0;
	j = 0;
	maxDiff = -1;
	while (j < size && i < size) {
		if (leftMin[i] < rightMax[j]) {
			maxDiff = max(maxDiff, j - i);
			j = j + 1;
		} else {
			i = i + 1;
		}
	}
	return maxDiff;
}

int arrayIndexMaxDiff3(int arr[], int size) {
	int *leftMin = (int*) malloc(sizeof(int) * size);
	int *rightMax = (int*) malloc(sizeof(int) * size);
	int minIndex = 0, maxIndex = 0;
	int i, j;
	int maxDiff;
	leftMin[minIndex++] = 0;
	for (i = 1; i < size; i++) {
		if (arr[leftMin[minIndex]] > arr[i]) {
			leftMin[minIndex++] = i;
		}
	}

	rightMax[maxIndex++] = size - 1;
	for (i = size - 2; i >= 0; i--) {
		if (arr[rightMax[-1]] < arr[i]) {
			rightMax[maxIndex++] = i;
		}
	}

	i = 0;
	j = maxIndex - 1;
	maxDiff = -1;

	while (i < minIndex && j >= 0) {
		if (arr[leftMin[i]] < arr[rightMax[j]]) {
			maxDiff = max(maxDiff, rightMax[j] - leftMin[i]);
			j -= 1;
		} else {
			i += 1;
		}
	}
	return maxDiff;
}

int main19() {
	int arr[] = { 33, 9, 10, 3, 2, 60, 30, 33, 1 };
	printf("arrayIndexMaxDiff : %d\n",
			arrayIndexMaxDiff(arr, sizeof(arr) / sizeof(int)));
	printf("arrayIndexMaxDiff : %d\n",
			arrayIndexMaxDiff2(arr, sizeof(arr) / sizeof(int)));
	printf("arrayIndexMaxDiff : %d\n",
			arrayIndexMaxDiff3(arr, sizeof(arr) / sizeof(int)));
}

/*
 arrayIndexMaxDiff : 6
 arrayIndexMaxDiff : 6
 arrayIndexMaxDiff : 5
 */

int maxPathSum(int arr1[], int size1, int arr2[], int size2) {
	int i = 0, j = 0, result = 0, sum1 = 0, sum2 = 0;

	while (i < size1 && j < size2) {
		if (arr1[i] < arr2[j]) {
			sum1 += arr1[i];
			i += 1;
		} else if (arr1[i] > arr2[j]) {
			sum2 += arr2[j];
			j += 1;
		} else {
			result += max(sum1, sum2);
			result = result + arr1[i];
			sum1 = 0;
			sum2 = 0;
			i += 1;
			j += 1;
		}
	}
	while (i < size1) {
		sum1 += arr1[i];
		i += 1;
	}

	while (j < size2) {
		sum2 += arr2[j];
		j += 1;
	}

	result += max(sum1, sum2);
	return result;
}

/* Testing code */
int main20() {
	int arr1[] = { 12, 13, 18, 20, 22, 26, 70 };
	int arr2[] = { 11, 15, 18, 19, 20, 26, 30, 31 };
	printf("Max Path Sum :: %d\n",
			maxPathSum(arr1, sizeof(arr1) / sizeof(int), arr2,
					sizeof(arr2) / sizeof(int)));
}

/*
 Max Path Sum :: 201
 */

int factorial(unsigned int i) {
	/* Termination Condition */
	if (i <= 1)
		return 1;
	/* Body, Recursive Expansion */
	return i * factorial(i - 1);
}

void printIntRec(unsigned int number) {
	char digit = number % 10 + '0';
	if (number /= 10)
		printIntRec(number / 10);
	printf("%c", digit);
}

void printInt(unsigned int number, const int base) {
	char *conversion = "0123456789ABCDEF";
	char digit = number % base;
	if (number /= base)
		printInt(number, base);
	printf("%c", conversion[digit]);
}

char* intToStr(char *p, unsigned int number) {
	char digit = number % 10 + '0';
	if (number /= 10)
		p = intToStr(p, number);
	*p++ = digit;
	return (p);
}

void towerOfHanoi(int num, char src, char dst, char temp) {
	if (num < 1)
		return;

	towerOfHanoi(num - 1, src, temp, dst);
	printf("Move disk %d from peg %c to peg %c\n", num, src, dst);
	towerOfHanoi(num - 1, temp, dst, src);
}

int main21() {
	int num = 3;
	printf("The sequence of moves involved in the Tower of Hanoi are :\n");
	towerOfHanoi(num, 'A', 'C', 'B');
	return 0;
}

/*
 The sequence of moves involved in the Tower of Hanoi are :
 Move disk 1 from peg A to peg C
 Move disk 2 from peg A to peg B
 Move disk 1 from peg C to peg B
 Move disk 3 from peg A to peg C
 Move disk 1 from peg B to peg A
 Move disk 2 from peg B to peg C
 Move disk 1 from peg A to peg C
 */

/* Binary Search Algorithm  Recursive Way */
int binarySearchRecursive(int arr[], int low, int high, int value) {
	if (low > high)
		return -1;
	int mid = (low + high) / 2;
	if (arr[mid] == value)
		return mid;
	else if (arr[mid] < value)
		return binarySearchRecursive(arr, mid + 1, high, value);
	else
		return binarySearchRecursive(arr, low, mid - 1, value);
}

/* Testing code */
int main22() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("sequentialSearch : %d \n",
			sequentialSearch(arr, sizeof(arr) / sizeof(int), 6));
	printf("sequentialSearch : %d \n",
			sequentialSearch(arr, sizeof(arr) / sizeof(int), 16));
	printf("binarySearch : %d \n",
			binarySearch(arr, sizeof(arr) / sizeof(int), 6));
	printf("binarySearch : %d \n",
			binarySearch(arr, sizeof(arr) / sizeof(int), 16));
	printf("binarySearchRecursive : %d \n",
			binarySearchRecursive(arr, 0, sizeof(arr) / sizeof(int) - 1, 6));
	printf("binarySearchRecursive : %d \n",
			binarySearchRecursive(arr, 0, sizeof(arr) / sizeof(int) - 1, 16));
	return 0;
}
/*
 sequentialSearch : 5
 sequentialSearch : -1
 binarySearch : 5
 binarySearch : -1
 binarySearchRecursive : 5
 binarySearchRecursive : -1
 */

int gcd(int m, int n) {
	if (n == 0)
		return m;
	if (m == 0)
		return n;
	return (gcd(n, m % n));
}

/* Testing code */
int main23() {
	printf("%d\n", gcd(5, 2));
	printf("%d\n", gcd(2, 5));
	printf("%d\n", gcd(9, 6));
	printf("%d\n", gcd(6, 9));
	return 0;
}
/*
 1
 1
 3
 3
 */

int fibonacci(int n) {
	if (n < 2)
		return n;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacci2(int n) {
	if (n < 2)
		return n;

	int first = 0;
	int second = 1;
	int temp;

	for (int i = 2; i <= n; i++) {
		temp = first + second;
		first = second;
		second = temp;
	}
	return temp;
}

/* Testing code */
int main24() {
	printf("fibonacci : %d\n", fibonacci(10));
	printf("fibonacci : %d\n", fibonacci2(10));
	return 0;
}
/*
 fibonacci : 55
 fibonacci : 55
 */

int ackermann(int m, int n) {
	if (m == 0)
		return n + 1;

	if (m > 0 && n == 0)
		return ackermann(m - 1, 1);

	if (m > 0 && n > 0)
		return ackermann(m - 1, ackermann(m, n - 1));
}

/* Testing code */
int main25() {
	printf("%d ", ackermann(3, 6));
	return 0;
}
/*
 509
 */

int main() {
	main1();
	main2();
	main3();
	main4();
	main5();
	main6();
	main7();
	main8();
	main9();
	main10();
	main11();
	main12();
	main13();
	main14();
	main15();
	main16();
	main17();
	main18();
	main19();
	main20();
	main21();
	main22();
	main23();
	main24();
	main25();
	return 0;
}
