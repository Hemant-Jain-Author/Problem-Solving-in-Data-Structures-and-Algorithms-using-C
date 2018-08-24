#include <stdio.h>
#include <stdlib.h>
void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
    return;
}

int max(int X, int Y)
{
    if (X > Y)
        return X;
    return Y;
}

int main1()
{
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

void printArray(int *arr, int size)
{
    printf("Values stored in array are : ");
    for (int i = 0; i < size; i++)
    {
        printf("  %d  ", arr[i]);
    }
    printf("\n");
}

int main2()
{
    int arr[10];
    for (int i = 0; i < 10; i++)
    {
        arr[i] = i;
    }
    int size = sizeof(arr) / sizeof(int);

    printArray(arr, size);
    return 0;
}

void printArrayAddress(int arr[], int count)
{
    printf("Values stored in array are : ");
    for (int i = 0; i < count; i++)
    {
        printf("Data: [%d] has Address: [%p] \n", arr[i], arr + i);
    }
}

void printArrayUsingPointer(int arr[], int count)
{
    printf("Values stored in array are : ");
    int *ptr = arr;
    for (int i = 0; i < count; i++)
    {
        printf("Data: [%d] has Address: [%p] \n", *ptr, ptr);
        ptr++;
    }
}

void print2DArray(int *arr[], int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            printf("[ %d ]", *(arr + i * col + j));
}
void print2DArrayAddress(int *arr[], int row, int col)
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            printf("Value: %d, Address: %p\n", *(arr + i * col + j),
                   (arr + i * col + j));
}

int main3()
{
    int arr[4][2];
    int count = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 2; j++)
            arr[i][j] = count++;

    print2DArray((int **)arr, 4, 2);
    print2DArrayAddress((int **)arr, 4, 2);
}

int SumArray(int arr[], int size)
{
    int total = 0;
    int index = 0;
    for (index = 0; index < size; index++)
    {
        total = total + arr[index];
    }
    return total;
}

int SequentialSearch(int arr[], int size, int value)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        if (value == arr[i])
            return i;
    }
    return -1;
}
/* Binary Search Algorithm � Iterative Way */
int BinarySearch(int arr[], int size, int value)
{
    int low = 0, mid;
    int high = size - 1;
    while (low <= high)
    {
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

void reverseArray(int *a, int n)
{
    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
        a[i] ^= a[j] ^= a[i] ^= a[j];
    }
}
void rotateArray2(int *a, int n, int k)
{
    reverseArray(a, k);
    reverseArray(&a[k], n - k);
    reverseArray(a, n);
}

int maxSubArraySum(int a[], int size)
{
    int maxSoFar = 0, maxEndingHere = 0;

    for (int i = 0; i < size; i++)
    {
        maxEndingHere = maxEndingHere + a[i];
        if (maxEndingHere < 0)
            maxEndingHere = 0;
        if (maxSoFar < maxEndingHere)
            maxSoFar = maxEndingHere;
    }
    return maxSoFar;
}

struct coord
{
    int x;
    int y;
};
int main6()
{
    struct coord point;
    point.x = 10;
    point.y = 10;
    printf("X axis coord value is %d \n", point.x);
    printf("Y axis coord value is %d \n", point.y);
    printf("Size of structure is %d bytes\n", sizeof(point));
    return 0;
}

struct student
{
    int rollNo;
    char *firstName;
    char *lastName;
};
int main7()
{
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

int sum(int num1, int num2);
int main8()
{
    /* local variable definition */
    int x = 10;
    int y = 20;
    int result;
    /* calling a function to find sum */
    result = sum(x, y);
    printf("Sum is : %d\n", result);
    return 0;
}
/* function returning the sum of two numbers */
int sum(int num1, int num2)
{
    /* local variable declaration */
    int result;
    result = num1 + num2;
    return result;
}

void function2()
{
    printf("fun2 line 1\n");
}

void function1()
{
    printf("fun1 line 1\n");
    function2();
    printf("fun1 line 2\n");
}

int main9()
{
    printf("main line 1\n");
    function1();
    printf("main line 2\n");
}

void increment(int var)
{
    var++;
}

int main10()
{
    int i = 10;
    printf("Value of i before increment is : %d \n", i);
    increment(i);
    printf("Value of i before increment is : %d \n", i);
}

void incrementP(int *ptr)
{
    (*ptr)++;
}
int main11()
{
    int i = 10;
    printf("Value of i before increment is : %d \n", i);
    incrementP(&i);
    printf("Value of i before increment is : %d \n", i);
}

void WaveArray2(int arr[], int size)
{
    /* Odd elements are lesser then even elements. */
    for (int i = 1; i < size; i += 2)
    {
        if ((i - 1) >= 0 && arr[i] > arr[i - 1])
        {
            swap(arr, i, i - 1);
        }
        if ((i + 1) < size && arr[i] > arr[i + 1])
        {
            swap(arr, i, i + 1);
        }
    }
}

void quickSortUtil(int arr[], int lower, int upper)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper)
    {
        while (arr[lower] <= pivot)
        {
            lower++;
        }
        while (arr[upper] > pivot)
        {
            upper--;
        }
        if (lower < upper)
        {
            swap(arr, upper, lower);
        }
    }
    swap(arr, upper, start); //upper is the pivot position

    quickSortUtil(arr, start, upper - 1); //pivot -1 is the upper for left sub array.
    quickSortUtil(arr, upper + 1, stop);  // pivot + 1 is the lower for right sub array.
}
void quickSort(int arr[], int size)
{
    quickSortUtil(arr, 0, size - 1);
}
int main444()
{
    int arr[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    int size = sizeof(arr) / sizeof(int);
    printArray(arr, size);
    quickSort(arr, size);
    printArray(arr, size);
}

void WaveArray(int arr[], int size)
{
    quickSort(arr, size);
    /* Swap adjacent elements in array */
    for (int i = 0; i < size - 1; i += 2)
    {
        swap(arr, i, i + 1);
    }
}

/* Testing code*/
int main34()
{
    int arr[] = {8, 1, 2, 3, 4, 5, 6, 4, 2};
    int size = sizeof(arr) / sizeof(int);
    WaveArray(arr, size);
    printArray(arr, size);
    return 0;
}

void indexArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int curr = i;
        int value = -1;

        /* swaps to move elements in proper position. */
        while (arr[curr] != -1 && arr[curr] != curr)
        {
            int temp = arr[curr];
            arr[curr] = value;
            value = curr = temp;
        }
        /* check if some swaps happened.*/
        if (value != -1)
        {
            arr[curr] = value;
        }
    }
}

void indexArray2(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        while (arr[i] != -1 && arr[i] != i)
        {
            /* swap arr[i] and arr[arr[i]] */
            int temp = arr[i];
            arr[i] = arr[temp];
            arr[temp] = temp;
        }
    }
}

/* Testing code */
int main66()
{
    int arr[] = {8, -1, 6, 1, 9, 3, 2, 7, 4, -1};
    int size = sizeof(arr) / sizeof(int);
    indexArray2(arr, size);
    printArray(arr, size);
    return 0;
}

void Sort1toN(int arr[], int size)
{
    int curr, value, next;
    for (int i = 0; i < size; i++)
    {
        curr = i;
        value = -1;
        /* swaps to move elements in proper position.*/
        while (curr >= 0 && curr < size && arr[curr] != curr + 1)
        {
            next = arr[curr];
            arr[curr] = value;
            value = next;
            curr = next - 1;
        }
    }
}

void Sort1toN2(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        while (arr[i] != i + 1 && arr[i] > 1)
        {
            temp = arr[i];
            arr[i] = arr[temp - 1];
            arr[temp - 1] = temp;
        }
    }
}

int SmallestPositiveMissingNumber(int arr[], int size)
{
    int found;
    for (int i = 1; i < size + 1; 1)
    {
        found = 0;
        for (int j = 0; j < size; j++)
        {
            if (arr[j] == i)
            {
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            return i;
        }
    }
    return -1;
}
/*
int SmallestPositiveMissingNumber2(int arr[], int size){
	HashTable hs;
	for(int i = 0;i< size; i++) {
		HashAdd(hs, arr[i], 1);
	}
	for(int i=1;i< size+1; i++) {
		if (HashFind(hs, i)){
			return i;
		}
	}
	return -1;	
}
*/
int SmallestPositiveMissingNumber3(int arr[], int size)
{
    int *aux = (int *)malloc(size * sizeof(int));
    /* aux = [-1]*size; */
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > 0 && arr[i] <= size)
        {
            aux[arr[i] - 1] = arr[i];
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (aux[i] != i + 1)
        {
            return i + 1;
        }
    }
    return -1;
}

int SmallestPositiveMissingNumber5(int arr[], int size)
{
    int temp;
    for (int i = 0; i < size; i++)
    {
        while (arr[i] != i + 1 && arr[i] > 0 && arr[i] <= size)
        {
            temp = arr[i];
            arr[i] = arr[temp - 1];
            arr[temp - 1] = temp;
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[i] != i + 1)
        {
            return i + 1;
        }
    }
    return -1;
}

void MaxMinArr(int arr[], int size)
{
    int *aux = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
    {
        aux[i] = arr[i];
    }

    int start = 0;
    int stop = size - 1;
    for (int i = 0; i < size; i++)
    {
        if (i % 2 == 0)
        {
            arr[i] = aux[stop];
            stop -= 1;
        }
        else
        {
            arr[i] = aux[start];
            start += 1;
        }
    }
}

/*
arr = [1, 2, 3, 4, 5, 6, 7]
MaxMinArr(int arr[], int size)
print arr
*/

void ReverseArr(int arr[], int start, int stop)
{
    while (start < stop)
    {
        swap(arr, start, stop);
        start += 1;
        stop -= 1;
    }
}

void MaxMinArr2(int arr[], int size)
{
    for (int i = 0; i < (size - 1); i++)
    {
        ReverseArr(arr, i, size - 1);
    }
}

/* Testing code */
int main213()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(int);
    MaxMinArr(arr, size);
    printArray(arr, size);

    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int size2 = sizeof(arr) / sizeof(int);
    MaxMinArr2(arr2, size2);
    printArray(arr2, size2);
    return 0;
}

int maxCircularSum(int arr[], int n)
{
    int sumAll = 0;
    int currVal = 0;
    int maxVal;

    for (int i = 0; i < n; i++)
    {
        sumAll += arr[i];
        currVal += (i * arr[i]);
    }
    maxVal = currVal;
    for (int i = 1; i < n; i++)
    {
        currVal = (currVal + sumAll) - (n * arr[n - i]);
        if (currVal > maxVal)
        {
            maxVal = currVal;
        }
    }
    return maxVal;
}

/* Testing code */
int main777()
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    printf("MaxCirculrSm : %d", maxCircularSum(arr, sizeof(arr) / sizeof(int)));
}

int ArrayIndexMaxDiff(int arr[], int size)
{
    int maxDiff = -1;
    int j;
    for (int i = 0; i < size; i++)
    {
        j = size - 1;
        while (j > i)
        {
            if (arr[j] > arr[i])
            {
                maxDiff = max(maxDiff, j - i);
                break;
            }
            j -= 1;
        }
    }
    return maxDiff;
}

int ArrayIndexMaxDiff2(int arr[], int size)
{
    int *leftMin = (int *)malloc(sizeof(int) * size);
    int *rightMax = (int *)malloc(sizeof(int) * size);
    leftMin[0] = arr[0];
    int i, j;
    int maxDiff;
    for (i = 1; i < size; i++)
    {
        if (leftMin[i - 1] < arr[i])
        {
            leftMin[i] = leftMin[i - 1];
        }
        else
        {
            leftMin[i] = arr[i];
        }
    }
    rightMax[size - 1] = arr[size - 1];
    for (i = size - 2; i >= 0; i--)
    {
        if (rightMax[i + 1] > arr[i])
        {
            rightMax[i] = rightMax[i + 1];
        }
        else
        {
            rightMax[i] = arr[i];
        }
    }
    i = 0;
    j = 0;
    maxDiff = -1;
    while (j < size && i < size)
    {
        if (leftMin[i] < rightMax[j])
        {
            maxDiff = max(maxDiff, j - i);
            j = j + 1;
        }
        else
        {
            i = i + 1;
        }
    }
    return maxDiff;
}

int ArrayIndexMaxDiff3(int arr[], int size)
{
    int *leftMin = (int *)malloc(sizeof(int) * size);
    int *rightMax = (int *)malloc(sizeof(int) * size);
    int minIndex = 0, maxIndex = 0;
    int i, j;
    int maxDiff;
    leftMin[minIndex++] = 0;
    for (i = 1; i < size; i++)
    {
        if (arr[leftMin[minIndex]] > arr[i])
        {
            leftMin[minIndex++] = i;
        }
    }

    rightMax[maxIndex++] = size - 1;
    for (i = size - 2; i >= 0; i--)
    {
        if (arr[rightMax[-1]] < arr[i])
        {
            rightMax[maxIndex++] = i;
        }
    }

    i = 0;
    j = maxIndex - 1;
    maxDiff = -1;

    while (i < minIndex && j >= 0)
    {
        if (arr[leftMin[i]] < arr[rightMax[j]])
        {
            maxDiff = max(maxDiff, rightMax[j] - leftMin[i]);
            j -= 1;
        }
        else
        {
            i += 1;
        }
    }
    return maxDiff;
}

int main212()
{
    int arr[] = {33, 9, 10, 3, 2, 60, 30, 33, 1};
    printf("ArrayIndexMaxDiff : %d", ArrayIndexMaxDiff(arr, sizeof(arr) / sizeof(int)));
    printf("ArrayIndexMaxDiff : %d", ArrayIndexMaxDiff2(arr, sizeof(arr) / sizeof(int)));
    printf("ArrayIndexMaxDiff : %d", ArrayIndexMaxDiff3(arr, sizeof(arr) / sizeof(int)));
}

int maxPathSum(int arr1[], int size1, int arr2[], int size2)
{
    int i = 0, j = 0, result = 0, sum1 = 0, sum2 = 0;

    while (i < size1 && j < size2)
    {
        if (arr1[i] < arr2[j])
        {
            sum1 += arr1[i];
            i += 1;
        }
        else if (arr1[i] > arr2[j])
        {
            sum2 += arr2[j];
            j += 1;
        }
        else
        {
            result += max(sum1, sum2);
            result = result + arr1[i];
            sum1 = 0;
            sum2 = 0;
            i += 1;
            j += 1;
        }
    }
    while (i < size1)
    {
        sum1 += arr1[i];
        i += 1;
    }

    while (j < size2)
    {
        sum2 += arr2[j];
        j += 1;
    }

    result += max(sum1, sum2);
    return result;
}

/* Testing code */
int main12()
{
    int arr1[] = {12, 13, 18, 20, 22, 26, 70};
    int arr2[] = {11, 15, 18, 19, 20, 26, 30, 31};
    printf("Max Path Sum :: %d ", maxPathSum(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int)));
}

int factorial(unsigned int i)
{
    /* Termination Condition */
    if (i <= 1)
        return 1;
    /* Body, Recursive Expansion */
    return i * factorial(i - 1);
}

void printIntRec(unsigned int number)
{
    char digit = number % 10 + '0';
    if (number /= 10)
        printIntRec(number / 10);
    printf("%c", digit);
}

void printInt(unsigned int number, const int base)
{
    char *conversion = "0123456789ABCDEF";
    char digit = number % base;
    if (number /= base)
        printInt(number, base);
    printf("%c", conversion[digit]);
}

char *intToStr(char *p, unsigned int number)
{
    char digit = number % 10 + '0';
    if (number /= 10)
        p = intToStr(p, number);
    *p++ = digit;
    return (p);
}

void towerOfHanoi(int num, char src, char dst, char temp)
{
    if (num < 1)
        return;

    towerOfHanoi(num - 1, src, temp, dst);
    printf("\n Move disk %d from peg %c to peg %c", num, src, dst);
    towerOfHanoi(num - 1, temp, dst, src);
}

int main131()
{
    int num = 4;
    printf("The sequence of moves involved in the Tower of Hanoi are :\n");
    towerOfHanoi(num, 'A', 'C', 'B');
    return 0;
}

int GCD(int m, int n)
{
    if (m < n)
        return (GCD(n, m));
    if (m % n == 0)
        return (n);
    return (GCD(n, m % n));
}

int fibonacci(int n)
{
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibonacci(n) :
{
    int first = 0;
    int second = 1;
    int i, temp;

    if (n == 0)
        return first;
    else if (n == 1)
        return second;
    i = 2;
    while (i <= n)
    {
        temp = first + second;
        first = second;
        second = temp;
        i += 1;
    }
    return temp;
}
void permutation(int *arr, int i, int length)
{
    if (length == i)
    {
        printArray(arr, length);
        return;
    }
    int j = i;
    for (j = i; j < length; j++)
    {
        swap(arr, i, j);
        permutation(arr, i + 1, length);
        swap(arr, i, j);
    }
    return;
}
int main132()
{
    int arr[5];
    for (int i = 0; i < 5; i++)
    {
        arr[i] = i;
    }
    permutation(arr, 0, 5);
}

/* Binary Search Algorithm � Recursive Way */
int BinarySearchRecursive(int arr[], int low, int high, int value)
{
    if (low > high)
        return -1;
    int mid = (low + high) / 2;
    if (arr[mid] == value)
        return mid;
    else if (arr[mid] < value)
        return BinarySearchRecursive(arr, mid + 1, high, value);
    else
        return BinarySearchRecursive(arr, low, mid - 1, value);
}

/* Testing code */
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    printf(" %d ", BinarySearchRecursive(arr, 0, sizeof(arr) / sizeof(int) - 1, 6));
    printf(" %d ", BinarySearchRecursive(arr, 0, sizeof(arr) / sizeof(int) - 1, 16));
    return 0;
}

/*
void sortedArrayUtil (int first[], int fSize, int fIndex, int second[], int sSize, int sIndex, int arr[], int index, int flag):
	# print arr # all alternate sorted array. 
	if flag == 0:
		for i in range(fIndex, fSize):
			# first element should be from first.
			if (len(int arr[], int size == 0 or first[i] > arr[-1]):
				arr.append(first[i])
				sortedArrayUtil(first, fSize, i+1, second, sSize, sIndex,arr, index+1, not flag)
				arr.pop()

	if flag == 1:
		for i in range(sIndex, sSize):
			if second[i] > arr[-1]:
				arr.append(second[i])
				print arr # last element should be from second.
				sortedArrayUtil(first, fSize, fIndex, second, sSize, i+1,arr, index+1, not flag)
				arr.pop()

def sortedArray(first, second):
	fSize = len(first)
	sSize = len(second)
	arr=[]
	sortedArrayUtil(first, fSize, 0, second, sSize, 0, arr, 0, 0)
*/
