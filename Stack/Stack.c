#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"

#define MAX_CAPACITY 50
#define ERROR_VALUE -999

typedef struct stack
{
    int top;
    int data[MAX_CAPACITY];
} Stack;

void StackInitialize(Stack *stk);
void StackPush(Stack *stk, int value);
int StackPop(Stack *stk);
int StackTop(Stack *stk);
int StackIsEmpty(Stack *stk);
int StackSize(Stack *stk);

void StackInitialize(Stack *stk)
{
    stk->top = -1;
}

void StackPush(Stack *stk, int value)
{
    if (stk->top < MAX_CAPACITY - 1)
    {
        stk->top++;
        stk->data[stk->top] = value;
        printf("value push : %d \n", value);
    }
    else
    {
        printf("stack overflow\n");
    }
}

int StackPop(Stack *stk)
{
    if (stk->top >= 0)
    {
        int value = stk->data[stk->top];
        stk->top--;
        printf("value pop : %d \n", value);
        return value;
    }
    printf("stack empty\n");
    return ERROR_VALUE;
}

int StackTop(Stack *stk)
{
    int value = stk->data[stk->top];
    return value;
}

int StackIsEmpty(Stack *stk)
{
    return (stk->top == -1);
}

int StackSize(Stack *stk)
{
    return (stk->top + 1);
}

int isBalancedParenthesis(char *expn)
{
    Stack stk;
    StackInitialize(&stk);

    int i = 0;
    char ch;

    while ((ch = expn[i++]) != '\0')
    {
        switch (ch)
        {

        case '{':
        case '[':
        case '(':
            StackPush(&stk, ch);
            break;

        case '}':
            if (StackPop(&stk) != '{')
                return 0;
            break;

        case ']':
            if (StackPop(&stk) != '[')
                return 0;
            break;

        case ')':
            if (StackPop(&stk) != '(')
                return 0;
            break;
        }
    }

    return StackIsEmpty(&stk);
}

int precedence(char x)
{
    if (x == '(')
        return (0);
    if (x == '+' || x == '-')
        return (1);
    if (x == '*' || x == '/' || x == '%')
        return (2);
    if (x == '^')
        return (3);
    return (4);
}

void infixToPostFix(char *expn, char *output)
{
    Stack stk;
    StackInitialize(&stk);
    char ch, op;
    int i = 0;
    int index = 0;
    int digit = 0;
    while ((ch = expn[i++]) != '\0')
    {
        if (isdigit(ch))
        {
            output[index++] = ch;
            digit = 1;
        }
        else
        {
            if (digit)
            {
                output[index++] = ' ';
                digit = 0;
            }
            switch (ch)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!StackIsEmpty(&stk) && precedence(ch) <= precedence(StackTop(&stk)))
                {
                    op = StackPop(&stk);
                    output[index++] = op;
                    output[index++] = ' ';
                }
                StackPush(&stk, ch);
                break;
            case '(':
                StackPush(&stk, ch);
                break;
            case ')':
                while (!StackIsEmpty(&stk) && (op = StackPop(&stk)) != '(')
                {
                    output[index++] = op;
                    output[index++] = ' ';
                }
                break;
            }
        }
    }
    while (!StackIsEmpty(&stk))
    {
        op = StackPop(&stk);
        output[index++] = op;
        output[index++] = ' ';
    }
    output[index++] = '\0';
}
/*
void infixToPostFix(char* expn,char* output)
{
	Stack stk;
	StackInitialize(&stk);
	char ch, op;
	int i = 0;
	int index =0;
	int digit = 0;
	while ((ch = expn[i++]) != '\0')
	{
		if (isdigit(ch))
		{
			output[index++] = ch;
			digit=1;
		}
		else 
		{
			if(digit)
			{
				output[index++] = ' ';
				digit = 0;
			}
			switch (ch)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case '^':
				while (precedence(ch) <= precedence(StackTop(&stk)) && !StackIsEmpty(&stk))
				{
					op = StackPop(&stk);
					output[index++] = op;
					output[index++] = ' ';
				}
				StackPush(&stk, ch); 
				break;
			case ')':
				StackPush(&stk, ch);
				break;
			case '(':
				while (!StackIsEmpty(&stk) && (op = StackPop(&stk)) != ')')
				{
					output[index++] = op;
					output[index++] = ' ';
				}
				break;
			}
		}
	}
	while (!StackIsEmpty(&stk))
	{
		op = StackPop(&stk);
		output[index++] = op;
		output[index++] = ' ';
	}
	output[index++] = '\0';
}
*/
void reverseString(char *a)
{
    int lower = 0;
    int upper = strlen(a) - 1;
    char tempChar;
    while (lower < upper)
    {
        tempChar = a[lower];
        a[lower] = a[upper];
        a[upper] = tempChar;

        lower++;
        upper--;
    }
}

void replaceParanthesis(char *a)
{
    int lower = 0;
    int upper = strlen(a) - 1;
    while (lower <= upper)
    {
        if (a[lower] == '(')
            a[lower] = ')';
        else if (a[lower] == ')')
            a[lower] = '(';
        lower++;
    }
}

void infixToPreFix(char *expn, char *output)
{
    reverseString(expn);
    replaceParanthesis(expn);
    infixToPostFix(expn, output);
    reverseString(output);
}

int postfixEvaluate(char *postfx)
{
    Stack s;
    StackInitialize(&s);
    int i = 0, op1, op2;
    char ch;
    int digit = 0;
    int value = 0;
    while ((ch = postfx[i++]) != '\0')
    {
        if (isdigit(ch))
        {
            digit = 1;
            value = value * 10 + (ch - '0');
        }
        else if (ch == ' ')
        {
            if (digit == 1)
            {
                StackPush(&s, value); /* Push the operand */
                digit = 0;
                value = 0;
            }
        }
        else
        {
            op2 = StackPop(&s);
            op1 = StackPop(&s);
            switch (ch)
            {
            case '+':
                StackPush(&s, op1 + op2);
                break;
            case '-':
                StackPush(&s, op1 - op2);
                break;
            case '*':
                StackPush(&s, op1 * op2);
                break;
            case '/':
                StackPush(&s, op1 / op2);
                break;
            }
        }
    }
    return StackTop(&s);
}

/* The stock span problem is a financial problem where we have a series of n daily price quotes for a stock and we need to calculate span of stock�s price for all n days.
The span Si of the stocks price on a given day i is defined as the maximum number of consecutive days just before the given day, for which the price of the stock on the current day is less than or equal to its price on the given day. */

int *StockSpanRange(int arr[], int size)
{
    int *SR = (int *)malloc(size * sizeof(int));
    SR[0] = 1;

    for (int i = 1; i < size; i++)
    {
        SR[i] = 1;

        for (int j = i - 1; (j >= 0) && (arr[i] >= arr[j]); j--)
            SR[i]++;
    }
    return SR;
}

int *StockSpanRange2(int arr[], int size)
{
    Stack stk;
    int *SR = (int *)malloc(size * sizeof(int));
    StackInitialize(&stk);
    StackPush(&stk, 0);
    SR[0] = 1;

    for (int i = 1; i < size; i++)
    {
        while (!StackIsEmpty(&stk) && arr[StackTop(&stk)] <= arr[i])
        {
            StackPop(&stk);
        }

        SR[i] = (StackIsEmpty(&stk)) ? (i + 1) : (i - StackTop(&stk));
        StackPush(&stk, i);
    }
    return SR;
}

/* The main function to find the maximum rectangular area under given
 histogram with n bars */
int getMaxArea(int hist[], int n)
{
    /* Create an empty stack. The stack holds indexes of hist[] array
	 The bars stored in stack are always in increasing order of their
	 heights.*/
    Stack stk;

    int max_area = 0;  /* Initalize max area */
    int tp;            /*  To store top of stack */
    int area_with_top; /* To store area with top bar as the smallest bar */

    /* Run through all bars of given histogram */
    int i = 0;
    while (i < n)
    {
        /* If this bar is higher than the bar on top stack, push it to stack */
        if (StackIsEmpty(&stk) || hist[StackTop(&stk)] <= hist[i])
            StackPush(&stk, i);

        /* If this bar is lower than top of stack, then calculate area of rectangle 
		 with stack top as the smallest (or minimum height) bar. 'i' is 
		 'right index' for the top and element before top in stack is 'left index' */
        else
        {
            tp = StackTop(&stk); /* store the top index */
            StackPop(&stk);      /* pop the top */

            /* Calculate the area with hist[tp] stack as smallest bar */
            area_with_top = hist[tp] * (StackIsEmpty(&stk) ? i : i - StackTop(&stk) - 1);

            /* update max area, if needed */
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }

    /* Now pop the remaining bars from stack and calculate area with every
	 popped bar as the smallest bar */
    while (StackIsEmpty(&stk) == 0)
    {
        tp = StackTop(&stk);
        StackPop(&stk);
        area_with_top = hist[tp] * (StackIsEmpty(&stk) ? i : i - StackTop(&stk) - 1);

        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    return max_area;
}

int GetMaxArea(int arr[], int size)
{
    int maxArea = -1;
    int currArea;
    int minHeight = 0;
    for (int i = 1; i < size; i++)
    {
        minHeight = arr[i];
        for (int j = i - 1; j >= 0; j--)
        {
            if (minHeight > arr[j])
                minHeight = arr[j];

            currArea = minHeight * (i - j + 1);

            if (maxArea < currArea)
                maxArea = currArea;
        }
    }
    return maxArea;
}

int GetMaxArea2(int arr[], int size)
{
    Stack stk;
    StackInitialize(&stk);
    int maxArea = 0;
    int top;
    int topArea;

    int i = 0;
    while (i < size)
    {
        while ((i < size) && (StackIsEmpty(&stk) || arr[StackTop(&stk)] <= arr[i]))
        {
            StackPush(&stk, i);
            i++;
        }

        while (!StackIsEmpty(&stk) && (i == size || arr[StackTop(&stk)] > arr[i]))
        {
            top = StackTop(&stk);
            StackPop(&stk);
            topArea = arr[top] * (StackIsEmpty(&stk) ? i : i - StackTop(&stk) - 1);
            if (maxArea < topArea)
                maxArea = topArea;
        }
    }
    return maxArea;
}

int IsMinHeap(int arr[], int size)
{
    for (int i = 0; i <= (size - 2) / 2; i++)
    {
        if (2 * i + 1 < size)
        {
            if (arr[i] > arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size)
        {
            if (arr[i] > arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}

int IsMaxHeap(int arr[], int size)
{
    for (int i = 0; i <= (size - 2) / 2; i++)
    {
        if (2 * i + 1 < size)
        {
            if (arr[i] < arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size)
        {
            if (arr[i] < arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}


int main()
{
    Stack stk;
    StackInitialize(&stk);
    for (int i = 0; i < 20; i++)
        StackPush(&stk, i);
    printf("StackTop %d \n", StackTop(&stk));
    printf("StackSize %d \n", StackSize(&stk));
    printf("StackIsEmpty %d \n", StackIsEmpty(&stk));
    for (int i = 0; i < 20; i++)
        StackPop(&stk);
    printf("StackIsEmpty %d \n", StackIsEmpty(&stk));

    printf("isBalancedParenthesis %d \n", isBalancedParenthesis("{()}"));
    printf("isBalancedParenthesis %d \n", isBalancedParenthesis("{()({})}"));
    printf("isBalancedParenthesis %d \n", isBalancedParenthesis("{((}"));
    printf("isBalancedParenthesis %d \n", isBalancedParenthesis("{(})"));

    char expn[50] = "(10 + 3) * 5"; /// (16 - 4)";
    char output[50];
    printf("\n Given Expn: %s\n", expn);
    infixToPostFix(expn, output);
    printf("\n PostFix: %s\n", output);
    infixToPreFix(expn, output);
    printf("\n PreFix: %s\n", output);
    printf("\n postfixEvaluate: %d\n", postfixEvaluate(output));

    return 0;
}