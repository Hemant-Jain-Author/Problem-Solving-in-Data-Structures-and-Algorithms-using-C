#include <stdio.h>
#include <stdlib.h>

/* Dummy function and structure  start*/
typedef struct HT {
    int i;
}HashTable;

void HashAdd(HashTable hs, int value){

}

int HashFind(HashTable hs, int value){
    return 1;
}

void HashRemove(HashTable hs, int value){

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
		{
			return 1;
		}
		else if (value < data[i])
		{
			return 0;
		}
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
	{
		return 0;
	}
	int mid = (low + high) / 2;
	if (data[mid] == value)
	{
		return 1;
	}
	else if (data[mid] < value)
	{
		return BinarySearchRecursive(data, size,  mid + 1, high, value);
	}
	else
	{
		return BinarySearchRecursive(data, size, low, mid - 1, value);
	}
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
	
	printf(" Repeating elements are : ");
	for (int i = 0; i < size; i++)
	{
		if (HashFind(hs, data[i]))
			printf(" %d " , data[i]);
		else
			HashAdd(hs, data[i]);
	}
}

void printRepeating4(int data[], int size)
{
	int* count = (int*)malloc(sizeof(int)*size);
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
	Sort(data,size);
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
	
	int* count = (int*)malloc(sizeof(int)*range);
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
		printf("MajorityDoesNotExist");
}

int getMajority2(int data[], int size)
{
	int majIndex = size / 2, count = 1;
	int candidate;
	Sort(data,size);
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
		printf("MajorityDoesNotExist");
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
		printf("MajorityDoesNotExist");
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

int FindPair(int data[], int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if ((data[i] + data[j]) == value)
			{
				printf("The pair is : %d , %d " , data[i] , data[j] );
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
			printf("The pair is %d , %d " , data[first] , data[second] );
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
	int i;
	
	for (i = 0; i < size; i++)
	{
		if (HashFind(hs, value - data[i]))
		{
			printf("The pair is : %d , %d " , data[i] , (value - data[i]));
			return 1;
		}
		HashAdd(hs, data[i]);
	}
	return 0;
}

void minabsSumPair(int data[], int size)
{
	int minSum, sum, minFirst, minSecond;
	
	// Array should have at least two elements
	if (size < 2)
	{
		printf("InvalidInput");
	}
	// Initialization of values
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
	printf(" The two elements with minimum sum are : %d, %d " , data[minFirst] , data[minSecond] );
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
	printf(" The two elements with minimum sum are : %d , %d " , data[minFirst] , data[minSecond] );
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
		printf("NoMaximaFound");

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
		{
			return mid;
		}
		else if (data[mid - 1] < data[mid] && data[mid] < data[mid + 1]) // increasing
		{
			start = mid + 1;
		}
		else if (data[mid - 1] > data[mid] && data[mid] > data[mid + 1]) // decreasing
		{
			end = mid - 1;
		}
		else
		{
			break;
		}
	}
	printf("error" );
	return -1;
}

int BinarySearch(int data[], int size, int start, int end, int key, int isInc)
{
	int mid;
	if (end < start)
	{
		return -1;
	}
	mid = (start + end) / 2;
	if (key == data[mid])
	{
		return mid;
	}
	if (isInc != 0 && key < data[mid] || isInc == 0 && key > data[mid])
	{
		return BinarySearch(data, size, start, mid - 1, key, isInc);
	}
	else
	{
		return BinarySearch(data, size, mid + 1, end, key, isInc);
	}
}

int SearchBitonicArray(int data[], int size, int key)
{
	int max = FindMaxBitonicArray(data, size);
	int k = BinarySearch(data, size, 0, max, key, 1);
	if (k != -1)
	{
		return k;
	}
	else
	{
		return BinarySearch(data, size, max + 1, size - 1, key, 0);
	}
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
	printf("Purchase day is:: %d at price:: %d \n" , buy , stocks[buy] );
	printf("Sell day is:: %d at price:: %d \n" , sell , stocks[sell] );
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

int BinarySearchRotateArrayUtil(int data[], int start, int end, int key)
{
	int mid;
	if (end < start)
	{
		return -1;
	}
	mid = (start + end) / 2;
	if (key == data[mid])
	{
		return mid;
	}
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

int BinarySearch01(int data[], int size)
{
	if (size == 1 && data[0] == 1)
	{
		return 0;
	}
	return BinarySearch01Util(data, 0, size - 1);
}

int BinarySearchRotateArray(int data[], int size, int key)
{
	return BinarySearchRotateArrayUtil(data, 0, size - 1, key);
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
	HashTable h;

	for (i = 0; i < size1; i++)
		HashAdd(h, array1[i]);

	for (i = 0; i < size2; i++) 
	{
		if (!HashFind(h, array2[i]))
			return 0;
	}
	return 1;
}

int removeDuplicates(int data[], int size)
{
	int j = 0;
	if (size == 0)
		return 0;

	Sort(data,size);
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
		printf("Index %d :: Value %d \n" , i , removeDuplicates(first, sizeof(first)/ sizeof(int)));
	}
	return 0;
}