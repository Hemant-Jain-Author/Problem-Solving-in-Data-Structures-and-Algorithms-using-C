#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define ERROR_VALUE -999999

typedef struct stack
{
    int top;
    int *data;
    int max;
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
    stk->max = size;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < stk->max - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
    }
    else
    {
        stk->max = stk->max * 2;
        stk->data = (int *)realloc(stk->data, stk->max * sizeof(int));
        push(stk, value);
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0)
    {
        int value = stk->data[stk->top];
        stk->top--;
        if (stk->top < (stk->max / 2) && stk->max > stk->min)
        {
            stk->max = stk->max / 2;
            stk->data = (int *)realloc(stk->data, stk->max * sizeof(int));
            printf("stack size halfed");
        }
        return value;
    }
    printf("stack empty\n");
}

int main()
{
    Stack stk;
    StackInitialize(&stk);
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    return 0;
}