#include "Tree.h"

Tree* createBinaryTree() {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = NULL;
    return tree;
}

TreeNode *createBinarySearchTreeUtil(int arr[], int start, int end) {
    if (start > end)
        return NULL;
    
    int mid = (start + end) / 2;
    TreeNode *curr = (TreeNode *)malloc(sizeof(TreeNode));
    curr->value = arr[mid];
    curr->lChild = createBinarySearchTreeUtil(arr, start, mid - 1);
    curr->rChild = createBinarySearchTreeUtil(arr, mid + 1, end);
    return curr;
}

Tree* createBinarySearchTree(int arr[], int size) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = createBinarySearchTreeUtil(arr, 0, size - 1);
    return tree;
}

TreeNode *levelOrderBinaryTreeUtil(int arr[], int start, int size) {
    TreeNode *curr = (TreeNode *)malloc(sizeof(TreeNode));
    curr->lChild = curr->rChild = NULL;
    curr->value = arr[start];
    int left = 2 * start + 1;
    int right = 2 * start + 2;
        
    if (left < size)
        curr->lChild = levelOrderBinaryTreeUtil(arr, left, size);
    
    if (right < size)
        curr->rChild = levelOrderBinaryTreeUtil(arr, right, size);
    
    return curr;
}

Tree* levelOrderBinaryTree(int arr[], int size) {
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->root = levelOrderBinaryTreeUtil(arr, 0, size);
    return tree;
}

void printPreOrderUtil(TreeNode *root) /* pre order  */
{
    if (root) {
        printf("%d ", root->value);
        printPreOrderUtil(root->lChild);
        printPreOrderUtil(root->rChild);
    }
}

void printPreOrder(Tree *tree) {
    printPreOrderUtil(tree->root);
    printf("\n");
}

void printPostOrderUtil(TreeNode *root) /*  post order  */
{
    if (root) {
        printPostOrderUtil(root->lChild);
        printPostOrderUtil(root->rChild);
        printf("%d ", root->value);
    }
}

void printPostOrder(Tree *tree) {
    printPostOrderUtil(tree->root);
    printf("\n");
}

void printInOrderUtil(TreeNode *root) /*  in order  */
{
    if (root) {
        printInOrderUtil(root->lChild);
        printf("%d ", root->value);
        printInOrderUtil(root->rChild);
    }
}

void printInOrder(Tree *tree) {
    printInOrderUtil(tree->root);
    printf("\n");
}

int main1() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    printPreOrder(t);
    printPostOrder(t);
    printInOrder(t);
    return 0;
}
/*
1 2 4 8 9 5 10 3 6 7 
8 9 4 10 5 2 6 7 3 1 
8 4 9 2 10 5 1 6 3 7 
*/

TreeNode *insertUtil(TreeNode *root, int value) {
    if (root == NULL) {
        root = (TreeNode *)malloc(sizeof(TreeNode));
        if (root == NULL) {
            printf("Memory allocation error.");
            return root;
        }
        root->value = value;
        root->lChild = root->rChild = NULL;
    } else {
        if (root->value >= value)
            root->lChild = insertUtil(root->lChild, value);
        else
            root->rChild = insertUtil(root->rChild, value);
    }
    return root;
}

void insert(Tree *tree, int value) {
    tree->root = insertUtil(tree->root, value);
}

int main2() {
    Tree *t = createBinaryTree();
    insert(t, 5);
    insert(t, 3);
    insert(t, 7);
    insert(t, 2);
    insert(t, 1);
    insert(t, 4);
    insert(t, 6);
    insert(t, 8);
    printInOrder(t);
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 
*/


TreeNode *nthPreOrderUtil(TreeNode *root, int index) {
    static int count = 0;

    if (root == NULL)
        return NULL;

    count++;
    if (count == index)
        return root;

    TreeNode *temp = nthPreOrderUtil(root->lChild, index);
    if (temp != NULL)
        return temp;

    temp = nthPreOrderUtil(root->rChild, index);
    if (temp != NULL)
        return temp;

    return NULL;
}

int nthPreOrder(Tree *tree, int index) {
    TreeNode *temp = nthPreOrderUtil(tree->root, index);
    if (temp != NULL)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}

TreeNode *nthPostOrderUtil(TreeNode *root, int index) {
    static int count = 0;

    if (root == NULL)
        return NULL;

    TreeNode *temp = nthPostOrderUtil(root->lChild, index);
    if (temp != NULL)
        return temp;

    temp = nthPostOrderUtil(root->rChild, index);
    if (temp != NULL)
        return temp;

    count++;
    if (count == index)
        return root;

    return NULL;
}

int nthPostOrder(Tree *tree, int index) {
    TreeNode *temp = nthPostOrderUtil(tree->root, index);
    if (temp != NULL)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}

TreeNode *nthInOrderUtil(TreeNode *root, int index) {
    static int count = 0;

    if (root == NULL)
        return NULL;

    TreeNode *temp = nthInOrderUtil(root->lChild, index);
    if (temp != NULL)
        return temp;

    count++;
    if (count == index)
        return root;

    temp = nthInOrderUtil(root->rChild, index);
    if (temp != NULL)
        return temp;

    return NULL;
}

int nthInOrder(Tree *tree, int index) {
    TreeNode *temp = nthInOrderUtil(tree->root, index);
    if (temp != NULL)
        return temp->value;
    printf("Errro, value not found.\n");
    return 9999;
}


int main3() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    printf("nthInOrder : %d\n", nthInOrder(t, 4));
    printf("nthPostOrder : %d\n", nthPostOrder(t, 4));
    printf("nthPreOrder : %d\n", nthPreOrder(t, 4));
    return 0;
}

/*
nthInOrder : 2
nthPostOrder : 10
nthPreOrder : 8
*/


void printBreadthFirst(Tree *tree) {
    Queue* que = createQueue();
    TreeNode *temp, *root = tree->root;
    if (root != NULL) {
       queueAdd(que, root);
    }

    while (queueIsEmpty(que) == 0) {
        temp = queueRemove(que);
        printf("%d ", temp->value);

        if (temp->lChild != NULL) {
           queueAdd(que, temp->lChild);
        }
        if (temp->rChild != NULL) {
           queueAdd(que, temp->rChild);
        }
    }
    printf("\n");
}

void printDepthFirst(Tree *tree) {
    Stack* stk = createStack();
    TreeNode *temp, *root = tree->root;

    if (root != NULL) {
        stackPush(stk, root);
    }

    while (stackIsEmpty(stk) == 0) {
        temp = stackPop(stk);
        printf("%d ", temp->value);

        if (temp->lChild != NULL) {
            stackPush(stk, temp->lChild);
        }
        if (temp->rChild != NULL) {
            stackPush(stk, temp->rChild);
        }
    }
    printf("\n");
}

void printLevelOrderLineByLine(Tree *tree) {
    Queue* que1 = createQueue();
    Queue* que2 = createQueue();
    TreeNode *temp = NULL, *root = tree->root;
    if (root != NULL)
        queueAdd(que1, root);
    while (queueSize(que1) != 0 || queueSize(que2) != 0) {
        while (queueSize(que1) != 0) {
            temp = queueRemove(que1);
            printf("%d ", temp->value);
            if (temp->lChild != NULL)
                queueAdd(que2, temp->lChild);
            if (temp->rChild != NULL)
                queueAdd(que2, temp->rChild);
        }
        printf("\n");

        while (queueSize(que2) != 0) {
            temp = queueRemove(que2);
            printf("%d ", temp->value);
            if (temp->lChild != NULL)
                queueAdd(que1, temp->lChild);
            if (temp->rChild != NULL)
                queueAdd(que1, temp->rChild);
        }
        printf("\n");
    }
}

void printLevelOrderLineByLine2(Tree *tree) {
    Queue* que = createQueue();
    TreeNode *temp = NULL, *root=tree->root;
    int count = 0;

    if (root != NULL)
       queueAdd(que, root);
    while (queueSize(que) != 0) {
        count = queueSize(que);
        while (count > 0) {
            temp = queueRemove(que);
            printf("%d ", temp->value);
            if (temp->lChild != NULL)
               queueAdd(que, temp->lChild);
            if (temp->rChild != NULL)
               queueAdd(que, temp->rChild);
            count -= 1;
        }
        printf("\n");
    }
}

void printSpiralTree(Tree *tree) {
    Stack* stk1 = createStack();
    Stack* stk2 = createStack();

    TreeNode *temp, *root = tree->root;
    if (root != NULL)
        stackPush(stk1, root);

    while (stackIsEmpty(stk1) == 0 || stackIsEmpty(stk2) == 0) {
        while (stackIsEmpty(stk1) == 0) {
            temp = stackPop(stk1);
            printf("%d ", temp->value);
            if (temp->rChild != NULL)
                stackPush(stk2, temp->rChild);
            if (temp->lChild != NULL)
                stackPush(stk2, temp->lChild);
        }
        while (stackIsEmpty(stk2) == 0) {
            temp = stackPop(stk2);
            printf("%d ", temp->value);
            if (temp->lChild != NULL)
                stackPush(stk1, temp->lChild);
            if (temp->rChild != NULL)
                stackPush(stk1, temp->rChild);
        }
    }
    printf("\n");
}

void printAllPathUtil(TreeNode *curr, Stack* stk) {
    if(curr == NULL)
        return;
    
    stackPush(stk, curr);
    if (curr->lChild == NULL && curr->rChild == NULL) {
        stackPrint(stk);
        stackPop(stk);
        return;
    }

    printAllPathUtil(curr->rChild, stk);
    printAllPathUtil(curr->lChild, stk);
    stackPop(stk);
}

void printAllPath(Tree *tree) {
    Stack* stk = createStack();
    if (tree->root == NULL)
        return;
    printAllPathUtil(tree->root, stk);
}

int main4() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    printBreadthFirst(t);
    printDepthFirst(t);
    printLevelOrderLineByLine(t);
    printLevelOrderLineByLine2(t);
    printSpiralTree(t);
    printAllPath(t);
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 10 
1 3 7 6 2 5 10 4 9 8 

1 
2 3 
4 5 6 7 
8 9 10

1 
2 3 
4 5 6 7 
8 9 10 

1 2 3 7 6 5 4 8 9 10 

[7 3 1 ]
[6 3 1 ]
[10 5 2 1 ]
[9 4 2 1 ]
[8 4 2 1 ]

*/

void iterativePreOrder(Tree *t) {
    if (t->root == NULL)
        return;

    Stack* stk = createStack();
    stackPush(stk, t->root);
    TreeNode *curr;

    while (stackIsEmpty(stk) == 0) {
        curr = stackPop(stk);
        printf("%d ", curr->value);

        if (curr->rChild != NULL)
            stackPush(stk, curr->rChild);

        if (curr->lChild != NULL)
            stackPush(stk, curr->lChild);
    }
    printf("\n");
}

int main5() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    iterativePreOrder(t);
    return 0;
}

/*
1 2 4 8 9 5 10 3 6 7 
*/


int find(Tree *tree, int value) {
    TreeNode *curr = tree->root;
    while (curr != NULL) {
        if(curr->value == value) {
            return 1;
        } else if (curr->value > value) {
            curr =  curr->lChild ;   
        } else {
            curr =  curr->rChild;
        }
    }
    return 0;
}

int find2(Tree *tree, int value) {
    TreeNode *curr = tree->root;
    while (curr != NULL && curr->value != value) {
        curr = (curr->value > value) ? curr->lChild : curr->rChild;
    }
    return curr != NULL;
}


TreeNode *findNode(TreeNode *root, int value) {
    if (!root)
        return NULL;

    if (root->value == value)
        return root;
    else if (root->value > value)
        return findNode(root->lChild, value);
    else
        return findNode(root->rChild, value);
}

int find3(Tree *tree, int value) {
    if (findNode(tree->root, value) != NULL)
        return 1;
    return 0;
}

int findMin(Tree *tree) {
    TreeNode *root = tree->root;
    if (!root)
        return -999;

    while (root->lChild) {
        root = root->lChild;
    }
    return root->value;
}

int findMax(Tree *tree) {
    TreeNode *root = tree->root;
    if (!root)
        return -999;

    while (root->rChild) {
        root = root->rChild;
    }
    return root->value;
}

TreeNode *findMaxNode(TreeNode *root) {
    if (!root)
        return NULL;

    while (root->rChild) {
        root = root->rChild;
    }
    return root;
}

TreeNode *findMinNode(TreeNode *root) {
    if (!root)
        return NULL;

    while (root->lChild) {
        root = root->lChild;
    }
    return root;
}

int findMin2(Tree *tree) {
    TreeNode *tmp = findMinNode(tree->root);
    if(tmp)
        return tmp->value;
    return 9999;
}

int findMax2(Tree *tree) {
    TreeNode *tmp = findMaxNode(tree->root);
    if(tmp)
        return tmp->value;
    return 9999;
}


TreeNode *findMinNodeRec(TreeNode *root) {
    if (!root)
        return NULL;

    if (root->lChild == NULL)
        return root;
    else
        return findMinNodeRec(root->lChild);
}

TreeNode *findMaxNodeRec(TreeNode *root) {
    if (!root)
        return NULL;

    if (root->rChild == NULL)
        return root;
    else
        return findMaxNodeRec(root->rChild);
}

int minValue(TreeNode *root) {
    if (!root)
        return -999;

    while (root->lChild) {
        root = root->lChild;
    }
    return root->value;
}

int maxValue(TreeNode *root) {
    if (!root)
        return -99999;

    while (root->rChild) {
        root = root->rChild;
    }
    return root->value;
}


int main6() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printf("find:: %d \n", find(t, 7));
    printf("find:: %d \n", find2(t, 7));
    printf("find:: %d \n", find3(t, 7));
    printf("findMax:: %d \n", findMax(t));
    printf("findMin:: %d \n", findMin(t));
    printf("Find Min : %d \n", findMin2(t));
    printf("Find Max : %d \n", findMax2(t));
  //  printf("Find Min : %d \n", findMinRec(t));
   // printf("Find Max : %d \n", findMaxRec(t));
    return 0;
}

/*
find:: 1 
find:: 1 
find:: 1 
findMax:: 10 
findMin:: 1 
Find Min : 1 
Find Max : 10 
*/

void freeTreeUtil(TreeNode *root) {
    if (root) {
        freeTreeUtil(root->lChild);
        freeTreeUtil(root->rChild);
        free(root);
    }
}

void freeTree(Tree *tree) {
    freeTreeUtil(tree->root);
    tree->root = NULL;
}

TreeNode *removeDataUtil(TreeNode *root, int value) {
    if (!root)
        return NULL;

    if (root->value == value) {
        if (root->lChild == NULL && root->rChild == NULL) {
            free(root);
            return NULL;
        } else {
            TreeNode *temp = NULL;
            if (root->lChild == NULL) {
                temp = root->rChild;
                free(root);
                return temp;
            }
            if (root->rChild == NULL) {
                temp = root->lChild;
                free(root);
                return temp;
            }

            int mx = maxValue(root->lChild);
            root->value = mx;
            root->lChild = removeDataUtil(root->lChild, mx);
        }
    } else {
        if (root->value > value)
            root->lChild = removeDataUtil(root->lChild, value);
        else
            root->rChild = removeDataUtil(root->rChild, value);
    }
    return root;
}

void removeData(Tree *tree, int value) {
    tree->root = removeDataUtil(tree->root, value);
}

int main7() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printPreOrder(t);
    removeData(t, 6);
    printPreOrder(t);
    freeTree(t);
    printPreOrder(t);
    free(t);
    return 0;
}

/*
5 2 1 3 4 8 7 9 10 
*/

int numNodesUtil(TreeNode *root) {
    if (!root)
        return 0;

    return (1 + numNodesUtil(root->rChild) + numNodesUtil(root->lChild));
}

int numNodes(Tree *tree) {
    return numNodesUtil(tree->root);
}


int numFullNodesBTUtil(TreeNode *root) {
    if (root == NULL)
        return 0;

    int count = numFullNodesBTUtil(root->lChild) 
                + numFullNodesBTUtil(root->rChild);

    if (root->lChild && root->rChild)
        count++;

    return count;
}

int numFullNodesBT(Tree *tree) {
    return numFullNodesBTUtil(tree->root);
}

int numLeafsUtil(TreeNode *root) {
    if (!root)
        return 0;

    if (!root->lChild && !root->rChild)
        return 1;

    return (numLeafsUtil(root->rChild) + numLeafsUtil(root->lChild));
}

int numLeafs(Tree *tree) {
    return numLeafsUtil(tree->root);
}

int sumAllBTUtil(TreeNode *root) {
    if (root == NULL)
        return 0;

    return root->value + sumAllBTUtil(root->lChild) + sumAllBTUtil(root->rChild);
}

int sumAllBT(Tree *tree) {
    return sumAllBTUtil(tree->root);
}

int treeDepthUtil(TreeNode *root) {
    if (!root)
        return 0;

    int lDepth = treeDepthUtil(root->lChild);
    int rDepth = treeDepthUtil(root->rChild);

    if (lDepth > rDepth)
        return lDepth + 1;
    else
        return rDepth + 1;
}

int treeDepth(Tree *tree) {
    return treeDepthUtil(tree->root);
}

int maxLengthPathBTUtil(TreeNode *root) //diameter
{
    if (root == NULL)
        return 0;

    int max = treeDepthUtil(root->lChild) + treeDepthUtil(root->rChild) + 1;
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

int main8() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    printInOrder(t);
    printf("numNodes:: %d\n", numNodes(t));
    printf("numFullNodesBT:: %d\n", numFullNodesBT(t));
    printf("numLeafNodes:: %d\n", numLeafs(t));
    printf("treeDepth:: %d\n", treeDepth(t));
    printf("maxLengthPathBT:: %d\n", maxLengthPathBT(t));
    printf("sumAllBT:: %d\n", sumAllBT(t));
    return 0;
}

/*
numNodes:: 10
numFullNodesBT:: 4
numLeafNodes:: 5
treeDepth:: 4
maxLengthPathBT:: 6
sumAllBT:: 55
*/

TreeNode *copyTreeUtil(TreeNode *root) {
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

Tree* copyTree(Tree *src) {
    Tree *dest = createBinaryTree();
    dest->root = copyTreeUtil(src->root);
    return dest;
}

TreeNode *copyMirrorTreeUtil(TreeNode *root) {
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

Tree *copyMirrorTree(Tree *src) {
    Tree *dest = createBinaryTree();
    dest->root = copyMirrorTreeUtil(src->root);
    return dest;
}

void printMirrorUtil(TreeNode *root) {
    if (!root)
        return;

    printf(" %d ", root->value);
    printMirrorUtil(root->rChild);
    printMirrorUtil(root->lChild);
    return;
}

void printMirror(Tree *tree) {
    printMirrorUtil(tree->root);
    return;
}

int isEqualUtil(TreeNode *root1, TreeNode *root2) {
    if (!root1 && !root2)
        return 1;

    if (!root1 || !root2)
        return 0;

    return isEqualUtil(root1->lChild, root2->lChild) &&
           isEqualUtil(root1->rChild, root2->rChild) &&
           (root1->value == root2->value);
}

int isEqual(Tree *tree1, Tree *tree2) {
    return isEqualUtil(tree1->root, tree2->root);
}


int main9() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    Tree* t1 = copyTree(t);
    Tree* t2 = copyMirrorTree(t);
    printInOrder(t);
    printInOrder(t1);
    printInOrder(t2);

    printf("Equal :: %d\n", isEqual(t, t1));
    printf("Equal :: %d\n", isEqual(t, t2));
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 10 
1 2 3 4 5 6 7 8 9 10 
10 9 8 7 6 5 4 3 2 1 
Equal :: 1
Equal :: 0
*/

TreeNode *ancestorUtil(TreeNode *curr, int first, int second) {
    if (curr == NULL)
        return NULL;

    if (curr->value > first && curr->value > second) {
        return ancestorUtil(curr->lChild, first, second);
    }
    if (curr->value < first && curr->value < second) {
        return ancestorUtil(curr->rChild, first, second);
    }
    return curr;
}

TreeNode *ancestor(Tree* tree, int first, int second) {
    if (first > second) {
        int temp = first;
        first = second;
        second = temp;
    }
    return ancestorUtil(tree->root, first, second);
}

int isCompleteTree(Tree *tree) {
    Queue* que = createQueue();
    TreeNode* temp = NULL, *root = tree->root;
    int noChild = 0;
    if (root != NULL)
       queueAdd(que, root);
    
    while (queueSize(que) != 0) {
        temp = queueRemove(que);
        if (temp->lChild != NULL) {
            if (noChild == 1)
                return 0;
           queueAdd(que, temp->lChild);
        }
        else
            noChild = 1;

        if (temp->rChild != NULL) {
            if (noChild == 1)
                return 0;
           queueAdd(que, temp->rChild);
        }
        else
            noChild = 1;
    }
    return 1;
}

int isCompleteTreeUtil(TreeNode* curr, int index, int count) {
    if (curr == NULL)
        return 1;
    if (index > count)
        return 0;
    return isCompleteTreeUtil(curr->lChild, index * 2 + 1, count)
           && isCompleteTreeUtil(curr->rChild, index * 2 + 2, count);
}

int isCompleteTree2(Tree *tree) {
    int count = numNodes(tree);
    return isCompleteTreeUtil(tree->root, 0, count);
}

int isHeapUtil(TreeNode* curr, int parentValue) {
    if (curr == NULL)
        return 1;
    if (curr->value < parentValue)
        return 0;
    return (isHeapUtil(curr->lChild, curr->value) && isHeapUtil(curr->rChild, curr->value));
}

int isHeap(Tree *tree) {
    int infi = -9999999;
    return (isCompleteTree(tree) && isHeapUtil(tree->root, infi));
}

int isHeapUtil2(TreeNode* curr, int index, int count, int parentValue) {
    if (curr == NULL)
        return 1;
    if (index > count)
        return 0;
    if (curr->value < parentValue)
        return 0;
    return isHeapUtil2(curr->lChild, index * 2 + 1, count, curr->value)
           && isHeapUtil2(curr->rChild, index * 2 + 2, count, curr->value);
}

int isHeap2(Tree *tree) {
    int count = numNodes(tree);
    int parentValue = -9999999;
    return isHeapUtil2(tree->root, 0, count, parentValue);
}

int main10() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = levelOrderBinaryTree(arr, 10);
    printf("isHeap :: %d\n", isHeap(t));
    printf("isHeap :: %d\n",  isHeap2(t));
    printf("isCompleteTree :: %d\n",  isCompleteTree(t));    
    return 0;
}

/*
isHeap :: 1
isHeap :: 1
isCompleteTree :: 1
*/

int findMaxBTUtil(TreeNode *root) {
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

int findMaxBT(Tree *tree) {
    return findMaxBTUtil(tree->root);
}

int findMinBTUtil(TreeNode *root) {
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

int findMinBT(Tree *tree) {
    return findMinBTUtil(tree->root);
}

int searchBTUtil(TreeNode *root, int value) {
    if (root == NULL)
        return 0;

    if ((root->value == value) || 
            searchBTUtil(root->lChild, value) || 
            searchBTUtil(root->rChild, value))
        return 1;

    return 0;
}

int searchBT(Tree *tree, int value) {
    return searchBTUtil(tree->root, value);
}

TreeNode *searchBST(TreeNode *root, int value) /* iterative */
{
    while (root) {
        if (root->value == value)
            return root;
        else if (root->value > value)
            root = root->lChild;
        else
            root = root->rChild;
    }
    return NULL;
}

int main11() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printf("searchBT :: %d\n", searchBT(t, 9));
    printf("findMaxBT :: %d\n", findMaxBT(t));
    return 0;
}

/*
searchBT :: 1
findMaxBT :: 10
*/


int isBSTUtil(TreeNode *root) {
    if (!root)
        return 1;

    if ((root->lChild && maxValue(root->lChild) > root->value) ||
        (root->rChild && minValue(root->rChild) <= root->value))
        return 0;

    return isBSTUtil(root->lChild) && isBSTUtil(root->rChild);
}

int isBST(Tree *tree) {
    return isBSTUtil(tree->root);
}

int isBSTUtil2(TreeNode *root, int min, int max) {
    if (!root)
        return 1;

    if (root->value < min || root->value > max)
        return 0;

    return isBSTUtil2(root->lChild, min, root->value) &&
           isBSTUtil2(root->rChild, root->value, max);
}

int isBST2(Tree *tree) {
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

int isBST3(Tree *tree) {
    int temp = 0;
    return isBSTUtil3(tree->root, &temp);
}

TreeNode *trimOutsideRangeUtil(TreeNode *root, int min, int max) {
    TreeNode *tempNode;
    if (root == NULL)
        return NULL;

    root->rChild = trimOutsideRangeUtil(root->rChild, min, max);
    root->lChild = trimOutsideRangeUtil(root->lChild, min, max);

    if (root->value < min) {
        tempNode = root->rChild;
        freeTreeUtil(root->lChild);
        return tempNode;
    }

    if (root->value > max) {
        tempNode = root->lChild;
        freeTreeUtil(root->rChild);
        return tempNode;
    }

    return root;
}

void trimOutsideRange(Tree *tree, int min, int max) {
    tree->root = trimOutsideRangeUtil(tree->root, min, max);
}

void printInRangeUtil(TreeNode *root, int min, int max) {
    if (!root)
        return;

    printInRangeUtil(root->lChild, min, max);

    if (root->value >= min && root->value <= max)
        printf("%d ", root->value);

    printInRangeUtil(root->rChild, min, max);
}

void printInRange(Tree *tree, int min, int max) {
    printInRangeUtil(tree->root, min, max);
    printf("\n");
}

int main12() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printf("isBST :: %d\n", isBST(t));
    printf("isBST2 :: %d\n", isBST2(t));
    printf("isBST3 :: %d\n", isBST3(t));
    printInRange(t, 4, 8);
    trimOutsideRange(t, 4, 8);
    printInOrder(t); 
    return 0;
}

/*
isBST :: 1
isBST2 :: 1
isBST3 :: 1
4 5 6 7 8 
4 5 6 7 8 
*/


int ceilBST(Tree *tree, int value) {
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

int floorBST(Tree *tree, int value) {
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


int main13() {
    int arr[] = { 1, 2, 4, 5, 6, 7, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printInOrder(t);
    printf("floorBST : %d\n", floorBST(t, 3));
    printf("ceilBST : %d\n", ceilBST(t, 3));
    printf("floorBST : %d\n", floorBST(t, 8));
    printf("ceilBST : %d\n", ceilBST(t, 8));
    return 0;
}

/*
floorBST : 2
ceilBST : 4
floorBST : 7
ceilBST : 9
*/


TreeNode *lcaBSTUtil(TreeNode *root, int first, int second) {
    if (!root)
        return root;

    if (root->value > first && root->value > second) {
        return lcaBSTUtil(root->lChild, first, second);
    }
    if (root->value < first && root->value < second) {
        return lcaBSTUtil(root->rChild, first, second);
    }
    return root;
}

int lcaBST(Tree *tree, int first, int second) {
    TreeNode* ans = lcaBSTUtil(tree->root, first, second);
    if(ans)
        return ans->value;
    return -99999;
}


TreeNode *LcaBT(TreeNode *root, TreeNode *firstPtr, TreeNode *secondPtr) {
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

int main14() {
    int arr[] = { 1, 2, 4, 5, 6, 7, 9, 10 };
    Tree *t = createBinarySearchTree(arr, 10);
    printf("%d\n", lcaBST(t, 3, 4));
    printf("%d\n", lcaBST(t, 1, 4));
    printf("%d\n", lcaBST(t, 10, 4));
    return 0;
}


/*
4
2
6
*/


TreeNode *treeToListRec(TreeNode *curr) {
    TreeNode *head, *tail, *tempHead;

    if (!curr)
        return NULL;

    if (curr->lChild == NULL && curr->rChild == NULL) {
        curr->lChild = curr;
        curr->rChild = curr;
        return curr;
    }
    if (curr->lChild) {
        head = treeToListRec(curr->lChild);
        tail = head->lChild;

        curr->lChild = tail;
        tail->rChild = curr;
    }
    else
        head = curr;

    if (curr->rChild) {
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

TreeNode *treeToList(Tree *tree) {
    return treeToListRec(tree->root);
}

void  printDLL(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    TreeNode *curr = root;
    TreeNode *tail = curr->lChild;
    printf("DLL nodes are : " );
    while (curr != tail) {
        printf("%d ", curr->value);
        curr = curr->rChild;
    };
    printf("%d\n", curr->value);
    
}

int main16() {
    int arr[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Tree *t = createBinarySearchTree(arr, 10);
    printInOrder(t);
    TreeNode *head = treeToList(t); 
    printDLL(head);
    return 0;
}

/*
1 2 3 4 5 6 7 8 9 10 
DLL nodes are : 1 2 3 4 5 6 7 8 9 10
*/

void printBoundaryUtil(TreeNode *root, int isLastNode) {
    static int PrintOnlyLeafFlag = 0;
    static int PrintParentsFlag = 0;

    if (!root)
        return;

    if (!root->rChild && !root->lChild) {
        printf("%d ", root->value);
        PrintOnlyLeafFlag = 1;
        if (isLastNode)
            PrintParentsFlag = 1;
        return;
    }

    if (!PrintOnlyLeafFlag)
        printf("%d ", root->value);

    printBoundaryUtil(root->lChild, (!root->rChild) ? isLastNode : 0);

    if (root->rChild)
        printBoundaryUtil(root->rChild, isLastNode);

    if (PrintParentsFlag)
        printf("%d ", root->value);
}

void printBoundary(Tree *tree) {
    printBoundaryUtil(tree->root, 1);
}

int main17() {
    int arr[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Tree *t = createBinarySearchTree(arr, 10);
    printBoundary(t);
    return 0;
}

/*
5 2 1 4 7 10 9 8 5 
*/

int findNodeDepth(TreeNode *root, TreeNode *dstPtr) {
    int value;
    if (!root || !dstPtr)
        return -1;

    if (root->value == dstPtr->value)
        return 0;
    else if (root->value > dstPtr->value)
        value = findNodeDepth(root->lChild, dstPtr);
    else
        value = findNodeDepth(root->rChild, dstPtr);

    if (value != -1)
        return (value + 1);
    return -1;
}
/*
int pathLength(TreeNode *root, TreeNode *firstPtr, TreeNode *secondPtr) {
    TreeNode *parent = lcaBST(root, firstPtr, secondPtr);
    int first = findNodeDepth(parent, firstPtr);
    int second = findNodeDepth(parent, secondPtr);
    return first + second;
}
*/
int main() {
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
    main16();
    main17();
    return 0;
}
