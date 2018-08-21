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
void insert(TSTNode **root, char *word)
{

    if (!(*root))
        *root = newNode(*word);

    if ((*word) < (*root)->data)
        insert(&((*root)->left), word);
    else if ((*word) > (*root)->data)
        insert(&((*root)->right), word);
    else
    {
        if (*(word + 1))
            insert(&((*root)->equal), word + 1);
        else
            (*root)->isLastChar = 1;
    }
}
int searchTST(TSTNode *root, char *word)
{
    if (!root)
        return 0;

    if (*word < (root)->data)
        return searchTST(root->left, word);
    else if (*word > (root)->data)
        return searchTST(root->right, word);
    else
    {
        if (*(word + 1) == '\0')
            return root->isLastChar;

        return searchTST(root->equal, word + 1);
    }
}
int searchTSTWrapper(TSTNode *root, char *word)
{
    int ret = searchTST(root, word);
    printf(" %s : ", word);
    ret ? printf("Found\n") : printf("Not Found\n");
    return ret;
}
int main()
{
    TSTNode *root = NULL;
    insert(&root, "banana");
    insert(&root, "apple");
    insert(&root, "mango");

    printf("\nSearch results for apple, banana, grapes and mango :\n");
    searchTSTWrapper(root, "apple");
    searchTSTWrapper(root, "banana");
    searchTSTWrapper(root, "grapes");
    searchTSTWrapper(root, "mango");

    return 0;
}

