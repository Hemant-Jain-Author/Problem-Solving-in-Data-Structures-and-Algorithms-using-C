#include "Queue.c"

int main1() {
    Queue* queue = createQueue();
    queueAdd(queue, 1);
    queueAdd(queue, 2);
    queueAdd(queue, 3);
	queuePrint(queue);
    while(!queueIsEmpty(queue))
        printf("%d ", queueRemove(queue));
    printf("\n");
	return 0;
}

/*
[ 1 2 3 ]
1 2 3 
*/

void printArray(int *arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("]\n");
}

int CircularTour(int arr[][2], int n) {
	Queue* que = createQueue();
	int nextPump = 0, prevPump;
	int count = 0;
	int petrol = 0;

	while (queueSize(que) != n) {
		while (petrol >= 0 && queueSize(que) != n) {
			queueAdd(que, nextPump);
			petrol += (arr[nextPump][0] - arr[nextPump][1]);
			nextPump = (nextPump + 1) % n;
		}
		while (petrol < 0 && queueSize(que) > 0) {
			prevPump = queueRemove(que);
			petrol -= (arr[prevPump][0] - arr[prevPump][1]);
		}
		count += 1;
		if (count == n)
			return -1;
	}
	if (petrol >= 0)
		return queueRemove(que);
	else
		return -1;
}

int main2() {
	// Testing code
	int tour[3][2] = { { 8, 6 },{ 1, 4 },{ 7, 6 } };
	printf("Circular Tour : %d\n", CircularTour(tour, 3));
	return 0;
}

/*
Circular Tour : 2 
*/

int convertXY(int src, int dst) {
	int arr[100];
	int steps = 0;
	int index = 0;
	int value;
	Queue* que = createQueue();	
	queueAdd(que, src);
	while (queueSize(que) != 0) {
		value = queueRemove(que);
		arr[index++] = value;

		if (value == dst) {
			//printArray(arr, index);
			return steps;
		}
		steps++;
		if (value < dst)
			queueAdd(que, value * 2);
		else
			queueAdd(que, value - 1);
	}
	return -1;
}

int main3() {
	printf("steps : %d\n", convertXY(2, 7));
	return 0;
}

/*
steps : 3 
*/

void maxSlidingWindows(int arr[], int size, int k) {
	Queue* que = createQueue();
	for (int i = 0; i < size; i++) {
		//Remove out of range elements
		if (queueSize(que) && queueFront(que) <= i - k)
			queueRemove(que);
		//Remove smaller values at left.
		while (queueSize(que) && arr[queueBack(que)] <= arr[i])
			queueRemoveBack(que);

		queueAdd(que, i);
		//Largest value in window of size k is at index que[0]
		//It is displayed to the screen.
		if (i >= (k - 1))
			printf("%d ", arr[queueFront(que)]);
	}
	printf("\n");
}

int main4() {
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxSlidingWindows(arr, 7, 3);
	return 0;
}

/*
75 92 92 92 90 
*/

int minOfMaxSlidingWindows(int arr[], int size, int k) {
	Queue* que = createQueue();
	int minVal = 999999;
	for (int i = 0; i < size; i++) {
		//Remove out of range elements 
		if (queueSize(que) && queueFront(que) <= i - k)
			queueRemove(que);
		//Remove smaller values at left.
		while (queueSize(que) && arr[queueBack(que)] <= arr[i])
			queueRemove(que);
		queueAdd(que, i);
		//window of size k
		if (i >= (k - 1) && minVal > arr[queueFront(que)])
			minVal = arr[queueFront(que)];
	}
	printf("Min of max is :: %d\n", minVal);
	return minVal;
}

int main5() {
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	minOfMaxSlidingWindows(arr, 7, 3);
	return 0;
}

/*
Min of max is :: 75 
*/

void maxOfMinSlidingWindows(int arr[], int size, int k) {
	Queue* que = createQueue();
	int maxVal = -999999;
	for (int i = 0; i < size; i++) {
		//Remove out of range elements 
		if (queueSize(que) && queueFront(que) <= i - k)
			queueRemove(que);
		//Remove smaller values at left.
		while (queueSize(que) && arr[queueBack(que)] >= arr[i])
			queueRemove(que);
		queueAdd(que, i);
		//window of size k
		if (i >= (k - 1) && maxVal < arr[queueFront(que)])
			maxVal = arr[queueFront(que)];
	}
	printf("Max of min is :: %d\n", maxVal);
}

int main6() {
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxOfMinSlidingWindows(arr, 7, 3);
	return 0;
	//Output  59, as minimum values in sliding windows are [2, 2, 59, 59, 55]
}

/*
Max of min is :: 59 
*/

void firstNegSlidingWindows(int arr[], int size, int k) {
	Queue* que = createQueue();
	for (int i = 0; i < size; i++) {
		//Remove out of range elements 
		if (queueSize(que) && queueFront(que) <= i - k)
			queueRemove(que);
		if (arr[i] < 0)
			queueAdd(que, i);
		//window of size k
		if (i >= (k - 1)) {
			if (queueSize(que) > 0)
				printf("%d ", arr[queueFront(que)]);
			else
				printf("NAN");
		}
	}
	printf("\n");
}

int main7() {
	int arr[] = { 3, -2, -6, 10, -14, 50, 14, 21 };
	int k = 3;
	firstNegSlidingWindows(arr, 8, 3);
	return 0;
}

/*
-2 -2 -6 -14 -14 NAN
*/

int main(){
	main1();	
	main2();
	main3();
	main4();
	main5();
	main6();
	main7();
	return 0;	
}