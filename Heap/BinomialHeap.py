function BinomailHeapUnion(H1, H2):
    H = CreateBinomialHeap()
    H.head = BinomailHeapMerge(H1, H2)
    if H.head == null:
        then return H
    prev = null
    curr = H.head
    sibling = curr.sibling

    while sibling != null:
        if curr.degree != sibling.degree or 
            ( sibling.next != null and sibling.next.degree == curr.degree ):
            prev = curr
            curr = sibling
        else :
            if curr.key <= sibling.key: # sibling become child of curr.
                curr.sibling = sibling.sibling
                left = curr.leftchild
                curr.leftchild = sibling
                sibling.sibling = left
                sibling.parent = curr

            else: # curr become child of sibling.
                if prev == null:
                    H.head = sibling
                else:
                    prev.sibling = sibling

                left = sibling.leftchild
                sibling.leftchild = curr
                curr.parent = sibling
                curr.sibling = left

                # Sibling became new root.
                curr = sibling
        
        
        sibling = curr.sibling
    
    return H
       







function BinomialHeapMinimum(H)
    y = null
    x = H.head
    min = ∞
    while x != null
        do if x.key < min
            then min = x.key
            y = x
        x = x.sibling
    return y


function BinomialHeapInsert(H, x)
    H2 = CreateBinomialHeap()
    x.parent = null
    x.leftchild = null
    x.sibling = null
    x.degree = 0
    H2.head = x
    H = BinomailHeapUnion(H,H2)