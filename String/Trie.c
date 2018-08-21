#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trieNode_t
{
    int flag;
    char ch;
    struct trieNode_t *child[26];
} TrieNode;

TrieNode *createNode()
{
    TrieNode *temp = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++)
        temp->child[i] == NULL;
    return temp;
}

char ToLower(char s)
{
    if (s >= 65 && s <= (65 + 25))
        s = s + 32;
    return s;
}

void myToLower(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++)
        str[i] = ToLower(str[i]);
}

void trie(TrieNode *root, char *str)
{
    if (*(str + 1) == '\0')
    {
        if (root->child[*str - 'a'] == NULL)
        {
            root->child[*str - 'a'] = createNode();
        }
        root->child[*str - 'a']->flag = 1;
        root->child[*str - 'a']->ch = *str;
        return;
    }
    else
    {
        if (root->child[*str - 'a'] == NULL)
        {
            root->child[*str - 'a'] = createNode();
            root->child[*str - 'a']->flag = 0;
        }
        root->child[*str - 'a']->ch = *str;
        trie(root->child[*str - 'a'], (str + 1));
    }
}
TrieNode *trieInsert(TrieNode *root, char *str)
{
    myToLower(str);
    if (str == NULL || *str == '\0')
        return root;
    if (root == NULL)
    {
        root = createNode();
        trie(root, str);
    }
    else
    {
        trie(root, str);
    }
    return root;
}
int findNode(TrieNode *root, char *str)
{
    myToLower(str);
    if (str == NULL)
    {
        printf("node found\n");
        return 0;
    }
    if (root == NULL)
    {
        printf("node found\n");
        return 0;
    }
    while (root->child[*str - 'a'] && *(str + 1) != '\0' && root->child[*str - 'a']->ch == *str)
    {
        root = root->child[*str - 'a'];
        str++;
    }
    //char does not match  or  char index child does not exist
    if (!root->child[*str - 'a'] || root->child[*str - 'a']->ch != *str)
    {
        printf("node not found\n");
        return 0;
    }
    if (*(str + 1) == '\0')
    {
        if (root->child[*str - 'a']->ch == *str && root->child[*str - 'a']->flag == 1)
        {
            printf("node found\n");
            return 1;
        }
    }
    printf("node not found\n");
    return 0;
}
int main()
{
    TrieNode *root = NULL;
    char a[] = "hemant";
    char b[] = "heman";
    char c[] = "hemantjain";
    char d[] = "jain";
    root = trieInsert(root, a);
    root = trieInsert(root, d);
    printf("% s", findNode(root, a));
    printf("% s", findNode(root, b));
    printf("% s", findNode(root, c));
    printf("% s", findNode(root, d));
}
