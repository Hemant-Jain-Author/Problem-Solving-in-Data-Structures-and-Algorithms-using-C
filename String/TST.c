#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tstNode
{
    char data;
    unsigned isLastChar : 1;
    struct tstNode *left, *equal, *right;
} TSTNode;

TSTNode *newNode(char data)
{
    TSTNode *temp = (TSTNode *)malloc(sizeof(TSTNode));
    temp->data = data;
    temp->isLastChar = 0;
    temp->left = temp->equal = temp->right = NULL;
    return temp;
}
void insertTST(TSTNode **root, char *word)
{

    if (!(*root))
        *root = newNode(*word);

    if ((*word) < (*root)->data)
        insertTST(&((*root)->left), word);
    else if ((*word) > (*root)->data)
        insertTST(&((*root)->right), word);
    else
    {
        if (*(word + 1))
            insertTST(&((*root)->equal), word + 1);
        else
            (*root)->isLastChar = 1;
    }
}
int findTSTUtil(TSTNode *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return findTSTUtil(root->left, word);
    else if (*word > (root)->data)
        return findTSTUtil(root->right, word);
    else
    {
        if (*(word + 1) == '\0')
            return root->isLastChar;

        return findTSTUtil(root->equal, word + 1);
    }
}
int findTST(TSTNode *root, char *word)
{
    int ret = findTSTUtil(root, word);
    printf(" %s : ", word);
    ret ? printf("Found\n") : printf("Not Found\n");
    return ret;
}
int main()
{
    TSTNode *root = NULL;
    insertTST(&root, "banana");
    insertTST(&root, "apple");
    insertTST(&root, "mango");

    printf("\nSearch results for apple, banana, grapes and mango :\n");
    findTST(root, "apple");
    findTST(root, "banana");
    findTST(root, "grapes");
    findTST(root, "mango");
    return 0;
}

