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
        temp->child[i] = NULL;
    return temp;
}

void toLowerCase(char *str)
{
    int length = strlen(str);
    for (int i = 0; i < length; i++)
        if (str[i] >= 65 && str[i] <= (65 + 25))
            str[i] += 32;
}

void trieInserUtil(TrieNode *root, char *str)
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
        trieInserUtil(root->child[*str - 'a'], (str + 1));
    }
}
TrieNode *trieInsert(TrieNode *root, char *str)
{
    toLowerCase(str);
    if (str == NULL || *str == '\0')
        return root;
    if (root == NULL)
    {
        root = createNode();
        trieInserUtil(root, str);
    }
    else
    {
        trieInserUtil(root, str);
    }
    return root;
}

int findNode(TrieNode *root, char *str)
{
    toLowerCase(str);
    if (str == NULL)
    {
        printf("\n Input string empty.\n");
        return 0;
    }
    if (root == NULL)
    {
        printf("\n Trie empty \n");
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
        printf("\n Node not found \n");
        return 0;
    }
    if (*(str + 1) == '\0')
    {
        if (root->child[*str - 'a']->ch == *str && root->child[*str - 'a']->flag == 1)
        {
            printf("\n Node found \n");
            return 1;
        }
    }
    printf("\n Node not found \n");
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
    printf("%d", findNode(root, a));
    printf("%d", findNode(root, b));
    printf("%d", findNode(root, c));
    printf("%d", findNode(root, d));
}