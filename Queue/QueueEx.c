#include "Queue.c"

int main1() {
    Queue* queue = createQueue();
    QueueAdd(queue, 1);
    QueueAdd(queue, 2);
    QueueAdd(queue, 3);
    printf("%d ", QueueRemove(queue));
    printf("%d ", QueueRemove(queue));
    printf("%d ", QueueRemove(queue));
	printf("\n");
	return 0;
}

/*
1 2 3 
*/

void printArray(int *arr, int size) {
	printf("[ ");
	for (int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("]\n");
}

int CircularTour(int arr[][2], int n) {
	for(int i=0;i<n;i++){
		int total = 0;
		int found = 1;
		for(int j=0;j<n;j++){
			total += (arr[(i+j)%n][0] - arr[(i+j)%n][1]);
			if(total < 0){
				found = 0;
				break;
			}
		}
		if(found)
			return i;
	}
	return -1;
}

int CircularTour2(int arr[][2], int n) {
	Queue* que = createQueue();
	int nextPump = 0, prevPump;
	int count = 0;
	int petrol = 0;

	while (QueueSize(que) != n) {
		while (petrol >= 0 && QueueSize(que) != n) {
			QueueAdd(que, nextPump);
			petrol += (arr[nextPump][0] - arr[nextPump][1]);
			nextPump = (nextPump + 1) % n;
		}
		while (petrol < 0 && QueueSize(que) > 0) {
			prevPump = QueueRemove(que);
			petrol -= (arr[prevPump][0] - arr[prevPump][1]);
		}
		count += 1;
		if (count == n)
			return -1;
	}
	if (petrol >= 0)
		return QueueRemove(que);
	else
		return -1;
}

// Testing code
int main2() {
	int tour[3][2] = { { 8, 6 },{ 1, 4 },{ 7, 6 } };
	printf("Circular Tour : %d\n", CircularTour(tour, 3));
	printf("Circular Tour : %d\n", CircularTour2(tour, 3));
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
	QueueAdd(que, src);
	while (QueueSize(que) != 0) {
		value = QueueRemove(que);
		arr[index++] = value;

		if (value == dst) {
			//printArray(arr, index);
			return steps;
		}
		steps++;
		if (value < dst)
			QueueAdd(que, value * 2);
		else
			QueueAdd(que, value - 1);
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

int max(int a, int b) {
    return a < b ? b : a;
}

void maxSlidingWindows(int arr[], int size, int k) {
	for(int i=0;i<size-k+1;i++) {
		int maxVal = arr[i];
		for(int j=1;j<k;j++) {
			maxVal = max(maxVal, arr[i+j]);
		}
		printf("%d ", maxVal);
	}
	printf("\n");
}

void maxSlidingWindows2(int arr[], int size, int k) {
	Queue* que = createQueue();
	for (int i = 0; i < size; i++) {
		//Remove out of range elements
		if (QueueSize(que) && QueueFront(que) <= i - k)
			QueueRemove(que);
		//Remove smaller values at left.
		while (QueueSize(que) && arr[QueueBack(que)] <= arr[i])
			QueueRemoveBack(que);

		QueueAdd(que, i);
		//Largest value in window of size k is at index que[0]
		//It is displayed to the screen.
		if (i >= (k - 1))
			printf("%d ", arr[QueueFront(que)]);
	}
	printf("\n");
}

int main4() {
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxSlidingWindows(arr, 7, 3);
	maxSlidingWindows2(arr, 7, 3);
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
		if (QueueSize(que) && QueueFront(que) <= i - k)
			QueueRemove(que);
		//Remove smaller values at left.
		while (QueueSize(que) && arr[QueueBack(que)] <= arr[i])
			QueueRemove(que);
		QueueAdd(que, i);
		//window of size k
		if (i >= (k - 1) && minVal > arr[QueueFront(que)])
			minVal = arr[QueueFront(que)];
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
		if (QueueSize(que) && QueueFront(que) <= i - k)
			QueueRemove(que);
		//Remove smaller values at left.
		while (QueueSize(que) && arr[QueueBack(que)] >= arr[i])
			QueueRemove(que);
		QueueAdd(que, i);
		//window of size k
		if (i >= (k - 1) && maxVal < arr[QueueFront(que)])
			maxVal = arr[QueueFront(que)];
	}
	printf("Max of min is :: %d\n", maxVal);
}

int main6() {
	int arr[] = { 11, 2, 75, 92, 59, 90, 55 };
	int k = 3;
	maxOfMinSlidingWindows(arr, 7, 3);
	return 0;
}
//Output  59, as minimum values in sliding windows are [2, 2, 59, 59, 55]
/*
Max of min is :: 59 
*/

void firstNegSlidingWindows(int arr[], int size, int k) {
	Queue* que = createQueue();
	for (int i = 0; i < size; i++) {
		//Remove out of range elements 
		if (QueueSize(que) && QueueFront(que) <= i - k)
			QueueRemove(que);
		if (arr[i] < 0)
			QueueAdd(que, i);
		//window of size k
		if (i >= (k - 1)) {
			if (QueueSize(que) > 0)
				printf("%d ", arr[QueueFront(que)]);
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

void rottenFruitUtil(int arr[][5], int maxCol, int maxRow, 
    int currCol, int currRow, int **traversed, int day) { 
    int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i=0; i<4; i++){ 
        int x = currCol + dir[i][0];
        int y = currRow + dir[i][1];
        if(x >= 0 && x < maxCol && y >= 0 && y < maxRow && 
        traversed[x][y] > day+1 && arr[x][y] == 1){
            traversed[x][y] = day+1;
            rottenFruitUtil(arr, maxCol, maxRow, x, y, traversed, day+1);
        }
    }
}

int rottenFruit(int arr[][5], int maxCol, int maxRow) {
    int **traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 9999;
        }
    }

    for (int i = 0; i < maxCol - 1; i++) {
        for (int j = 0; j < maxRow - 1; j++) {
            if (arr[i][j] == 2) {
				traversed[i][j] = 0;
                rottenFruitUtil(arr, maxCol, maxRow, i, j, traversed, 0);
        	}
		}
    }

    int maxDay = 0;
    for (int i = 0; i < maxCol - 1; i++) {
        for (int j = 0; j < maxRow - 1; j++) {
            if (arr[i][j] == 1) {
                if (traversed[i][j] == 9999)
                    return -1;
                if (maxDay < traversed[i][j])
                    maxDay = traversed[i][j];
            }
        }
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
    return maxDay;
}

int rottenFruit2(int arr[][5], int maxCol, int maxRow) {
    int **traversed = (int **)malloc(maxCol * sizeof(int *));
	Queue* que = createQueue();

    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 0;
			if (arr[i][j] == 2) {    
				QueueAdd(que, i);
				QueueAdd(que, j);
				QueueAdd(que, 0);
				traversed[i][j] = 1;
			}
        }
    }
	
	int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int maxVal = 0, x, y, day;
	int tempX, tempY, tempDay;
	while(!QueueIsEmpty(que)){
		tempX = QueueRemove(que);
		tempY = QueueRemove(que);
		tempDay = QueueRemove(que);

		for(int i=0;i<4;i++){
			x = tempX + dir[i][0];
			y = tempY + dir[i][1];
			day = tempDay + 1;
			if(x >= 0 && x < maxCol && y >= 0 && y < maxRow && 
				arr[x][y] != 0 && traversed[x][y] == 0) {
				QueueAdd(que, x);
				QueueAdd(que, y);
				QueueAdd(que, day);
				maxVal = max(maxVal, day);
				traversed[x][y] = 1;
			}
		}
	}
	for (int i = 0; i < maxCol; i++) {
		for (int j = 0; j < maxRow; j++) {
			if (arr[i][j] == 1 && traversed[i][j] == 0){
				return -1;
			}
		}
	}
	
	for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
	return maxVal;
}

int main8() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {2, 1, 0, 1, 0},
        {0, 0, 0, 2, 1},
        {0, 2, 0, 0, 1},
        {1, 1, 0, 0, 1}};

    printf("%d\n", rottenFruit(arr, 5, 5));
	printf("%d\n", rottenFruit2(arr, 5, 5));
    return 0;
}

/*
3
*/

void stepsOfKnightUtil(int size, int currCol, int currRow,
    int** traversed, int dist) {
    int dir[][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, 
                    {-1, -2}, {1, -2}, {-1, 2}, {1, 2}};
    for(int i=0;i<8;i++){
        int x = currCol + dir[i][0];
        int y = currRow + dir[i][1];
        if(x >= 0 && x < size && y >= 0 && y < size && 
        traversed[x][y] > dist+1){
            traversed[x][y] = dist+1;
            stepsOfKnightUtil(size, x, y, traversed, dist + 1);
        }
    }
}

int stepsOfKnight(int size, int srcX, int srcY, int dstX, int dstY) {
    int **traversed = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        traversed[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            traversed[i][j] = 999;
        }
    }
	traversed[srcX - 1][srcY - 1] = 0;
    stepsOfKnightUtil(size, srcX - 1, srcY - 1, traversed, 0);

    int retval = traversed[dstX - 1][dstY - 1];
    for (int i = 0; i < size; i++)
        free(traversed[i]);
    free(traversed);
    return retval;
}

int stepsOfKnight2(int size, int srcX, int srcY, 
    int dstX, int dstY) {
	int **traversed = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        traversed[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            traversed[i][j] = 999;
        }
    }

	int dir[][2] = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, 
	{-1, -2}, {1, -2}, {-1, 2}, {1, 2}};
	Queue* que = createQueue();	
	traversed[srcX-1][srcY-1] = 0;
	QueueAdd(que, srcX-1);
	QueueAdd(que, srcY-1);
	QueueAdd(que, 0);
	
	int x, y, cost;
	int tempX, tempY, tempCost;
	while(!QueueIsEmpty(que)){
		tempX = QueueRemove(que);
		tempY = QueueRemove(que);
		tempCost = QueueRemove(que);

		for(int i=0;i<8;i++){
			x = tempX + dir[i][0];
			y = tempY + dir[i][1];
			cost = tempCost + 1;
			if(x >= 0 && x < size && y >= 0 && y < size && 
					traversed[x][y] > cost){
				traversed[x][y] = cost;
				QueueAdd(que, x);
				QueueAdd(que, y);
				QueueAdd(que, cost);
			}
		}
	}
	int retval = traversed[dstX-1][dstY-1]; 
	for (int i = 0; i < size; i++)
        free(traversed[i]);
    free(traversed);
	return retval;
}

int main9() {
    printf("stepsOfKnight :: %d\n", stepsOfKnight(20, 10, 10, 20, 20));
    printf("stepsOfKnight :: %d\n", stepsOfKnight2(20, 10, 10, 20, 20));
    return 0;
}

/*
stepsOfKnight :: 8
*/

void distNearestFillUtil(int arr[][5], int maxCol, int maxRow, int currCol, int currRow,
    int** traversed, int dist) { // Range check
    int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i=0;i<4;i++){
        int x = currCol + dir[i][0];
        int y = currRow + dir[i][1];
        if(x >= 0 && x < maxCol && y >= 0 && y < maxRow && 
        traversed[x][y] > dist+1){
            traversed[x][y] = dist+1;
            distNearestFillUtil(arr, maxCol, maxRow, x, y, traversed, dist+1);
        }
    }
}

void distNearestFill(int arr[][5], int maxCol, int maxRow) {
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 9999;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            if (arr[i][j] == 1) {
                traversed[i][j] = 0;
                distNearestFillUtil(arr, maxCol, maxRow, i, j, traversed, 0);
            }
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            printf("%d ", traversed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}

void distNearestFill2(int arr[][5], int maxCol, int maxRow) {
	int **traversed = (int **)malloc(maxCol * sizeof(int *));
    Queue* que = createQueue();
	for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 9999;
			if (arr[i][j] == 1) {    
				QueueAdd(que, i);
				QueueAdd(que, j);
				QueueAdd(que, 0);
				traversed[i][j] = 0;
			}
        }
    }
	
	int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
	int x, y, dist;
	int tempX, tempY, tempDist;
	while(!QueueIsEmpty(que)){
		tempX = QueueRemove(que);
		tempY = QueueRemove(que);
		tempDist = QueueRemove(que);

		for(int i=0;i<4;i++){
			x = tempX + dir[i][0];
			y = tempY + dir[i][1];
			dist = tempDist + 1;
			if(x >= 0 && x < maxCol && 
			y >= 0 && y < maxRow && 
			traversed[x][y] > dist) {
				QueueAdd(que, x);
				QueueAdd(que, y);
				QueueAdd(que, dist);
				traversed[x][y] = dist;
			}
		}
	}
	for (int i = 0; i < maxCol; i++) {
		for (int j = 0; j < maxRow; j++) {
			printf("%d ", traversed[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}


int main10() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}};
    distNearestFill(arr, 5, 5);
    distNearestFill2(arr, 5, 5);
    return 0;
}

/*
0 1 0 0 1 
0 0 1 0 1 
1 1 2 1 0 
2 2 2 1 0 
3 3 2 1 0
*/

int findLargestIslandUtil(int arr[][5], int maxCol, int maxRow, int currCol,
                            int currRow, int **traversed) {
    int dir[][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, 
                    {1, -1}, {1, 0}, {1, 1}};
    int x, y, sum = 1;
    for(int i=0; i<8; i++) {
        x = currCol + dir[i][0];
        y = currRow + dir[i][1];
        if(x >= 0 && x < maxCol && y >= 0 && y < maxRow && 
        traversed[x][y] == 0 && arr[x][y] == 1){
            traversed[x][y] = 1;
            sum += findLargestIslandUtil(arr, maxCol, maxRow, x, y, traversed);
        }
    }
    return sum;
}

int findLargestIsland(int arr[][5], int maxCol, int maxRow) {
    int maxVal = 0;
    int currVal = 0;
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 0;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = 1;
            currVal = findLargestIslandUtil(arr, maxCol, maxRow, i, j, traversed);
            if (currVal > maxVal)
                maxVal = currVal;
        }
        return maxVal;
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    
    free(traversed);
}

int main11() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1}};
    printf("Largest Island : %d", findLargestIsland(arr, 5, 5));
    return 0;
}

/*
Largest Island : 12
*/

int Josephus(int n, int k) {
	Queue* que = createQueue();	

	for(int i=0;i<n;i++)
		QueueAdd(que, i+1);
	
	while(QueueSize(que) > 1) {
		for(int i=0;i<k-1;i++) {
			QueueAdd(que, QueueRemove(que));
		}
		QueueRemove(que);// Kth person executed.
	}
	return QueueFront(que);
}

int main12(){
	printf("Position : %d", Josephus(11, 5));
}
/*
Position : 8
*/


int main(){
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
	return 0;	
}