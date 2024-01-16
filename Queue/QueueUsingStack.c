#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"
#include <math.h>
#include "../Stack/Stack.c"

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b) {
	return a < b ? b : a;
}

typedef struct Queue {
	Stack* stk1;
	Stack* stk2;
}Queue;

Queue* createQueue() {
	Queue* que = (Queue*)malloc(sizeof(Queue));
	que->stk1 = createStack();	
	que->stk2 = createStack();
	return que;
}

void queueAdd(Queue* que, int value) {
	stackPush(que->stk1, value);
}

int queueRemove(Queue* que) {
	int value;
	if (stackIsEmpty(que->stk2)) {	
		while (!stackIsEmpty(que->stk1)) {
			value = stackPop(que->stk1);
			stackPush(que->stk2, value);
		}
	}
	return stackPop(que->stk2);
}

int queueSize(Queue* que) {
	return stackSize(que->stk1) + stackSize(que->stk2);
}

int main() {
	Queue* que = createQueue();
	queueAdd(que, 1);
	queueAdd(que, 2);
	queueAdd(que, 3);
    queueAdd(que, 4);
	while(queueSize(que) > 0)
		printf("%d  ", queueRemove(que));
}