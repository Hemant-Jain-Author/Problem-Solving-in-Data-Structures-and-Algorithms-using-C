#include <stdio.h>
#include <stdlib.h>

/* Dummy function and structure  start*/
typedef struct HT
{
    int i;
} HashTable;

void HashInit(HashTable *hs)
{
}

void HashAdd(HashTable *hs, int value)
{
}

void HashAdd2(HashTable *hs, int key, int value)
{
}

int HashFind(HashTable *hs, int value)
{
    return 1;
}

int HashGet(HashTable *hs, int value)
{
    return 1;
}

void HashRemove(HashTable *hs, int value)
{
}

typedef struct ST
{
    int i;
} Set;

void SetInit(Set *hs)
{
}

void SetAdd(Set *hs, int value)
{
}

int SetFind(Set *hs, int value)
{
    return 1;
}

void SetRemove(Set *hs, int value)
{
}

typedef struct CT
{
    int i;
} Counter;

void CounterInit(Counter *hs)
{
}

void CounterAdd(Counter *hs, int value)
{
}

int CounterFind(Counter *hs, int value)
{
    return 1;
}

int CounterGetCount(Counter *hs, int value)
{
    return 1;
}

void CounterRemove(Counter *hs, int value)
{
}

void CounterDelete(Counter *hs, int value)
{
}

/* dummy function end */

int more(int value1, int value2)
{
    return value1 > value2;
}

void Sort(int arr[], int size)
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

int linearSearchUnsorted(int data[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (value == data[i])
        {
            return 1;
        }
    }
    return 0;
}

int linearSearchSorted(int data[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        if (value == data[i])
            return 1;
        if (value < data[i])
            return 0;
    }
    return 0;
}

int Binarysearch(int data[], int size, int value)
{
    int low = 0;
    int high = size - 1;
    int mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (data[mid] == value)
        {
            return 1;
        }
        else if (data[mid] < value)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return 0;
}

int BinarySearchRecursive(int data[], int size, int low, int high, int value)
{
    if (low > high)
        return 0;

    int mid = (low + high) / 2;
    if (data[mid] == value)
        return 1;
    else if (data[mid] < value)
        return BinarySearchRecursive(data, size, mid + 1, high, value);
    else
        return BinarySearchRecursive(data, size, low, mid - 1, value);
}

int FirstRepeated(int data[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
                return data[i];
        }
    }
    return 0;
}

void printRepeating(int data[], int size)
{
    printf(" Repeating elements are : ");
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
                printf(" %d ", data[i]);
        }
    }
}

void printRepeating2(int data[], int size)
{
    Sort(data, size);
    printf(" Repeating elements are : ");

    for (int i = 1; i < size; i++)
    {
        if (data[i] == data[i - 1])
            printf(" %d ", data[i]);
    }
}

void printRepeating3(int data[], int size)
{
    HashTable hs;
    HashInit(&hs);

    printf(" Repeating elements are : ");
    for (int i = 0; i < size; i++)
    {
        if (HashFind(&hs, data[i]))
            printf(" %d ", data[i]);
        else
            HashAdd(&hs, data[i]);
    }
}

void printRepeating4(int data[], int size)
{
    int *count = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        count[i] = 0;
    }
    printf("Repeating elements are : ");
    for (int i = 0; i < size; i++)
    {
        if (count[data[i]] == 1)
            printf(" %d ", data[i]);
        else
            count[data[i]]++;
    }
}
int removeDuplicates(int data[], int size)
{
    int j = 0;
    if (size == 0)
        return 0;

    Sort(data, size);
    for (int i = 1; i < size; i++)
    {
        if (data[i] != data[j])
        {
            j++;
            data[j] = data[i];
        }
    }
    return j + 1;
}

int main()
{
    int first[] = {1, 3, 5, 7, 9, 25, 30};
    int second[] = {2, 4, 6, 8, 10, 12, 14, 16, 21, 23, 24};

    for (int i = 1; i < 16; i++)
    {
        printf("Index %d :: Value %d \n", i, removeDuplicates(first, sizeof(first) / sizeof(int)));
    }
    return 0;
}

int getMax(int data[], int size)
{
    int max = data[0], count = 1, maxCount = 1;
    for (int i = 0; i < size; i++)
    {
        count = 1;
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
                count++;
        }
        if (count > maxCount)
        {
            max = data[i];
            maxCount = count;
        }
    }
    return max;
}

int getMax2(int data[], int size)
{
    int max = data[0], maxCount = 1;
    int curr = data[0], currCount = 1;
    Sort(data, size);
    for (int i = 1; i < size; i++)
    {
        if (data[i] == data[i - 1])
            currCount++;
        else
        {
            currCount = 1;
            curr = data[i];
        }
        if (currCount > maxCount)
        {
            maxCount = currCount;
            max = curr;
        }
    }
    return max;
}

int getMax3(int data[], int size, int range)
{
    int max = data[0], maxCount = 1;

    int *count = (int *)malloc(sizeof(int) * range);
    for (int i = 0; i < size; i++)
    {
        count[data[i]]++;
        if (count[data[i]] > maxCount)
        {
            maxCount = count[data[i]];
            max = data[i];
        }
    }
    return max;
}

int getMajority(int data[], int size)
{
    int max = 0, count = 0, maxCount = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (data[i] == data[j])
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            max = data[i];
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

int getMajority2(int data[], int size)
{
    int majIndex = size / 2, count = 1;
    int candidate;
    Sort(data, size);
    candidate = data[majIndex];
    count = 0;
    for (int i = 0; i < size; i++)
    {
        if (data[i] == candidate)
            count++;
    }

    if (count > size / 2)
        return data[majIndex];
    else
    {
        printf("MajorityDoesNotExist");
        return 0;
    }
}

int getMajority3(int data[], int size)
{
    int majIndex = 0, count = 1;
    int candidate;

    for (int i = 1; i < size; i++)
    {
        if (data[majIndex] == data[i])
            count++;
        else
            count--;

        if (count == 0)
        {
            majIndex = i;
            count = 1;
        }
    }
    candidate = data[majIndex];
    count = 0;
    for (int i = 0; i < size; i++)
    {
        if (data[i] == candidate)
        {
            count++;
        }
    }
    if (count > size / 2)
        return data[majIndex];
    else
    {
        printf("MajorityDoesNotExist");
        return 0;
    }
}

/* Using binary search method.*/
int FirstIndex(int arr[], int size, int low, int high, int value)
{
    int mid;
    if (high >= low)
        mid = (low + high) / 2;

    /*
		Find first occurrence of value, either it should be the first 
		element of the array or the value before it is smaller than it.
		*/
    if ((mid == 0 || arr[mid - 1] < value) && (arr[mid] == value))
        return mid;
    else if (arr[mid] < value)
        return FirstIndex(arr, size, mid + 1, high, value);
    else
        return FirstIndex(arr, size, low, mid - 1, value);
    return -1;
}

int isMajority(int arr[], int size)
{
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

int findMissingNumber(int data[], int size)
{
    int found;
    for (int i = 1; i <= size; i++)
    {
        found = 0;
        for (int j = 0; j < size; j++)
        {
            if (data[j] == i)
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
    printf("NoNumberMissing");
}

int findMissingNumber2(int data[], int size, int range)
{
    int xorSum = 0;
    // get the XOR of all the numbers from 1 to range
    for (int i = 1; i <= range; i++)
    {
        xorSum ^= i;
    }
    // loop through the array and get the XOR of elements
    for (int i = 0; i < size; i++)
    {
        xorSum ^= data[i];
    }
    return xorSum;
}

int findMissingNumber3(int arr[], int size, int upperRange)
{
    Set st;
    SetInit(&st);
    int i = 0;
    while (i < size)
    {
        SetAdd(&st, arr[i]);
        i += 1;
    }
    i = 1;
    while (i <= upperRange)
    {
        if (SetFind(&st, i) == 0)
            return i;
        i += 1;
    }
    return -1;
}

void MissingValues(int arr[], int size)
{
    Sort(arr, size);
    int value = arr[0];
    int i = 0;
    printf("Missing Values are :: ");
    while (i < size)
    {
        if (value == arr[i])
        {
            value += 1;
            i += 1;
        }
        else
        {
            printf(" %d ", value);
            value += 1;
        }
    }
}

void MissingValues2(int arr[], int size)
{
    HashTable ht;
    HashInit(&ht);

    int minVal = 999999;
    int maxVal = -999999;

    for (int i = 0; i < size; i++)
    {
        HashAdd(&ht, arr[i]);
        if (minVal > arr[i])
            minVal = arr[i];
        if (maxVal < arr[i])
            maxVal = arr[i];
    }
    for (int i = minVal; i < maxVal + 1; i++)
    {
        if (HashFind(&ht, i) == 0)
            printf(" %d ", i);
    }
}

void OddCount(int arr[], int size)
{
    Counter ctr;
    CounterInit(&ctr);
    Set st;
    SetInit(&st);
    int count;

    for (int i = 0; i < size; i++)
    {
        CounterAdd(&ctr, arr[i]);
    }
    for (int i = 0; i < size; i++)
    {
        count = CounterGetCount(&ctr, arr[i]);
        if (count > 0 && (count % 2 == 1))
        {
            printf("%d", count);
            CounterDelete(&ctr, arr[i]);
        }
    }
}

void OddCount2(int arr[], int size)
{
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
    for (int i = 0; i < size; i++)
    {
        if (arr[i] & setBit)
            first = first ^ arr[i];
        else
            second = second ^ arr[i];
    }
    printf(" %d & %d ", first, second);
}

void SumDistinct(int arr[], int size)
{
    int sum = 0;
    Sort(arr, size);
    for (int i = 0; i < (size - 1); i++)
    {
        if (arr[i] != arr[i + 1])
            sum += arr[i];
    }
    sum += arr[size - 1];
    printf(" %d ", sum);
}

int FindPair(int data[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if ((data[i] + data[j]) == value)
            {
                printf("The pair is : %d , %d ", data[i], data[j]);
                return 1;
            }
        }
    }
    return 0;
}

int FindPair2(int data[], int size, int value)
{
    int first = 0, second = size - 1;
    int curr;
    Sort(data, size);
    while (first < second)
    {
        curr = data[first] + data[second];
        if (curr == value)
        {
            printf("The pair is %d , %d ", data[first], data[second]);
            return 1;
        }
        else if (curr < value)
            first++;
        else
            second--;
    }
    return 0;
}

int FindPair3(int data[], int size, int value)
{
    HashTable hs;
    HashInit(&hs);

    for (int i = 0; i < size; i++)
    {
        if (HashFind(&hs, value - data[i]))
        {
            printf("The pair is : %d , %d ", data[i], (value - data[i]));
            return 1;
        }
        HashAdd(&hs, data[i]);
    }
    return 0;
}

int FindDifference(int arr[], int size, int value)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (abs(arr[i] - arr[j]) == value)
                printf("The pair is:: %d & %d ", arr[i], arr[j]);
            return 1;
        }
    }
    return 0;
}

int FindDifference2(int arr[], int size, int value)
{
    int first = 0;
    int second = 0;
    int diff;
    Sort(arr, size);
    while (first < size && second < size)
    {
        diff = abs(arr[first] - arr[second]);
        if (diff == value)
        {
            printf("The pair is:: %d & %d ", arr[first], arr[second]);
            return 1;
        }
        else if (diff > value)
            first += 1;
        else
            second += 1;
    }
    return 0;
}

int findMinDiff(int arr[], int size)
{
    Sort(arr, size);
    int diff = 9999999;

    for (int i = 0; i < (size - 1); i++)
    {
        if ((arr[i + 1] - arr[i]) < diff)
            diff = arr[i + 1] - arr[i];
    }
    return diff;
}

int MinDiffPair(int arr1[], int size1, int arr2[], int size2)
{
    int minDiff = 9999999;
    int first = 0;
    int second = 0;
    int out1, out2, diff;
    Sort(arr1, size1);
    Sort(arr2, size2);
    while (first < size1 && second < size2)
    {
        diff = abs(arr1[first] - arr2[second]);
        if (minDiff > diff)
        {
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

void minabsSumPair(int data[], int size)
{
    int minSum, sum, minFirst, minSecond;

    // Array should have at least two elements
    if (size < 2)
    {
        printf("InvalidInput");
    }
    minFirst = 0;
    minSecond = 1;
    minSum = abs(data[0] + data[1]);
    for (int l = 0; l < size - 1; l++)
    {
        for (int r = l + 1; r < size; r++)
        {
            sum = abs(data[l] + data[r]);
            if (sum < minSum)
            {
                minSum = sum;
                minFirst = l;
                minSecond = r;
            }
        }
    }
    printf(" The two elements with minimum sum are : %d, %d ", data[minFirst], data[minSecond]);
}

void minabsSumPair2(int data[], int size)
{
    int minSum, sum, minFirst, minSecond;
    // Array should have at least two elements
    if (size < 2)
    {
        printf("InvalidInput");
    }
    Sort(data, size);

    // Initialization of values
    minFirst = 0;
    minSecond = size - 1;
    minSum = abs(data[minFirst] + data[minSecond]);
    for (int l = 0, r = size - 1; l < r;)
    {
        sum = (data[l] + data[r]);
        if (abs(sum) < minSum)
        {
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
    printf(" The two elements with minimum sum are : %d , %d ", data[minFirst], data[minSecond]);
}

void ClosestPair(int arr[], int size, int value)
{
    int diff = 999999;
    int first = -1;
    int second = -1;
    int curr;
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            curr = abs(value - (arr[i] + arr[j]));
            if (curr < diff)
            {
                diff = curr;
                first = arr[i];
                second = arr[j];
            }
        }
    }
    printf("closest pair is :: %d, %d ", first, second);
}

void ClosestPair2(int arr[], int size, int value)
{
    int first = 0, second = 0;
    int start = 0;
    int stop = size - 1;
    int diff, curr;
    Sort(arr, size);
    diff = 9999999;
    {
        while (start < stop)
        {
            curr = (value - (arr[start] + arr[stop]));
            if (abs(curr) < diff)
            {
                diff = abs(curr);
                first = arr[start];
                second = arr[stop];
            }
            if (curr == 0)
            {
                break;
            }
            else if (curr > 0)
            {
                start += 1;
            }
            else
            {
                stop -= 1;
            }
        }
    }
    printf("closest pair is :: %d, %d \n", first, second);
}

int SumPairRestArray(int arr[], int size)
{
    int total, low, high, curr, value;
    Sort(arr, size);
    total = 0;
    for (int i = 0; i < size; i++)
        total += arr[i];
    value = total / 2;
    low = 0;
    high = size - 1;
    while (low < high)
    {
        curr = arr[low] + arr[high];
        if (curr == value)
        {
            printf("Pair is :: %d, %d", arr[low], arr[high]);
            return 1;
        }
        else if (curr < value)
            low += 1;
        else
            high -= 1;
    }
    return 0;
}

void ZeroSumTriplets(int arr[], int size)
{
    for (int i = 0; i < (size - 2); i++)
    {
        for (int j = i + 1; j < (size - 1); j++)
        {
            for (int k = j + 1; k < size; k++)
            {
                if (arr[i] + arr[j] + arr[k] == 0)
                    printf("Triplet :: %d, %d, %d \n", arr[i], arr[j], arr[k]);
            }
        }
    }
}

void ZeroSumTriplets2(int arr[], int size)
{
    int start, stop, i;
    Sort(arr, size);
    for (i = 0; i < (size - 2); i++)
    {
        start = i + 1;
        stop = size - 1;

        while (start < stop)
        {
            if (arr[i] + arr[start] + arr[stop] == 0)
            {
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

void findTriplet(int arr[], int size, int value)
{
    for (int i = 0; i < (size - 2); i++)
        for (int j = i + 1; j < (size - 1); j++)
            for (int k = j + 1; k < size; k++)
            {
                if ((arr[i] + arr[j] + arr[k]) == value)
                    printf("Triplet :: %d, %d, %d", arr[i], arr[j], arr[k]);
            }
}

void findTriplet2(int arr[], int size, int value)
{
    int start, stop;
    Sort(arr, size);
    for (int i = 0; i < size - 2; i++)
    {
        start = i + 1;
        stop = size - 1;
        while (start < stop)
        {
            if (arr[i] + arr[start] + arr[stop] == value)
            {
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

void ABCTriplet(int arr[], int size)
{
    int start, stop;
    Sort(arr, size);
    for (int i = 0; i < (size - 2); i++)
    {
        start = i + 1;
        stop = size - 1;
        while (start < stop)
        {
            if (arr[i] == arr[start] + arr[stop])
            {
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

void SmallerThenTripletCount(int arr[], int size, int value)
{
    int start, stop;
    int count = 0;
    Sort(arr, size);

    for (int i = 0; i < (size - 2); i++)
    {
        start = i + 1;
        stop = size - 1;
        while (start < stop)
        {
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

void APTriplets(int arr[], int size)
{
    int i, j, k;
    for (i = 1; i < size - 1; i++)
    {
        j = i - 1;
        k = i + 1;
        while (j >= 0 && k < size)
        {
            if (arr[j] + arr[k] == 2 * arr[i])
            {
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

void GPTriplets(int arr[], int size)
{
    int i, j, k;
    for (i = 1; i < size - 1; i++)
    {
        j = i - 1;
        k = i + 1;
        while (j >= 0 && k < size)
        {
            if (arr[j] * arr[k] == arr[i] * arr[i])
            {
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

int numberOfTriangles(int arr[], int size)
{
    int i, j, k, count = 0;

    for (i = 0; i < (size - 2); i++)
    {
        for (j = i + 1; j < (size - 1); j++)
        {
            for (k = j + 1; k < size; k++)
            {
                if (arr[i] + arr[j] > arr[k])
                    count += 1;
            }
        }
    }
    return count;
}
int numberOfTriangles2(int arr[], int size)
{
    int i, j, k, count = 0;
    Sort(arr, size);

    for (i = 0; i < (size - 2); i++)
    {
        k = i + 2;
        for (j = i + 1; j < (size - 1); j++)
        {
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

int SearchBotinicArrayMax(int data[], int size)
{
    int start = 0, end = size - 1;
    int mid = (start + end) / 2;
    int maximaFound = 0;
    if (size < 3)
    {
        printf("InvalidInput");
    }
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (data[mid - 1] < data[mid] && data[mid + 1] < data[mid]) // maxima
        {
            maximaFound = 1;
            break;
        }
        else if (data[mid - 1] < data[mid] && data[mid] < data[mid + 1]) // increasing
            start = mid + 1;
        else if (data[mid - 1] > data[mid] && data[mid] > data[mid + 1]) // decreasing
            end = mid - 1;
        else
            break;
    }

    if (maximaFound == 0)
    {
        printf("NoMaximaFound");
        return 0;
    }

    return data[mid];
}

int FindMaxBitonicArray(int data[], int size)
{
    int start = 0, end = size - 1, mid;
    if (size < 3)
    {
        printf("InvalidInput");
    }
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (data[mid - 1] < data[mid] && data[mid + 1] < data[mid]) // maxima
            return mid;
        else if (data[mid - 1] < data[mid] && data[mid] < data[mid + 1]) // increasing
            start = mid + 1;
        else if (data[mid - 1] > data[mid] && data[mid] > data[mid + 1]) // decreasing
            end = mid - 1;
        else
            break;
    }
    printf("Maxima not found");
    return -1;
}

int BinarySearch(int data[], int start, int end, int key, int isInc)
{
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == data[mid])
        return mid;

    if (isInc != 0 && key < data[mid] || isInc == 0 && key > data[mid])
        return BinarySearch(data, start, mid - 1, key, isInc);
    else
        return BinarySearch(data, mid + 1, end, key, isInc);
}

int SearchBitonicArray(int data[], int size, int key)
{
    int max = FindMaxBitonicArray(data, size);
    int k = BinarySearch(data, 0, max, key, 1);
    if (k != -1)
        return k;
    else
        return BinarySearch(data, max + 1, size - 1, key, 0);
}

int findKeyCount(int data[], int size, int key)
{
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (data[i] == key)
            count++;
    }
    return count;
}

int findFirstIndex(int data[], int size, int start, int end, int key)
{
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == data[mid] && (mid == start || data[mid - 1] != key))
        return mid;

    if (key <= data[mid]) // <= is us the number.t in sorted array.
        return findFirstIndex(data, size, start, mid - 1, key);
    else
        return findFirstIndex(data, size, mid + 1, end, key);
}

int findLastIndex(int data[], int size, int start, int end, int key)
{
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == data[mid] && (mid == end || data[mid + 1] != key))
        return mid;

    if (key < data[mid])
        return findLastIndex(data, size, start, mid - 1, key);
    else
        return findLastIndex(data, size, mid + 1, end, key);
}

int findKeyCount2(int data[], int size, int key)
{
    int firstIndex, lastIndex;
    firstIndex = findFirstIndex(data, size, 0, size - 1, key);
    lastIndex = findLastIndex(data, size, 0, size - 1, key);
    return (lastIndex - firstIndex + 1);
}

void swap(int data[], int first, int second)
{
    int temp = data[first];
    data[first] = data[second];
    data[second] = temp;
}

void seperateEvenAndOdd(int data[], int size)
{
    int left = 0, right = size - 1;
    while (left < right)
    {
        if (data[left] % 2 == 0)
            left++;
        else if (data[right] % 2 == 1)
            right--;
        else
        {
            swap(data, left, right);
            left++;
            right--;
        }
    }
}

void maxProfit(int stocks[], int size)
{
    int buy = 0, sell = 0;
    int curMin = 0;
    int currProfit = 0;
    int maxProfit = 0;

    for (int i = 0; i < size; i++)
    {
        if (stocks[i] < stocks[curMin])
            curMin = i;

        currProfit = stocks[i] - stocks[curMin];
        if (currProfit > maxProfit)
        {
            buy = curMin;
            sell = i;
            maxProfit = currProfit;
        }
    }
    printf("Purchase day is:: %d at price:: %d \n", buy, stocks[buy]);
    printf("Sell day is:: %d at price:: %d \n", sell, stocks[sell]);
}

int getMedian(int data[], int size)
{
    Sort(data, size);
    return data[size / 2];
}

int findMedian(int dataFirst[], int sizeFirst, int dataSecond[], int sizeSecond)
{
    int medianIndex = ((sizeFirst + sizeSecond) + (sizeFirst + sizeSecond) % 2) / 2; // cealing function.
    int i = 0, j = 0;
    int count = 0;
    while (count < medianIndex - 1)
    {
        if (i < sizeFirst - 1 && dataFirst[i] < dataSecond[j])
        {
            i++;
        }
        else
        {
            j++;
        }
        count++;
    }
    if (dataFirst[i] < dataSecond[j])
    {
        return dataFirst[i];
    }
    else
    {
        return dataSecond[j];
    }
}

int min(int a, int b)
{
    return a > b ? b : a;
}

int max(int a, int b)
{
    return a < b ? b : a;
}

int BinarySearch01Util(int data[], int start, int end)
{
    int mid;
    if (end < start)
    {
        return -1;
    }
    mid = (start + end) / 2;
    if (1 == data[mid] && 0 == data[mid - 1])
    {
        return mid;
    }
    if (0 == data[mid])
    {
        return BinarySearch01Util(data, mid + 1, end);
    }
    else
    {
        return BinarySearch01Util(data, start, mid - 1);
    }
}

int BinarySearch01(int data[], int size)
{
    if (size == 1 && data[0] == 1)
    {
        return 0;
    }
    return BinarySearch01Util(data, 0, size - 1);
}
int RotationMaxUtil(int arr[], int start, int end)
{
    int mid;
    if (end <= start)
    {
        return arr[start];
    }
    mid = (start + end) / 2;
    if (arr[mid] > arr[mid + 1])
        return arr[mid];

    if (arr[start] <= arr[mid]) /* increasing part.*/
        return RotationMaxUtil(arr, mid + 1, end);
    else
        return RotationMaxUtil(arr, start, mid - 1);
}

int RotationMax(int arr[], int size)
{
    return RotationMaxUtil(arr, 0, size - 1);
}

/* Testing Code
first = [34, 56, 1, 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 ]
second = [1, 5, 6,6,6,6,6,6,7,8,10, 13, 20, 30 ]
print(RotationMax(first))
print(RotationMax(second))
*/

int FindRotationMaxUtil(int arr[], int start, int end)
{
    /* single element case.*/
    int mid;
    if (end <= start)
        return start;

    mid = (start + end) / 2;
    if (arr[mid] > arr[mid + 1])
        return mid;

    if (arr[start] <= arr[mid]) /* increasing part.*/
        return FindRotationMaxUtil(arr, mid + 1, end);
    else
        return FindRotationMaxUtil(arr, start, mid - 1);
}

int FindRotationMax(int arr[], int size)
{
    return FindRotationMaxUtil(arr, 0, size - 1);
}

/* Testing Code
first = [34, 56, 1, 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 ]
second = [1, 5, 6,6,6,6,6,6,7,8,10, 13, 20, 30 ]
print(FindRotationMax(first))
print(FindRotationMax(second))
*/

int CountRotation(int arr[], int size)
{
    int maxIndex = FindRotationMaxUtil(arr, 0, size - 1);
    return (maxIndex + 1) % size;
}
/* Testing Code
first = [34, 56, 1, 1, 5, 6, 6, 6, 6, 6, 6, 7, 8, 10, 13, 20, 30 ]
second = [1, 5, 6,6,6,6,6,6,7,8,10, 13, 20, 30 ]
print(CountRotation(first))
print(CountRotation(second))
*/

int BinarySearchRotateArrayUtil(int data[], int start, int end, int key)
{
    int mid;
    if (end < start)
        return -1;

    mid = (start + end) / 2;
    if (key == data[mid])
        return mid;

    if (data[mid] > data[start])
    {
        if (data[start] <= key && key < data[mid])
        {
            return BinarySearchRotateArrayUtil(data, start, mid - 1, key);
        }
        else
        {
            return BinarySearchRotateArrayUtil(data, mid + 1, end, key);
        }
    }
    else
    {
        if (data[mid] < key && key <= data[end])
        {
            return BinarySearchRotateArrayUtil(data, mid + 1, end, key);
        }
        else
        {
            return BinarySearchRotateArrayUtil(data, start, mid - 1, key);
        }
    }
}

int BinarySearchRotateArray(int data[], int size, int key)
{
    return BinarySearchRotateArrayUtil(data, 0, size - 1, key);
}

int minAbsDiffAdjCircular(int arr[], int size)
{
    int diff = 9999999;
    if (size < 2)
        return -1;

    for (int i = 0; i < size; i++)
        diff = min(diff, abs(arr[i] - arr[(i + 1) % size]));

    return diff;
}
/* Testing code
arr = [5, 29, 18, 51, 11]
print minAbsDiffAdjCircular(arr)
*/

void transformArrayAB1(int data[], int size)
{
    int N = size / 2;
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < i; j++)
            swap(data, N - i + 2 * j, N - i + 2 * j + 1);
    }
}

int checkPermutation(int data1[], int size1, int data2[], int size2)
{
    if (size1 != size2)
        return 0;

    Sort(data1, size1);
    Sort(data2, size2);

    for (int i = 0; i < size1; i++)
    {
        if (data1[i] != data2[i])
            return 0;
    }
    return 1;
}

int checkPermutation2(int array1[], int size1, int array2[], int size2)
{
    int i;
    if (size1 != size2)
        return 0;
    HashTable hs;
    HashInit(&hs);

    for (i = 0; i < size1; i++)
        HashAdd(&hs, array1[i]);

    for (i = 0; i < size2; i++)
    {
        if (!HashFind(&hs, array2[i]))
            return 0;
    }
    return 1;
}
////////////////////

int FindElementIn2DArray(int **arr, int r, int c, int value)
{
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

int isAP(int arr[], int size)
{
    int diff;
    if (size <= 1)
        return 1;

    Sort(arr, size);
    diff = arr[1] - arr[0];
    for (int i = 2; i < size; i++)
    {
        if (arr[i] - arr[i - 1] != diff)
            return 0;
    }
    return 1;
}

int isAP2(int arr[], int size)
{
    int first = 9999999;
    int second = 9999999;
    int diff, value;
    HashTable hs;
    HashInit(&hs);
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < first)
        {
            second = first;
            first = arr[i];
        }
        else if (arr[i] < second)
            second = arr[i];
    }
    diff = second - first;

    for (int i = 0; i < size; i++)
    {
        if (HashFind(&hs, arr[i]))
            return 0;
        HashAdd(&hs, arr[i]);
    }
    for (int i = 0; i < size; i++)
    {
        value = first + i * diff;
        if (!HashFind(&hs, value) || HashGet(&hs, value) != 1)
            return 0;
    }
    return 1;
}

int isAP3(int arr[], int size)
{
    int first = 9999999;
    int second = 9999999;
    int *count = (int *)calloc(0, size);
    int diff, index;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] < first)
        {
            second = first;
            first = arr[i];
        }
        else if (arr[i] < second)
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

int findBalancedPoint(int arr[], int size)
{
    int first = 0;
    int second = 0;
    for (int i = 1; i < size; i++)
        second += arr[i];

    for (int i = 0; i < size; i++)
    {
        if (first == second)
            printf("%d", i);
        if (i < size - 1)
            first += arr[i];
        second -= arr[i + 1];
    }
}

/* Testing code
arr = [-7, 1, 5, 2, -4, 3, 0]
findBalancedPoint(arr)
*/

int findFloor(int arr[], int size, int value)
{
    int start = 0;
    int stop = size - 1;
    int mid;
    while (start <= stop)
    {
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

int findCeil(int arr[], int size, int value)
{
    int start = 0;
    int stop = size - 1;
    int mid;

    while (start <= stop)
    {
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

int ClosestNumber(int arr[], int size, int num)
{
    int start = 0;
    int stop = size - 1;
    int output = -1;
    int minDist = 9999;
    int mid;

    while (start <= stop)
    {
        mid = (start + stop) / 2;
        if (minDist > abs(arr[mid] - num))
        {
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

int DuplicateKDistance(int arr[], int size, int k)
{
    HashTable hs;
    for (int i = 0; i < size; i++)
    {
        if (HashFind(&hs, arr[i]) && i - HashGet(&hs, arr[i]) <= k)
        {
            printf("%d, %d, %d", arr[i], HashGet(&hs, arr[i]), i);
            return 1;
        }
        else
            HashAdd2(&hs, arr[i], i);
    }
    return 0;
}
/* Testing code
arr = [1, 2, 3, 1, 4, 5]
DuplicateKDistance(arr, 3)
*/

int frequencyCounts(int arr[], int size)
{
    int index;
    for (int i = 0; i < size; i++)
    {
        while (arr[i] > 0)
        {
            index = arr[i] - 1;
            if (arr[index] > 0)
            {
                arr[i] = arr[index];
                arr[index] = -1;
            }
            else
            {
                arr[index] -= 1;
                arr[i] = 0;
            }
        }
    }
    for (int i = 0; i < size; i++)
        printf("%d : %d \n", i + 1, abs(arr[i]));
}

int KLargestElements(int arrIn[], int size, int k)
{
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = arrIn[i];

    Sort(arr, size);
    for (int i = 0; i < size; i++)
    {
        if (arrIn[i] >= arr[size - k])
            printf(" %d ", arrIn[i]);
    }
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
    if (k < upper)
        QuickSelectUtil(arr, start, upper - 1, k); //pivot -1 is the upper for left sub array.
    if (k > upper)
        QuickSelectUtil(arr, upper + 1, stop, k); // pivot + 1 is the lower for right sub array.
}

int KLargestElements2(int arrIn[], int size, int k)
{
    int *arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++)
        arr[i] = arrIn[i];

    QuickSelectUtil(arr, 0, size - 1, size - k);
    for (int i = 0; i < size; i++)
    {
        if (arrIn[i] >= arr[size - k])
            printf("%d", arrIn[i]);
    }
}

/* linear search method */
int FixPoint(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == i)
            return i;
    } /* fix point not found so return invalid index */
    return -1;
}

/* Binary search method */
int FixPoint2(int arr[], int size)
{
    int low = 0;
    int high = size - 1;
    int mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == mid)
            return mid;
        else if (arr[mid] < mid)
            low = mid + 1;
        else
            high = mid - 1;
    }
    /* fix point not found so return invalid index */
    return -1;
}

int subArraySums(int arr[], int size, int value)
{
    int first = 0;
    int second = 0;
    int sum = arr[first];
    while (second < size && first < size)
    {
        if (sum == value)
            printf("%d , %d ", first, second);

        if (sum < value)
        {
            second += 1;
            if (second < size)
                sum += arr[second];
        }
        else
        {
            sum -= arr[first];
            first += 1;
        }
    }
}

int MaxConSub(int arr[], int size)
{
    int currMax = 0;
    int maximum = 0;
    for (int i = 0; i < size; i++)
    {
        currMax = max(arr[i], currMax + arr[i]);
        if (currMax < 0)
            currMax = 0;
        if (maximum < currMax)
            maximum = currMax;
    }
    printf(" %d ", maximum);
}

int MaxConSubArr(int A[], int sizeA, int B[], int sizeB)
{
    int currMax = 0;
    int maximum = 0;
    HashTable hs;
    HashInit(&hs);

    for (int i = 0; i < sizeB; i++)
        HashAdd(&hs, B[i]);

    for (int i = 0; i < sizeA; i++)
        if (HashFind(&hs, A[i]))
            currMax = 0;
        else
            currMax = max(A[i], currMax + A[i]);
    if (currMax < 0)
        currMax = 0;
    if (maximum < currMax)
        maximum = currMax;
    printf(" %d ", maximum);
}

int MaxConSubArr2(int A[], int sizeA, int B[], int sizeB)
{
    Sort(B, sizeB);
    int currMax = 0;
    int maximum = 0;

    for (int i = 0; i < sizeA; i++)
    {
        if (Binarysearch(B, sizeB, A[i]))
            currMax = 0;
        else
        {
            currMax = max(A[i], currMax + A[i]);
            if (currMax < 0)
                currMax = 0;
            if (maximum < currMax)
                maximum = currMax;
        }
    }
    printf(" %d ", maximum);
}

int RainWater(int arr[], int size)
{
    int water = 0;
    int *leftHigh = (int *)calloc(size, sizeof(int));
    int *rightHigh = (int *)calloc(size, sizeof(int));
    int max = arr[0];
    leftHigh[0] = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
        leftHigh[i] = max;
    }
    max = arr[size - 1];
    rightHigh[size - 1] = arr[size - 1];
    for (int i = (size - 2); i >= 0; i--)
    {
        if (max < arr[i])
            max = arr[i];
        rightHigh[i] = max;
    }

    for (int i = 0; i < size; i++)
        water += min(leftHigh[i], rightHigh[i]) - arr[i];
    printf("Water : %d ", water);
}

int RainWater2(int arr[], int size)
{
    int water = 0;
    int leftMax = 0, rightMax = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        if (arr[left] < arr[right])
        {
            if (arr[left] > leftMax)
                leftMax = arr[left];
            else
                water += leftMax - arr[left];
            left += 1;
        }
        else
        {
            if (arr[right] > rightMax)
                rightMax = arr[right];
            else
                water += rightMax - arr[right];
            right -= 1;
        }
    }
    printf("Water : %d ", water);
}
/*
int SubArrayZeroOneEqual(int arr[], int size)
{
    int maxLength = -1;
    int start = -1, stop = -1;
    int sum = 0;
    int currLength;
    HashTable hs;
    HashInit(&hs);

    HashAdd(&hs, 0, -1);
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 1)
            sum += 1;
        else
            sum -= 1;

        if (HashFind(&hs, sum))
        {
            currLength = i - HashGet(&hs, sum);
            if (currLength > maxLength)
                maxLength = currLength;
            start = HashGet(&hs, sum);
            stop = i;
        }
        else
            HashAdd(&hs, sum, i);
    }
    printf("%d %d %d", start + 1, stop, maxLength);
}

Testing code
arr = [0, 0, 0, 1, 0, 1, 0]
SubArrayZeroOneEqual(arr)
*/