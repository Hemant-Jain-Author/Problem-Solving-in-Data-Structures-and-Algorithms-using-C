#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define ERROR_VALUE -999

typedef struct stack
{
    int top;
    int *data;
    int capacity;
    int min;
} Stack;

void StackInitialize(Stack *stk, int size);
void StackPush(Stack *stk, int value);
int StackPop(Stack *stk);
int StackTop(Stack *stk);
int StackIsEmpty(Stack *stk);
int StackSize(Stack *stk);

void StackInitialize(Stack *stk, int size)
{
    stk->data = (int *)malloc(size * sizeof(int));
    stk->top = -1;
    stk->capacity = size;
    stk->min = size;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < stk->capacity - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push : %d \n", value);
    }
    else
    {
        stk->capacity = stk->capacity * 2;
        stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
        printf("Stack size doubled");
        printf("Stack capacity %d", stk->capacity);
        StackPush(stk, value);
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0)
    {
        int value = stk->data[stk->top];
        stk->top--;
        if (stk->top < (stk->capacity / 2) && stk->capacity > stk->min)
        {
            stk->capacity = stk->capacity / 2;
            stk->data = (int *)realloc(stk->data, stk->capacity * sizeof(int));
            printf("Stack size halfed\n");
            printf("Stack capacity %d", stk->capacity);
        }
        return value;
    }
    printf("stack empty\n");
}

int main()
{
    Stack stk;
    StackInitialize(&stk, 5);
    for (int i = 0; i < 20; i++)
        StackPush(&stk, i);
    for (int i = 0; i < 20; i++)
        printf(" %d \n", StackPop(&stk));

    return 0;
}

