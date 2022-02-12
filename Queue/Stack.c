#include "Queue.c"

typedef struct Stack {
	Queue* que1;
	Queue* que2;
    int size;
}Stack;

Stack* createStack() {
	Stack* stk = (Stack*)malloc(sizeof(Stack));
	stk->que1 = createQueue();	
	stk->que2 = createQueue();
	return stk;
}

void StackPush(Stack* stk, int value) {
    QueueAdd(stk->que1, value);
    stk->size += 1;
}

int StackPop(Stack* stk) {
    int value=0, s = stk->size;        
    while(s > 0){
        value = QueueRemove(stk->que1);
        if(s > 1)
            QueueAdd(stk->que2, value);
        s--;
    }
    Queue* temp = stk->que1;
    stk->que1 = stk->que2;
    stk->que2 = temp;
    stk->size -= 1;
    return value;
}

void StackPush2(Stack* stk, int value) {
    QueueAdd(stk->que1, value);
    stk->size += 1;
}

int StackPop2(Stack* stk) {
    int value=0, s = stk->size;        
    while(s > 0){
        value = QueueRemove(stk->que1);
        if(s > 1)
            QueueAdd(stk->que1, value);
        s--;
    }
    stk->size -= 1;
    return value;
}

int main() {
	Stack* stk = createStack();
	StackPush(stk, 1);
	StackPush(stk, 2);
	StackPush(stk, 3);
	printf("%d  ", StackPop(stk));
    printf("%d  ", StackPop(stk));
    printf("%d  ", StackPop(stk));

	StackPush2(stk, 1);
	StackPush2(stk, 2);
	StackPush2(stk, 3);
	printf("%d  ", StackPop2(stk));
    printf("%d  ", StackPop2(stk));
    printf("%d  ", StackPop2(stk));
}