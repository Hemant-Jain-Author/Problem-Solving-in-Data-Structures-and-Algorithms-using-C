#include "../Stack/Stack.c"

int isBSTArray(int preorder[], int size) {
    Stack* stk = createStack();
    int value;
    int root = -999999;
    for (int i = 0; i < size; i++) {
        value = preorder[i];

        // If value of the right child is less than roo
        if (value < root)
            return 0;
        // First left child `alues will be popped
        // Last popped value will be the roo
        while (StackIsEmpty(stk) == 0 && StackTop(stk) < value) {
            root = StackPop(stk);
        }
        // add current value to the stack.
        StackPush(stk, value);
    }
    return 1;
}

int main() {
    int arr1[] = {5, 2, 4, 6, 9, 10}; 
    printf("%d\n", isBSTArray(arr1, 6));

    int arr2[] = {5, 2, 6, 4, 7, 9, 10};
    printf("%d\n", isBSTArray(arr2, 6));
    return 0;
}

/*
1
0
*/
