#include <stdio.h>
#include <stdlib.h>

int less(int value1, int value2)
{
    return value1 < value2;
}

int more(int value1, int value2)
{
    return value1 > value2;
}

void swap(int arr[], int x, int y)
{
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

void BubbleSort(int arr[], int size)
{
    int i, j, temp;
    for (i = 0; i < (size - 1); i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (more(arr[j], arr[j + 1]))
            {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void BubbleSort2(int arr[], int size)
{
    int i, j, temp, swapped = 1;
    for (i = 0; i < (size - 1) && swapped; i++)
    {
        swapped = 0;
        for (j = 0; j < size - i - 1; j++)
        {
            if (more(arr[j], arr[j + 1]))
            {
                /* Swapping */
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
    }
}

void InsertionSort(int arr[], int size)
{
    int temp, j;
    for (int i = 1; i < size; i++)
    {
        temp = arr[i];
        for (j = i; (j > 0 && more(arr[j - 1], temp)); j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = temp;
    }
}

void SelectionSort(int arr[], int size)
{
    int i, j, max, temp;
    for (i = 0; i < size - 1; i++)
    {
        max = 0;
        for (j = 1; j <= (size - 1 - i); j++)
        {
            if (arr[j] > arr[max])
            {
                max = j;
            }
        }
        temp = arr[size - 1 - i];
        arr[size - 1 - i] = arr[max];
        arr[max] = temp;
    }
}

void SelectionSort2(int arr[], int size)
{
    int i, j, min, temp;
    for (i = 0; i < size - 1; i++)
    {
        min = i;
        for (j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void QuickSortUtil(int arr[], int lower, int upper)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper)
    {
        while (lower < upper && arr[lower] <= pivot)
        {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot)
        {
            upper--;
        }
        if (lower < upper)
        {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start);              //upper is the pivot position
    QuickSortUtil(arr, start, upper - 1); //pivot -1 is the upper for left sub array.
    QuickSortUtil(arr, upper + 1, stop);  // pivot + 1 is the lower for right sub array.
}

void QuickSort(int arr[], int size)
{
    QuickSortUtil(arr, 0, size - 1);
}

void QuickSelectUtil(int arr[], int lower, int upper, int k)
{
    if (upper <= lower)
        return;

    int pivot = arr[lower];

    int start = lower;
    int stop = upper;

    while (lower < upper)
    {
        while (lower < upper && arr[lower] <= pivot)
        {
            lower++;
        }
        while (lower <= upper && arr[upper] > pivot)
        {
            upper--;
        }
        if (lower < upper)
        {
            swap(arr, upper, lower);
        }
    }

    swap(arr, upper, start); //upper is the pivot position
    if (k < upper)
        QuickSelectUtil(arr, start, upper - 1, k); //pivot -1 is the upper for left sub array.
    if (k > upper)
        QuickSelectUtil(arr, upper + 1, stop, k); // pivot + 1 is the lower for right sub array.
}
int QuickSelect(int *a, int count, int index)
{
    QuickSelectUtil(a, 0, count - 1, index - 1);
    return a[index - 1];
}

void Merge(int *arr, int *tempArray, int lowerIndex, int middleIndex, int upperIndex)
{
    int lowerStart = lowerIndex;
    int lowerStop = middleIndex;
    int upperStart = middleIndex + 1;
    int upperStop = upperIndex;
    int count = lowerIndex;
    while (lowerStart <= lowerStop && upperStart <= upperStop)
    {
        if (arr[lowerStart] < arr[upperStart])
            tempArray[count++] = arr[lowerStart++];
        else
            tempArray[count++] = arr[upperStart++];
    }
    while (lowerStart <= lowerStop)
    {
        tempArray[count++] = arr[lowerStart++];
    }
    while (upperStart <= upperStop)
    {
        tempArray[count++] = arr[upperStart++];
    }
    for (int i = lowerIndex; i <= upperIndex; i++)
        arr[i] = tempArray[i];
}

void MergeSortUtil(int *arr, int *tempArray, int lowerIndex, int upperIndex)
{
    if (lowerIndex >= upperIndex)
        return;
    int middleIndex = (lowerIndex + upperIndex) / 2;
    MergeSortUtil(arr, tempArray, lowerIndex, middleIndex);
    MergeSortUtil(arr, tempArray, middleIndex + 1, upperIndex);
    Merge(arr, tempArray, lowerIndex, middleIndex, upperIndex);
}

void MergeSort(int *arr, int size)
{
    int *tempArray = (int *)malloc(size * sizeof(int));
    MergeSortUtil(arr, tempArray, 0, size - 1);
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf(" %d ", arr[i]);
    printf("\n");
}

void BucketSort(int array[], int n, int range)
{
    int i, j = 0;
    int *count = (int *)malloc((range + 1) * sizeof(int));
    for (i = 0; i < range; i++)
        count[i] = 0;

    for (i = 0; i < n; i++)
        count[array[i]]++;

    for (i = 0; i < range; i++)
    {
        for (; count[i] > 0; count[i]--)
        {
            array[j++] = i;
        }
    }
    free(count);
}

/* Testing code */
int main1()
{
    int arr[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    BubbleSort(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));
    

    int arr2[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    InsertionSort(arr2, sizeof(arr2) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));
 
    //int arr3[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    int arr3[10] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    SelectionSort(arr3, sizeof(arr3) / sizeof(int));
    printArray(arr3, sizeof(arr3) / sizeof(int));
 
    int arr4[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    SelectionSort2(arr4, sizeof(arr4) / sizeof(int));
    printArray(arr4, sizeof(arr4) / sizeof(int));
 
    int arr5[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    MergeSort(arr5, sizeof(arr5) / sizeof(int));
    printArray(arr5, sizeof(arr5) / sizeof(int));
 
    int arr6[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    QuickSort(arr6, sizeof(arr6) / sizeof(int));
    printArray(arr6, sizeof(arr6) / sizeof(int));
 
    int arr7[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    BucketSort(arr7, sizeof(arr7) / sizeof(int), 10);
    printArray(arr7, sizeof(arr7) / sizeof(int));
 
    int arr8[10] = {4, 5, 3, 2, 6, 7, 1, 8, 9, 10};
    printf("Fifth element :: %d", QuickSelect(arr8, sizeof(arr8) / sizeof(int), 5));
    printArray(arr, sizeof(arr8) / sizeof(int));
}

int Partition01(int arr[], int size)
{
    int left = 0;
    int right = size - 1;
    int count = 0;
    while (left < right)
    {
        while (arr[left] == 0)
            left += 1;

        while (arr[right] == 1)
            right -= 1;

        if (left < right)
        {
            swap(arr, left, right);
            count += 1;
        }
    }
    return count;
}

void Partition012(int arr[], int size)
{
    int left = 0;
    int right = size - 1;
    int i = 0;
    while (i <= right)
    {
        if (arr[i] == 0)
        {
            swap(arr, i, left);
            i += 1;
            left += 1;
        }
        else if (arr[i] == 2)
        {
            swap(arr, i, right);
            right -= 1;
        }
        else
        {
            i += 1;
        }
    }
}

// Testing code
int main2()
{
    int arr[] = {0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1};
    Partition01(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));

    int arr2[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    Partition012(arr2, sizeof(arr2) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));
}

void RangePartition(int arr[], int size, int lower, int higher)
{
    int start = 0;
    int end = size - 1;
    int i = 0;
    while (i <= end)
    {
        if (arr[i] < lower)
        {
            swap(arr, i, start);
            i += 1;
            start += 1;
        }
        else if (arr[i] > higher)
        {
            swap(arr, i, end);
            end -= 1;
        }
        else
        {
            i += 1;
        }
    }
}

// Testing code
int main3()
{
    int arr[] = {1, 21, 2, 20, 3, 19, 4, 18, 5, 17, 6, 16, 7, 15, 8, 14, 9, 13, 10, 12, 11};
    RangePartition(arr, sizeof(arr) / sizeof(int), 9, 12);
    printArray(arr, sizeof(arr) / sizeof(int));
}

int AbsMore(int value1, int value2, int ref)
{
    return abs(value1 - ref) > abs(value2 - ref);
}

void AbsBubbleSort(int arr[], int size, int ref)
{
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 0; j < (size - i - 1); j++)
        {
            if (AbsMore(arr[j], arr[j + 1], ref))
            {
                swap(arr, j, j + 1);
            }
        }
    }
}

// Testing code
int main4()
{
    int array[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    int ref = 5;
    AbsBubbleSort(array, sizeof(array) / sizeof(int), ref);
    printArray(array, sizeof(array) / sizeof(int));
}

int EqMore(int value1, int value2, int A)
{
    value1 = A * value1 * value1;
    value2 = A * value2 * value2;
    return value1 > value2;
}

void ArrayReduction(int arr[], int size)
{
    QuickSort(arr, size);
    int count = 1;
    int reduction = arr[0];

    for (int i = 0; i < size; i++)
    {
        if (arr[i] - reduction > 0)
        {
            printf("%d ", (size - i));
            reduction = arr[i];
            count += 1;
        }
    }
    printf("\nTotal number of reductions %d ", count);
}

//Testing code
int main5()
{
    int arr[] = {5, 1, 1, 1, 2, 3, 5};
    ArrayReduction(arr, sizeof(arr) / sizeof(int));
}

/*
def SortFrequency(int arr[], int size):
	HashTable ht;
	int value;
	for (int i = 0; i< size; i++) {
		if (HashFind(ht, arr[i])){
			value = HashGet(arr[i]);
			HashAdd(arr[i], value+1);
		}
		else {
			HashAdd(arr[i], 1);
		}
	}
	
	//User is recommended to write his own sorting function.
	//For convenience author is using inbuilt functions. 
	

	
	for key, value in reversed(sorted(mp.iteritems(), key = lambda (k, v): (v, k))):
		for i in range(value):
			print key ,
// Testing code
arr = [2, 3, 2, 4, 5, 12, 2, 3, 3, 3, 12]
SortFrequency(arr)
*/
/*
void SortByOrder(int arr[], int size, int arr2[], int size2)
{
    HashTable ht;
    int value;
    for (int i = 0; i < size; i++)
    {
        if (HashFind(ht, arr[i]))
        {
            value = HashGet(arr[i]);
            HashAdd(arr[i], value + 1);
        }
        else
        {
            HashAdd(arr[i], 1);
        }
    }

    for (int j = 0; j < size2; j++)
    {
        if (HashFind(ht, j))
        {
            value = HashGet(ht, j);
            for (int k = 0; k < value; k++)
            {
                printf("%d", k);
            }
            HashRemove(ht, j);
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (HashFind(ht, arr[i]))
        {
            value = HashGet(arr[i]);
            for (int k = 0; k < value; k++)
            {
                printf("%d", k);
            }
            HashRemove(ht, j);
        }
    }
}

// Testing code
int main6()
{
    int arr[] = {2, 1, 2, 5, 7, 1, 9, 3, 6, 8, 8};
    int arr2[] = {2, 1, 8, 3};
    SortByOrder(arr, sizeof(arr) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
}
*/

void merge(int arr1[], int size1, int arr2[], int size2)
{
    int index = 0;
    while (index < size1)
    {
        if (arr1[index] <= arr2[0])
        {
            index += 1;
        }
        else
        {
            // always first element of arr2 is compared.
            arr1[index] ^= arr2[0] ^= arr1[index] ^= arr2[0];
            index += 1;
            // After swap arr2 may be unsorted.
            // Insertion of the element in proper sorted position.
            for (int i = 0; i < (size2 - 1); i++)
            {
                if (arr2[i] < arr2[i + 1])
                    break;
                arr2[i] ^= arr2[i + 1] ^= arr2[i] ^= arr2[i + 1];
            }
        }
    }
}

// Testing code.
int main7()
{
    int arr1[] = {1, 5, 9, 10, 15, 20};
    int arr2[] = {2, 3, 8, 13};
    merge(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
    printArray(arr1, sizeof(arr1) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));
}

int checkReverse(int arr[], int size)
{
    int start = -1;
    int stop = -1;
    for (int i = 0; i < (size - 1); i++)
    {
        if (arr[i] > arr[i + 1])
        {
            start = i;
            break;
        }
    }

    if (start == -1)
        return 1;

    for (int i = start; i < (size - 1); i++)
    {
        if (arr[i] < arr[i + 1])
        {
            stop = i;
            break;
        }
    }

    if (stop == -1)
        return 1;

    // increasing property
    // after reversal the sub array should fit in the array.
    if (arr[start - 1] > arr[stop] || arr[stop + 1] < arr[start])
        return 0;

    for (int i = stop + 1; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return 0;
        }
    }
    return 1;
}

int min(int X, int Y)
{
    if (X < Y)
    {
        return X;
    }
    return Y;
}

void UnionIntersectionSorted(int arr1[], int size1, int arr2[], int size2)
{
    int first = 0, second = 0;
    int *unionArr = (int *)malloc(sizeof(int) * (size1 + size2));
    int *interArr = (int *)malloc(sizeof(int) * min(size1, size2));
    int uIndex = 0;
    int iIndex = 0;

    while (first < size1 && second < size2)
    {
        if (arr1[first] == arr2[second])
        {
            unionArr[uIndex++] = arr1[first];
            interArr[iIndex++] = arr1[first];
            first += 1;
            second += 1;
        }
        else if (arr1[first] < arr2[second])
        {
            unionArr[uIndex++] = arr1[first];
            first += 1;
        }
        else
        {
            unionArr[uIndex++] = arr2[second];
            second += 1;
        }
    }

    while (first < size1)
    {
        unionArr[uIndex++] = arr1[first];
        first += 1;
    }

    while (second < size2)
    {
        unionArr[uIndex++] = arr2[second];
        second += 1;
    }
    printArray(unionArr, uIndex);
    printArray(interArr, iIndex);
}

void UnionIntersectionUnsorted(int arr1[], int size1, int arr2[], int size2)
{
    QuickSort(arr1, size1);
    QuickSort(arr2, size2);
    UnionIntersectionSorted(arr1, size1, arr2, size2);
}

int main8()
{
    int arr1[] = {1, 11, 2, 3, 14, 5, 6, 8, 9};
    int arr2[] = {2, 4, 5, 12, 7, 8, 13, 10};
    UnionIntersectionUnsorted(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
}

int main(){
    main1();
    main2();
    main3();
    main4();
    main5();
    main7();
    main8();
}