#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treeNode_t
{
    char *value;
    int count;
    struct treeNode_t *lChild;
    struct treeNode_t *rChild;
} TreeNode;

void printTree(TreeNode *root) /*   pre order  */
{
    if (root)
    {
        printf(" value is :: %s " ,root->value);
        printf(" count is :: %d \n", root->count);
        printTree(root->lChild);
        printTree(root->rChild);
    }
}

TreeNode *insertNodeUtil(char *value, TreeNode *root)
{
    int compare;
    if (root == NULL)
    {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        if (root == NULL)
        {
            printf("fallel memory shortage ...");
            return root;
        }
        root->value = (char *)malloc((1 + strlen(value)) * sizeof(char));
        strcpy(root->value, value);
        root->lChild = root->rChild = NULL;
        root->count = 1;
    }
    else
    {
        compare = strcmp(root->value, value);
        if (compare == 0)
        {
            root->count++;
        }
        else if (compare == 1)
        {
            root->lChild = insertNodeUtil(value, root->lChild);
        }
        else
        {
            root->rChild = insertNodeUtil(value, root->rChild);
        }
    }
    return root;
}

void insertNode(char *value, TreeNode **ptrRoot)
{
    *ptrRoot = insertNodeUtil(value, *ptrRoot);
}

TreeNode *freeTreeUtil(TreeNode *root)
{
    if (root)
    {
        freeTreeUtil(root->lChild);
        freeTreeUtil(root->rChild);
        free(root->value);
        free(root);
    }
    return NULL;
}
void freeTree(TreeNode **rootPtr)
{
    *rootPtr = freeTreeUtil(*rootPtr);
}
TreeNode *findNode(TreeNode *root, char *value)
{
    int compare;
    if (!root)
        return NULL;
    compare = strcmp(root->value, value);
    if (compare == 0)
        return root;
    else
    {
        if (compare == 1)
            return findNode(root->lChild, value);
        else
            return findNode(root->rChild, value);
    }
}

int frequency(TreeNode *root, char *value)
{
    int compare;
    if (!root)
        return 0;
    compare = strcmp(root->value, value);
    if (compare == 0)
        return root->count;
    else
    {
        if (compare == 1)
            return frequency(root->lChild, value);
        else
            return frequency(root->rChild, value);
    }
}

int getword(char *a, FILE *fp)
{
    int i = 0;
    while (1)
    {
        a[i] = getc(fp);
        if (a[i] == EOF)
        {
            a[i] = '\0';
            return 0;
        }
        else if (a[i] == ' ' || a[i] == '\t' || a[i] == '\n')
        {
            a[i] = '\0';
            return 1;
        }
        i++;
    }
}

int main()
{

    TreeNode *root = NULL;
    TreeNode *temp = NULL;
    FILE *fp = fopen("String.c", "r");
    char a[100];
    while (getword(a, fp))
    {
        root = insertNodeUtil(a, root);
    }
    printTree(root);
    printf("\n");
    printf("quency returned :: %d ",frequency(root, "0"));
    printf("\n");
}
