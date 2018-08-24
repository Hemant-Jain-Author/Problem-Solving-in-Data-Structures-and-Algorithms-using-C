#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 50
#define ERROR_VALUE 999999

typedef struct stack
{
    int top1;
    int top2;
    int data[MAX_SIZE];
} Stack;

void StackInitialize(Stack *stk)
{
    stk->top1 = -1;
    stk->top2 = MAX_SIZE;
}

void StackPush1(Stack *stk, int data)
{
    if (stk->top1 < stk->top2 - 1)
    {
        stk->data[++stk->top1] = data;
    }
    else
    {
        printf("Stack is Full!\n");
    }
}

void StackPush2(Stack *stk, int data)
{
    if (stk->top1 < stk->top2 - 1)
    {
        stk->data[--stk->top2] = data;
    }
    else
    {
        printf("Stack is Full!\n");
    }
}

int StackPop1(Stack *stk)
{
    if (stk->top1 >= 0)
    {
        int value = stk->data[stk->top1--];
        printf("%d is being popped from Stack 1\n", value);
        return value;
    }
    else
    {
        printf("Stack Empty! Cannot Pop\n");
    }
    return ERROR_VALUE;
}

int StackPop2(Stack *stk)
{
    if (stk->top2 < MAX_SIZE)
    {
        int value = stk->data[stk->top2++];
        printf("%d is being popped from Stack 2\n", value);
        return value;
    }
    else
    {
        printf("Stack Empty! Cannot Pop\n");
    }
    return ERROR_VALUE;
}

int main()
{
    Stack stk;
    StackInitialize(&stk);
    for (int i = 0; i < 20; i++)
    {
        StackPush1(&stk, i);
        StackPush2(&stk, i + 10);
    }
    for (int i = 0; i < 21; i++)
    {
        StackPop1(&stk);
        StackPop2(&stk);
    }
}