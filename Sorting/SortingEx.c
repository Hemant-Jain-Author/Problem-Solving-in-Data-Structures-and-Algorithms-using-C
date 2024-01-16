#include "Sorting.c"

int Partition01(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    int count = 0;
    while (left < right) {
        while (arr[left] == 0)
            left += 1;

        while (arr[right] == 1)
            right -= 1;

        if (left < right) {
            swap(arr, left, right);
            count += 1;
        }
    }
    return count;
}

void partition012_(int arr[], int size) {
    int zero = 0, one = 0, two = 0;

    for (int i =0; i < size;i++) {
        if (arr[i] == 0) {
            zero += 1;
        } else if (arr[i] == 1) {
            one += 1;
        } else {
            two += 1;
        }
    }
    int index = 0;
    while(zero > 0){
        arr[index++] = 0;
        zero -= 1;
    }
    while(one > 0){
        arr[index++] = 1;
        one -= 1;
    }
    while(two > 0){
        arr[index++] = 2;
        two -= 1;
    }
}

void Partition012(int arr[], int size) {
    int left = 0;
    int right = size - 1;
    int i = 0;
    while (i <= right) {
        if (arr[i] == 0) {
            swap(arr, i, left);
            i += 1;
            left += 1;
        }
        else if (arr[i] == 2) {
            swap(arr, i, right);
            right -= 1;
        } else {
            i += 1;
        }
    }
}

// Testing code
int main2() {
    int arr[] = {0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1};
    Partition01(arr, sizeof(arr) / sizeof(int));
    printArray(arr, sizeof(arr) / sizeof(int));

    int arr2[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    Partition012(arr2, sizeof(arr2) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));

    int arr3[] = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
    Partition012(arr3, sizeof(arr3) / sizeof(int));
    printArray(arr3, sizeof(arr3) / sizeof(int));
}

/*
[ 0 0 0 0 0 0 1 1 1 1 1 1 ]
[ 0 0 0 0 0 1 1 1 1 1 2 2 ]
*/

void RangePartition(int arr[], int size, int lower, int higher) {
    int start = 0;
    int end = size - 1;
    int i = 0;
    while (i <= end) {
        if (arr[i] < lower) {
            swap(arr, i, start);
            i += 1;
            start += 1;
        } else if (arr[i] > higher) {
            swap(arr, i, end);
            end -= 1;
        } else {
            i += 1;
        }
    }
}

// Testing code
int main3() {
    int arr[] = {1, 21, 2, 20, 3, 19, 4, 18, 5, 17, 6, 16, 7, 15, 8, 14, 9, 13, 10, 12, 11};
    RangePartition(arr, sizeof(arr) / sizeof(int), 9, 12);
    printArray(arr, sizeof(arr) / sizeof(int));
}

/*
[ 1 2 3 4 5 8 6 7 11 10 12 9 15 16 14 17 13 18 19 20 21 ]
*/

int AbsGreater(int value1, int value2, int ref) {
    return abs(value1 - ref) > abs(value2 - ref);
}

void AbsBubbleSort(int arr[], int size, int ref) {
    for (int i = 0; i < (size - 1); i++) {
        for (int j = 0; j < (size - i - 1); j++) {
            if (AbsGreater(arr[j], arr[j + 1], ref)) {
                swap(arr, j, j + 1);
            }
        }
    }
}

// Testing code
int main4() {
    int array[] = {9, 1, 8, 2, 7, 3, 6, 4, 5};
    int ref = 5;
    AbsBubbleSort(array, sizeof(array) / sizeof(int), ref);
    printArray(array, sizeof(array) / sizeof(int));
}

/*
[ 5 6 4 7 3 8 2 9 1 ]
*/

int EqGreater(int value1, int value2, int A) {
    value1 = A * value1 * value1;
    value2 = A * value2 * value2;
    return value1 > value2;
}

void ArrayReduction(int arr[], int size) {
    QuickSort(arr, size);
    int count = 1;
    int reduction = arr[0];

    for (int i = 0; i < size; i++) {
        if (arr[i] - reduction > 0) {
            reduction = arr[i];
            count += 1;
        }
    }
    printf("\nTotal number of reductions %d\n", count);
}

//Testing code
int main5() {
    int arr[] = {5, 1, 1, 1, 2, 3, 5};
    ArrayReduction(arr, sizeof(arr) / sizeof(int));
}

/*
Total number of reductions 4
*/

void merge(int arr1[], int size1, int arr2[], int size2) {
    int index = 0;
    while (index < size1) {
        if (arr1[index] <= arr2[0]) {
            index += 1;
        } else {
            // always first element of arr2 is compared.
            arr1[index] ^= arr2[0] ^= arr1[index] ^= arr2[0];
            index += 1;
            // After swap arr2 may be unsorted.
            // Insertion of the element in proper sorted position.
            for (int i = 0; i < (size2 - 1); i++) {
                if (arr2[i] < arr2[i + 1])
                    break;
                arr2[i] ^= arr2[i + 1] ^= arr2[i] ^= arr2[i + 1];
            }
        }
    }
}

// Testing code.
int main6() {
    int arr1[] = {1, 5, 9, 10, 15, 20};
    int arr2[] = {2, 3, 8, 13};
    merge(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
    printArray(arr1, sizeof(arr1) / sizeof(int));
    printArray(arr2, sizeof(arr2) / sizeof(int));
}

/*
[ 1 2 3 5 8 9 ]
[ 10 13 15 20 ]
*/

int checkReverse(int arr[], int size) {
    int start = -1;
    int stop = -1;
    for (int i = 0; i < (size - 1); i++) {
        if (arr[i] > arr[i + 1]) {
            start = i;
            break;
        }
    }

    if (start == -1)
        return 1;

    for (int i = start; i < (size - 1); i++) {
        if (arr[i] < arr[i + 1]) {
            stop = i;
            break;
        }
    }

    if (stop == -1)
        return 1;

    // increasing property after reversal the sub array should fit in the array.
    if (arr[start - 1] > arr[stop] || arr[stop + 1] < arr[start])
        return 0;

    for (int i = stop + 1; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main7() {
    int arr[] = {1, 3, 8, 5, 4, 3, 10, 11, 12, 18, 28};
    int n = sizeof(arr)/sizeof(int);
    printf("checkReverse : %d\n", checkReverse(arr, n));
    return 0;
}

/*
checkReverse : 1
*/

int min(int X, int Y) {
    return (X < Y) ? X : Y;
}

void UnionIntersectionSorted(int arr1[], int size1, int arr2[], int size2) {
    int first = 0, second = 0;
    int unionArr[size1 + size2];
    int interArr[min(size1, size2)];
    int uIndex = 0;
    int iIndex = 0;

    while (first < size1 && second < size2) {
        if (arr1[first] == arr2[second]) {
            unionArr[uIndex++] = arr1[first];
            interArr[iIndex++] = arr1[first];
            first += 1;
            second += 1;
        } else if (arr1[first] < arr2[second]) {
            unionArr[uIndex++] = arr1[first];
            first += 1;
        } else {
            unionArr[uIndex++] = arr2[second];
            second += 1;
        }
    }

    while (first < size1) {
        unionArr[uIndex++] = arr1[first];
        first += 1;
    }

    while (second < size2) {
        unionArr[uIndex++] = arr2[second];
        second += 1;
    }
    printArray(unionArr, uIndex);
    printArray(interArr, iIndex);
}

void UnionIntersectionUnsorted(int arr1[], int size1, int arr2[], int size2) {
    QuickSort(arr1, size1);
    QuickSort(arr2, size2);
    UnionIntersectionSorted(arr1, size1, arr2, size2);
}

int main8() {
    int arr1[] = {1, 11, 2, 3, 14, 5, 6, 8, 9};
    int arr2[] = {2, 4, 5, 12, 7, 8, 13, 10};
    UnionIntersectionUnsorted(arr1, sizeof(arr1) / sizeof(int), arr2, sizeof(arr2) / sizeof(int));
}

/*
[ 1 2 3 4 5 6 7 8 9 10 11 12 13 14 ]
[ 2 5 8 ]
*/

int minSwaps(int arr[], int size, int val) {
    int swapCount = 0;
    int first = 0;
    int second = size - 1;
    printf("%d %d\n", first, second);
    int temp;
    while (first < second) {
        if (arr[first] <= val)
            first += 1;
        else if (arr[second] > val)
            second -= 1;
        else {
            temp = arr[first];
            arr[first] = arr[second];
            arr[second] = temp;
            swapCount += 1;
        }
    }
    return swapCount;
}

//Testing code
int main9() {
 int array[] = {1, 2, 3, 4, 18, 5, 17, 6, 16, 7, 15, 8, 14, 9, 13, 10, 12, 11};
 printf("minSwaps: %d\n", minSwaps(array, sizeof(array) / sizeof(int), 10));
}

void separateEvenAndOdd(int data[], int size) {
    int left = 0, right = size - 1;
    int aux[size];
    
    for (int i=0;i< size;i++) {
        if (data[i] % 2 == 0) {
            aux[left] = data[i];
            left++;
        } else if (data[i] % 2 == 1) {
            aux[right] = data[i];
            right--;
        }
    }
    for (int i=0;i< size;i++)
        data[i] = aux[i];
}

void separateEvenAndOdd2(int data[], int size) {
    int left = 0, right = size - 1;
    while (left < right) {
        if (data[left] % 2 == 0)
            left++;
        else if (data[right] % 2 == 1)
            right--;
        else {
            swap(data, left, right);
            left++;
            right--;
        }
    }
}

// Testing code
int main10() {
    int array[] = { 9, 1, 8, 2, 7, 3, 6, 4, 5 };
    separateEvenAndOdd(array, 9);
    printArray(array, 9);
    int array2[] = { 9, 1, 8, 2, 7, 3, 6, 4, 5 };
    separateEvenAndOdd2(array2, 9);
    printArray(array2, 9);
}
// [ 4 6 8 2 7 3 1 9 5 ]


int main() {
    //main1();
    main2();
    main3();
    main4();
    main5();
    main6();
    main7();
    main8();
    main9();
    main10();
    return 0;
}
