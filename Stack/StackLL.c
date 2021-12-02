#include <stdlib.h>
#include <stdio.h>
#define ERROR_VALUE -99999

typedef struct StackNode
{
    int value;
    struct StackNode *next;
} StackNode;


typedef struct Stack
{
    StackNode *head;
} Stack;

Stack* createStack() 
{
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->head = NULL;
    return stk;
}

int StackIsEmpty(Stack *stk) {
    return stk->head == NULL;
}

void StackPush(Stack *stk, int value) {
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    if (!temp) {
        printf("Memory allocation error.\n");
        return;
    }
    temp->value = value;
    temp->next = stk->head;
    stk->head = temp;
}

int StackPop(Stack *stk) {
    StackNode *deleteMe;
    if(stk->head == NULL) {
        printf("Stack is empty.\n");
        return ERROR_VALUE;
    }
    deleteMe = stk->head;
    stk->head = stk->head->next;
    int value = deleteMe->value;
    free(deleteMe);
    return value;
}

void StackPrint(Stack *stk) {
    if (!stk->head)
        return;

    StackNode *head = stk->head;
    printf("Stack : ");
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}


int main() {
    Stack* stk= createStack();
    StackPush(stk, 1);
    StackPush(stk, 2);
    StackPush(stk, 3);
    StackPrint(stk);
    while (!StackIsEmpty(stk))
        printf("%d ", StackPop(stk));
    return 0;
}
