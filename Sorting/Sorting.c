#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int less(int value1, int value2) {
    return value1 < value2;
}

int greater(int value1, int value2) {
    return value1 > value2;
}

void swap(int arr[], int x, int y) {
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void BubbleSort(int arr[], int size) {
    for (int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (greater(arr[j], arr[j + 1])) {
                /* Swapping */
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void BubbleSort2(int arr[], int size) {
    for (int i = 0, swapped = 1; i < (size - 1) && swapped; i++) {
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (greater(arr[j], arr[j + 1])) {
                /* Swapping */
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
    }
}

void InsertionSort(int arr[], int size) {
    int temp, j;
    for (int i = 1; i < size; i++) {
        temp = arr[i];
        for (j = i; (j > 0 && greater(arr[j - 1], temp)); j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}

void SelectionSort(int arr[], int size) {
    int max, temp;
    for (int i = 0; i < size - 1; i++) {
        max = 0;
        for (int j = 1; j <= (size - 1 - i); j++) {
            if (arr[j] > arr[max]) {
                max = j;
            }
        }
        temp = arr[size - 1 - i];
        arr[size - 1 - i] = arr[max];
        arr[max] = temp;
    }
}

void SelectionSort2(int arr[], int size) {
    int min, temp;
    for (int i = 0; i < size - 1; i++) {
        min = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void QuickSortUtil(int arr[], int lower, int upper) {
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (lower < upper && arr[lower] <= pivot) {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start);              //upper is the pivot position
    QuickSortUtil(arr, start, upper - 1); //pivot -1 is the upper for left sub array.
    QuickSortUtil(arr, upper + 1, stop);  // pivot + 1 is the lower for right sub array.
}

void QuickSort(int arr[], int size) {
    QuickSortUtil(arr, 0, size - 1);
}

void QuickSelectUtil(int arr[], int lower, int upper, int k) {
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper) {
        while (lower < upper && arr[lower] <= pivot) {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot) {
            upper--;
        }
        if (lower < upper) {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start); //upper is the pivot position
    if (k < upper)
        QuickSelectUtil(arr, start, upper - 1, k); //pivot -1 is the upper for left sub array.
    if (k > upper)
        QuickSelectUtil(arr, upper + 1, stop, k); // pivot + 1 is the lower for right sub array.
}
int QuickSelect(int *a, int count, int k) {
    QuickSelectUtil(a, 0, count - 1, k - 1);
    return a[k - 1];
}

void Merge(int *arr, int *tempArray, int lowerIndex, int middleIndex, int upperIndex) {
    int lowerStart = lowerIndex;
    int lowerStop = middleIndex;
    int upperStart = middleIndex + 1;
    int upperStop = upperIndex;
    int count = lowerIndex;
    while (lowerStart <= lowerStop && upperStart <= upperStop) {
        if (arr[lowerStart] < arr[upperStart])
            tempArray[count++] = arr[lowerStart++];
        else
            tempArray[count++] = arr[upperStart++];
    }
    while (lowerStart <= lowerStop) {
        tempArray[count++] = arr[lowerStart++];
    }
    while (upperStart <= upperStop) {
        tempArray[count++] = arr[upperStart++];
    }
    for (int i = lowerIndex; i <= upperIndex; i++) {
        arr[i] = tempArray[i];
    }
}

void MergeSortUtil(int *arr, int *tempArray, int lowerIndex, int upperIndex) {
    if (lowerIndex >= upperIndex)
        return;
    int middleIndex = (lowerIndex + upperIndex) / 2;
    MergeSortUtil(arr, tempArray, lowerIndex, middleIndex);
    MergeSortUtil(arr, tempArray, middleIndex + 1, upperIndex);
    Merge(arr, tempArray, lowerIndex, middleIndex, upperIndex);
}

void MergeSort(int *arr, int size) {
    int tempArray[size];
    MergeSortUtil(arr, tempArray, 0, size - 1);
}

void printArray(int *arr, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("]\n");
}

void CountSort(int array[], int n, int range) {
    int i, j = 0;
    int count[range + 1];
    for (i = 0; i < range; i++)
        count[i] = 0;

    for (i = 0; i < n; i++)
        count[array[i]]++;

    for (i = 0; i < range; i++) {
        for (; count[i] > 0; count[i]--) {
            array[j++] = i;
        }
    }
}

void shellSort(int arr[], int n) {
	// Gap starts with n/2 and half in each iteration.
	for (int gap = n / 2; gap > 0; gap /= 2) {
		// Do a gapped insertion sort.
		for (int i = gap; i < n; i += 1) {
			int curr = arr[i];

			// Shift elements of already sorted list
			// to find right position for curr value.
			int j;
			for (j = i; j >= gap && greater(arr[j - gap], curr); j -= gap)
			{
				arr[j] = arr[j - gap];
			}

			// Put current value in its correct location
			arr[j] = curr;
		}
	}
}

void bucketSort(int arr[], int size, int maxValue) {
    int numBucket = 5;
	if (size == 0) {
		return;
	}
    int bucket[numBucket][size];
    int count[numBucket];

	// Create empty buckets
	for (int i = 0; i < numBucket; i++)
        count[i] = 0;
        
	int div = ceil((double)maxValue / numBucket);

	// Add elements into the buckets
	for (int i = 0; i < size; i++) {
		if (arr[i] < 0 || arr[i] > maxValue) {
			printf("Value out of range.\n");
			return;
		}

		int bucketIndex = (arr[i] / div);

		// Maximum value will be assigned to last bucket.
		if (bucketIndex >= numBucket) {
			bucketIndex = numBucket - 1;
		}
		bucket[bucketIndex][count[bucketIndex]] = arr[i];
        count[bucketIndex] += 1;
	}

	// Sort the elements of each bucket.
	for (int i = 0; i < numBucket; i++)
		BubbleSort(bucket[i], count[i]);

	// Populate output from the sorted subarray.
	int index = 0, cnt;
	for (int i = 0; i < numBucket; i++) {
		cnt = count[i];
		for (int j = 0; j < cnt; j++) {
			arr[index++] = bucket[i][j];
		}
	}
}

/* Testing code */
int main1() {
    int arr[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    BubbleSort(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));
    
    int arr1[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    BubbleSort2(arr1, sizeof(arr) / sizeof(int));
    printArray(arr1, sizeof(arr) / sizeof(int));

    int arr2[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    InsertionSort(arr2, sizeof(arr2) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));
 
    int arr3[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    SelectionSort(arr3, sizeof(arr3) / sizeof(int));
    printArray(arr3, sizeof(arr3) / sizeof(int));
 
    int arr4[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    SelectionSort2(arr4, sizeof(arr4) / sizeof(int));
    printArray(arr4, sizeof(arr4) / sizeof(int));
 
    int arr5[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    MergeSort(arr5, sizeof(arr5) / sizeof(int));
    printArray(arr5, sizeof(arr5) / sizeof(int));
 
    int arr6[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    QuickSort(arr6, sizeof(arr6) / sizeof(int));
    printArray(arr6, sizeof(arr6) / sizeof(int));
 
    int arr7[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    CountSort(arr7, sizeof(arr7) / sizeof(int), 10);
    printArray(arr7, sizeof(arr7) / sizeof(int));
 
    int arr8[] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    printf("Fifth element :: %d\n", QuickSelect(arr8, sizeof(arr8) / sizeof(int), 5));

    int arr9[] = {36, 32, 11, 6, 19, 31, 17, 3};
    shellSort(arr9, sizeof(arr9) / sizeof(int));
    printArray(arr9, sizeof(arr9) / sizeof(int));

    int arr10[] = {1, 34, 7, 99, 5, 23, 45, 88, 77, 19, 91, 100};
    bucketSort(arr10, sizeof(arr10) / sizeof(int), 100);
    printArray(arr10, sizeof(arr10) / sizeof(int));
}

/*
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
[ 1 2 3 4 5 6 7 8 9 10 ]
Fifth element :: 5
[ 3 6 11 17 19 31 32 36 ]
[ 1 5 7 19 23 34 45 77 88 91 99 100 ]
*/
