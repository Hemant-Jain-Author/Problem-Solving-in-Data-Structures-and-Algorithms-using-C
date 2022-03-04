#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BruteForceSearch(char *text, char *pattern) {
    const int n = strlen(text);
    const int m = strlen(pattern);
    int j;

    for (int i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (pattern[j] != text[i + j])
                break;
        }
        if (j == m)
            return i;
    }
    return -1;
}

int RobinKarp(char *text, char *pattern) {
    const int n = strlen(text);
    const int m = strlen(pattern);
    int prime = 101;
    int powm = 1;
    int TextHash = 0, PatternHash = 0;

    if (m == 0 || m > n)
        return -1;

    for (int i = 0; i < m - 1; i++)
        powm = (powm << 1) % prime;

    for (int i = 0; i < m; i++) {
        PatternHash = ((PatternHash << 1) + pattern[i]) % prime;
        TextHash = ((TextHash << 1) + text[i]) % prime;
    }

    for (int i = 0; i <= (n - m); i++) {
        if (TextHash == PatternHash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j == m)
                return i;
        }

        if(i < (n - m)) 
            TextHash = (((TextHash - text[i] * powm) << 1) + text[i + m]) % prime;

        if (TextHash < 0)
            TextHash = (TextHash + prime);
    }
    return -1;
}

void KMPPreprocess(char *pattern, int *ShiftArr) {
    const int m = strlen(pattern);
    int i = 0, j = -1;
    ShiftArr[i] = -1;
    while (i < m) {
        while (j >= 0 && pattern[i] != pattern[j])
            j = ShiftArr[j];
        i++;
        j++;
        ShiftArr[i] = j;
    }
}

int KMP(char *text, char *pattern) {
    int i = 0, j = 0, count = 0;
    const int n = strlen(text);
    const int m = strlen(pattern);

    int *ShiftArr = (int *)calloc(m + 1, sizeof(int));

    KMPPreprocess(pattern, ShiftArr);

    while (i < n) {
        while (j >= 0 && text[i] != pattern[j])
            j = ShiftArr[j];
        i++;
        j++;
        if (j == m) {
            return (i - m);
        }
    }
    return -1;
}
int KMPFindCount(char *text, char *pattern) {
    int i = 0, j = 0, count = 0;
    const int n = strlen(text);
    const int m = strlen(pattern);
    int *ShiftArr = (int *)calloc(m + 1, sizeof(int));

    KMPPreprocess(pattern, ShiftArr);
    while (i < n) {
        while (j >= 0 && text[i] != pattern[j])
            j = ShiftArr[j];

        i++;
        j++;

        if (j == m) {
            count++;
            j = ShiftArr[j];
        }
    }
    return count;
}

int main1() {
    char *text = "hello, world!";
    char *pattern = "world";
    printf("BruteForceSearch returns: %d \n", BruteForceSearch(text, pattern));
    printf("RobinKarp returns: %d \n", RobinKarp(text, pattern));
    printf("KMP returns: %d \n", KMP(text, pattern));
    return 0;
}

/*
BruteForceSearch : 7 
RobinKarp : 7 
KMP : 7 
*/

int main() {
    main1();
    char* str = "Only time will tell if we stand the test of time";
    printf("Frequency of 'time' is : %d\n", KMPFindCount(str, "time"));
    return 0;
}
/*
Frequency of 'time' is : 2
*/