function Search(list, key)
    p = top-left node in list
    while (p.below != null)       //Scan down
        p = p.below
        while (key >= p.next)      //Scan forward
            p = p.next
    return p


function Insert(list, key, value)
    // Create update array
    local update[0...MaxLevel+1]
    x = list.header

    // Populate update array to find 
    // the possition of new node at each level.
    for i = (list.level - 1) downto 0
        while x.forward[i] != Null and x.forward[i].key < key 
            x = x.forward[i]
        update[i] = x

    // Key already present so just update value.
    if x.forward[0] != Null and x.forward[0].key = key
        x.forward[0].value = value
        return;


    // Level of the new node is created.
    // if level is increased then header will be 
    // the start of new level list.
    lvl = randomLevel()
    if lvl > list.level
        for i = list.level to (lvl - 1)
            update[i] = list.header
        list.level = lvl

    // New node is created and linked at each level.
    x = makeNode(key, value, lvl)
    for i = 0 to lvl
        x.forward[i] = update[i].forward[i]
        update[i].forward[i] = x


function Delete(list, key)
    local update[0..MaxLevel+1]
    x = list.header
    for i = (list.level - 1) downto 0 do
        while x.forward[i] != Null and x.forward[i].key < key
            x = x.forward[i]
        update[i] = x

    x = x.forward[0]
    if x.key = key
        for i = 0 to list.level-1
            if update[i].forward[i] ≠ x 
                then break
            update[i].forward[i] = x.forward[i]
        free(x)
        while list.level > 0 and list.header.forward[list.level] = Null
            list.level = list.level - 1
