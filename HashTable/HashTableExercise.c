
#include<stdio.h>
#include<string.h>

int isAnagram(char* str1, char* str2){
    int size1 = strlen(str1);
    int size2 = strlen(str2);
    if (size1 != size2)
        return 0;
    Counter cm;
    CounterInit(&cm);

    for(int i=0;i<size1;i++)
        CounterAdd(&cm, str1[i]);

    for(int i=0;i<size2;i++)
    {
        if (CounterFind(&cm, str2[i]) == 0)
            return 0;
        else
            CounterRemove(&cm, str2[i]);
    }
      return 1;
}
    
def removeDuplicate(char* exp)
{   Set hs;
    SetInit(&hs);
    retexp = ""
    for ch in exp:
        if (ch in hs) == False:
            retexp += ch
            hs.add(ch)
    return retexp
}

def findMissing(arr, start, end):
    hs = set()
    for i in arr:
        hs.add(i)
    curr = start
    while curr <= end:
        if (curr in hs) == False:
            return curr
        curr += 1
    return sys.maxsize

def printRepeating(arr):
    hs = set()
    print("Repeating elements are:", end=' ')
    for val in arr:
        if val in hs:
            print(val, end=' ')
        else:
            hs.add(val)

def printFirstRepeating(arr):
    size = len(arr)
    i = 0
    hs = Counter()
    while i < size:
        hs[arr[i]] += 1
        i += 1
    i = 0
    while i < size:
        if hs.get(arr[i]) > 1:
            print("First Repeating number is : " , arr[i])
            return arr[i]
        i += 1

def hornerHash(self, key, tableSize):
    size = len(key)
    h = 0
    i = 0
    while i < size:
        h = (32 * h + key[i]) % tableSize
        i += 1
    return h

first = "hello"
second = "elloh"
third = "world"
print("isAnagram : " , isAnagram(first, second))
print("isAnagram : " , isAnagram(first, third))
print(removeDuplicate(first))
print(first)
arr = [1, 2, 3, 5, 6, 7, 8, 9, 10]
print(findMissing(arr, 1, 10))
arr1 = [1, 2, 3, 4, 4, 5, 6, 7, 8, 9, 1]
printRepeating(arr1)
printFirstRepeating(arr1)