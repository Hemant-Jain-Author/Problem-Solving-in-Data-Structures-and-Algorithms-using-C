#include <stdio.h>
#include <stdlib.h>

typedef struct Node_t
{
    int value;
    struct Node_t *lChild;
    struct Node_t *rChild;
} TreeNode;

typedef struct tree_t
{
    TreeNode* root;
} Tree;

Tree* createTree()
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

TreeNode *insertUtil(TreeNode *root, int value)
{
    if (root == NULL)
    {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        if (root == NULL)
        {
            printf("Memory allocation error.");
            return root;
        }
        root->value = value;
        root->lChild = root->rChild = NULL;
    }
    else
    {
        if (root->value >= value)
            root->lChild = insertUtil(root->lChild, value);
        else
            root->rChild = insertUtil(root->rChild, value);
    }
    return root;
}

void insert(Tree *tree, int value)
{
    tree->root = insertUtil(tree->root, value);
}

void printPreOrderUtil(TreeNode *root) /* pre order  */
{
    if (root)
    {
        printf("%d ", root->value);
        printPreOrderUtil(root->lChild);
        printPreOrderUtil(root->rChild);
    }
}

void printPreOrder(Tree *tree)
{
    printPreOrderUtil(tree->root);
}

void printPostOrderUtil(TreeNode *root) /*  post order  */
{
    if (root)
    {
        printPostOrderUtil(root->lChild);
        printPostOrderUtil(root->rChild);
        printf("%d ", root->value);
    }
}

void printPostOrder(Tree *tree)
{
    printPostOrderUtil(tree->root);
}

void printInOrderUtil(TreeNode *root) /*  in order  */
{
    if (root)
    {
        printInOrderUtil(root->lChild);
        printf("%d ", root->value);
        printInOrderUtil(root->rChild);
    }
}

void printInOrder(Tree *tree)
{
    printInOrderUtil(tree->root);
}

void freeTreeUtil(TreeNode *root)
{
    if (root)
    {
        freeTreeUtil(root->lChild);
        freeTreeUtil(root->rChild);
        free(root);
    }
}

void freeTree(Tree *tree)
{
    freeTreeUtil(tree->root);
    tree->root = NULL;
}

TreeNode *findNode(TreeNode *root, int value)
{
    if (!root)
        return NULL;

    if (root->value == value)
        return root;
    else if (root->value > value)
        return findNode(root->lChild, value);
    else
        return findNode(root->rChild, value);
}

int find(Tree *tree, int value)
{
    if (findNode(tree->root, value) != NULL)
        return 1;

    return 0;
}

TreeNode *findMinNode(TreeNode *root)
{
    if (!root)
        return NULL;

    while (root->lChild)
    {
        root = root->lChild;
    }
    return root;
}

int findMin2(Tree *tree)
{
    TreeNode *tmp = findMinNode(tree->root);
    if(tmp)
        return tmp->value;
    return 9999;
}

TreeNode *findMinNodeRec(TreeNode *root)
{
    if (!root)
        return NULL;

    if (root->lChild == NULL)
        return root;
    else
        return findMinNodeRec(root->lChild);
}

int findMin3(Tree *tree)
{
    TreeNode *tmp = findMinNodeRec(tree->root);
    if(tmp)
        return tmp->value;
    return 9999;
}

TreeNode *findMaxNode(TreeNode *root)
{
    if (!root)
        return NULL;

    while (root->rChild)
    {
        root = root->rChild;
    }
    return root;
}

TreeNode *findMaxNodeRec(TreeNode *root)
{
    if (!root)
        return NULL;

    if (root->rChild == NULL)
        return root;
    else
        return findMaxNodeRec(root->rChild);
}

int findMax(Tree *tree)
{
    TreeNode *root = tree->root;
    if (!root)
        return -999;

    while (root->rChild)
    {
        root = root->rChild;
    }
    return root->value;
}

int maxValue(TreeNode *root )
{
    if (!root)
        return -999;

    while (root->rChild)
    {
        root = root->rChild;
    }
    return root->value;
}

int findMin(Tree *tree)
{
    TreeNode *root = tree->root;
    if (!root)
        return -999;

    while (root->lChild)
    {
        root = root->lChild;
    }
    return root->value;
}

int minValue(TreeNode *root)
{
    if (!root)
        return -999;

    while (root->lChild)
    {
        root = root->lChild;
    }
    return root->value;
}

TreeNode *deleteNodeUtil(TreeNode *root, int value)
{
    if (!root)
        return NULL;

    if (root->value == value)
    {
        if (root->lChild == NULL && root->rChild == NULL)
        {
            free(root);
            return NULL;
        }
        else
        {
            TreeNode *temp = NULL;
            if (root->lChild == NULL)
            {
                temp = root->rChild;
                free(root);
                return temp;
            }
            if (root->rChild == NULL)
            {
                temp = root->lChild;
                free(root);
                return temp;
            }

            int mx = maxValue(root->lChild);
            root->value = mx;
            root->lChild = deleteNodeUtil(root->lChild, mx);
        }
    }
    else
    {
        if (root->value > value)
            root->lChild = deleteNodeUtil(root->lChild, value);
        else
            root->rChild = deleteNodeUtil(root->rChild, value);
    }
    return root;
}

void deleteNode(Tree *tree, int value)
{
    tree->root = deleteNodeUtil(tree->root, value);
}

int treeDepthUtil(TreeNode *root)
{
    if (!root)
        return 0;

    int lDepth = treeDepthUtil(root->lChild);
    int rDepth = treeDepthUtil(root->rChild);

    if (lDepth > rDepth)
        return lDepth + 1;
    else
        return rDepth + 1;
}

int treeDepth(Tree *tree)
{
    return treeDepthUtil(tree->root);
}

TreeNode *copyTreeUtil(TreeNode *root)
{
    if (!root)
        return NULL;

    TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
    if (!temp)
        return NULL;

    temp->value = root->value;
    temp->lChild = copyTreeUtil(root->lChild);
    temp->rChild = copyTreeUtil(root->rChild);
    return temp;
}

void copyTree(Tree *src, Tree *dest)
{
    dest->root = copyTreeUtil(src->root);
}

TreeNode *copyMirrorTreeUtil(TreeNode *root)
{
    TreeNode *temp;

    if (!root)
        return NULL;

    temp = (TreeNode *)malloc(sizeof(TreeNode));
    if (!temp)
        return NULL;

    temp->value = root->value;
    temp->lChild = copyMirrorTreeUtil(root->rChild);
    temp->rChild = copyMirrorTreeUtil(root->lChild);
    return temp;
}

void copyMirrorTree(Tree *src, Tree *dest)
{
    dest->root = copyMirrorTreeUtil(src->root);
}

void printMirrorUtil(TreeNode *root)
{
    if (!root)
        return;

    printf(" %d ", root->value);
    printMirrorUtil(root->rChild);
    printMirrorUtil(root->lChild);
    return;
}

void printMirror(Tree *tree)
{
    printMirrorUtil(tree->root);
    return;
}

TreeNode *NthPreeOrderUtil(TreeNode *root, int index) /* pre order  */
{
    static int count = 0;

    if (!root)
        NULL;

    count++;
    if (count == index)
        return root;

    TreeNode *temp = NthPreeOrderUtil(root->lChild, index);
    if (temp)
        return temp;

    temp = NthPreeOrderUtil(root->rChild, index);
    if (temp)
        return temp;

    return NULL;
}

int NthPreeOrder(Tree *tree, int index)
{
    TreeNode *temp = NthPreeOrderUtil(tree->root, index);
    if (temp)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}

TreeNode *NthPostOrderUtil(TreeNode *root, int index) /*  post order  */
{
    static int count = 0;

    if (root)
        return NULL;

            TreeNode *
            temp = NthPostOrderUtil(root->lChild, index);
    if (temp)
        return temp;

    temp = NthPostOrderUtil(root->rChild, index);
    if (temp)
        return temp;

    count++;
    if (count == index)
        return root;

    return NULL;
}

int NthPostOrder(Tree *tree, int index)
{
    TreeNode *temp = NthPostOrderUtil(tree->root, index);
    if (temp)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}

TreeNode *NthInOrderUtil(TreeNode *root, int index) /*  in order  */
{
    static int count = 0;

    if (root)
        return NULL;

    TreeNode *temp = NthInOrderUtil(root->lChild, index);
    if (temp)
        return temp;

    count++;
    if (count == index)
        return root;

    temp = NthInOrderUtil(root->rChild, index);
    if (temp)
        return temp;

    return NULL;
}

int NthInOrder(Tree *tree, int index)
{
    TreeNode *temp = NthInOrderUtil(tree->root, index);
    if (temp)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}

int numNodesUtil(TreeNode *root)
{
    if (!root)
        return 0;

    return (1 + numNodesUtil(root->rChild) + numNodesUtil(root->lChild));
}

int numNodes(Tree *tree)
{
    return numNodesUtil(tree->root);
}

int numLeafsUtil(TreeNode *root)
{
    if (!root)
        return 0;

    if (!root->lChild && !root->rChild)
        return 1;

    return (numLeafsUtil(root->rChild) + numLeafsUtil(root->lChild));
}

int numLeafs(Tree *tree)
{
    return numLeafsUtil(tree->root);
}

int isIdenticalUtil(TreeNode *root1, TreeNode *root2)
{
    if (!root1 && !root2)
        return 1;

    if (!root1 || !root2)
        return 0;

    return isIdenticalUtil(root1->lChild, root2->lChild) &&
           isIdenticalUtil(root1->rChild, root2->rChild) &&
           (root1->value == root2->value);
}

int isIdentical(Tree *tree1, Tree *tree2)
{
    return isIdenticalUtil(tree1->root, tree2->root);
}

int isBSTUtil(TreeNode *root)
{
    if (!root)
        return 1;

    if ((root->lChild && maxValue(root->lChild) > root->value) ||
        (root->rChild && minValue(root->rChild) <= root->value))
        return 0;

    return isBSTUtil(root->lChild) && isBSTUtil(root->rChild);
}

int isBST(Tree *tree)
{
    return isBSTUtil(tree->root);
}

int isBSTUtil2(TreeNode *root, int min, int max)
{
    if (!root)
        return 1;

    if (root->value < min || root->value > max)
        return 0;

    return isBSTUtil2(root->lChild, min, root->value) &&
           isBSTUtil2(root->rChild, root->value, max);
}

#define INT_MIN -99999
#define INT_MAX 99999

int isBST2(Tree *tree)
{
    return isBSTUtil2(tree->root, INT_MIN, INT_MAX);
}

int isBSTUtil3(TreeNode *root, int *value) /*  in order  */
{
    if (!root)
        return 1;

    if (!isBSTUtil3(root->lChild, value))
        return 0;

    if (*value > root->value)
        return 0;

    *value = root->value;

    if (!isBSTUtil3(root->rChild, value))
        return 0;

    return 1;
}

int isBST3(Tree *tree)
{
    int temp = 0;
    return isBSTUtil3(tree->root, &temp);
}

TreeNode *findNodeIterative(TreeNode *root, int value) /* iterative */
{
    while (root)
    {
        if (root->value == value)
            return root;
        else if (root->value > value)
            root = root->lChild;
        else
            root = root->rChild;
    }
    return NULL;
}

TreeNode *LcaBST(TreeNode *root, TreeNode *firstPtr, TreeNode *secondPtr)
{
    if (!firstPtr || !secondPtr || !root)
        return root;

    if (root->value > firstPtr->value &&
        root->value > secondPtr->value)
    {
        return LcaBST(root->lChild, firstPtr, secondPtr);
    }
    if (root->value < firstPtr->value &&
        root->value < secondPtr->value)
    {
        return LcaBST(root->rChild, firstPtr, secondPtr);
    }
    return root;
}

int findNodeDepth(TreeNode *root, TreeNode *dstPtr)
{
    int value;
    if (!root || !dstPtr)
        return -1;

    if (root->value == dstPtr->value)
        return 0;
    else
    {
        if (root->value > dstPtr->value)
            value = findNodeDepth(root->lChild, dstPtr);
        else
            value = findNodeDepth(root->rChild, dstPtr);

        if (value != -1)
            return (value + 1);
    }
}

int pathLength(TreeNode *root, TreeNode *firstPtr, TreeNode *secondPtr)
{
    TreeNode *parent = LcaBST(root, firstPtr, secondPtr);
    int first = findNodeDepth(parent, firstPtr);
    int second = findNodeDepth(parent, secondPtr);
    return first + second;
}

TreeNode *LcaBT(TreeNode *root, TreeNode *firstPtr, TreeNode *secondPtr)
{
    if (root == NULL)
        return NULL;

    if (root == firstPtr || root == secondPtr)
        return root;

    TreeNode *left = LcaBT(root->lChild, firstPtr, secondPtr);
    TreeNode *right = LcaBT(root->rChild, firstPtr, secondPtr);

    if (left && right)
        return root;
    else if (left)
        return left;
    else
        return right;
}

int findMaxBTUtil(TreeNode *root)
{
    if (root == NULL)
        return INT_MIN;

    int max = root->value;
    int left = findMaxBTUtil(root->lChild);
    int right = findMaxBTUtil(root->rChild);

    if (left > max)
        max = left;
    if (right > max)
        max = right;

    return max;
}

int findMaxBT(Tree *tree)
{
    return findMaxBTUtil(tree->root);
}

int findMinBTUtil(TreeNode *root)
{
    if (root == NULL)
        return INT_MAX;

    int min = root->value;
    int left = findMinBTUtil(root->lChild);
    int right = findMinBTUtil(root->rChild);

    if (left < min)
        min = left;
    if (right < min)
        min = right;

    return min;
}

int findMinBT(Tree *tree)
{
    return findMinBTUtil(tree->root);
}

int searchBTUtil(TreeNode *root, int value)
{
    if (root == NULL)
        return 0;

    if ((root->value == value) || 
            searchBTUtil(root->lChild, value) || 
            searchBTUtil(root->rChild, value))
        return 1;

    return 0;
}

int searchBT(Tree *tree, int value)
{
    return searchBTUtil(tree->root, value);
}

int maxDepthBTUtil(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int max = 0;
    int left = maxDepthBTUtil(root->lChild);
    int right = maxDepthBTUtil(root->rChild);

    if (left > max)
        max = left;
    if (right > max)
        max = right;

    return max + 1;
}

int maxDepthBT(Tree *tree)
{
    return maxDepthBTUtil(tree->root);
}

int numFullNodesBTUtil(TreeNode *root)
{
    if (root == NULL)
        return 0;

    int count = 0;
    count += numFullNodesBTUtil(root->lChild);
    count += numFullNodesBTUtil(root->rChild);

    if (root->lChild && root->rChild)
        count++;

    return count;
}

int numFullNodesBT(Tree *tree)
{
    return numFullNodesBTUtil(tree->root);
}

int maxLengthPathBTUtil(TreeNode *root) //diameter
{
    if (root == NULL)
        return 0;

    int max = maxDepthBTUtil(root->lChild) + maxDepthBTUtil(root->rChild) + 1;
    int leftMax = maxLengthPathBTUtil(root->lChild);
    int rightMax = maxLengthPathBTUtil(root->rChild);

    if (leftMax > max)
        max = leftMax;

    if (rightMax > max)
        max = rightMax;

    return max;
}
int maxLengthPathBT(Tree *tree) //diameter
{
    return maxLengthPathBTUtil(tree->root);
}

int sumAllBTUtil(TreeNode *root)
{
    if (root == NULL)
        return 0;

    return root->value + sumAllBTUtil(root->lChild) + sumAllBTUtil(root->rChild);
}

int sumAllBT(Tree *tree)
{
    return sumAllBTUtil(tree->root);
}

TreeNode *trimOutsideRangeUtil(TreeNode *root, int min, int max)
{
    TreeNode *tempNode;
    if (root == NULL)
        return NULL;

    root->rChild = trimOutsideRangeUtil(root->rChild, min, max);
    root->lChild = trimOutsideRangeUtil(root->lChild, min, max);

    if (root->value < min)
    {
        tempNode = root->rChild;
        freeTreeUtil(root->lChild);
        return tempNode;
    }

    if (root->value > max)
    {
        tempNode = root->lChild;
        freeTreeUtil(root->rChild);
        return tempNode;
    }

    return root;
}

void trimOutsideRange(Tree *tree, int min, int max)
{
    tree->root = trimOutsideRangeUtil(tree->root, min, max);
}

void printInRangeUtil(TreeNode *root, int min, int max)
{
    if (!root)
        return;

    printInRangeUtil(root->lChild, min, max);

    if (root->value >= min && root->value <= max)
        printf("%d ", root->value);

    printInRangeUtil(root->rChild, min, max);
}

void printInRange(Tree *tree, int min, int max)
{
    printInRangeUtil(tree->root, min, max);
}

int CeilBST(Tree *tree, int value)
{
    TreeNode *root = tree->root;
    int ceil = 0;
    while (root) {
        if (root->value == value) {
            ceil = root->value;
            break;
        } else if (root->value > value) {
            ceil = root->value;
            root = root->lChild;
        } else {
            root = root->rChild;
        }
    }
    return ceil;
}

int FloorBST(Tree *tree, int value)
{
    TreeNode *root = tree->root;
    int floor = 0;
    while (root) {
        if (root->value == value) {
            floor = root->value;
            break;
        } else if (root->value > value) {
            root = root->lChild;
        } else {
            floor = root->value;
            root = root->rChild;
        }
    }
    return floor;
}

void printBoundaryUtil(TreeNode *root, int isLastNode)
{
    static int PrintOnlyLeafFlag = 0;
    static int PrintParentsFlag = 0;

    if (!root)
        return;

    if (!root->rChild && !root->lChild)
    {
        printf(" %d ", root->value);
        PrintOnlyLeafFlag = 1;
        if (isLastNode)
            PrintParentsFlag = 1;
        return;
    }

    if (!PrintOnlyLeafFlag)
        printf(" %d ", root->value);

    printBoundaryUtil(root->lChild, (!root->rChild) ? isLastNode : 0);

    if (root->rChild)
        printBoundaryUtil(root->rChild, isLastNode);

    if (PrintParentsFlag)
        printf(" %d ", root->value);
}

void printBoundary(Tree *tree)
{
    printBoundaryUtil(tree->root, 1);
}

TreeNode *treeToListRec(TreeNode *curr)
{
    TreeNode *head, *tail, *tempHead;

    if (!curr)
        return NULL;

    if (curr->lChild == NULL && curr->rChild == NULL)
    {
        curr->lChild = curr;
        curr->rChild = curr;
        return curr;
    }
    if (curr->lChild)
    {
        head = treeToListRec(curr->lChild);
        tail = head->lChild;

        curr->lChild = tail;
        tail->rChild = curr;
    }
    else
        head = curr;

    if (curr->rChild)
    {
        tempHead = treeToListRec(curr->rChild);
        tail = tempHead->lChild;

        curr->rChild = tempHead;
        tempHead->lChild = curr;
    }
    else
        tail = curr;

    head->lChild = tail;
    tail->rChild = head;
    return head;
}

TreeNode *createBinaryTreeUtil(int arr[], int start, int end)
{
    if (start > end)
        return NULL;
    
    int mid = (start + end) / 2;
    TreeNode *curr = (TreeNode *)malloc(sizeof(TreeNode));
    curr->value = arr[mid];
    curr->lChild = createBinaryTreeUtil(arr, start, mid - 1);
    curr->rChild = createBinaryTreeUtil(arr, mid + 1, end);
    return curr;
}

Tree* createBinaryTree(int arr[], int size)
{
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = createBinaryTreeUtil(arr, 0, size - 1);
    return tree;
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Tree *t2 = createBinaryTree(arr, 10);
    printInOrder(t2);
    printf("\n");
}
/*
TreeNode *root = NULL;
TreeNode *temp = NULL;

root = insertUtil(root, 5);
root = insertUtil(root, 2);
root = insertUtil(root, 9);
root = insertUtil(root, 7);
root = insertUtil(root, 6);
root = insertUtil(root, 10);
root = insertUtil(root, 11);
root = insertUtil(root, 9);
root = insertUtil(root, 1);
root = insertUtil(root, 3);
root = insertUtil(root, 5);
printPreOrder(root);
printf("\n");
printPostOrder(root);
printf("\n");
printInOrder(root);
printf("\n");
printBoundary(root, 1); //error
printf("\n");

printf("Find Node : %d \n", findNode(root, 9));
printf("Find Min : %d \n", findMin(root)->value);
printf("Find Max : %d \n", findMax(root)->value);
printf("Find Min : %d \n", findMinRec(root)->value);
printf("Find Max : %d \n", findMaxRec(root)->value);
//root = deleteNode(root, 5);
printf("Min Value : %d \n", minValue(root));
printf("Max Value : %d \n", maxValue(root));
printf("Tree Depth : %d \n", treeDepth(root));
TreeNode *root2 = NULL;
TreeNode *root3 = NULL;
root2 = copyTree(root);
printf("\n");
printPreOrder(root2);
printf("\n");
printMirror(root);
printf("\n");
root3 = copyMirrorTree(root);
printPreOrder(root3);
printf("\n");
printf("NthPreeOrder : %d \n", NthPreeOrder(root, 4)->value);
printf("NthPostOrder : %d \n", NthPostOrder(root, 4)->value);
printf("NthInOrder : %d \n", NthInOrder(root, 4)->value);

//freeTree2(&root);
//printPreOrder(root);
printf("Find Node : %d \n", findNode(root, 9));
printf("\n");
printf("numNodes : %d \n", numNodes(root));
printf("numLeafs : %d \n", numLeafs(root));
printf("isIdentical : %d \n", isIdentical(root, root2));
printf("isBST : %d \n", isBST(root));
printf("isBST2 : %d \n", isBST2(root));
printf("isBST3 : %d \n", isBST3(root));

printf("\n");
printf("Find Node : %d \n", findNodeIterative(root, 9));
printf("Find Node : %d \n", findNodeIterativeOptimized(root, 9));
printf("Find max : %d \n", findMaxBT(root));
printf("Find min : %d \n", findMinBT(root));
printf("Find Node : %d \n", searchBT(root, 9));
printf("Max Depth : %d \n", maxDepthBT(root));
printf("Num full nodes : %d \n", numFullNodesBT(root));
printf("MaxLengthPathBT : %d \n", maxLengthPathBT(root));
printf("sumAllBT : %d \n", sumAllBT(root));
printf("CeilBST : %d \n", CeilBST(root, 8));
printf("FloorBST : %d \n", FloorBST(root, 4));
printInRange(root, 4, 9);
root = trimOutsideRange(root, 4, 9);
printf("\n");
printInOrder(root);
printf("Find Node : %d \n", findNodeIterativeOptimized(root, 9));
return 0;
}
*/