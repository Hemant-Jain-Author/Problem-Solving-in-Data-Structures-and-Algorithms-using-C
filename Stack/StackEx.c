// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "stdlib.h"
#include <ctype.h>
#include "string.h"
#include <math.h>
#include "Stack.c"
#include "../Queue/Queue.c"

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a < b ? b : a;
}

void function2() {
    printf("fun2 line 1\n");
}

void function1() {
    printf("fun1 line 1\n");
    function2();
    printf("fun1 line 2\n");
}

int main1() {
    printf("main line 1\n");
    function1();
    printf("main line 2\n");
}

/*
main line 1
fun1 line 1
fun2 line 1
fun1 line 2
main line 2
*/

void sortedInsert(Stack *stk, int element) {
    int temp;
    if (stackIsEmpty(stk) || element > stackTop(stk)) {
        stackPush(stk, element);
    } else {
        temp = stackPop(stk);
        sortedInsert(stk, element);
        stackPush(stk, temp);
    }
}

int main2()
{
    Stack* stk = createStack();
    stackPush(stk, 1);
    stackPush(stk, 2);
    stackPush(stk, 4);
    stackPush(stk, 5);
    stackPrint(stk);
    sortedInsert(stk, 3);
    stackPrint(stk);
    return 0;
}

void sortStack(Stack *stk) {
    int temp;
    if (stackIsEmpty(stk) == 0) {
        temp = stackPop(stk);
        sortStack(stk);
        sortedInsert(stk, temp);
    }
}

void sortStack2(Stack *stk) {
    int temp;
    Stack* stk2 = createStack();
    while (stackIsEmpty(stk) == 0) {
        temp = stackPop(stk);
        while ((stackIsEmpty(stk2) == 0) && (stackTop(stk2) < temp))
            stackPush(stk, stackPop(stk2));
        stackPush(stk2, temp);
    }
    while (stackIsEmpty(stk2) == 0)
        stackPush(stk, stackPop(stk2));
}

int main3()
{
    Stack* stk = createStack();
    stackPush(stk, 1);
    stackPush(stk, 5);
    stackPush(stk, 4);
    stackPush(stk, 3);
    stackPrint(stk);
    sortStack(stk);
    stackPrint(stk);

    Stack* stk2 = createStack();
    stackPush(stk2, 1);
    stackPush(stk2, 5);
    stackPush(stk2, 4);
    stackPush(stk2, 3);
    stackPrint(stk2);
    sortStack2(stk2);
    stackPrint(stk2);
    return 0;
}

void bottomInsert(Stack *stk, int element) {
    if (stackIsEmpty(stk))
        stackPush(stk, element);
    else
    {
        int temp = stackPop(stk);
        bottomInsert(stk, element);
        stackPush(stk, temp);
    }
}

int main4() {
    Stack* stk = createStack();
    stackPush(stk, 1);
    stackPush(stk, 2);
    stackPush(stk, 3);
    bottomInsert(stk, 4);
    stackPrint(stk);
    return 0;
}


void reverseStack(Stack *stk) {
    int temp;
    if (stackIsEmpty(stk) == 0) {
        temp = stackPop(stk);
        reverseStack(stk);
        bottomInsert(stk, temp);
    }
}

void reverseStack2(Stack *stk) {
    Queue* que = createQueue();
    while (stackIsEmpty(stk) == 0)
        queueAdd(que, stackPop(stk));

    while (queueIsEmpty(que) == 0)
        stackPush(stk, queueRemove(que));
}

int main5()
{
    Stack* stk = createStack();
    stackPush(stk, 1);
    stackPush(stk, 2);
    stackPush(stk, 3);
    stackPush(stk, 4);
    stackPrint(stk);
    reverseStack(stk);
    stackPrint(stk);
    reverseStack2(stk);
    stackPrint(stk);
    return 0;
}

void reverseKElementInStack(Stack *stk, int k) {
    Queue* que = createQueue();
    int i = 0;
    while (stackIsEmpty(stk) == 0 && i < k) {
        queueAdd(que, stackPop(stk));
        i++;
    }
    while (queueIsEmpty(que) == 0)
        stackPush(stk, queueRemove(que));
}

int main6()
{
    Stack* stk = createStack();
    stackPush(stk, 1);
    stackPush(stk, 2);
    stackPush(stk, 3);
    stackPush(stk, 4);
    stackPrint(stk);
    reverseKElementInStack(stk, 2);
    stackPrint(stk);
    return 0;
}

void reverseQueue(Queue *que) {
    Stack* stk = createStack();
    while (queueIsEmpty(que) == 0)
        stackPush(stk, queueRemove(que));

    while (stackIsEmpty(stk) == 0)
        queueAdd(que, stackPop(stk));
}

int main7()
{
    Queue* que = createQueue();
    queueAdd(que, 1);
    queueAdd(que, 2);
    queueAdd(que, 3);
    queueAdd(que, 4);
    queuePrint(que);
    reverseQueue(que);
    queuePrint(que);
    return 0;
}

void reverseKElementInQueue(Queue *que, int k) {
    Stack* stk = createStack();
    int i = 0, diff, temp;
    while (queueIsEmpty(que) == 0 && i < k) {
        stackPush(stk, queueRemove(que));
        i++;
    }

    while (stackIsEmpty(stk) == 0) {
        queueAdd(que, stackPop(stk));
    }

    diff = queueSize(que) - k;
    while (diff > 0) {
        temp = queueRemove(que);
        queueAdd(que, temp);
        diff -= 1;
    }
}

int main8()
{
    Queue* que = createQueue();
    queueAdd(que, 1);
    queueAdd(que, 2);
    queueAdd(que, 3);
    queueAdd(que, 4);
    queuePrint(que);
    reverseKElementInQueue(que, 2);
    queuePrint(que);
    return 0;
}

int isBalancedParenthesis(char *expn, int size) {
    Stack* stk = createStack();
    char ch;

    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '{' || ch == '[' || ch == '(')
            stackPush(stk, ch);
        else if (ch == '}') {
            if (stackPop(stk) != '{')
                return 0;
        }
        else if (ch == ']') {
            if (stackPop(stk) != '[')
                return 0;
        }
        else if (ch == ')') {
            if (stackPop(stk) != '(')
                return 0;
        }
    }
    return (stackSize(stk) == 0);
}

int main9() {
    char *expn = "{()}[]";
    int size = strlen(expn);
    int value = isBalancedParenthesis(expn, size);
    printf("Given Expn %s \n", expn);
    printf("Result after isParenthesisMatched :: %d \n", value);
    return 0;
}

int maxDepthParenthesis(char *expn, int size) {
    Stack* stk = createStack();
    int maxDepth = 0;
    int depth = 0;
    char ch;

    for (int i = 0; i < size; i++) {
        ch = expn[i];

        if (ch == '(') {
            stackPush(stk, ch);
            depth += 1;
        }
        else if (ch == ')') {
            stackPop(stk);
            depth -= 1;
        }
        if (depth > maxDepth)
            maxDepth = depth;
    }
    return maxDepth;
}

int maxDepthParenthesis2(char *expn, int size) {
    int maxDepth = 0;
    int depth = 0;
    char ch;
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(')
            depth += 1;
        else if (ch == ')')
            depth -= 1;

        if (depth > maxDepth)
            maxDepth = depth;
    }
    return maxDepth;
}

int main10() {
    char *expn = "((((A)))((((BBB()))))()()()())";
    int size = strlen(expn);
    int value = maxDepthParenthesis(expn, size);
    int value2 = maxDepthParenthesis2(expn, size);

    printf("Given expn %s \n", expn);
    printf("Max depth parenthesis is %d \n", value);
    printf("Max depth parenthesis is %d \n", value2);
    return 0;
}

int longestContBalParen(char *string, int size) {
    Stack* stk = createStack();
    stackPush(stk, -1);
    int length = 0;

    for (int i = 0; i < size; i++) {
        if (string[i] == '(')
            stackPush(stk, i);
        else // string[i] == ')'
        {
            stackPop(stk);
            if (stackSize(stk) != 0)
                length = max(length, i - stackTop(stk));
            else
                stackPush(stk, i);
        }
    }
    return length;
}

int main11() {
    char *expn = "())((()))(())()(()";
    int size = strlen(expn);
    int value = longestContBalParen(expn, size);
    printf("longestContBalParen %d \n", value);
    return 0;
}

int reverseParenthesis(char *expn, int size) {
    Stack* stk = createStack();
    int openCount = 0;
    int closeCount = 0;
    char ch;

    if (size % 2 == 1) {
        printf("Invalid odd length %d ", size);
        return -1;
    }
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(')
            stackPush(stk, ch);
        else if (ch == ')')
            if (stackSize(stk) != 0 && stackTop(stk) == '(')
                stackPop(stk);
            else
                stackPush(stk, ')');
    }
    while (stackSize(stk) != 0) {
        if (stackPop(stk) == '(')
            openCount += 1;
        else
            closeCount += 1;
    }
    int reversal = ceil(openCount / 2.0) + ceil(closeCount / 2.0);
    return reversal;
}
int main12() {
    char *expn = "())((()))(())()(()()()()))";
    char *expn2 = ")(())(((";
    int size = strlen(expn2);
    int value = reverseParenthesis(expn2, size);
    printf("Given expn : %s \n", expn2);
    printf("reverse Parenthesis is : %d \n", value);
    return 0;
}

int findDuplicateParenthesis(char *expn, int size) {
    Stack* stk = createStack();
    char ch;
    int count;

    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == ')') {
            count = 0;
            while (stackSize(stk) != 0 && stackTop(stk) != '(') {
                stackPop(stk);
                count += 1;
            }
            if (count <= 1)
                return 1;
        }
        else
            stackPush(stk, ch);
    }
    return 0;
}

int main13() {
    // expn = "(((a+(b))+(c+d)))"
    // expn = "(b)"
    char *expn = "(((a+b))+c)";
    printf("Given expn : %s ", expn);
    int size = strlen(expn);
    int value = findDuplicateParenthesis(expn, size);
    printf("Duplicate Found : %d", value);
    return 0;
}

void printParenthesisNumber(char *expn, int size) {
    char ch;
    Stack* stk = createStack();
    int output[10];
    int outputIndex = 0;
    int count = 1;
    for (int i = 0; i < size; i++) {
        ch = expn[i];
        if (ch == '(') {
            stackPush(stk, count);
            output[outputIndex++] = count;
            count += 1;
        }
        else if (ch == ')')
            output[outputIndex++] = stackPop(stk);
    }
    printf("Parenthesis Count ");
    for (int i = 0; i < outputIndex; i++) {
        printf(" %d", output[i]);
    }
}
int main14() {
    char *expn1 = "(((a+(b))+(c+d)))";
    char *expn2 = "(((a+b))+c)(((";
    int size = strlen(expn1);
    printf("Given expn %s \n", expn1);
    printParenthesisNumber(expn1, size);
    size = strlen(expn2);
    printf("\nGiven expn %s \n", expn2);
    printParenthesisNumber(expn2, size);
    return 0;
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf(" %d ", arr[i]);
    }
    printf("\n");
}

int precedence(char x) {
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

void infixToPostfix(char *expn, char *output) {
    Stack* stk = createStack();
    char ch, op;
    int i = 0;
    int index = 0;
    int digit = 0;
    while ((ch = expn[i++]) != '\0') {
        if (isdigit(ch)) {
            output[index++] = ch;
            digit = 1;
        } else {
            if (digit) {
                output[index++] = ' ';
                digit = 0;
            }
            switch (ch) {
            case '+':
            case '-':
            case '*':
            case '/':
            case '%':
            case '^':
                while (!stackIsEmpty(stk) && precedence(ch) <= precedence(stackTop(stk)))
                {
                    op = stackPop(stk);
                    output[index++] = op;
                    output[index++] = ' ';
                }
                stackPush(stk, ch);
                break;
            case '(':
                stackPush(stk, ch);
                break;
            case ')':
                while (!stackIsEmpty(stk) && (op = stackPop(stk)) != '(')
                {
                    output[index++] = op;
                    output[index++] = ' ';
                }
                break;
            }
        }
    }
    while (!stackIsEmpty(stk)) {
        op = stackPop(stk);
        output[index++] = op;
        output[index++] = ' ';
    }
    output[index++] = '\0';
}

int main15() {
    char *expn = "10 + ( ( 3 ) ) * 5 / ( 16 - 4 )";
    char out[100];
    infixToPostfix(expn, out);
    printf("Infix Expn: %s \n", expn);
    printf("Postfix Expn: %s \n", out);
    return 0;
}

void reverseString(char *a) {
    int lower = 0;
    int upper = strlen(a) - 1;
    char tempChar;
    while (lower < upper) {
        tempChar = a[lower];
        a[lower] = a[upper];
        a[upper] = tempChar;

        lower++;
        upper--;
    }
}

void replaceParanthesis(char *a) {
    int lower = 0;
    int upper = strlen(a) - 1;
    while (lower <= upper) {
        if (a[lower] == '(')
            a[lower] = ')';
        else if (a[lower] == ')')
            a[lower] = '(';
        lower++;
    }
}

void infixToPrefix(char *expn, char *output) {
    reverseString(expn);
    replaceParanthesis(expn);
    infixToPostfix(expn, output);
    reverseString(output);
}

int main16() {
    char expn[100] = "10 + ( ( 3 ) ) * 5 / ( 16 - 4 )";
    char out[100];
    infixToPrefix(expn, out);
    printf("Infix Expn: %s \n", expn);
    printf("Prefix Expn: %s \n", out);
    return 0;
}

int postfixEvaluate(char *postfix) {
    Stack* s = createStack();
    int i = 0, op1, op2;
    char ch;
    int digit = 0;
    int value = 0;
    while ((ch = postfix[i++]) != '\0') {
        if (isdigit(ch)) {
            digit = 1;
            value = value * 10 + (ch - '0');
        }
        else if (ch == ' ') {
            if (digit == 1) {
                stackPush(s, value); /* Push the operand */
                digit = 0;
                value = 0;
            }
        } else {
            op2 = stackPop(s);
            op1 = stackPop(s);
            switch (ch) {
            case '+':
                stackPush(s, op1 + op2);
                break;
            case '-':
                stackPush(s, op1 - op2);
                break;
            case '*':
                stackPush(s, op1 * op2);
                break;
            case '/':
                stackPush(s, op1 / op2);
                break;
            }
        }
    }
    return stackTop(s);
}

int main17() {
    char expn[] = "6 5 2 3 + 8 * + 3 + *";
    int value = postfixEvaluate(expn);
    printf("Given Postfix Expn: %s \n", expn);
    printf("Result after Evaluation: %d", value);
}

int *StockSpanRange(int arr[], int size) {
    int *SR = (int *)malloc(sizeof(int) * size);
    SR[0] = 1;
    int i = 1;
    int j;

    while (i < size) {
        SR[i] = 1;
        j = i - 1;
        while ((j >= 0) && (arr[i] >= arr[j])) {
            SR[i] += 1;
            j -= 1;
        }
        i += 1;
    }
    return SR;
}

int *StockSpanRange2(int *arr, int size) {
    Stack* stk = createStack();
    int *SR = (int *)malloc(sizeof(int) * size);
    stackPush(stk, 0);
    SR[0] = 1;
    int i = 1;
    while (i < size) {
        while (stackSize(stk) != 0 && arr[stackTop(stk)] <= arr[i])
            stackPop(stk);
        if (stackSize(stk) == 0)
            SR[i] = i + 1;
        else
            SR[i] = i - stackTop(stk);
        stackPush(stk, i);
        i += 1;
    }
    return SR;
}

int main18() {
    int arr[] = {6, 5, 4, 3, 2, 4, 5, 7, 9};
    int size = sizeof(arr) / sizeof(int);
    int *value = StockSpanRange(arr, size);
    printf("StockSpanRange : ");
    printArray(value, size);
    free(value);

    value = StockSpanRange2(arr, size);
    printf("StockSpanRange : ");
    printArray(value, size);
    return 0;
}

int GetMaxArea(int arr[], int size) {
    int maxArea = -1;
    int minHeight = 0;
    int i = 1;
    int j;
    int currArea;

    while (i < size) {
        minHeight = arr[i];
        j = i - 1;
        while (j >= 0) {
            if (minHeight > arr[j])
                minHeight = arr[j];
            currArea = minHeight * (i - j + 1);
            if (maxArea < currArea)
                maxArea = currArea;
            j -= 1;
        }
        i += 1;
    }
    return maxArea;
}

int GetMaxArea2(int arr[], int size) {
    Stack* stk = createStack();
    int maxArea = 0;
    int i = 0;
    int top, topArea;

    while (i < size) {
        while ((i < size) && (stackSize(stk) == 0 || arr[stackTop(stk)] <= arr[i])) {
            stackPush(stk, i);
            i += 1;
        }
        while (stackSize(stk) != 0 && (i == size || arr[stackTop(stk)] > arr[i])) {
            top = stackTop(stk);
            stackPop(stk);
            if (stackSize(stk) == 0) {
                topArea = arr[top] * i;
            }
            else
                topArea = arr[top] * (i - stackTop(stk) - 1);

            if (maxArea < topArea)
                maxArea = topArea;
        }
    }
    return maxArea;
}

int main19() {
    int arr[] = {7, 6, 5, 4, 4, 1, 6, 3, 1};
    int size = sizeof(arr) / sizeof(int);
    int value = GetMaxArea(arr, size);
    printf("GetMaxArea :: %d ", value);
    value = GetMaxArea2(arr, size);
    printf("GetMaxArea :: %d ", value);
    return 0;
}

void nextLargerElement(int arr[], int size) {
    int *output = (int *)malloc(sizeof(int) * size);
    int outIndex = 0;
    int next;

    for (int i = 0; i < size; i++) {
        next = -1;
        for (int j = i + 1; j < size; j++) {
            if (arr[i] < arr[j]) {
                next = arr[j];
                break;
            }
        }
        output[outIndex++] = next;
    }
    printArray(output, outIndex);
}

void nextLargerElement2(int arr[], int size) {
    Stack* stk = createStack();
    //output = [-1] * size;
    int *output = (int *)malloc(sizeof(int) * size);
    int index = 0;
    int curr;

    for (int i = 0; i < size; i++) {
        curr = arr[i];
        // stack always have values in decreasing order.
        while (stackIsEmpty(stk) == 0 && arr[stackTop(stk)] <= curr) {
            index = stackPop(stk);
            output[index] = curr;
        }
        stackPush(stk, i);
    }
    // index which dont have any next Larger.
    while (stackIsEmpty(stk) == 0) {
        index = stackPop(stk);
        output[index] = -1;
    }
    printArray(output, size);
}

int main20() {
    int arr[] = {13, 21, 3, 6, 20, 3};
    int size = sizeof(arr) / sizeof(int);
    printArray(arr, size);
    nextLargerElement(arr, size);
    nextLargerElement2(arr, size);
    return 0;
}

void nextSmallerElement(int arr[], int size) {
    Stack* stk = createStack();
    int *output = (int *)malloc(sizeof(int) * size);
    int curr, index;
    for (int i = 0; i < size; i++) {
        curr = arr[i];
        // stack always have values in increasing order.
        while (stackIsEmpty(stk) == 0 && arr[stackTop(stk)] > curr) {
            index = stackPop(stk);
            output[index] = curr;
        }
        stackPush(stk, i);
    }
    // index which dont have any next Smaller.
    while (stackIsEmpty(stk) == 0) {
        index = stackPop(stk);
        output[index] = -1;
    }
    printArray(output, size);
}

int main21() {
    int arr[] = {13, 21, 3, 6, 20, 3};
    int size = sizeof(arr) / sizeof(int);
    printArray(arr, size);
    nextSmallerElement(arr, size);
    return 0;
}

void nextLargerElementCircular(int arr[], int size) {
    Stack* stk = createStack();
    int curr, index;
    int *output = (int *)malloc(sizeof(int) * size);
    for (int i = 0; i < (2 * size - 1); i++) {
        curr = arr[i % size];
        // stack always have values in decreasing order.
        while (stackIsEmpty(stk) == 0 && arr[stackTop(stk)] <= curr) {
            index = stackPop(stk);
            output[index] = curr;
        }
        stackPush(stk, i % size);
    }
    // index which dont have any next Larger.
    while (stackIsEmpty(stk) == 0) {
        index = stackPop(stk);
        output[index] = -1;
    }
    printArray(output, size);
}

int main22() {
    int arr[] = {6, 3, 9, 8, 10, 2, 1, 15, 7};
    int size = sizeof(arr) / sizeof(int);
    nextLargerElementCircular(arr, size);
    return 0;
}

int infi = 99999;

void RottenFruitUtil(int arr[][5], int maxCol, int maxRow,
                     int currCol, int currRow, int **traversed, int day) { // Range check
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return;
    // Traversable and rot if not already rotten.
    if (traversed[currCol][currRow] <= day || arr[currCol][currRow] == 0)
        return;
    // Update rot time.
    traversed[currCol][currRow] = day;
    // each line corresponding to 4 direction.
    RottenFruitUtil(arr, maxCol, maxRow, currCol - 1, currRow, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol + 1, currRow, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol, currRow + 1, traversed, day + 1);
    RottenFruitUtil(arr, maxCol, maxRow, currCol, currRow - 1, traversed, day + 1);
}

int RottenFruit(int arr[][5], int maxCol, int maxRow) {
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol - 1; i++) {
        for (int j = 0; j < maxRow - 1; j++) {
            if (arr[i][j] == 2)
                RottenFruitUtil(arr, maxCol, maxRow, i, j, traversed, 0);
        }
    }

    int maxDay = 0;
    for (int i = 0; i < maxCol - 1; i++) {
        for (int j = 0; j < maxRow - 1; j++) {
            if (arr[i][j] == 1) {
                if (traversed[i][j] == infi)
                    return -1;
                if (maxDay < traversed[i][j])
                    maxDay = traversed[i][j];
            }
        }
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);

    return maxDay;
}

int main23() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {2, 1, 0, 1, 0},
        {0, 0, 0, 2, 1},
        {0, 2, 0, 0, 1},
        {1, 1, 0, 0, 1}};

    printf("%d", RottenFruit(arr, 5, 5));
    return 0;
}


void StepsOfKnightUtil(int size, int currCol, int currRow, int **traversed, int dist) { // Range check
    if (currCol < 0 || currCol >= size || currRow < 0 || currRow >= size)
        return;

    // Traversable and rot if not already rotten.
    if (traversed[currCol][currRow] <= dist)
        return;

    // Update rot time.
    traversed[currCol][currRow] = dist;
    // each line corresponding to 4 direction.
    StepsOfKnightUtil(size, currCol - 2, currRow - 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 2, currRow + 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 2, currRow - 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 2, currRow + 1, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 1, currRow - 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 1, currRow - 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol - 1, currRow + 2, traversed, dist + 1);
    StepsOfKnightUtil(size, currCol + 1, currRow + 2, traversed, dist + 1);
}

int StepsOfKnight(int size, int srcX, int srcY, int dstX, int dstY) {
    int **traversed;
    traversed = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++) {
        traversed[i] = (int *)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            traversed[i][j] = infi;
        }
    }

    StepsOfKnightUtil(size, srcX - 1, srcY - 1, traversed, 0);
    int retval = traversed[dstX - 1][dstY - 1];

    for (int i = 0; i < size; i++)
        free(traversed[i]);
    free(traversed);

    return retval;
}

int main24() {
    printf("stepsOfKnight :: %d ", StepsOfKnight(20, 10, 10, 20, 20));
    return 0;
}

void DistNearestFillUtil(int arr[][5], int maxCol, int maxRow, int currCol, int currRow, int **traversed, int dist) { // Range check
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return;
    // Traversable if their is a better distance.
    if (traversed[currCol][currRow] <= dist)
        return;
    // Update distance.
    traversed[currCol][currRow] = dist;
    // each line corresponding to 4 direction.
    DistNearestFillUtil(arr, maxCol, maxRow, currCol - 1, currRow, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol + 1, currRow, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol, currRow + 1, traversed, dist + 1);
    DistNearestFillUtil(arr, maxCol, maxRow, currCol, currRow - 1, traversed, dist + 1);
}

void DistNearestFill(int arr[][5], int maxCol, int maxRow) {
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            if (arr[i][j] == 1)
                DistNearestFillUtil(arr, maxCol, maxRow, i, j, traversed, 0);
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            printf("%d ", traversed[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}

int main25() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}};
    DistNearestFill(arr, 5, 5);
    return 0;
}

int findLargestIslandUtil(int arr[][5], int maxCol, int maxRow, int currCol,
                          int currRow, int value, int **traversed) {
    if (currCol < 0 || currCol >= maxCol || currRow < 0 || currRow >= maxRow)
        return 0;
    if (traversed[currCol][currRow] == 1 || arr[currCol][currRow] != value)
        return 0;
    traversed[currCol][currRow] = 1;
    // each call corresponding to 8 direction.
    return 1 +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol - 1, currRow + 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol, currRow + 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow - 1, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow, value, traversed) +
           findLargestIslandUtil(arr, maxCol, maxRow, currCol + 1, currRow + 1, value, traversed);
}

int findLargestIsland(int arr[][5], int maxCol, int maxRow) {
    int maxVal = 0;
    int currVal = 0;
    int **traversed;
    traversed = (int **)malloc(maxCol * sizeof(int *));
    for (int i = 0; i < maxCol; i++) {
        traversed[i] = (int *)malloc(maxRow * sizeof(int));
        for (int j = 0; j < maxRow; j++) {
            traversed[i][j] = infi;
        }
    }

    for (int i = 0; i < maxCol; i++) {
        for (int j = 0; j < maxRow; j++) {
            {
                currVal = findLargestIslandUtil(arr, maxCol, maxRow, i, j, arr[i][j], traversed);
                if (currVal > maxVal)
                    maxVal = currVal;
            }
        }
        return maxVal;
    }

    for (int i = 0; i < maxCol; i++)
        free(traversed[i]);
    free(traversed);
}

int main26() {
    int arr[5][5] = {
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {1, 1, 0, 0, 1}};
    printf("Largest Island : %d", findLargestIsland(arr, 5, 5));
    return 0;
}

int isKnown(int relation[][5], int a, int b) {
    if (relation[a][b] == 1)
        return 1;
    return 0;
}

int findCelebrity(int relation[][5], int count) {
    Stack* stk = createStack();
    int first = 0, second = 0;
    for (int i = 0; i < count; i++) {
        stackPush(stk, i);
    }
    first = stackPop(stk);
    while (stackSize(stk) != 0) {
        second = stackPop(stk);
        if (isKnown(relation, first, second))
            first = second;
    }
    for (int i = 0; i < count; i++) {
        if (first != i && isKnown(relation, first, i))
            return -1;
        if (first != i && isKnown(relation, i, first) == 0)
            return -1;
    }
    return first;
}

int findCelebrity2(int relation[][5], int count) {
    int first = 0;
    int second = 1;

    for (int i = 0; i < (count - 1); i++) {
        if (isKnown(relation, first, second))
            first = second;
        second = second + 1;
    }
    for (int i = 0; i < count; i++) {
        if (first != i && isKnown(relation, first, i))
            return -1;
        if (first != i && isKnown(relation, i, first) == 0)
            return -1;
    }
    return first;
}

int main27() {
    int arr[][5] = {
        {1, 0, 1, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 0, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1}};

    printf("Celebrity : %d ", findCelebrity(arr, 5));
    printf("Celebrity : %d ", findCelebrity2(arr, 5));
    return 0;
}

int IsMinHeap(int arr[], int size) {
    for (int i = 0; i <= (size - 2) / 2; i++) {
        if (2 * i + 1 < size) {
            if (arr[i] > arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size) {
            if (arr[i] > arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}

int IsMaxHeap(int arr[], int size) {
    for (int i = 0; i <= (size - 2) / 2; i++) {
        if (2 * i + 1 < size) {
            if (arr[i] < arr[2 * i + 1])
                return 0;
        }
        if (2 * i + 2 < size) {
            if (arr[i] < arr[2 * i + 2])
                return 0;
        }
    }
    return 1;
}

int main()
{
    main1();
    main2();
    main3();
    main4();
    main5();
    main6();  
    main7();
    main8();
    main9();
    main10();
    main11();
    main12();
    main13();
    main14();
    main15();
    main16();
    main17();
    main18();
    main19();
    main20();
    main21();
    main22();
    main23();
    main24();
    main25();
    main26();
    main27();
    return 0;
}