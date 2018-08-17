#include "stdio.h"
#include "stdlib.h"

#define MAX_CAPACITY 100
#define ERROR_VALUE -999

typedef struct Queue_t
{
    int front;
    int back;
    int size;
    int data[MAX_CAPACITY];
} Queue;

void QueueInitialize(Queue *que)
{
    que->back = 0;
    que->front = 0;
    que->size = 0;
}

void Enqueue(Queue *que, int value)
{
    if (que->size >= MAX_CAPACITY)
    {
        printf("\n Queue is full.");
        return;
    }
    else
    {
        que->size++;
        que->data[que->back] = value;
        que->back = (++(que->back)) % (MAX_CAPACITY - 1);
    }
}

int Dequeue(Queue *que)
{
    int value;
    if (que->size <= 0)
    {
        printf("\n Queue is empty.");
        return ERROR_VALUE;
    }
    else
    {
        que->size--;
        value = que->data[que->front];
        que->front = (++(que->front)) % (MAX_CAPACITY - 1);
    }
    return value;
}

int QueueIsEmpty(Queue *que)
{
    return que->size == 0;
}

int QueueSize(Queue *que)
{
    return que->size;
}

int main()
{
    Queue que;
    QueueInitialize(&que);
    for (int i = 0; i < 20; i++)
    {
        Enqueue(&que, i);
    }
    for (int i = 0; i < 20; i++)
    {
        printf(" %d ", Dequeue(&que));
    }
    return 0;
}

def CircularTour(arr, n):
	que = deque([])
	nextPump = 0
	count = 0
	petrol = 0

	while len(que) != n:
		while petrol >= 0 and len(que) != n :
			que.append(nextPump)
			petrol += (arr[nextPump][0] - arr[nextPump][1])
			nextPump = (nextPump + 1) % n
			
		while petrol < 0 and len(que) > 0:
			prevPump = que.popleft()
			petrol -= (arr[prevPump][0] - arr[prevPump][1])
		
		count += 1
		if count == n:
			return -1

	if petrol >= 0:
		return que.popleft()
	else:
		return -1

# Testing code
tour = [[8, 6], 
[1, 4], 
[7, 6]]

print CircularTour(tour, 3)


def convertXY(src, dst):
	que = deque([])
	visited = {}
	que.append((src, 0))
	while len(que) != 0:
		node = que.popleft()
		visited[node[0]] = 1
		value = node[0]
		steps = node[1]
		if value == dst:
			return steps
		if value < dst and (value*2) not in visited:
			que.append((value*2, steps+1))
		if value > 0 and (value - 1) not in visited:
			que.append((value-1, steps+1))
	return -1


def maxSlidingWindows(arr, k):
	size = len(arr)
	que = deque()
	for i in range(size):
		# Remove out of range elements
		if que and que[0] <= i - k:
			que.popleft()
		# Remove smaller values at left.
		while que and arr[que[-1]] <= arr[i] :
			que.pop()

		que.append(i)
		# Largest value in window of size k is at index que[0]
		# It is displayed to the screen.  
		if i >= (k - 1):
			print(arr[que[0]])

Input: 11, 2, 75, 92, 59, 90, 55   and   k = 3
Output: 75, 92, 92, 92, 90


def minOfMaxSlidingWindows(arr, k):
	size = len(arr)
	que = deque()
	minVal = 999999
	for i in range(size):
		# Remove out of range elements
		if que and que[0] <= i - k:
			que.popleft()
		# Remove smaller values at left.
		while que and arr[que[-1]] <= arr[i] :
			que.pop()
		que.append(i)
		# window of size k
		if i >= (k - 1) and minVal > arr[que[0]] :
			minVal = arr[que[0]]
	print("Min of max is : ", minVal)


Input: 11, 2, 75, 92, 59, 90, 55   and   k = 3
Output: 75

def maxOfMinSlidingWindows(arr, k):
	size = len(arr)
	que = deque()
	maxVal = -999999
	for i in range(size):
		# Remove out of range elements
		if que and que[0] <= i - k:
			que.popleft()
		# Remove smaller values at left.
		while que and arr[que[-1]] >= arr[i] :
			que.pop()
		que.append(i)
		# window of size k
		if i >= (k - 1) and maxVal < arr[que[0]] :
			maxVal = arr[que[0]]
	print("Max of min is : ", maxVal)


Input: 11, 2, 75, 92, 59, 90, 55   and   k = 3
Output:  59, as minimum values in sliding windows are [2, 2, 59, 59, 55]


def firstNegSlidingWindows(arr, k):
	size = len(arr)
	que = deque()
	for i in range(size):
		# Remove out of range elements
		if que and que[0] <= i - k:
			que.popleft()
		if arr[i] < 0:
			que.append(i)
		# window of size k
		if i >= (k - 1) :
			if len(que) > 0:
				print(arr[que[0]])
			else:
				print("NAN") 


Arr = [13, -2, -6, 10, -14, 50, 14, 21]	 
k = 3

Output:  [-2, -2, -6, -14, -14, NAN]



class Tree(object):
    class Node(object):
        def __init__(self, v, l=None, r=None):
            self.value = v
            self.lChild = l
            self.rChild = r
    
    def __init__(self):
        self.root = None

    def levelOrderBinaryTree(self, arr):
        self.root = self.levelOrderBinaryTreeUtil(arr, 0)

    def levelOrderBinaryTreeUtil(self, arr, start):
        size = len(arr)
        curr = self.Node(arr[start])
        left = 2 * start + 1
        right = 2 * start + 2
        if left < size:
            curr.lChild = self.levelOrderBinaryTreeUtil(arr, left)
        if right < size:
            curr.rChild = self.levelOrderBinaryTreeUtil(arr, right)
        return curr

    def PrintBredthFirst(self):
        que = deque([])
        output = []
        temp = None
        if self.root != None:
            que.append(self.root)
        while len(que) != 0:
            temp = que.popleft()
            output.append(temp.value)
            if temp.lChild != None:
                que.append(temp.lChild)
            if temp.rChild != None:
                que.append(temp.rChild)
        print output

    def PrintLevelOrderLineByLine(self):
        que1 = deque([])
        que2 = deque([])
        temp = None
        if self.root != None:
            que1.append(self.root)
        while len(que1) != 0 or len(que2) != 0 :
            while len(que1) != 0:
                temp = que1.popleft()
                print temp.value,
                if temp.lChild != None:
                    que2.append(temp.lChild)
                if temp.rChild != None:
                    que2.append(temp.rChild)
            print ""
            while len(que2) != 0:
                temp = que2.popleft()
                print temp.value,
                if temp.lChild != None:
                    que1.append(temp.lChild)
                if temp.rChild != None:
                    que1.append(temp.rChild)
            print ""

    def PrintLevelOrderLineByLine2(self):
        que = deque([])
        temp = None
        if self.root != None:
            que.append(self.root)
        while len(que) != 0 :
            count = len(que)
            while count > 0:
                temp = que.popleft()
                print temp.value,
                if temp.lChild != None:
                    que.append(temp.lChild)
                if temp.rChild != None:
                    que.append(temp.rChild)
                count -= 1
            print ""

    def PrintSpiralTree(self):
        stk1 = []
        stk2 = []
        output = []
        temp = None
        if self.root != None:
            stk1.append(self.root)
        while len(stk1) !=0 or len(stk2) != 0:
            while len(stk1) != 0:
                temp = stk1.pop()
                output.append(temp.value)
                if temp.rChild != None:
                    stk2.append(temp.rChild)
                if temp.lChild != None:
                    stk2.append(temp.lChild)

            while len(stk2) != 0:
                temp = stk2.pop()
                output.append(temp.value)
                if temp.lChild != None:
                    stk1.append(temp.lChild)
                if temp.rChild != None:
                    stk1.append(temp.rChild)
        print output

    """
    To see if tree is a heap we need to check two conditions:
    1) It is a complete tree.
    2) Value of a node is grater than or equal to it's left and right child.
    """
    def findCountUtil(self, curr):
        if curr == None:
            return 0
        return (1 + self.findCountUtil(curr.lChild) + self.findCountUtil(curr.rChild))

    def findCount(self):
        return self.findCountUtil(self.root)
    
    def isCompleteTreeUtil(self, curr, index, count):
        if curr == None:
            return True
        if index > count:
            return False 
        return self.isCompleteTreeUtil(curr.lChild, index*2+1, count) and self.isCompleteTreeUtil(curr.rChild, index*2+2, count)

    def isCompleteTree(self):
        count = self.findCount()
        return self.isCompleteTreeUtil(self.root, 0, count)

    def isCompleteTree2(self):
        que = deque([])
        temp = None
        noChild = False
        if self.root != None:
            que.append(self.root)
        while len(que) != 0:
            temp = que.popleft()
            if temp.lChild != None:
                if noChild == True:
                    return False
                que.append(temp.lChild)
            else:
                noChild = True

            if temp.rChild != None:
                if noChild == True:
                    return False
                que.append(temp.rChild)
            else:
                noChild = True

    def isHeapUtil(self, curr, parentValue):
        if curr == None:
            return True
        if curr.value < parentValue:
            return False
        return ( self.isHeapUtil(curr.lChild, curr.value) and self.isHeapUtil(curr.rChild, curr.value ))

    def isHeap(self):
        infi = -9999999
        return self.isCompleteTree() and self.isHeapUtil(self.root, infi)


    def isHeapUtil2(self, curr, index, count, parentValue):
        if curr == None:
            return True
        if index > count:
            return False
        if curr.value < parentValue:
            return False 
        return self.isHeapUtil2(curr.lChild, index*2+1, count, curr.value) and self.isHeapUtil2(curr.rChild, index*2+2, count, curr.value)

    def isHeap2(self):
        count = self.findCount()
        parentValue = -9999999
        return self.isHeapUtil2(self.root, 0, count, parentValue)



    def isHeap3(self):
        que = deque([])
        que.append(self.root)
        que.append(0)
        que.append(-99999)
        count = 0
        while len(que) != 0:
            curr = que.popleft()
            currIndex = que.popleft()
            parentValue = que.popleft()

            if curr.value < parentValue or currIndex != count :
                return False
            count += 1
            if curr.lChild != None :
                que.append(curr.lChild)
                que.append(currIndex * 2 + 1)
                que.append(curr.value)
            
            if curr.rChild != None :
                que.append(curr.rChild)
                que.append(currIndex * 2 + 2)
                que.append(curr.value)

        return True


"""
Use queue to traverse the tree. In queue you will keep index and parent value. 
When you dequeue element from queue you will keep track count of element 
count should be equal to the index value.
"""

t = Tree()
arr = [1, 2, 3, 4, 5, 6, 7,8,9,10,11,12,13,14,15,16,17,18,19,20]
t.levelOrderBinaryTree(arr)
t.PrintBredthFirst()
t.PrintLevelOrderLineByLine()
#print t.isCompleteTree()
print t.isHeap()
# t.PrintSpiralTree()
# t.PrintLevelOrderLineByLine()
# t.PrintLevelOrderLineByLine2()
# Print Level order sum
# Print level order max
# Print Level order sum max



