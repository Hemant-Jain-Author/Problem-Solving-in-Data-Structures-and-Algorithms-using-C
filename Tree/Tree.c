#include <stdio.h>
#include <stdlib.h>

typedef struct tNode
{
    int value;
    struct tNode *lChild;
    struct tNode *rChild;
} treeNode;

treeNode *insertNode(treeNode *root, int value)
{
    if (root == NULL)
    {
        root = (treeNode *)malloc(sizeof(treeNode));
        if (root == NULL)
        {
            printf("fallel memory shortage ...");
            return root;
        }
        root->value = value;
        root->lChild = root->rChild = NULL;
    }
    else
    {
        if (root->value >= value)
            root->lChild = insertNode(root->lChild, value);
        else
            root->rChild = insertNode(root->rChild, value);
    }
    return root;
}

void insertNode2(treeNode **ptrRoot, int value)
{
    *ptrRoot = insertNode(*ptrRoot, value);
}

void printPreOrder(treeNode *root) /* pre order  */
{
    if (root)
    {
        printf(" %d ", root->value);
        printPreOrder(root->lChild);
        printPreOrder(root->rChild);
    }
}

void printPostOrder(treeNode *root) /*  post order  */
{
    if (root)
    {
        printPostOrder(root->lChild);
        printPostOrder(root->rChild);
        printf(" %d ", root->value);
    }
}

void printInOrder(treeNode *root) /*  in order  */
{
    if (root)
    {
        printInOrder(root->lChild);
        printf(" %d ", root->value);
        printInOrder(root->rChild);
    }
}

treeNode *freeTree(treeNode *root)
{
    if (root)
    {
        root->lChild = freeTree(root->lChild);
        root->rChild = freeTree(root->rChild);

        if (root->lChild == NULL && root->rChild == NULL)
        {
            free(root);
            return NULL;
        }
    }
    return NULL;
}

void freeTree2(treeNode **rootPtr)
{
    *rootPtr = freeTree(*rootPtr);
}

treeNode *findNode(treeNode *root, int value)
{
    if (!root)
        return NULL;
    if (root->value == value)
        return root;
    else
    {
        if (root->value > value)
            return findNode(root->lChild, value);
        else
            return findNode(root->rChild, value);
    }
}

treeNode *findMin(treeNode *root)
{
    if (root)
        while (root->lChild)
        {
            root = root->lChild;
        }
    return root;
}

treeNode *findMinRec(treeNode *root)
{
    if (!root)
        return NULL;

    if (root->lChild == NULL)
        return root;
    else
        return findMinRec(root->lChild);
}

treeNode *findMax(treeNode *root)
{
    if (root)
        while (root->rChild)
        {
            root = root->rChild;
        }
    return root;
}

treeNode *findMaxRec(treeNode *root)
{
    if (!root)
        return NULL;

    if (root->rChild == NULL)
        return root;
    else
        return findMaxRec(root->rChild);
}

treeNode *deleteNode(treeNode *root, int value)
{
    treeNode *temp = NULL;
    if (root)
    {
        if (root->value == value)
        {
            if (root->lChild == NULL && root->rChild == NULL)
            {
                free(root);
                return NULL;
            }
            else
            {
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

                temp = findMax(root->lChild);
                root->value = temp->value;
                root->lChild = deleteNode(root->lChild, temp->value);
            }
        }
        else
        {
            if (root->value > value)
                root->lChild = deleteNode(root->lChild, value);
            else
                root->rChild = deleteNode(root->rChild, value);
        }
    }
    return root;
}

void deleteNode2(treeNode **rootPtr, int value)
{
    *rootPtr = deleteNode(*rootPtr, value);
}

int maxValue(treeNode *root)
{
    if (root)
    {
        while (root->rChild)
        {
            root = root->rChild;
        }
        return root->value;
    }
    return -999;
}

int minValue(treeNode *root)
{
    if (root)
    {
        while (root->lChild)
        {
            root = root->lChild;
        }
        return root->value;
    }
    return -999;
}

int treeDepth(treeNode *root)
{
    if (!root)
        return 0;
    else
    {
        int lDepth = treeDepth(root->lChild);
        int rDepth = treeDepth(root->rChild);

        if (lDepth > rDepth)
            return lDepth + 1;
        else
            return rDepth + 1;
    }
}

treeNode *copyTree(treeNode *root)
{
    treeNode *temp;

    if (root != NULL)
    {
        temp = (treeNode *)malloc(sizeof(treeNode));
        if (!temp)
            return NULL;
        temp->value = root->value;
        temp->lChild = copyTree(root->lChild);
        temp->rChild = copyTree(root->rChild);
        return temp;
    }
    else
        return NULL;
}

treeNode *copyMirrorTree(treeNode *root)
{
    treeNode *temp;

    if (root != NULL)
    {
        temp = (treeNode *)malloc(sizeof(treeNode));
        if (!temp)
            return NULL;

        temp->value = root->value;
        temp->lChild = copyMirrorTree(root->rChild);
        temp->rChild = copyMirrorTree(root->lChild);
        return temp;
    }
    else
        return NULL;
}

void printMirror(treeNode *root) /*pre order*/
{
    if (root != NULL)
    {
        printf(" %d ", root->value);
        printMirror(root->rChild);
        printMirror(root->lChild);
        return;
    }
    else
        return;
}

treeNode *NthPreeOrder(treeNode *root, int index) /* pre order  */
{
    static int count = 0;
    treeNode *temp = NULL;

    if (root)
    {
        count++;
        if (count == index)
        {
            printf(" %d ", root->value);
            return root;
        }

        temp = NthPreeOrder(root->lChild, index);
        if (temp)
            return temp;

        temp = NthPreeOrder(root->rChild, index);
        if (temp)
            return temp;
    }
    return NULL;
}

treeNode *NthPostOrder(treeNode *root, int index) /*  post order  */
{
    static int count = 0;
    treeNode *temp = NULL;

    if (root)
    {
        temp = NthPostOrder(root->lChild, index);
        if (temp)
            return temp;

        temp = NthPostOrder(root->rChild, index);
        if (temp)
            return temp;

        count++;

        if (count == index)
        {
            printf(" %d ", root->value);
            return root;
        }
    }
    return NULL;
}

treeNode *NthInOrder(treeNode *root, int index) /*  in order  */
{
    static int count = 0;
    treeNode *temp = NULL;

    if (root)
    {
        temp = NthInOrder(root->lChild, index);
        if (temp)
            return temp;

        count++;
        if (count == index)
        {
            printf(" %d ", root->value);
            return root;
        }

        temp = NthInOrder(root->rChild, index);
        if (temp)
            return temp;
    }
    return NULL;
}

int numNodes(treeNode *root)
{
    if (!root)
        return 0;
    else
        return (1 + numNodes(root->rChild) + numNodes(root->lChild));
}

int numLeafs(treeNode *root)
{
    if (!root)
        return 0;
    if (!root->lChild && !root->rChild)
        return 1;
    else
        return (numLeafs(root->rChild) + numLeafs(root->lChild));
}

int isIdentical(treeNode *root1, treeNode *root2)
{
    if (!root1 && !root2)
        return 1;
    else if (!root1 || !root2)
        return 0;
    else
        return (isIdentical(root1->lChild, root2->lChild) && isIdentical(root1->rChild, root2->rChild) && (root1->value == root2->value));
}

int isBST(treeNode *root)
{
    if (!root)
        return 1;

    if (root->lChild && maxValue(root->lChild) > root->value)
        return 0;
    if (root->rChild && minValue(root->rChild) <= root->value)
        return 0;

    return (isBST(root->lChild) && isBST(root->rChild));
}


int isBSTUtil2(treeNode *root, int min, int max)
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

int isBST2(treeNode *root)
{
    return isBSTUtil2(root, INT_MIN, INT_MAX);
}

int isBSTUtil3(treeNode *root, int *value) /*  in order  */
{
    int ret;
    if (root)
    {
        ret = isBSTUtil3(root->lChild, value);
        if (!ret)
            return 0;

        if (*value > root->value)
            return 0;

        *value = root->value;

        ret = isBSTUtil3(root->rChild, value);
        if (!ret)
            return 0;
    }
    return 1;
}

int isBST3(treeNode *root)
{
    int temp=0;
    return isBSTUtil3(root, &temp);
}

treeNode *findNodeIterative(treeNode *root, int value) /* iterative */
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

treeNode *findNodeIterativeOptimized(treeNode *root, int value)
{
    while (root && root->value != value)
    {
        if (root->value > value)
            root = root->lChild;
        else
            root = root->rChild;
    }
    return root;
}

treeNode *LcaBST(treeNode *root, treeNode *firstPtr, treeNode *secondPtr)
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

int findNodeDepth(treeNode *root, treeNode *dstPtr)
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

int pathLenght(treeNode *root, treeNode *firstPtr, treeNode *secondPtr)
{
    treeNode *parent = LcaBST(root, firstPtr, secondPtr);
    int first = findNodeDepth(parent, firstPtr);
    int second = findNodeDepth(parent, secondPtr);
    return first + second;
}

treeNode *LcaBT(treeNode *root, treeNode *firstPtr, treeNode *secondPtr)
{
    treeNode *left, *right;

    if (root == NULL)
        return NULL;

    if (root == firstPtr || root == secondPtr)
        return root;

    left = LcaBT(root->lChild, firstPtr, secondPtr);
    right = LcaBT(root->rChild, firstPtr, secondPtr);

    if (left && right)
        return root;
    else if (left)
        return left;
    else
        return right;
}

int findMaxBT(treeNode *root)
{
    int max;
    int left, right;

    if (root == NULL)
        return INT_MIN;

    max = root->value;

    left = findMaxBT(root->lChild);
    right = findMaxBT(root->rChild);

    if (left > max)
        max = left;
    if (right > max)
        max = right;

    return max;
}

int findMinBT(treeNode *root)
{
    int min;
    int left, right;

    if (root == NULL)
        return INT_MAX;

    min = root->value;

    left = findMinBT(root->lChild);
    right = findMinBT(root->rChild);

    if (left < min)
        min = left;
    if (right < min)
        min = right;

    return min;
}

int searchBT(treeNode *root, int value)
{
    int max;
    int left, right;

    if (root == NULL)
        return 0;

    if (root->value == value)
        return 1;

    left = searchBT(root->lChild, value);
    if (left)
        return 1;

    right = searchBT(root->rChild, value);
    if (right)
        return 1;

    return 0;
}

int maxDepthBT(treeNode *root)
{
    int max = 0;
    int left, right;

    if (root == NULL)
        return 0;

    left = maxDepthBT(root->lChild);
    right = maxDepthBT(root->rChild);

    if (left > max)
        max = left;
    if (right > max)
        max = right;

    return max + 1;
}

int numFullNodesBT(treeNode *root)
{
    int count = 0;
    int left, right;

    if (root == NULL)
        return 0;

    left = numFullNodesBT(root->lChild);
    right = numFullNodesBT(root->rChild);

    count = left + right;

    if (root->lChild && root->rChild) //this line can be changed to solve many problems.
        count++;

    return count;
}

int maxLengthPathBT(treeNode *root) //diameter
{
    int max;
    int leftPath, rightPath;
    int leftMax, rightMax;

    if (root == NULL)
        return 0;

    leftPath = maxDepthBT(root->lChild);
    rightPath = maxDepthBT(root->rChild);

    max = leftPath + rightPath + 1;

    leftMax = maxLengthPathBT(root->lChild);
    rightMax = maxLengthPathBT(root->rChild);

    if (leftMax > max)
        max = leftMax;

    if (rightMax > max)
        max = rightMax;

    return max;
}

int sumAllBT(treeNode *root)
{
    if (root == NULL)
        return 0;

    return root->value + sumAllBT(root->lChild) + 
    sumAllBT(root->rChild);
}

treeNode *trimOutsideRange(treeNode *root, int min, int max)
{
    treeNode *tempNode;
    if (root == NULL)
        return NULL;

    root->rChild = trimOutsideRange(root->rChild, min, max);
    root->lChild = trimOutsideRange(root->lChild, min, max);

    if (root->value < min)
    {
        tempNode = root->rChild;
        freeTree(root->lChild);
        free(root);
        return tempNode;
    }

    if (root->value > max)
    {
        tempNode = root->lChild;
        freeTree(root->rChild);
        free(root);
        return tempNode;
    }

    return root;
}

void printInRange(treeNode *root, int min, int max)
{
    if (!root)
        return;

    printInRange(root->lChild, min, max);

    if (root->value >= min && root->value <= max)
        printf(" %d ", root->value);

    printInRange(root->rChild, min, max);
}

int CeilBST(treeNode *root, int value)
{
    int ceil=0;
    while (root)
    {
        if (root->value == value)
        {
            ceil = root->value;
            break;
        }
        else if (root->value > value)
        {
            ceil = root->value;
            root = root->lChild;
        }
        else
        {
            root = root->rChild;
        }
    }
    return ceil;
}

int FloorBST(treeNode *root, int value)
{
    int floor=0;
    while (root)
    {
        if (root->value == value)
        {
            floor = root->value;
            break;
        }
        else if (root->value > value)
        {
            root = root->lChild;
        }
        else
        {
            floor = root->value;
            root = root->rChild;
        }
    }
    return floor;
}

/*
Print boundry of fully binary tree.

Traverse the tree in a preorder traversal.
PrintOnlyLeafFlag = false
PrintParentsFlag = false
Print the nodes in the tree till you get to first leaf. Then set flag printOnlyLeaf = true.
Then print only leafs.
There is a flag isLastNode which is passed from root. If I have a isLastNode flag as 0 then I will pass 0 to all my child.
If isLastNode flag is 1 then
If I have a right child I will pass isLastNode flag to 0 to left child and will pass isLastNode flag to my right child.
If I don’t have a right child then I will pass isLastNode flag to 1 to my left child.
IF I don’t have any child and got flag isLastNode as 1 then will print my self and set flag PrintParentsFlags.
When the funciton exits it will print all the nodes in the path in the reverse order and you are done.

*/

void printBoundry(treeNode *root, int isLastNode)
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

    printBoundry(root->lChild, (!root->rChild) ? isLastNode : 0);

    if (root->rChild)
        printBoundry(root->rChild, isLastNode);

    if (PrintParentsFlag)
        printf(" %d ", root->value);
}

treeNode *treeToListRec(treeNode *curr)
{
    treeNode *head, *tail, *tempHead;

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


treeNode*  CreateBinaryTreeUtil(int arr[], int start, int end)
{	treeNode* curr;
    if (start > end)
		return NULL;
	int mid = (start + end) / 2;
	curr = (treeNode* )malloc(sizeof(treeNode));
    curr->value = arr[mid];
	curr->lChild = CreateBinaryTreeUtil(arr, start, mid-1);
	curr->rChild = CreateBinaryTreeUtil(arr, mid + 1, end);
	return curr;
}
treeNode* CreateBinaryTree(int arr[], int size)
{
	return CreateBinaryTreeUtil(arr, 0, size-1);
}



int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    treeNode* t2 = CreateBinaryTree(arr, 10);
    printInOrder(t2);
    printf("\n");
}
    treeNode *root = NULL;
    treeNode *temp = NULL;

    root = insertNode(root, 5);
    root = insertNode(root, 2);
    root = insertNode(root, 9);
    root = insertNode(root, 7);
    root = insertNode(root, 6);
    root = insertNode(root, 10);
    root = insertNode(root, 11);
    root = insertNode(root, 9);
    root = insertNode(root, 1);
    root = insertNode(root, 3);
    root = insertNode(root, 5);
    printPreOrder(root);
    printf("\n");
    printPostOrder(root);
    printf("\n");
    printInOrder(root);
    printf("\n");
    printBoundry(root, 1);//error
    printf("\n");
    
    printf("Find Node : %d \n",findNode(root, 9));
    printf("Find Min : %d \n",findMin(root)->value);
    printf("Find Max : %d \n",findMax(root)->value);
    printf("Find Min : %d \n",findMinRec(root)->value);
    printf("Find Max : %d \n",findMaxRec(root)->value);
    //root = deleteNode(root, 5);
    printf("Min Value : %d \n",minValue(root));
    printf("Max Value : %d \n",maxValue(root));
    printf("Tree Depth : %d \n",treeDepth(root));
    treeNode *root2 = NULL;
    treeNode *root3 = NULL;
    root2 = copyTree(root);
    printf("\n");
    printPreOrder(root2);
    printf("\n");
    printMirror(root);
    printf("\n");
    root3 = copyMirrorTree(root);
    printPreOrder(root3);
    printf("\n");
    printf("NthPreeOrder : %d \n",NthPreeOrder(root,4)->value);
    printf("NthPostOrder : %d \n",NthPostOrder(root,4)->value);
    printf("NthInOrder : %d \n",NthInOrder(root,4)->value);
   
    //freeTree2(&root);
    //printPreOrder(root);
    printf("Find Node : %d \n",findNode(root, 9));
    printf("\n");
    printf("numNodes : %d \n",numNodes(root));
    printf("numLeafs : %d \n",numLeafs(root));
    printf("isIdentical : %d \n",isIdentical(root, root2));
    printf("isBST : %d \n",isBST(root));
    printf("isBST2 : %d \n",isBST2(root));
    printf("isBST3 : %d \n",isBST3(root));
    
    printf("\n");
    printf("Find Node : %d \n",findNodeIterative(root, 9));
    printf("Find Node : %d \n",findNodeIterativeOptimized(root, 9));
    printf("Find max : %d \n",findMaxBT(root));
    printf("Find min : %d \n",findMinBT(root));
    printf("Find Node : %d \n",searchBT(root, 9));
    printf("Max Depth : %d \n",maxDepthBT(root));
    printf("Num full nodes : %d \n",numFullNodesBT(root));
    printf("MaxLengthPathBT : %d \n",maxLengthPathBT(root));
    printf("sumAllBT : %d \n",sumAllBT(root));
    printf("CeilBST : %d \n",CeilBST(root, 8));
    printf("FloorBST : %d \n",FloorBST(root, 4));
    printInRange(root, 4, 9);
    root = trimOutsideRange(root, 4, 9);
    printf("\n");
    printInOrder(root);
    printf("Find Node : %d \n",findNodeIterativeOptimized(root, 9));
    return 0;
}
