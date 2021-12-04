#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char *value;
    int count;
    struct TreeNode *lChild;
    struct TreeNode *rChild;
} TreeNode;

TreeNode *createTreeNode(char* value, TreeNode *left, TreeNode *right) {
    TreeNode *node = (TreeNode*) malloc(sizeof(TreeNode));
    node->value = value;
    node->value = (char *)malloc((1 + strlen(value)) * sizeof(char));
    strcpy(node->value, value);
    node->count = 1;
    node->lChild = left;
    node->rChild = right;
    return node;
}

typedef struct StringTree {
    TreeNode *root;
} StringTree;

StringTree *createTree() {
    StringTree *tree = (StringTree*)malloc(sizeof(StringTree));
    tree->root = NULL;
    return tree;
}

void printTreeUtil(TreeNode *root) /*   pre order  */
{
    if (root) {
        printf("(value: %s, count: %d) ", root->value, root->count);
        printTreeUtil(root->lChild);
        printTreeUtil(root->rChild);
    }
}

void printTree(StringTree* tree) {
    printTreeUtil(tree->root);
    printf("\n");
}

TreeNode *addTreeUtil(TreeNode *root, char *value) {
    if (root == NULL) {
        return createTreeNode(value, NULL, NULL);
    }

    int compare = strcmp(root->value, value);
    if (compare == 0) {
        root->count++;
    } else if (compare > 0) {
        root->lChild = addTreeUtil(root->lChild, value);
    } else {
        root->rChild = addTreeUtil(root->rChild, value);
    }
    return root;
}

void addTree(StringTree* tree, char *value) {
    tree->root = addTreeUtil(tree->root, value);
}

TreeNode *freeTreeUtil(TreeNode *root) {
    if (root) {
        freeTreeUtil(root->lChild);
        freeTreeUtil(root->rChild);
        free(root->value);
        free(root);
    }
    return NULL;
}

void freeTree(StringTree* tree) {
    tree->root = freeTreeUtil(tree->root);
}

TreeNode *findTreeUtil(TreeNode *root, char *value) {
    if (!root)
        return NULL;
    
    int compare = strcmp(root->value, value);

    if (compare == 0)
        return root;
    else if (compare > 0)
        return findTreeUtil(root->lChild, value);
    else
        return findTreeUtil(root->rChild, value);
}

int findTree(StringTree* tree, char *value) {
    if(findTreeUtil(tree->root, value))
        return 1;
    return 0;
}

int frequency(TreeNode *root, char *value) {
    if (!root)
        return 0;

    int compare = strcmp(root->value, value);
    if (compare == 0)
        return root->count;
    else if (compare > 0)
        return frequency(root->lChild, value);
    else
        return frequency(root->rChild, value);
}

int main() {
    StringTree *tt = createTree();
    addTree(tt, "banana");
    addTree(tt, "apple");
    addTree(tt, "mango");

    printf("find apple : %d\n", findTree(tt, "apple"));
    printf("find apple : %d\n", findTree(tt, "banana"));
    printf("find apple : %d\n", findTree(tt, "grapes"));
    printf("find apple : %d\n", findTree(tt, "mango"));
}

/*
find apple : 1
find apple : 1
find apple : 0
find apple : 1
*/