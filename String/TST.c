#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TSTNode {
    char data;
    unsigned isLastChar : 1;
    struct TSTNode *left, *equal, *right;
} TSTNode;

TSTNode* createNode(char data) {
    TSTNode *node = (TSTNode *)malloc(sizeof(TSTNode));
    node->data = data;
    node->isLastChar = 0;
    node->left = node->equal = node->right = NULL;
    return node;
}

typedef struct TST {
    TSTNode *root;
} TST;

TST* createTST() {
    TST* tst = (TST*)malloc(sizeof(TST));
    tst->root = NULL;
    return tst;
}

TSTNode* addTSTUtil(TSTNode *node, char *word) {
    if (!node)
        node = createNode(*word);

    if ((*word) < node->data)
        node->left = addTSTUtil(node->left, word);
    else if ((*word) > node->data)
        node->right = addTSTUtil(node->right, word);
    else if (*(word + 1)) // equal but not last char.
        node->equal = addTSTUtil(node->equal, word + 1);
    else // equal and last char.
        node->isLastChar = 1;

    return node;
}

void addTST(TST *tst, char *word) {
    tst->root = addTSTUtil(tst->root, word);
}

int findTSTUtil(TSTNode *node, char *word) {
    if (!node)
        return 0;

    if (*word < node->data)
        return findTSTUtil(node->left, word);
    else if (*word > node->data)
        return findTSTUtil(node->right, word);
    else if (*(word + 1)) // equal but not last character.
        return findTSTUtil(node->equal, word + 1);        
    else // equal and last character.
        return node->isLastChar;
}

int findTST(TST *tst, char *word) {
    return findTSTUtil(tst->root, word);
}

int removeTSTUtil(TSTNode *node, char *word) {
    if (!node)
        return 0;

    if (*word < (node)->data)
        return removeTSTUtil(node->left, word);
    else if (*word > node->data)
        return removeTSTUtil(node->right, word);
    else if (*(word + 1)) // equal but not last character.
        return removeTSTUtil(node->equal, word + 1);        
    else if(node->isLastChar)// equal and last character.
    {
        node->isLastChar = 0; 
        return 1;
    } 
    return 0;
    
}

int removeTST(TST *tst, char *word) {
    return removeTSTUtil(tst->root, word);
}

int main() {
    TST *tst = createTST();
    addTST(tst, "banana");
    addTST(tst, "apple");
    addTST(tst, "mango");

    printf("find apple : %d\n", findTST(tst, "apple"));
    printf("find banana : %d\n", findTST(tst, "banana"));
    printf("find grapes : %d\n", findTST(tst, "grapes"));
    printf("find mango : %d\n", findTST(tst, "mango"));

    return 0;
}

/*
find apple : 1
find banana : 1
find grapes : 0
find mango : 1
*/