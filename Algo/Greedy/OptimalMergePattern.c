#include <stdio.h>
#include <stdlib.h>
#include "../../Heap/Heap.c"

int merge(int lists[], int size) {
	Heap* hp = createHeap(greater);

	for (int i = 0; i < size; i++) {
		heapAdd(hp, lists[i]);
	}

	int total = 0;
	int value = 0;
	while (heapSize(hp) > 1) {
		value =  heapRemove(hp);
		value +=  heapRemove(hp);
		heapAdd(hp, value);
		total += value;
	}
	printf("Total : %d\n" , total );
	return total;
}

int main() {
	int lists[] = {4, 3, 2, 6};
	merge(lists, 4);
}

/*
Total : 29
*/