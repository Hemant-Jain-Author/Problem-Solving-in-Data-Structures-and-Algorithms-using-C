#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../HashTable/Counter.c"
#include "../HashTable/Set.c"

int greater(int value1, int value2) {
    return value1 > value2;
}

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a < b ? b : a;
}

void swap(int arr[], int first, int second) {
    int temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

void sort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (greater(arr[j], arr[j + 1])) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int linearSearchUnsorted(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (value == arr[i]) {
            return 1;
        }
    }
    return 0;
}

int linearSearchsorted(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (value == arr[i])
            return 1;
        if (value < arr[i])
            return 0;
    }
    return 0;
}

int binarySearch(int arr[], int size, int value) {
    int start = 0;
    int end = size - 1;
    int mid;

    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid] == value) {
            return 1;
        } else if (arr[mid] < value) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return 0;
}

int binarySearchUtil(int arr[], int start, int end, int value) {
    if (start > end)
        return 0;

    int mid = (start + end) / 2;
    if (arr[mid] == value)
        return 1;
    else if (value < arr[mid])
        return binarySearchUtil(arr, start, mid - 1, value);
    else
        return binarySearchUtil(arr, mid + 1, end, value);
}

int binarySearchRecursive(int arr[], int size, int value) {
    return binarySearchUtil(arr, 0, size-1, value);
}

int fibonacciSearch(int arr[], int size, int value) {
    /* Initialize fibonacci numbers */
	int fibNMn2 = 0;
	int fibNMn1 = 1;
	int fibN = fibNMn2 + fibNMn1;

	while (fibN < size) {
		fibNMn2 = fibNMn1;
		fibNMn1 = fibN;
		fibN = fibNMn2 + fibNMn1;
	}

	int low = 0;
	while (fibN > 1) { // fibonacci series start with 0, 1, 1, 2
		int i = min(low + fibNMn2, size-1);
		if (arr[i] == value) {
			return 1;
		} else if (arr[i] < value) {
			fibN = fibNMn1;
			fibNMn1 = fibNMn2;
			fibNMn2 = fibN - fibNMn1;
			low = i;
		} else { // for feb2 <= 1, these will be invalid.
			fibN = fibNMn2;
			fibNMn1 = fibNMn1 - fibNMn2;
			fibNMn2 = fibN - fibNMn1;
		}
	}
	if (arr[low + fibNMn2] == value) // above loop does not check when fibNMn2 = 0
	{
		return 1;
	}
	return 0;
}

int main1() {
    int first[] = { 1, 3, 5, 7, 9, 25, 30 };
    printf(" Search : %d\n", linearSearchUnsorted(first, 7, 8));
    printf(" Search : %d\n", linearSearchUnsorted(first, 7, 25));


    printf(" Search : %d\n", linearSearchsorted(first, 7, 8));
    printf(" Search : %d\n", linearSearchsorted(first, 7, 25));

    printf(" Search : %d\n", binarySearch(first, 7, 8));
    printf(" Search : %d\n", binarySearch(first, 7, 25));

    printf(" Search : %d\n", binarySearchRecursive(first, 7, 8));
    printf(" Search : %d\n", binarySearchRecursive(first, 7, 25));

    printf(" Search : %d\n", fibonacciSearch(first, 7, 8));
    printf(" Search : %d\n", fibonacciSearch(first, 7, 25));
    return 0;
}

int firstRepeated(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j])
                return arr[i];
        }
    }
    return 0;
}

int firstRepeated2(int arr[], int size) {
    Counter* ctr = createCounter();

    for (int i = 0; i < size; i++) {
        CounterAdd(ctr, arr[i]);
    }
    
    for (int i = 0; i < size; i++) {
        if(GetCount(ctr, arr[i]) > 1)
            return arr[i];
    }
    return 0;
}

int main2() {
    int first[] = { 1, 3, 5, 3, 9, 1, 30  };
    printf("FirstRepeated : %d\n", firstRepeated(first, 7));
    printf("FirstRepeated : %d\n", firstRepeated2(first, 7));
    return 0;
}

/*
FirstRepeated : 1
FirstRepeated : 1
*/

void printRepeating(int arr[], int size) {
    printf("Repeating elements are : ");
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j])
                printf("%d ", arr[i]);
        }
    }
}

void printRepeating2(int arr[], int size) {
    sort(arr, size);
    printf("Repeating elements are : ");

    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1])
            printf("%d ", arr[i]);
    }
}

void printRepeating3(int arr[], int size) {
    Set* hs = createSet();

    printf("Repeating elements are : ");
    for (int i = 0; i < size; i++) {
        if (SetFind(hs, arr[i]))
            printf("%d ", arr[i]);
        else
            SetAdd(hs, arr[i]);
    }
}

void printRepeating4(int arr[], int size, int range) {
    int *count = (int *)malloc(sizeof(int) * range);
    for (int i = 0; i < size; i++) {
        count[i] = 0;
    }
    printf("Repeating elements are : ");
    for (int i = 0; i < size; i++) {
        if (count[arr[i]] == 1)
            printf("%d ", arr[i]);
        else
            count[arr[i]]++;
    }
}

int main3() {
    int first[] = { 1, 3, 5, 3, 9, 1, 30 };
    printRepeating(first, 7);
    printf("\n");
    printRepeating2(first, 7);
    printf("\n");
    printRepeating3(first, 7);
    printf("\n");
    printRepeating4(first, 7, 50);
    return 0;
}

/*
Repeating elements are : 1 3 
Repeating elements are : 1 3 
Repeating elements are : 1 3 
Repeating elements are : 1 3 
*/

int removeDuplicates(int arr[], int size) {
    if (size == 0)
        return 0;

    sort(arr, size);
    int j = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }
    return j + 1;
}

int removeDuplicates2(int arr[], int size) {
    if (size == 0)
        return 0;
    Set* st = createSet();
    int j = 0;
    for (int i = 1; i < size; i++) {
        if (!SetFind(st, arr[i])) {
            arr[j] = arr[i];
            j++;
            SetAdd(st, arr[i]);
        }
    }
    return j;
}

int main4() {
    int arr[] = { 1, 3, 5, 3, 9, 1, 30 };
    int end = removeDuplicates(arr, 7);
    for (int i = 0; i  < end; i++)
        printf("%d ", arr[i]);
	printf("\n");

    int arr2[] = { 1, 3, 5, 3, 9, 1, 30 };
    end = removeDuplicates(arr2, 7);
    for (int i = 0; i < end; i++)
        printf("%d ", arr2[i]);
	printf("\n");
    return 0;
}

int findMissingNumber(int arr[], int size) {
    int found;
    for (int i = 1; i <= size; i++) {
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
    printf("No Number Missing");
    return -9999999;
}

int findMissingNumber2(int arr[], int size) {
    sort(arr, size);
    for (int i = 0; i < size; i++) {
        if (arr[i] != i+1) {
            return i+1;
        }
    }
    printf("No Number Missing");
    return -9999999;
}

int findMissingNumber3(int arr[], int size) {
    Set* st = createSet();
    for (int i = 0; i < size; i++) {
        SetAdd(st, arr[i]);
    }
    for (int i = 0; i < size; i++) {
        if (!SetFind(st,i+1)) {
            return i+1;
        }
    }
    printf("No Number Missing");
    return -9999999;
}

int findMissingNumber4(int arr[], int size) {
    int count[size+1];
    for (int i = 0; i < size; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        count[arr[i]-1] = 1;
    }

    for (int i = 0; i < size; i++) {
        if (count[i] == 0) {
            return i+1;
        }
    }
    printf("No Number Missing");
    return -9999999;
}


int findMissingNumber5(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size+2; i++) {
        sum += i;
    }
    for (int i = 0; i < size; i++) {
        sum -= arr[i];
    }
    return sum;
}

int findMissingNumber6(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		// len(arr)+1 value should be ignored.
		if (arr[i] != size+1 && arr[i] != size * 3 + 1) {
			// 1 should not become (len(arr)+1) so multiplied by 2
			arr[(arr[i] - 1) % size] += size * 2;
		}
	}

	for (int i = 0; i < size; i++) {
		if (arr[i] < (size * 2)) {
			return i + 1;
		}
	}
    printf("No Number Missing");
    return -9999999;
}

int findMissingNumber7(int arr[], int size, int range) {
    int xorSum = 0;
    // get the XOR of all the numbers from 1 to range
    for (int i = 1; i <= range; i++) {
        xorSum ^= i;
    }
    // loop through the array and get the XOR of elements
    for (int i = 0; i < size; i++) {
        xorSum ^= arr[i];
    }
    return xorSum;
}



int main5() {
    int first[]= {1, 5, 4, 3, 2, 7, 8, 9};
    printf("MissingNumber : %d\n", findMissingNumber(first, 8));
	printf("MissingNumber : %d\n", findMissingNumber2(first, 8));
	printf("MissingNumber : %d\n", findMissingNumber3(first, 8));
	printf("MissingNumber : %d\n", findMissingNumber4(first, 8));
	printf("MissingNumber : %d\n", findMissingNumber5(first, 8));
    printf("MissingNumber : %d\n", findMissingNumber7(first, 8, 9));
    printf("MissingNumber : %d\n", findMissingNumber6(first, 8)); // modify array
    return 0;
}

/*
MissingNumber : 6
MissingNumber : 6
MissingNumber : 6
MissingNumber : 6
MissingNumber : 6
MissingNumber : 6
MissingNumber : 6
*/

void missingValues(int arr[], int size) {
    int minVal = 999999;
    int maxVal = -999999;
    for (int i = 0; i < size; i++) {
        if (minVal > arr[i])
            minVal = arr[i];
        if (maxVal < arr[i])
            maxVal = arr[i];
    }

    int found;
    printf("Missing Value is :: ");
    for (int i = minVal; i < maxVal + 1; i++) {
        found = 0;
		for (int j = 0;j < size; j++) {
			if (arr[j] == i) {
				found = 1;
				break;
			}
		}
		if (!found)
            printf("%d ", i);
    }
    printf("\n");
}


void missingValues2(int arr[], int size) {
    sort(arr, size);
    int value = arr[0];
    int i = 0;
    printf("Missing Value is :: ");
    while (i < size) {
        if (value == arr[i]) {
            value += 1;
            i += 1;
        } else {
            printf("%d ", value);
            value += 1;
        }
    }
    printf("\n");
}

void missingValues3(int arr[], int size) {
    Set* ht = createSet();
    int minVal = 999999;
    int maxVal = -999999;

    for (int i = 0; i < size; i++) {
        SetAdd(ht, arr[i]);
        if (minVal > arr[i])
            minVal = arr[i];
        if (maxVal < arr[i])
            maxVal = arr[i];
    }
    printf("Missing Value is :: ");
    for (int i = minVal; i < maxVal + 1; i++) {
        if (SetFind(ht, i) == 0)
            printf("%d ", i);
    }
    printf("\n");
}

int main6() {
    int arr[] = { 1, 9, 2, 8, 3, 7, 4, 6 };
    missingValues(arr, 8);
    missingValues2(arr, 8);
    missingValues3(arr, 8);
    return 0;
}

/*
Missing Value is :: 5 
Missing Value is :: 5 
Missing Value is :: 5 
*/

void oddCount(int arr[], int size) {
    int xorSum = 0;
	for (int i = 0; i < size; i++)
		xorSum ^= arr[i];
	
    printf("Odd value: %d\n", xorSum);
}

void oddCount2(int arr[], int size) {
    Counter* ctr = createCounter();
    int count;

    for (int i = 0; i < size; i++) {
        CounterAdd(ctr, arr[i]);
    }
    printf("Odd value: ");
    for (int i = 0; i < size; i++) {
        count = GetCount(ctr, arr[i]);
        if (count > 0 && (count % 2 == 1)) {
            printf("%d ", arr[i]);
            CounterRemove(ctr, arr[i]);
        }
    }
    printf("\n");
}

void oddCount3(int arr[], int size) {
    int xorSum = 0;
    int first = 0;
    int second = 0;
    int setBit;
    /*
    xor of all elements in arr[]
	even occurrence will cancel each other.
	sum will contain sum of two odd elements.
	*/
    for (int i = 0; i < size; i++)
        xorSum = xorSum ^ arr[i];

    /* Rightmost set bit.*/
    setBit = xorSum & ~(xorSum - 1);

    /*
    Dividing elements in two group: 
	Elements having setBit bit as 1.
	Elements having setBit bit as 0.
	Even elements cancelled themselves if group and we get our numbers.
	*/
    for (int i = 0; i < size; i++) {
        if (arr[i] & setBit)
            first = first ^ arr[i];
        else
            second = second ^ arr[i];
    }
    printf("Odd values: %d & %d\n", first, second);
}

int main7() {
    int arr[] = { 10, 25, 30, 10, 15, 25, 15,};
    oddCount(arr, 7);
    int arr2[] = {10, 25, 30, 10, 15, 25, 15, 40};
    oddCount2(arr2, 8);
    oddCount3(arr2, 8);
    return 0;
}

/*
Odd value: 30
Odd value: 30 40 
Odd values: 30 & 40
*/

void sumDistinct(int arr[], int size) {
    int sum = 0;
    sort(arr, size);
    for (int i = 0; i < (size - 1); i++) {
        if (arr[i] != arr[i + 1])
            sum += arr[i];
    }
    sum += arr[size - 1];
    printf("%d ", sum);
}

int main8() {
    int arr[] = { 1, 2, 3, 1, 1, 4, 5, 6 };
    sumDistinct(arr, 8);
    return 0;
}

//21

void minAbsSumPair(int arr[], int size) {
    if (size < 2) {
        printf("InvalidInput");
    }
    int minFirst = 0;
    int minSecond = 1;
    int minSum = abs(arr[0] + arr[1]);
    for (int l = 0; l < size - 1; l++) {
        for (int r = l + 1; r < size; r++) {
            int sum = abs(arr[l] + arr[r]);
            if (sum < minSum) {
                minSum = sum;
                minFirst = l;
                minSecond = r;
            }
        }
    }
    printf("Elements with minimum sum are : %d, %d \n", arr[minFirst], arr[minSecond]);
}

void minAbsSumPair2(int arr[], int size) {
    // Array should have at least two elements
    if (size < 2) {
        printf("InvalidInput");
    }
    sort(arr, size);
    // Initialization of values
    int minFirst = 0;
    int minSecond = size - 1;
    int minSum = abs(arr[minFirst] + arr[minSecond]);
    for (int l = 0, r = size - 1; l < r;) {
        int sum = (arr[l] + arr[r]);
        if (abs(sum) < minSum) {
            minSum = abs(sum);
            minFirst = l;
            minSecond = r;
        }

        if (sum < 0)
            l++;
        else if (sum > 0)
            r--;
        else
            break;
    }
    printf("Elements with minimum sum are : %d, %d \n", arr[minFirst], arr[minSecond]);
}

int main9() {
    int first[] = { 1, 5, -10, 3, 2, -6, 8, 9, 6 };
    minAbsSumPair(first, 9);
    minAbsSumPair2(first, 9);
    return 0;
}

/*
Elements with minimum sum are : -6, 6 
Elements with minimum sum are : -6, 6 
*/

int findPair(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if ((arr[i] + arr[j]) == value) {
                printf("The pair is : %d, %d \n", arr[i], arr[j]);
                return 1;
            }
        }
    }
    return 0;
}

int findPair2(int arr[], int size, int value) {
    int first = 0, second = size - 1;
    int curr;
    sort(arr, size);
    while (first < second) {
        curr = arr[first] + arr[second];
        if (curr == value) {
            printf("The pair is : %d, %d \n", arr[first], arr[second]);
            return 1;
        } else if (curr < value)
            first++;
        else
            second--;
    }
    return 0;
}

int findPair3(int arr[], int size, int value) {
    Set* hs = createSet();

    for (int i = 0; i < size; i++) {
        if (SetFind(hs, value - arr[i])) {
            printf("The pair is : %d, %d \n", arr[i], (value - arr[i]));
            return 1;
        }
        SetAdd(hs, arr[i]);
    }
    return 0;
}

int findPair4(int arr[], int size, int range, int value) {
    int count[range+1];
    for (int i = 0; i <= range; i++) {
        count[range+1] = 0;
    }

    for (int i = 0; i < size; i++) {
        if (count[value - arr[i]] > 0) {
            printf("The pair is : %d, %d \n", arr[i], (value - arr[i]));
            return 1;
        }
        count[arr[i]] = 1;
    }
    return 0;
}

int main10() {
    int first[] = { 1, 5, 4, 3, 2, 7, 8, 9, 6 };
    findPair(first, 9, 8);
    findPair2(first, 9, 8);
    findPair3(first, 9, 8);
    findPair4(first, 9, 9, 8);
    return 0;
}

/*
The pair is : 1, 7 
The pair is : 1, 7 
The pair is : 5, 3 
The pair is : 1, 7 
*/

int findPairTwoLists(int arr1[], int size1, int arr2[], int size2, int value) {
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if ((arr1[i] + arr2[j]) == value) {
				printf("The pair is : %d, %d\n", arr1[i], arr2[j]);
				return 1;
			}
		}
	}
	return 0;
}

int findPairTwoLists2(int arr1[], int size1, int arr2[], int size2, int value) {
    sort(arr2, size2);
	for (int i = 0; i < size1; i++) {
		if (binarySearch(arr2, size2, value - arr1[i])) {
            printf("The pair is : %d, %d\n", arr1[i], (value - arr1[i]));
		}
		return 1;
	}
	return 0;
}

int findPairTwoLists3(int arr1[], int size1, int arr2[], int size2, int value) {
	int first = 0, second = size2 - 1, curr = 0;
	sort(arr1, size1);
	sort(arr2, size2);
	while (first < size1 && second >= 0) {
		curr = arr1[first] + arr2[second];
		if (curr == value) {
            printf("The pair is : %d, %d\n", arr1[first], arr2[second]);
			return 1;
		} else if (curr < value) {
			first++;
		} else {
			second--;
		}
	}
	return 0;
}

int findPairTwoLists4(int arr1[], int size1, int arr2[], int size2, int value) {
	Set* st = createSet();
	for (int i = 0; i < size2; i++) {
		SetAdd(st, arr2[i]);
	}

	for (int i = 0; i < size1; i++) {
		if (SetFind(st, value - arr1[i])) {
            printf("The pair is : %d, %d\n", arr1[i], (value - arr1[i]));
			return 1;
		}
	}
	return 0;
}

int findPairTwoLists5(int arr1[], int size1, int arr2[], int size2, int range, int value) {
    int count[range+1];
    for (int i = 0; i <= range; i++) {
		count[i] = 0;
	}

	for (int i = 0; i < size2; i++) {
		count[arr2[i]] = 1;
	}

	for (int i = 0; i < size1; i++) {
		if (count[value - arr1[i]] != 0) {
            printf("The pair is : %d, %d\n", arr1[i], (value - arr1[i]));
			return 1;
		}
	}
	return 0;
}

void main11() {
	int first[] = {1, 5, 4, 3, 2, 7, 8, 9, 6};
    int size1 = 9;
	int second[] = {1, 5, 4, 3, 2, 7, 8, 9, 6};
	int size2 = 9;
    findPairTwoLists(first, size1, second, size2, 8);
	findPairTwoLists2(first, size1, second, size2, 8);
	findPairTwoLists3(first, size1, second, size2, 8);
	findPairTwoLists4(first, size1, second, size2, 8);
	findPairTwoLists5(first, size1, second, size2, 9, 8);
}

/*
The pair is : 1, 7
The pair is : 1, 7
The pair is : 1, 7
The pair is : 1, 7
The pair is : 1, 7
*/

int findDifference(int arr[], int size, int value) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (abs(arr[i] - arr[j]) == value) {
                printf("The pair is:: %d & %d.\n", arr[i], arr[j]);
                return 1;
            }
        }
    }
    return 0;
}

int findDifference2(int arr[], int size, int value) {
    int first = 0;
    int second = 0;
    int diff;
    sort(arr, size);
    while (first < size && second < size) {
        diff = abs(arr[first] - arr[second]);
        if (diff == value) {
            printf("The pair is:: %d & %d.", arr[first], arr[second]);
            return 1;
        } else if (diff > value)
            first += 1;
        else
            second += 1;
    }
    return 0;
}

void main12() {
	int second[] = { 1, 5, 4, 3, 2, 7, 8, 9, 6};
	findDifference(second, 9, 6);
	findDifference2(second, 9, 6);
}

/*
The pair is:: 1 & 7.
The pair is:: 1 & 7.
*/

int findMinDiff(int arr[], int size) {
    int diff = 999999;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			int value = abs(arr[i] - arr[j]);
			if (diff > value) {
				diff = value;
			}
		}
	}
	return diff;
}

int findMinDiff2(int arr[], int size) {
    sort(arr, size);
    int diff = 9999999;

    for (int i = 0; i < (size - 1); i++) {
        if ((arr[i + 1] - arr[i]) < diff)
            diff = arr[i + 1] - arr[i];
    }
    return diff;
}

void main13() {
	int second[] = {1, 6, 4, 19, 17, 20};
    int n = 6;
	printf("findMinDiff : %d\n", findMinDiff(second, n));
	printf("findMinDiff : %d\n", findMinDiff2(second, n));
}

int minDiffPair(int arr1[], int size1, int arr2[], int size2) {
	int diff = 999999;
	int first = 0;
	int second = 0;
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			int value = abs(arr1[i] - arr2[j]);
			if (diff > value) {
				diff = value;
				first = arr1[i];
				second = arr2[j];
			}
		}
	}
	printf("The pair is :: %d & %d \n", first, second);
	printf("Minimum difference is :: %d \n", diff);
	return diff;
}

int minDiffPair2(int arr1[], int size1, int arr2[], int size2) {
    int minDiff = 9999999;
    int first = 0;
    int second = 0;
    int out1, out2, diff;
    sort(arr1, size1);
    sort(arr2, size2);
    while (first < size1 && second < size2) {
        diff = abs(arr1[first] - arr2[second]);
        if (minDiff > diff) {
            minDiff = diff;
            out1 = arr1[first];
            out2 = arr2[second];
        }
        if (arr1[first] < arr2[second])
            first += 1;
        else
            second += 1;
    }
    printf("The pair is :: %d, %d \n", out1, out2);
    printf("Minimum difference is :: %d \n", minDiff);
    return minDiff;
}

int main14() {
    int second[] =  {1, 5, 4, 3, 2, 7, 8, 9, 6};
    int third[] = {6, 4, 19, 17, 20};
    minDiffPair(second, 9, third, 5);
    minDiffPair2(second, 9, third, 5);
    return 0;
}

void closestPair(int arr[], int size, int value) {
    int diff = 999999;
    int first = -1;
    int second = -1;
    int curr;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            curr = abs(value - (arr[i] + arr[j]));
            if (curr < diff) {
                diff = curr;
                first = arr[i];
                second = arr[j];
            }
        }
    }
    printf("closest pair is :: %d, %d ", first, second);
}

void closestPair2(int arr[], int size, int value) {
    int first = 0, second = 0;
    int start = 0;
    int stop = size - 1;
    int diff, curr;
    sort(arr, size);
    diff = 9999999;
    
    while (start < stop) {
        curr = (value - (arr[start] + arr[stop]));
        if (abs(curr) < diff) {
            diff = abs(curr);
            first = arr[start];
            second = arr[stop];
        }
        if (curr == 0) {
            break;
        } else if (curr > 0) {
            start += 1;
        } else {
            stop -= 1;
        }
    }
    
    printf("closest pair is :: %d, %d \n", first, second);
}

int main15() {
    int first[] = { 10, 20, 3, 4, 50, 80  };
    int n = 6;
    closestPair(first, n, 47);
    closestPair2(first, n, 47);
    return 0;
}


int sumPairRestArray(int arr[], int size) {
    int total, start, end, curr, value;
    sort(arr, size);
    total = 0;
    for (int i = 0; i < size; i++)
        total += arr[i];
    value = total / 2;
    start = 0;
    end = size - 1;
    while (start < end) {
        curr = arr[start] + arr[end];
        if (curr == value) {
            printf("Pair is :: %d, %d", arr[start], arr[end]);
            return 1;
        } else if (curr < value)
            start += 1;
        else
            end -= 1;
    }
    return 0;
}

int main16() {
    int first[] = { 1, 2, 4, 3, 7, 3 };
    int n = 6;
    sumPairRestArray(first, n);
    return 0;
}



void zeroSumTriplets(int arr[], int size) {
    for (int i = 0; i < (size - 2); i++) {
        for (int j = i + 1; j < (size - 1); j++) {
            for (int k = j + 1; k < size; k++) {
                if (arr[i] + arr[j] + arr[k] == 0)
                    printf("Triplet :: %d, %d, %d \n", arr[i], arr[j], arr[k]);
            }
        }
    }
}

void zeroSumTriplets2(int arr[], int size) {
    int start, stop, i;
    sort(arr, size);
    for (i = 0; i < (size - 2); i++) {
        start = i + 1;
        stop = size - 1;

        while (start < stop) {
            if (arr[i] + arr[start] + arr[stop] == 0) {
                printf("Triplet :: %d %d %d", arr[i], arr[start], arr[stop]);
                start += 1;
                stop -= 1;
            }
            else if (arr[i] + arr[start] + arr[stop] > 0)
                stop -= 1;
            else
                start += 1;
        }
    }
}

int main17() {
    int first[] = { 1, 2, -4, 3, 7, -3 };
    int n = 6;
    zeroSumTriplets(first, n);
    zeroSumTriplets2(first, n);
    return 0;
}


void findTriplet(int arr[], int size, int value) {
    for (int i = 0; i < (size - 2); i++)
        for (int j = i + 1; j < (size - 1); j++)
            for (int k = j + 1; k < size; k++) {
                if ((arr[i] + arr[j] + arr[k]) == value)
                    printf("Triplet :: %d, %d, %d", arr[i], arr[j], arr[k]);
            }
}

void findTriplet2(int arr[], int size, int value) {
    int start, stop;
    sort(arr, size);
    for (int i = 0; i < size - 2; i++) {
        start = i + 1;
        stop = size - 1;
        while (start < stop) {
            if (arr[i] + arr[start] + arr[stop] == value) {
                printf("Triplet ::%d, %d, %d", arr[i], arr[start], arr[stop]);
                start += 1;
                stop -= 1;
            }
            else if (arr[i] + arr[start] + arr[stop] > value)
                stop -= 1;
            else
                start += 1;
        }
    }
}

int main18() {
    int first[] = { 1, 2, -4, 3, 7, -3 };
    int n = 6;
    findTriplet(first, n, 6);
    findTriplet2(first, n, 6);
    return 0;
}

void ABCTriplet(int arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = i + 1; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (k != i && k != j && arr[i] + arr[j] == arr[k]) {
                    printf("ABCTriplet:: %d, %d, %d\n", arr[i], arr[j], arr[k]);
                }
            }
        }
	}
}

void ABCTriplet2(int arr[], int size) {
    int start, stop;
    sort(arr, size);
    for (int i = 0; i < (size - 2); i++) {
        start = i + 1;
        stop = size - 1;
        while (start < stop) {
            if (arr[i] == arr[start] + arr[stop]) {
                printf("Triplet ::%d, %d, %d", arr[i], arr[start], arr[stop]);
                start += 1;
                stop -= 1;
            }
            else if (arr[i] > arr[start] + arr[stop])
                stop -= 1;
            else
                start += 1;
        }
    }
}

int main19() {
    int first[] = { 1, 2, -4, 3, 7, -3 };
    ABCTriplet(first, 6);
    ABCTriplet2(first, 6);
    return 0;
}

void smallerThenTripletCount(int arr[], int size, int value) {
	int count = 0;
	for (int i = 0; i < size-1; i++) {
        for (int j = i + 1; j < size; j++) {
            for (int k = j + 1; k < size; k++) {
                if (arr[i] + arr[j] + arr[k] < value) {
                    count += 1;
                }
            }
        }
	}
	printf("smallerThenTripletCount:: %d\n", count);
}

void smallerThenTripletCount2(int arr[], int size, int value) {
    int start, stop;
    int count = 0;
    sort(arr, size);
    for (int i = 0; i < (size - 2); i++) {
        start = i + 1;
        stop = size - 1;
        while (start < stop) {
            if (arr[i] + arr[start] + arr[stop] >= value)
                stop -= 1;
            else
            {
                count += stop - start;
                start += 1;
            }
        }
    }
    printf("%d", count);
}

void main20() {
    int first[] = { -2, -1,  0, 1 };
    int n = 4;
    smallerThenTripletCount(first, n, 2);
    smallerThenTripletCount2(first, n, 2);
}

void APTriplets(int arr[], int size) {
    int i, j, k;
    for (i = 1; i < size - 1; i++) {
        j = i - 1;
        k = i + 1;
        while (j >= 0 && k < size) {
            if (arr[j] + arr[k] == 2 * arr[i]) {
                printf("Triplet ::%d, %d, %d", arr[j], arr[i], arr[k]);
                k += 1;
                j -= 1;
            }
            else if (arr[j] + arr[k] < 2 * arr[i])
                k += 1;
            else
                j -= 1;
        }
    }
}

int main21() {
    int first[] = { 1, 2, 3, 4, 9, 17, 23 };
    int n = 7;
    APTriplets(first, n);
    return 0;
}

void GPTriplets(int arr[], int size) {
    int i, j, k;
    for (i = 1; i < size - 1; i++) {
        j = i - 1;
        k = i + 1;
        while (j >= 0 && k < size) {
            if (arr[j] * arr[k] == arr[i] * arr[i]) {
                printf("Triplet is :: %d,%d,%d", arr[j], arr[i], arr[k]);
                k += 1;
                j -= 1;
            }
            else if (arr[j] + arr[k] < 2 * arr[i])
                k += 1;
            else
                j -= 1;
        }
    }
}

int main22() {
    int first[] = { 1, 2, 3, 4, 9, 17, 23 };
    int n = 7;
    GPTriplets(first, n);
    return 0;
}

int numberOfTriangles(int arr[], int size) {
    int i, j, k, count = 0;
    for (i = 0; i < (size - 2); i++) {
        for (j = i + 1; j < (size - 1); j++) {
            for (k = j + 1; k < size; k++) {
                if (arr[i] + arr[j] > arr[k])
                    count += 1;
            }
        }
    }
    return count;
}
int numberOfTriangles2(int arr[], int size) {
    int k, count = 0;
    sort(arr, size);
    for (int i = 0; i < (size - 2); i++) {
        k = i + 2;
        for (int j = i + 1; j < (size - 1); j++) {
            /*
            if sum of arr[i] & arr[j] is greater arr[k]
            then sum of arr[i] & arr[j + 1] is also greater than arr[k]
            this improvement make algo O(n2)
            */
            while (k < size && arr[i] + arr[j] > arr[k])
                k += 1;

            count += k - j - 1;
        }
    }
    return count;
}

int main23() {
    int first[] = { 1, 2, 3, 4, 5 };
    int n = 5;
    printf("numberOfTriangles : %d\n", numberOfTriangles(first, n));
    printf("numberOfTriangles : %d\n", numberOfTriangles2(first, n));
    return 0;
}

int getMax(int arr[], int size) {
    int max = arr[0], count = 1, maxCount = 1;
    for (int i = 0; i < size; i++) {
        count = 1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j])
                count++;
        }
        if (count > maxCount) {
            max = arr[i];
            maxCount = count;
        }
    }
    return max;
}

int getMax2(int arr[], int size) {
    int max = arr[0], maxCount = 1;
    int curr = arr[0], currCount = 1;
    sort(arr, size);
    for (int i = 1; i < size; i++) {
        if (arr[i] == arr[i - 1]) {
            currCount++;
        } else {
            currCount = 1;
            curr = arr[i];
        }
        if (currCount > maxCount) {
            maxCount = currCount;
            max = curr;
        }
    }
    return max;
}

int getMax3(int arr[], int size, int range) {
    int max = arr[0], maxCount = 1;

    int *count = (int *)malloc(sizeof(int) * range);
    for (int i = 0; i < size; i++) {
        count[arr[i]]++;
        if (count[arr[i]] > maxCount) {
            maxCount = count[arr[i]];
            max = arr[i];
        }
    }
    return max;
}

int main24() {
    int first[] = { 1, 30, 5, 13, 9, 31, 5 };
    int n = 7;
    printf("%d\n", getMax(first, n));
    printf("%d\n", getMax2(first, n));
    printf("%d\n", getMax3(first, n, 50));
    return 0;
}

int getMajority(int arr[], int size) {
    int max = 0, count = 0, maxCount = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
        if (count > maxCount) {
            max = arr[i];
            maxCount = count;
        }
    }
    if (maxCount > size / 2)
        return max;
    else
    {
        printf("MajorityDoesNotExist");
        return 0;
    }
}

int getMajority2(int arr[], int size) {
    int majIndex = size / 2, count = 1;
    int candidate;
    sort(arr, size);
    candidate = arr[majIndex];
    count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == candidate)
            count++;
    }

    if (count > size / 2)
        return arr[majIndex];
    else
    {
        printf("MajorityDoesNotExist");
        return 0;
    }
}

int getMajority3(int arr[], int size) {
    int majIndex = 0, count = 1;
    int candidate;

    for (int i = 1; i < size; i++) {
        if (arr[majIndex] == arr[i])
            count++;
        else
            count--;

        if (count == 0) {
            majIndex = i;
            count = 1;
        }
    }
    candidate = arr[majIndex];
    count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == candidate) {
            count++;
        }
    }
    if (count > size / 2)
        return arr[majIndex];
    else
    {
        printf("MajorityDoesNotExist");
        return 0;
    }
}

int main25() {
    int first[] = { 1, 5, 5, 13, 5, 31, 5 };
    int n = 7;
    printf("%d\n", getMajority(first, n));
    printf("%d\n", getMajority2(first, n));
    printf("%d\n", getMajority3(first, n));
    return 0;
}

int getMedian(int arr[], int size) {
    sort(arr, size);
    return arr[size / 2];
}

void quickSelectUtil(int arr[], int lower, int upper, int k) {
    if (upper <= lower)
        return;

    int pivot = arr[lower];
    int start = lower;
    int stop = upper;


    while (start < stop) {
        while (arr[start] <= pivot) {
            start++;
        }
        while (arr[stop] > pivot) {
            stop--;
        }
        if (start < stop) {
            swap(arr, start, stop);
        }
    }
    swap(arr, lower, stop); //stop is at the pivot position

    if (k < stop)
        quickSelectUtil(arr, lower, stop - 1, k); //pivot -1 is the end for left sub array.
    if (k > stop)
        quickSelectUtil(arr, stop + 1, upper, k); // pivot + 1 is the start for right sub array.
}

int getMedian2(int arr[], int size) {
	quickSelectUtil(arr, 0, size - 1, size / 2);
	return arr[size / 2];
}

void main26() {
	int first[] = {1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30};
	int size = sizeof(first)/sizeof(int);
    printf("%d\n", getMedian(first, size));
	printf("%d\n", getMedian2(first, size));
}

int searchBitonicArrayMax(int arr[], int size) {
	for (int i = 0; i < size-2; i++) {
		if (arr[i] > arr[i + 1]) {
			return arr[i];
		}
	}
	printf("error not a bitonic array \n");
	return 0;
}

int searchBitonicArrayMax2(int arr[], int size) {
    int start = 0, end = size - 1;
    int mid = (start + end) / 2;
    int maximaFound = 0;
    if (size < 3) {
        printf("error");
        return 0;
    }
    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) // maxima
        {
            maximaFound = 1;
            break;
        } else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) // increasing
        {
            start = mid + 1;
        } else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) // decreasing
        {
            end = mid - 1;
        } else {
            break;
        }
    }
    if (maximaFound == 0) {
        printf("error");
        return 0;
    }
    return arr[mid];
}

int findBitonicArrayMax(int arr[], int size) {
    int start = 0, end = size - 1, mid;
    if (size < 3) {
        printf("error");
        return -1;
    }
    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) // maxima
            return mid;
        else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1])  // increasing
            start = mid + 1;
        else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1])  // increasing
            end = mid - 1;
        else
            break;
    }
    printf("error");
    return -1;
}

int binarySearch2(int arr[], int start, int end, int key, int isInc) {
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == arr[mid])
        return mid;

    if (isInc != 0 && key < arr[mid] || isInc == 0 && key > arr[mid])
        return binarySearch2(arr, start, mid - 1, key, isInc);
    else
        return binarySearch2(arr, mid + 1, end, key, isInc);
}


int FindMaxBitonicArray(int arr[], int size) {
    int start = 0, end = size - 1, mid;
    if (size < 3) {
        printf("InvalidInput");
    }
    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) // maxima
            return mid;
        else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) // increasing
            start = mid + 1;
        else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) // decreasing
            end = mid - 1;
        else
            break;
    }
    printf("Maxima not found");
    return -1;
}


int searchBitonicArray(int arr[], int size, int key) {
    int max = FindMaxBitonicArray(arr, size);
    int k = binarySearch2(arr, 0, max, key, 1);
    if (k != -1)
        return k;
    else
        return binarySearch2(arr, max + 1, size - 1, key, 0);
}

void main27() {
	int first[] = {1, 5, 10, 13, 20, 30, 8, 7, 6};
    int size = sizeof(first)/sizeof(int);
	printf("%d\n", searchBitonicArrayMax(first, size));
	printf("%d\n", searchBitonicArrayMax2(first, size));
	printf("%d\n", searchBitonicArray(first, size, 7));
    printf("%d\n", first[findBitonicArrayMax(first, size)]);
}


int findKeyCount(int arr[], int size, int key) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] == key)
            count++;
    }
    return count;
}

int findFirstIndex(int arr[], int size, int start, int end, int key) {
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == arr[mid] && (mid == start || arr[mid - 1] != key))
        return mid;

    if (key <= arr[mid]) // <= is us the number.t in sorted array.
        return findFirstIndex(arr, size, start, mid - 1, key);
    else
        return findFirstIndex(arr, size, mid + 1, end, key);
}

int findLastIndex(int arr[], int size, int start, int end, int key) {
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == arr[mid] && (mid == end || arr[mid + 1] != key))
        return mid;

    if (key < arr[mid])
        return findLastIndex(arr, size, start, mid - 1, key);
    else
        return findLastIndex(arr, size, mid + 1, end, key);
}

int findKeyCount2(int arr[], int size, int key) {
    int firstIndex, lastIndex;
    firstIndex = findFirstIndex(arr, size, 0, size - 1, key);
    lastIndex = findLastIndex(arr, size, 0, size - 1, key);
    return (lastIndex - firstIndex + 1);
}

int main28() {
    int first[] = {1, 5, 10, 13, 20, 30, 8, 7, 6  };
    int n = 9;
    printf("%d\n", findKeyCount(first, n, 6));
    printf("%d\n", findKeyCount2(first, n, 6));
    return 0;
}

int isMajority(int arr[], int size) {
	int count = 0;
	int mid = arr[size / 2];
	for (int i = 0;i < size;i++) {
		if (arr[i] == mid) {
			count += 1;
		}
	}

	if (count > size / 2) {
		return 1;
	}
	return 0;
}

/* Using binary search method.*/
int FirstIndex(int arr[], int size, int start, int end, int value) {
    int mid;
    if (end >= start)
        mid = (start + end) / 2;

    /*
		Find first occurrence of value, either it should be the first 
		element of the array or the value before it is smaller than it.
		*/
    if ((mid == 0 || arr[mid - 1] < value) && (arr[mid] == value))
        return mid;
    else if (arr[mid] < value)
        return FirstIndex(arr, size, mid + 1, end, value);
    else
        return FirstIndex(arr, size, start, mid - 1, value);
    return -1;
}

int isMajority2(int arr[], int size) {
    int i;
    int majority = arr[size / 2];
    i = FirstIndex(arr, size, 0, size - 1, majority);
    /*
    we are using majority element form array so 
	 we will get some valid index always.
    */
    if (((i + size / 2) <= (size - 1)) && arr[i + size / 2] == majority)
        return 1;
    else
        return 0;
}

int main29() {
    int first[] = {3, 3, 3, 3, 4, 5, 10};
    int n = 7;
    printf("%d\n", isMajority(first, n));
    printf("%d\n", isMajority2(first, n));
    return 0;
}

int maxProfit(int stocks[], int size) {
	int maxProfit = 0;
	int buy = 0, sell = 0;

	for (int i = 0;i < size-1;i++) {
		for (int j = i + 1;j < size ;j++) {
			if (maxProfit < stocks[j] - stocks[i]) {
				maxProfit = stocks[j] - stocks[i];
				buy = i;
				sell = j;
			}
		}
	}
	printf("Purchase day is %d at price %d\n", buy, stocks[buy]);
	printf("Sell day is %d at price %d\n", sell, stocks[sell]);
	printf("Profit is %d\n", maxProfit);
    return maxProfit;
}

void maxProfit2(int stocks[], int size) {
    int buy = 0, sell = 0;
    int curMin = 0;
    int currProfit = 0;
    int maxProfit = 0;

    for (int i = 0; i < size; i++) {
        if (stocks[i] < stocks[curMin])
            curMin = i;

        currProfit = stocks[i] - stocks[curMin];
        if (currProfit > maxProfit) {
            buy = curMin;
            sell = i;
            maxProfit = currProfit;
        }
    }
    printf("Purchase day is:: %d at price:: %d \n", buy, stocks[buy]);
    printf("Sell day is:: %d at price:: %d \n", sell, stocks[sell]);
}

int main30() {
    int first[] = { 10, 150, 6, 67, 61, 16, 86, 6, 67, 78, 150, 3, 28, 143 };
    int n = sizeof(first)/sizeof(int);
    maxProfit(first, n);
    maxProfit2(first, n);
    return 0;
}

int findMedian(int dataFirst[], int sizeFirst, int dataSecond[], int sizeSecond) {
    int medianIndex = ((sizeFirst + sizeSecond) + (sizeFirst + sizeSecond) % 2) / 2; // cealing function.
    int i = 0, j = 0;
    int count = 0;
    while (count < medianIndex - 1) {
        if (i < sizeFirst - 1 && dataFirst[i] < dataSecond[j]) {
            i++;
        } else {
            j++;
        }
        count++;
    }
    if (dataFirst[i] < dataSecond[j]) {
        return dataFirst[i];
    } else {
        return dataSecond[j];
    }
}

int main31() {
    int first[] = { 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 };
    int size1 = sizeof(first)/sizeof(int);
    int second[] = { 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 };
    int size2 = sizeof(second)/sizeof(int);
    printf("%d\n", findMedian(first, size1, second, size2));
    return 0;
}

int search01(int arr[], int size) {
	for (int i = 0;i < size;i++) {
		if (arr[i] == 1) {
			return i;
		}
	}
	return -1;
}

int binarySearch01Util(int arr[], int start, int end) {
    int mid;
    if (end < start) {
        return -1;
    }
    mid = (start + end) / 2;
    if (1 == arr[mid] && 0 == arr[mid - 1]) {
        return mid;
    }
    if (0 == arr[mid]) {
        return binarySearch01Util(arr, mid + 1, end);
    } else {
        return binarySearch01Util(arr, start, mid - 1);
    }
}

int binarySearch01(int arr[], int size) {
    if (size == 1 && arr[0] == 1) {
        return 0;
    }
    return binarySearch01Util(arr, 0, size - 1);
}

int main32() {
    int first[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1 };
    int size = sizeof(first)/sizeof(int);
	printf("%d\n", search01(first, size));
    printf("%d\n", binarySearch01(first, size));
    return 0;
}

int rotationMax(int arr[], int size) {
	for (int i = 0;i < size-1;i++) {
		if (arr[i] > arr[i + 1]) {
			return arr[i];
		}
	}
	return -1;
}

int rotationMaxUtil(int arr[], int start, int end) {
    int mid;
    if (end <= start) {
        return arr[start];
    }
    mid = (start + end) / 2;
    if (arr[mid] > arr[mid + 1])
        return arr[mid];

    if (arr[start] <= arr[mid]) /* increasing part.*/
        return rotationMaxUtil(arr, mid + 1, end);
    else
        return rotationMaxUtil(arr, start, mid - 1);
}

int rotationMax2(int arr[], int size) {
    return rotationMaxUtil(arr, 0, size - 1);
}

int main33() {
    int first[] = {8, 9, 10, 11, 3, 5, 7 };
    int size = sizeof(first)/sizeof(int);
    printf("RotationMax is :: %d\n", rotationMax(first, size));
    printf("RotationMax is :: %d\n", rotationMax2(first, size));
    return 0;
}

int findRotationMax(int arr[], int size) {
	for (int i = 0;i < size-1;i++) {
		if (arr[i] > arr[i + 1]) {
			return i;
		}
	}
	return -1;
}

int findRotationMaxUtil(int arr[], int start, int end) {
    /* single element case.*/
    int mid;
    if (end <= start)
        return start;

    mid = (start + end) / 2;
    if (arr[mid] > arr[mid + 1])
        return mid;

    if (arr[start] <= arr[mid]) /* increasing part.*/
        return findRotationMaxUtil(arr, mid + 1, end);
    else
        return findRotationMaxUtil(arr, start, mid - 1);
}

int findRotationMax2(int arr[], int size) {
    return findRotationMaxUtil(arr, 0, size - 1);
}

int main34() {
    int first[] =  { 34, 56, 77, 1, 5, 6, 6, 8, 10, 20, 30, 34 };
    int size = sizeof(first)/sizeof(int);
    printf("findRotationMax is :: %d\n", findRotationMax(first, size));
    printf("findRotationMax is :: %d\n", findRotationMax2(first, size));
    return 0;
}

int countRotation(int arr[], int size) {
    int maxIndex = findRotationMaxUtil(arr, 0, size - 1);
    return (maxIndex + 1) % size;
}

int main35() {
    int first[] = { 34, 56, 77, 1, 5, 6, 6, 8, 10, 20, 30, 34 };
    int size = sizeof(first)/sizeof(int);
    printf("%d\n", countRotation(first, size));
    return 0;
}

int searchRotateArray(int arr[], int size, int key) {
	for (int i = 0;i < size-1;i++) {
		if (arr[i] == key) {
			return i;
		}
	}
	return -1;
}

int binarySearchRotateArrayUtil(int arr[], int start, int end, int key) {
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == arr[mid])
        return mid;

    if (arr[mid] > arr[start]) {
        if (arr[start] <= key && key < arr[mid]) {
            return binarySearchRotateArrayUtil(arr, start, mid - 1, key);
        } else {
            return binarySearchRotateArrayUtil(arr, mid + 1, end, key);
        }
    } else {
        if (arr[mid] < key && key <= arr[end]) {
            return binarySearchRotateArrayUtil(arr, mid + 1, end, key);
        } else {
            return binarySearchRotateArrayUtil(arr, start, mid - 1, key);
        }
    }
}

int binarySearchRotateArray(int arr[], int size, int key) {
    return binarySearchRotateArrayUtil(arr, 0, size - 1, key);
}

int main36() {
    int first[] = { 34, 56, 77, 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 };
    int size = sizeof(first)/sizeof(int);
	printf("%d\n", searchRotateArray(first, size, 20));
    printf("%d\n", binarySearchRotateArray(first, size, 20));
    return 0;
}

int minAbsDiffAdjCircular(int arr[], int size) {
    int diff = 9999999;
    if (size < 2)
        return -1;

    for (int i = 0; i < size; i++)
        diff = min(diff, abs(arr[i] - arr[(i + 1) % size]));

    return diff;
}

int main37() {
    int arr[] = { 5, 29, 18, 51, 11 };
    int size = sizeof(arr)/sizeof(int);
    printf("%d\n", minAbsDiffAdjCircular(arr, size));
    return 0;
}

void swapch(char arr[], int first, int second) {
    char temp = arr[first];
    arr[first] = arr[second];
    arr[second] = temp;
}

void transformArrayAB1(char arr[], int size) {
    int N = size / 2;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++)
            swapch(arr, N - i + 2 * j, N - i + 2 * j + 1);
    }
}

int main38() {
    char str[] = "aaaabbbb";
    transformArrayAB1(str, 8);
    printf("%s\n", str);
    return 0;
}

void sortChar(char arr[], int size) {
    int i, j, temp;
    for (i = 0; i < (size - 1); i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int checkPermutation(char arr1[], int size1, char arr2[], int size2) {
    if (size1 != size2)
        return 0;

    sortChar(arr1, size1);
    sortChar(arr2, size2);

    for (int i = 0; i < size1; i++) {
        if (arr1[i] != arr2[i])
            return 0;
    }
    return 1;
}

int checkPermutation2(char array1[], int size1, char array2[], int size2) {
    if (size1 != size2)
        return 0;

    Set* hs = createSet();

    for (int i = 0; i < size1; i++)
        SetAdd(hs, array1[i]);

    for (int i = 0; i < size2; i++) {
        if (!SetFind(hs, array2[i]))
            return 0;
    }
    return 1;
}

int checkPermutation3(char array1[], int size1,  char array2[], int size2) {
	if (size1 != size2) {
		return 0;
	}
	int count[256];
    for (int i =0;i<256;i++)
        count[i] = 0;

	for (int i = 0; i < size1; i++) {
		count[array1[i]]++;
		count[array2[i]]--;
	}

	for (int i = 0; i < size1; i++) {
		if (count[i] != 0) {
			return 0;
		}
	}
	return 1;
}

int main39() {
    char str1[] = "aaaabbbb";
    int n1 = strlen(str1);
    char str2[] = "bbaaaabb";
    int n2 = strlen(str2);
    printf("%d\n", checkPermutation(str1, n1, str2, n2));
    printf("%d\n", checkPermutation2(str1, n1, str2, n2));
    printf("%d\n", checkPermutation3(str1, n1, str2, n2));
    return 0;
}

int FindElementIn2DArray(int **arr, int r, int c, int value) {
    int row = 0;
    int column = c - 1;
    while (row < r && column >= 0)
        if (arr[row][column] == value)
            return 1;
        else if (arr[row][column] > value)
            column -= 1;
        else
            row += 1;
    return 0;
}

int isAP(int arr[], int size) {
    int diff;
    if (size <= 1)
        return 1;

    sort(arr, size);
    diff = arr[1] - arr[0];
    for (int i = 2; i < size; i++) {
        if (arr[i] - arr[i - 1] != diff)
            return 0;
    }
    return 1;
}

int isAP2(int arr[], int size) {
    int first = 9999999;
    int second = 9999999;
    int diff, value;
    Set* hs = createSet();
    for (int i = 0; i < size; i++) {
        if (arr[i] < first) {
            second = first;
            first = arr[i];
        } else if (arr[i] < second)
            second = arr[i];
    }
    diff = second - first;

    for (int i = 0; i < size; i++) {
        if (SetFind(hs, arr[i]))
            return 0;
        SetAdd(hs, arr[i]);
    }
    for (int i = 0; i < size; i++) {
        value = first + i * diff;
        if (SetFind(hs, value) == 0)
            return 0;
    }
    return 1;
}

int isAP3(int arr[], int size) {
    int first = 9999999;
    int second = 9999999;
    int *count = (int *)calloc(0, size);
    int diff, index;
    for (int i = 0; i < size; i++) {
        if (arr[i] < first) {
            second = first;
            first = arr[i];
        } else if (arr[i] < second)
            second = arr[i];
    }
    diff = second - first;

    for (int i = 0; i < size; i++)
        index = (arr[i] - first) / diff;
    if (index > size - 1 || count[index] != 0)
        return 0;
    count[index] = 1;

    for (int i = 0; i < size; i++)
        if (count[i] != 1)
            return 0;
    return 1;
}

int main40() {
    int arr[] = { 3, 6, 9, 12, 15 };
    int n = 5;
    printf("%d\n", isAP(arr, n));
    printf("%d\n", isAP2(arr, n));
    printf("%d\n", isAP3(arr, n));
    return 0;
}

int findBalancedPoint(int arr[], int size) {
    int first = 0;
    int second = 0;
    for (int i = 1; i < size; i++)
        second += arr[i];

    for (int i = 0; i < size; i++) {
        if (first == second)
            printf("%d", i);
        if (i < size - 1)
            first += arr[i];
        second -= arr[i + 1];
    }
}

int main41() {
    int arr[] = { -7, 1, 5, 2, -4, 3, 0 };
    int n = 7;
    printf("%d\n", findBalancedPoint(arr, n));
    return 0;
}

int findFloor(int arr[], int size, int value) {
    int start = 0;
    int stop = size - 1;
    int mid;
    while (start <= stop) {
        mid = (start + stop) / 2;
        /* search value is equal to arr[mid] value..
		 search value is greater than mid index value and less than mid+1 index value.
		 value is greater than arr[size-1] then floor is arr[size-1]
		*/
        if (arr[mid] == value || (arr[mid] < value && (mid == size - 1 || arr[mid + 1] > value)))
            return mid;
        else if (arr[mid] < value)
            start = mid + 1;
        else
            stop = mid - 1;
    }
    return -1;
}

int findCeil(int arr[], int size, int value) {
    int start = 0;
    int stop = size - 1;
    int mid;

    while (start <= stop) {
        mid = (start + stop) / 2;
        /* search value is equal to arr[mid] value..
		 search value is less than mid index value and greater than mid-1 index value.
		 value is less than arr[0] then ceil is arr[0]
		*/
        if (arr[mid] == value || (arr[mid] > value && (mid == 0 || arr[mid - 1] < value)))
            return mid;
        else if (arr[mid] < value)
            start = mid + 1;
        else
            stop = mid - 1;
    }
    return -1;
}

int main42() {
    int arr[] = { -7, 1, 2, 3, 6, 8, 10 };
    int n = 7;
    printf("%d\n", findFloor(arr, n, 4));
    printf("%d\n", findCeil(arr, n, 4));
    return 0;
}

int closestNumber(int arr[], int size, int num) {
    int start = 0;
    int stop = size - 1;
    int output = -1;
    int minDist = 9999;
    int mid;

    while (start <= stop) {
        mid = (start + stop) / 2;
        if (minDist > abs(arr[mid] - num)) {
            minDist = abs(arr[mid] - num);
            output = arr[mid];
        }
        if (arr[mid] == num)
            break;
        else if (arr[mid] > num)
            stop = mid - 1;
        else
            start = mid + 1;
    }
    return output;
}

int main43() {
    int arr[] = {2, 4, 8, 16};
    int n = 4;
    printf("closestNumber : %d\n", closestNumber(arr, n, 7));
    return 0;
}

/*
int DuplicateKDistance(int arr[], int size, int k) {
    Set* hs = createSet(); 
    for (int i = 0; i < size; i++) {
        if (SetFind(hs, arr[i]) && i - arr[i] <= k) {
            printf("%d, %d, %d", arr[i], GetCount(hs, arr[i]), i);
            return 1;
        } else
            SetAdd2(hs, arr[i], i);
    }
    return 0;
}

int main44() {
    int arr[] = { 1, 2, 3, 1, 4, 5 };
    duplicateKDistance(arr, 3);
    return 0;
}
*/
void frequencyCounts(int arr[], int size) {
	Counter *ct = createCounter();
	for (int i = 0; i < size; i++) {
		CounterAdd(ct, arr[i]);
	}
	CounterPrint(ct);
	printf("\n");
}

void frequencyCounts2(int arr[], int size) {
	sort(arr, size);
	int count = 1;
	for (int i = 1; i < size; i++) {
		if (arr[i] == arr[i - 1]) {
			count++;
		} else {
		    printf("(%d : %d) ", arr[i - 1], count);
			count = 1;
		}
	}
	printf("(%d : %d) \n", arr[size-1], count);
}

void frequencyCounts3(int arr[], int size) {
	int aux[size+1];
	for (int i = 0; i < size; i++) {
		aux[arr[i]] += 1;
	}
	for (int i = 0; i < size+1; i++) {
		if (aux[i] > 0) {
			printf("(%d : %d) ", i, aux[i]);
		}
	}
	printf("\n");
}

int frequencyCounts4(int arr[], int size) {
    int index;
    for (int i = 0; i < size; i++) {
        while (arr[i] > 0) {
            index = arr[i] - 1;
            if (arr[index] > 0) {
                arr[i] = arr[index];
                arr[index] = -1;
            } else {
                arr[index] -= 1;
                arr[i] = 0;
            }
        }
    }
    for (int i = 0; i < size; i++)
        printf("(%d : %d) ", i + 1, abs(arr[i]));
    printf("\n");
}

int main45() {
    int arr[] = {1, 2, 2, 2, 1};
    int n = 5;
    frequencyCounts(arr, n);
	frequencyCounts2(arr, n);
	frequencyCounts3(arr, n);
    frequencyCounts4(arr, n);
    return 0;
}

int kLargestElements(int arrIn[], int size, int k) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = arrIn[i];

    sort(arr, size);
    for (int i = 0; i < size; i++) {
        if (arrIn[i] >= arr[size - k])
            printf(" %d ", arrIn[i]);
    }
}

int kLargestElements2(int arrIn[], int size, int k) {
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = arrIn[i];

    quickSelectUtil(arr, 0, size - 1, size - k);
    for (int i = 0; i < size; i++) {
        if (arrIn[i] >= arr[size - k])
            printf("%d", arrIn[i]);
    }
}

int main46() {
    int arr[] = {10, 50, 30, 60, 15};
    int n = 5;
    kLargestElements(arr, 5, 2);
    kLargestElements2(arr, 5, 2);
    return 0;
}

/* linear search method */
int fixPoint(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == i)
            return i;
    } /* fix point not found so return invalid index */
    return -1;
}

/* Binary search method */
int fixPoint2(int arr[], int size) {
    int start = 0;
    int end = size - 1;
    int mid;
    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid] == mid)
            return mid;
        else if (arr[mid] < mid)
            start = mid + 1;
        else
            end = mid - 1;
    }
    /* fix point not found so return invalid index */
    return -1;
}

int main47() {
    int arr[] = {-10, -2, 0, 3, 11, 12, 35, 51, 200};
    int n = 9;
    printf("%d\n", fixPoint(arr, n));
    printf("%d\n", fixPoint2(arr, n));
    return 0;
}

int subArraySums(int arr[], int size, int value) {
    int first = 0;
    int second = 0;
    int sum = arr[first];
    while (second < size && first < size) {
        if (sum == value)
            printf("%d , %d ", first, second);

        if (sum < value) {
            second += 1;
            if (second < size)
                sum += arr[second];
        } else {
            sum -= arr[first];
            first += 1;
        }
    }
}

int main48() {
    int arr[] = {15, 5, 5, 20, 10, 5, 5, 20, 10, 10};
    int n = 10;
    printf("%d\n", subArraySums(arr, 10, 20));
    return 0;
}

int maxConSub(int arr[], int size) {
    int currMax = 0;
    int maximum = 0;
    for (int i = 0; i < size; i++) {
        currMax = max(arr[i], currMax + arr[i]);
        if (currMax < 0)
            currMax = 0;
        if (maximum < currMax)
            maximum = currMax;
    }
    printf(" %d ", maximum);
}

int main49() {
    int arr[] = {1, -2, 3, 4, -4, 6, -4, 8, 2};
    int n = 9;
    maxConSub(arr, n);
    return 0;
}

int maxConSubArr(int A[], int sizeA, int B[], int sizeB) {
    int currMax = 0;
    int maximum = 0;
    Set* hs = createSet();

    for (int i = 0; i < sizeB; i++)
        SetAdd(hs, B[i]);

    for (int i = 0; i < sizeA; i++)
        if (SetFind(hs, A[i]))
            currMax = 0;
        else
            currMax = max(A[i], currMax + A[i]);
    if (currMax < 0)
        currMax = 0;
    if (maximum < currMax)
        maximum = currMax;
    printf(" %d ", maximum);
}

int maxConSubArr2(int A[], int sizeA, int B[], int sizeB) {
    sort(B, sizeB);
    int currMax = 0;
    int maximum = 0;

    for (int i = 0; i < sizeA; i++) {
        if (binarySearch(B, sizeB, A[i]))
            currMax = 0;
        else {
            currMax = max(A[i], currMax + A[i]);
            if (currMax < 0)
                currMax = 0;
            if (maximum < currMax)
                maximum = currMax;
        }
    }
    printf(" %d ", maximum);
}

int main50() {
    int arr1[] = {1, 2, 3, 4, 4, 6, 4, 8, 2};
    int size1 = sizeof(arr1)/sizeof(int);
    int arr2[] = {2,4, 8, 18, 10};
    int size2 = sizeof(arr2)/sizeof(int);
    printf("%d\n", maxConSubArr(arr1, size1, arr2, size2));
    printf("%d\n", maxConSubArr2(arr1, size1, arr2, size2));
    return 0;
}

int rainWater(int arr[], int size) {
    int water = 0;
    int *leftHigh = (int *)calloc(size, sizeof(int));
    int *rightHigh = (int *)calloc(size, sizeof(int));
    int max = arr[0];
    leftHigh[0] = arr[0];
    for (int i = 1; i < size; i++) {
        if (max < arr[i])
            max = arr[i];
        leftHigh[i] = max;
    }
    max = arr[size - 1];
    rightHigh[size - 1] = arr[size - 1];
    for (int i = (size - 2); i >= 0; i--) {
        if (max < arr[i])
            max = arr[i];
        rightHigh[i] = max;
    }

    for (int i = 0; i < size; i++)
        water += min(leftHigh[i], rightHigh[i]) - arr[i];
    printf("Water : %d ", water);
}

int rainWater2(int arr[], int size) {
    int water = 0;
    int leftMax = 0, rightMax = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        if (arr[left] < arr[right]) {
            if (arr[left] > leftMax)
                leftMax = arr[left];
            else
                water += leftMax - arr[left];
            left += 1;
        } else {
            if (arr[right] > rightMax)
                rightMax = arr[right];
            else
                water += rightMax - arr[right];
            right -= 1;
        }
    }
    printf("Water : %d \n", water);
}

int main51() {
    int arr[] = {4, 0, 1, 5};
    int n = 4;
    rainWater(arr, n);
    rainWater2(arr, n);
    return 0;
}

void seperateEvenAndOdd(int arr[], int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        if (arr[left] % 2 == 0)
            left++;
        else if (arr[right] % 2 == 1)
            right--;
        else {
            swap(arr, left, right);
            left++;
            right--;
        }
    }
}

int main52() {
    int first[] = { 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 };
    int n = sizeof(first)/sizeof(int);
    seperateEvenAndOdd(first, n);
    for(int i = 0; i< n;i++)
        printf("%d ", first[i]);
    printf("\n");
    return 0;
}

/*
30 20 6 6 6 6 6 6 10 8 7 13 5 1
*/

int SearchBotinicArrayMax(int arr[], int size) {
    int start = 0, end = size - 1;
    int mid = (start + end) / 2;
    int maximaFound = 0;
    if (size < 3) {
        printf("InvalidInput");
    }
    while (start <= end) {
        mid = (start + end) / 2;
        if (arr[mid - 1] < arr[mid] && arr[mid + 1] < arr[mid]) // maxima
        {
            maximaFound = 1;
            break;
        } else if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) // increasing
            start = mid + 1;
        else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) // decreasing
            end = mid - 1;
        else
            break;
    }

    if (maximaFound == 0) {
        printf("NoMaximaFound");
        return 0;
    }

    return arr[mid];
}

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
    main26();
    main27();
    main28();
    main29();
    main30();
    main31();
    main32();
    main33();
    main34();
    main35();
    main36();
    main37();
    main38();
    main39();
    main40();
    main41();
    main42();
    main43();
    main45();
    main46();
    main47();
    main48();
    main49();
    main50();
    main51();
    main52();
    return 0;
}
