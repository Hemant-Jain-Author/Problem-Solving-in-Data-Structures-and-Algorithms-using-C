def KthSmallest(arr, k):
	arr.sort()
	return arr[k-1]

import heapq
def KthSmallest2(arr, k):
	size = len(arr)
	heapq.heapify(arr)
	i = 0
	value = 0
	while i < size and i < k:
		value = heapq.heappop(arr)
		i += 1
	return value


def isMinHeap(arr):
	size = len(arr)
	parent = 0
	#last element index size - 1
	for parent in range(size/2 + 1):
		lchild = parent*2 + 1
		rchild = parent*2 + 2
		# heap property check.
		if ((lchild < size) and (arr[parent] > arr[lchild])) or ((rchild < size) and (arr[parent] > arr[rchild])) :
			return False
	return True


def isMaxHeap(arr):
	size = len(arr)
	parent = 0
	#last element index size - 1
	for parent in range(size/2 + 1):
		lchild = parent*2 + 1
		rchild = parent*2 + 2
		# heap property check.
		if ((lchild < size) and (arr[parent] < arr[lchild])) or ((rchild < size) and (arr[parent] < arr[rchild])) :
			return False
	return True

arr = [8,7,6,5,7,5,2.1]
print isMaxHeap(arr)


def KSmallestProduct(arr, k):
	arr.sort()
	product = 1
	for i in range(k):
		product *= arr[i]
	return product



def KSmallestProduct2(arr, k):
	size = len(arr)
	heapq.heapify(arr)
	i = 0
	product = 1
	while i < size and i < k:
		product *= heapq.heappop(arr)
		i += 1
	return product


def KSmallestProduct3(array, k):
	arr = array
	size = len(arr)
	QuickSelectUtil(arr, 0, size-1, k)
	product = 1
	for i in range(k):
		product *= arr[i]
	return product

def PrintLargerHalf(arr):
	arr.sort()
	size = len(arr)
	for i in range(size/2, size):
		print arr[i],


def PrintLargerHalf2(arr):
	size = len(arr)
	heapq.heapify(arr)
	for _ in range(size/2) :
		heapq.heappop(arr)
	print arr


def PrintLargerHalf3(array):
	arr = array
	size = len(arr)
	QuickSelectUtil(arr, 0, size-1, size/2)
	for i in range(size/2, size):
		print arr[i],


def minSwaps(arr, val):
	swapCount = 0
	first = 0
	second = len(arr) - 1
	while first < second:
		if arr[first] <= val:
			first += 1
		elif arr[second] > val:
			second -= 1
		else:
			arr[first], arr[second] = arr[second], arr[first]
			swapCount += 1
	return swapCount



def minJumps(arr):
	size = len(arr)
	jumps = [sys.maxint]*size
	jumps[0] = 0
 
	for i in range(size):
		steps = arr[i]
		# error checks can be added hear.
		j = i + 1
		while j <= i + steps and j < size:
			jumps[j] = min(jumps[j], jumps[i] + 1)
			j += 1
		print jumps
	return jumps[size-1]
 
arr = [1, 4, 3, 7, 6, 1, 0, 3, 5, 1, 10]
print minJumps(arr)


def sortK(arr, k):
	size = len(arr)
	heap = arr[0:k+1]
	heapq.heapify(heap)
	output = []
	for i in range(k+1, size, 1):
		output.append( heapq.heappop(heap))
		heapq.heappush(heap, arr[i])
	
	while len(heap) > 0:
		output.append( heapq.heappop(heap))
	print output



def sortK2(arr, k):
	size = len(arr)
	heap = arr[0:k+1]
	heapq.heapify(heap)
	index = 0
	for i in range(k+1, size, 1):
		arr[index] = heapq.heappop(heap)
		index += 1
		heapq.heappush(heap, arr[i])
	
	while len(heap) > 0:
		arr[index] = heapq.heappop(heap)
		index += 1

# Testing Code
k = 3
arr = [1, 5, 4, 10, 50, 9]
sortK2(arr, k)
print arr



def ChotaBhim(cup):
	cups = cup
	size = len(cups)
	time = 60
	cups.sort(reverse=True)
	value = 0
	while time > 0:
		print cups
		value += cups[0]
		cups[0] = math.ceil(cups[0]/2.0)
		index = 0
		temp = cups[0]
		while index < size-1 and temp < cups[index + 1]:
			cups[index] = cups[index + 1]
			index += 1
		cups[index] = temp
		time -= 1
	print value



def ChotaBhim(cups):
	time = 60
	size = len(cups)
	cups.sort(reverse=True)
	value = 0
	while time > 0:
		value += cups[0]
		cups[0] = math.ceil(cups[0]/2.0)
		i = 0
		# Insert into proper location.
		while i < size-1 :
			if(cups[i] > cups[i+1]):
				 break
			temp = cups[i]
			cups[i] = cups[i+1]
			cups[i+1] = temp
			i += 1
		time -= 1
	print value

cups = [2,1,7,4,2]
ChotaBhim(cups)


def JoinRopes(ropes):
	ropes.sort(reverse=True)
	total = 0
	value = 0
	while len(ropes) >= 2:
		value = ropes.pop() + ropes.pop()
		ropes.append(value)
		total += value 
		index = len(ropes) - 1
		temp = ropes[index]
		while index > 0 and ropes[index] < ropes[index - 1]:
			ropes[index] = ropes[index - 1]
			index -= 1
		ropes[index] = temp
		#ropes.sort(reverse=True)
	print total



def JoinRope2(ropes):
	heapq.heapify(ropes)
	total = 0
	value = 0
	while len(ropes) > 1:
		value = heapq.heappop(ropes)
		value += heapq.heappop(ropes)
		heapq.heappush(ropes, value)
		total += value
	print total


def kthAbsDiff(arr, k):
	size = len(arr)
	arr.sort()
	diff = []
	for i in range(size-1):
		for j in range(i+1,size, 1):
			diff.append(abs(arr[i] - arr[j]))

	diff.sort()
	return diff[k-1]


def kthAbsDiff(arr, k):
	size = len(arr)
	arr.sort()
	hp = []
	value = 0
	
	for i in range(size-1):
		hp.append((abs(arr[i] - arr[i+1]), i, i+1))
	heapq.heapify(hp)

	for i in range(k):
		tp = heapq.heappop(hp)
		value = tp[0]
		src = tp[1]
		dst = tp[2]
		if dst + 1 < size :
			heapq.heappush(hp, (abs(arr[src] - arr[dst+1]), src, dst+1))
	return value

arr = [1, 2, 3, 4]
print kthAbsDiff(arr, 5)


def kthLargestStream(k):
	hp = []
	size = 0
	while 1:
		data = input("Enter data: ") 
		if size < k - 1:
			hp.append(data)
		else:
			if size == k - 1:
				hp.append(data)
				heapq.heapify(hp)
			elif hp[0] < data :
				heapq.heappush(hp, data)
				heapq.heappop(hp)
			print hp
			print "Kth larges element is :: ", hp[0]
		size += 1

kthLargestStream(3)

