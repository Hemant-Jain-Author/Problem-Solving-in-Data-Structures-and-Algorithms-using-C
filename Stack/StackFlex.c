#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define ERROR_VALUE -999999

typedef struct stack {
    int top;
    int *data;
    int capacity;
    int min;
} Stack;

Stack* createStack(int size) {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->data = (int *)malloc(size * sizeof(int));
    stk->top = -1;
    stk->capacity = size;
    stk->min = size;
    return stk;
}

void stackPush(Stack *stk, int value) {
    if (stk->top < stk->capacity - 1) {
        stk->top++;
        stk->data[stk->top] = value;
        printf("Value push : %d.\n", value);
    } else {
        stk->capacity = stk->capacity * 2;
        stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
        printf("Stack size doubled.\n");
        printf("Stack capacity %d.\n", stk->capacity);
        stackPush(stk, value);
    }
}

int stackPop(Stack *stk) {
    if (stk->top >= 0) {
        int value = stk->data[stk->top];
        stk->top--;
        if (stk->top < (stk->capacity / 2) && stk->capacity > stk->min) {
            stk->capacity = stk->capacity / 2;
            stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
            printf("Stack size halfed.\n");
            printf("Stack capacity %d.\n", stk->capacity);
        }
        return value;
    }
    printf("stack empty.\n");
}

int main() {
    Stack* stk = createStack(5);
    for (int i = 0; i < 20; i++)
        stackPush(stk, i);
    for (int i = 0; i < 20; i++)
        printf("%d ", stackPop(stk));
    return 0;
}