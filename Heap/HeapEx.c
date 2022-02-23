/* Exercise of heap */

#include "Heap.c"

int main1() {
    int a[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    Heap* hp = createHeap2(a, 10, greater);//min heap
    printHeap(hp);

    while (!isEmpty(hp)) {
    	printf("%d ", heapRemove(hp));
    }
    
    printf("Top value removed : %d\n", heapRemove(hp));
    printHeap(hp);

    heapAdd(hp, 10);
    printHeap(hp);
    
    heapAdd(hp, 20);
    printHeap(hp);

    int b[10] = {4, 5, 3, 2, 6, 7, 10, 8, 9, 1};
    heapSort(b, 10, 1); // increasing
    printArray(b, 10);
    
    heapSort(b, 10, 0); // decreasing
    printArray(b, 10);
    return 0;
}

/*
1 2 3 4 5 7 10 8 9 6 
Top value 1 
2 4 3 6 5 7 10 8 9 
2 4 3 6 5 7 10 8 9 10 
2 4 3 6 5 7 10 8 9 10 
1 2 3 4 5 6 7 8 9 10 
10 9 8 7 6 5 4 3 2 1 
*/

int KthSmallest(int arr[], int size, int k) {
    heapSort(arr, size, 1);
    return arr[k - 1];
}

int KthSmallest2(int arr[], int size, int k) {
    Heap* hp = createHeap2(arr, size, greater);
    int i = 0;
    int value = 0;
    while (i < size && i < k) {
        value = heapRemove(hp);
        i += 1;
    }
    return value;
}

int KthSmallest3(int arr[], int size, int k) {
    Heap* hp = createHeap(less);
    for (int i = 0; i < size; i++) {
        if(i < k) {
            heapAdd(hp, arr[i]);
        } else {
            if (heapTop(hp) > arr[i]) {
                heapAdd(hp, arr[i]);
                heapRemove(hp);
            }
        }
    }
    return heapTop(hp);
}


int isMinHeap(int arr[], int size) {
    int lchild, rchild;
    //last element index size - 1
    for (int parent = 0; parent < (size / 2 + 1); parent++) {
        lchild = parent * 2 + 1;
        rchild = parent * 2 + 2;
        // heap property check.
        if (((lchild < size) && (arr[parent] > arr[lchild])) || ((rchild < size) && (arr[parent] > arr[rchild])))
            return 0;
    }
    return 1;
}

int isMaxHeap(int arr[], int size) {
    int lchild, rchild;
    //last element index size - 1
    for (int parent = 0; parent < (size / 2 + 1); parent++) {
        lchild = parent * 2 + 1;
        rchild = lchild + 1;
        // heap property check.
        if (((lchild < size) && (arr[parent] < arr[lchild])) || ((rchild < size) && (arr[parent] < arr[rchild])))
            return 0;
    }
    return 1;
}

int main2() {
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest :: %d\n", KthSmallest(arr, 8, 3));
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest :: %d\n", KthSmallest2(arr2, 8, 3));
    int arr3[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest :: %d\n", KthSmallest3(arr3, 8, 3));
    int arr4[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("isMaxHeap :: %d\n", isMaxHeap(arr4, sizeof(arr) / sizeof(int)));
    int arr5[] = {8, 7, 6, 5, 7, 5, 2, 1};
    heapSort(arr5, sizeof(arr) / sizeof(int), 1);
    printf("isMinHeap :: %d\n", isMinHeap(arr5, sizeof(arr) / sizeof(int)));
    return 0;
}

/*
Kth Smallest :: 5
Kth Smallest :: 5
isMaxHeap :: 1
isMinHeap :: 1
*/

int KSmallestProduct(int arr[], int size, int k) {
    heapSort(arr, size, 1);
    int product = 1;
    for (int i = 0; i < k; i++)
        product *= arr[i];
    return product;
}

void swap(int arr[], int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
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

int KSmallestProduct3(int arr[], int size, int k) {
    QuickSelectUtil(arr, 0, size - 1, k);
    int product = 1;
    for (int i = 0; i < k; i++)
        product *= arr[i];
    return product;
}

int KSmallestProduct2(int arr[], int size, int k) {
    Heap* hp = createHeap2(arr, size, greater);
    int i = 0;
    int product = 1;
    while (i < size && i < k) {
        product *= heapRemove(hp);
        i += 1;
    }
    return product;
}

int KSmallestProduct4(int arr[], int size, int k) {
    Heap* hp = createHeap(less);
    for (int i = 0; i < size; i++) {
        if(i < k)
            heapAdd(hp, arr[i]);
        else {
            if (heapTop(hp) > arr[i]) {
                heapAdd(hp, arr[i]);
                heapRemove(hp);
            }
        }
    }    
    int product = 1;
    for (int i = 0; i < k; i++) {
        product *= heapRemove(hp);
    }
    return product;
}

int main3() {
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n", KSmallestProduct(arr, 8, 3));
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n", KSmallestProduct2(arr2, 8, 3));
    int arr3[8] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n", KSmallestProduct3(arr3, 8, 3));
    int arr4[8] = {8, 7, 6, 5, 7, 5, 2, 1};
    printf("Kth Smallest product:: %d\n", KSmallestProduct4(arr4, 8, 3));
    return 0;
}

/*
Kth Smallest product:: 10
Kth Smallest product:: 10
Kth Smallest product:: 10
*/

void PrintLargerHalf(int arr[], int size) {
    heapSort(arr, size, 1);
    for (int i = size / 2; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void PrintLargerHalf2(int arr[], int size) {
    Heap* hp = createHeap2(arr, size, greater);
    for (int i = 0; i < size / 2; i++)
        heapRemove(hp);
    printArray(arr, size / 2);
}

void PrintLargerHalf3(int arr[], int size) {
    QuickSelectUtil(arr, 0, size - 1, size / 2);
    for (int i = size / 2; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main4() {
    int arr[] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf(arr, 8);
    int arr2[] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf2(arr2, 8);
    int arr3[8] = {8, 7, 6, 5, 7, 5, 2, 1};
    PrintLargerHalf3(arr3, 8);
    return 0;
}

/*
6 7 7 8 
6 7 8 7 
6 7 7 8 
*/

void heapSortK(int arr[], int size, int k) {
    Heap* hp = createHeap2(arr, k, greater);
    int *output = (int *)malloc(sizeof(int) * size);
    int index = 0;

    for (int i = k; i < size; i++) {
        output[index++] = heapRemove(hp);
        heapAdd(hp, arr[i]);
    }

    while (heapSize(hp) > 0)
        output[index++] = heapRemove(hp);

    for (int i = k; i < size; i++) {
        arr[i] = output[i];
    }
    printArray(output, index);
}

// Testing Code
int main5() {
    int k = 3;
    int arr[] = {1, 5, 4, 10, 50, 9};
    int size = sizeof(arr) / sizeof(int);
    heapSortK(arr, size, k);
    return 0;
}

//1 4 5 9 10 50 

int JoinRopes(int ropes[], int size) {
    heapSort(ropes, size, 0); // decreasing
    int total = 0;
    int value = 0;
    int temp, index;
    int length = size;

    while (length >= 2) {
        value = ropes[length - 1] + ropes[length - 2];
        total += value;
        index = length - 2;

        while (index > 0 && ropes[index - 1] < value) {
            ropes[index] = ropes[index - 1];
            index -= 1;
        }
        ropes[index] = value;
        length--;
    }
    printf("Total : %d\n", total);
    return total;
}

int JoinRopes2(int ropes[], int size) {
    Heap* hp = createHeap2(ropes, size, greater);
    int total = 0;
    int value = 0;
    while (heapSize(hp) > 1) {
        value = heapRemove(hp);
        value += heapRemove(hp);
        heapAdd(hp, value);
        total += value;
    }
    printf("Total : %d \n", total);
    return total;
}

int main6() {
    int ropes[] = {2, 1, 7, 4, 2};
    JoinRopes(ropes, sizeof(ropes) / sizeof(int));
    int rope2[] = {2, 1, 7, 4, 2};
    JoinRopes2(rope2, sizeof(rope2) / sizeof(int));
    return 0;
}

/*
Total : 33 
Total : 33 
*/

int kthLargestStream(int k) {
    Heap* hp = createHeap(greater);
    int size = 0;
    int data;
    while (1) {
        printf("Enter data: ");
        scanf("%d", &data);

        if (size < k - 1)
            heapAdd(hp, data);
        else {
            if (size == k - 1)
                heapAdd(hp, data);
            else if (heapTop(hp) < data) {
                heapAdd(hp, data);
                heapRemove(hp);
            }
            printf("Kth larges element is :: %d\n", heapTop(hp));
        }
        size += 1;
    }
}

int main7() {
    //kthLargestStream(3);
    return 0;
}

#define ERROR_VALUE 999999

typedef struct medianHeap {
    Heap* minHeap;
    Heap* maxHeap;
} MedianHeap;

MedianHeap* createMedianHeap() {
    MedianHeap* hp = (MedianHeap* )malloc(sizeof(MedianHeap));
    hp->minHeap = createHeap(greater);
    hp->maxHeap = createHeap(less);
    return hp;
}

void medianHeapAdd(MedianHeap *heap, int value) {
    if (heapSize(heap->maxHeap) == 0 || heapTop(heap->maxHeap) >= value) {
        heapAdd(heap->maxHeap, value);
    } else {
        heapAdd(heap->minHeap, value);
    }
    //size balancing
    if (heapSize(heap->maxHeap) > heapSize(heap->minHeap) + 1) {
        value = heapRemove(heap->maxHeap);
        heapAdd(heap->minHeap, value);
    }
    if (heapSize(heap->minHeap) > heapSize(heap->maxHeap) + 1) {
        value = heapRemove(heap->minHeap);
        heapAdd(heap->maxHeap, value);
    }
}

int getMedian(MedianHeap *heap) {
    if (heapSize(heap->maxHeap) == 0 && heapSize(heap->minHeap) == 0)
        return ERROR_VALUE;

    if (heapSize(heap->maxHeap) == heapSize(heap->minHeap))
        return (heapTop(heap->maxHeap) + heapTop(heap->minHeap)) / 2;
    else if (heapSize(heap->maxHeap) > heapSize(heap->minHeap))
        return heapTop(heap->maxHeap);
    else
        return heapTop(heap->minHeap);
}

int main8() {
    int arr[] = {1, 9, 2, 8, 3, 7, 4, 6, 5, 1};
    MedianHeap* heap = createMedianHeap();
    for (int i = 0; i < 10; i++) {
        medianHeapAdd(heap, arr[i]);
        printf("Median after insertion of %d is %d \n", arr[i], getMedian(heap));
    }
    return 0;
}
/*
Median after insertion of 1 is 1 
Median after insertion of 9 is 5 
Median after insertion of 2 is 2 
Median after insertion of 8 is 5 
Median after insertion of 3 is 3 
Median after insertion of 7 is 5 
Median after insertion of 4 is 4 
Median after insertion of 6 is 5 
Median after insertion of 5 is 5 
Median after insertion of 1 is 4 
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
    return 0;
}