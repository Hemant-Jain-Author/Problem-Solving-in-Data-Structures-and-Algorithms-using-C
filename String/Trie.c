#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TrieNode {
    int isLastChar;
    struct TrieNode *child[26];
} TrieNode;

TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++)
        node->child[i] = NULL;
    node->isLastChar = 0; 
    return node;
}

typedef struct Trie {
    TrieNode *root;
} Trie;

Trie *createTrie() {
    Trie *trie = (Trie*)malloc(sizeof(Trie));
    trie->root = createNode(); // first node with dummy value.
    return trie;
}

TrieNode* addTrieUtil(TrieNode *curr, char *str, int start) {
    if(curr == NULL)
        curr = createNode();
    
    if(strlen(str) == start)
        curr->isLastChar = 1;
    else{
        int index = (str[start] > 'a' && str[start] < 'z') ? str[start] - 'a' : str[start] - 'A';
        curr->child[index] = addTrieUtil(curr->child[index], str, start + 1);
    }   
    return curr;
}

void addTrie(Trie *trie, char *str) {
    if (str == NULL || *str == '\0')
        return;
    addTrieUtil(trie->root, str, 0);
}

void removeTrieUtil(TrieNode *curr, char *str, int start) {
    if(curr == NULL)
        return;
    
    if(strlen(str) == start) {
        curr->isLastChar = 0;
        return;
    }
    int index = (str[start] > 'a' && str[start] < 'z') ? str[start] - 'a' : str[start] - 'A';
    removeTrieUtil(curr->child[index], str, start + 1);  
}

void removeTrie(Trie *trie, char *str) {
    if (str == NULL || *str == '\0')
        return;
    removeTrieUtil(trie->root, str, 0);
}

int findTrieUtil(TrieNode *curr, char *str, int start) {
    if (curr == NULL)
        return 0;

    if(strlen(str) == start)
        return curr->isLastChar;

    int index = (str[start] > 'a' && str[start] < 'z') ? str[start] - 'a' : str[start] - 'A';
    return findTrieUtil(curr->child[index], str, start + 1);
}

int findTrie(Trie *trie, char *str) {
    if (str == NULL || *str == '\0')
        return 0;
    return findTrieUtil(trie->root, str, 0);
}

int main() {
    Trie *trie = createTrie();
    addTrie(trie, "banana");
    addTrie(trie, "apple");
    addTrie(trie, "Apple");
    addTrie(trie, "APPLE");
    addTrie(trie, "mango");

    printf("find apple : %d\n", findTrie(trie, "apple"));
    printf("find banana : %d\n", findTrie(trie, "banana"));
    printf("find grapes : %d\n", findTrie(trie, "grapes"));
    printf("find mango : %d\n", findTrie(trie, "mango"));
}

/*
find apple : 1
find banana : 1
find grapes : 0
find mango : 1
*/