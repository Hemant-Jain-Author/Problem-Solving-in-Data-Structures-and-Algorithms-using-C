#include <stdlib.h>
#include <stdio.h>
#define ERROR_VALUE -9999999

typedef struct StackNode {
    int value;
    struct StackNode *next;
} StackNode;


typedef struct Stack {
    StackNode *head;
} Stack;

Stack* createStack() {
    Stack *stk = (Stack*)malloc(sizeof(Stack));
    stk->head = NULL;
    return stk;
}

int stackIsEmpty(Stack *stk) {
    return stk->head == NULL;
}

void stackPush(Stack *stk, int value) {
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    if (!temp) {
        printf("Memory allocation error.\n");
        return;
    }
    temp->value = value;
    temp->next = stk->head;
    stk->head = temp;
}

int stackPop(Stack *stk) {
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

void stackPrint(Stack *stk) {
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
    stackPush(stk, 1);
    stackPush(stk, 2);
    stackPush(stk, 3);
    stackPrint(stk);
    printf("%d ", stackPop(stk));
    printf("%d ", stackPop(stk));
    return 0;
}
/*
Stack : 3 2 1 
3 2 
*/