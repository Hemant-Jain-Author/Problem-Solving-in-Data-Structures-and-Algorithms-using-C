function MakeFibonacciHeap():
    H = CreateFibonnacciHeap()
    H.n = 0
    H.min = Null
    return H

function FibonacciHeapMinimum(H):
    return H.min

function FibonacciHeapLink(H, y, x)
    remove y from the root list of H
    make y a child of x
    x.degree = x.degree + 1
    y.mark = FALSE

function Consolidate(H)
    for i=0 to Len(H)
        A[i] = Null

    for each root w in the root list of H
        x = w
        d = x.degree
        while A[d] != Null
            y = A[d]
            if x.key > y.key
                swap x & y
            FibonacciHeapLink(H, y, x)
            A[d] = Null
            d = d+1
        A[d] = x

        if H.min = Null or H.min.key > x.key:
            H.min = x

function FibonacciHeapUnion(H1,H2)
    Concatinate the root list of H2 into H1

    if (H1.min = Null) or (H2.min != Null and H2.min.key < H1.min.key)
        H1.min = H2.min
    H1.n = H1.n + H2.n
    free H2
    return H1


function FibonacciHeapInsert(H, x)
    x.degree = 0
    x.parent = Null
    x.child = Null
    x.left = x
    x.right = x
    mark = FALSE
    
    concatenate the root x into root list of H
    if H.min = Null or x.key < H.min.key
        H.min = x
    H.n = H.n + 1

funciton FibonacciHeapExtractMin(H)
    z = H.min
    if z != Null
        for each child x of z
            x.parent = Null
            add x to the root list of H
        remove z from the root list of H

        if z = z.right
            H.min = Null
        else 
            H.min = z.right
        Consolidate(H)
        H.n = H.n - 1
    return z

function FibonacciHeapDecreaseKey(H, x, k)
    if k > x.key
        error "new key is greater than current key"
    x.key = k
    y = x.parent
    if y  != Null and x.key < y.key
        Cut(H, x, y)
        CascadingCut(H,y)    
    if x.key < H.min.key
        H.min = x

function Cut(H,x,y)
    Remove x from the child list of y, decrementing y.degree
    Add x to the root list of H
    x.parent = Null
    x.mark = FALSE

function CascadingCut(H,y)
    z =  y.parent
    if z  != Null
        if y.mark = FALSE
            y.mark = TRUE
        else 
            Cut(H, y, z)
            CascadingCut(H, z)

function FibonacciHeapDelete(H,x)
    FibonacciHeapDecrease-Key(H,x,-infinity)
    FibonacciHeapExtractMin(H)





It is the most important operation on a fibonacci heap. In this operation, the node with minimum value is removed from the heap and the tree is re-adjusted.

The following steps are followed:

