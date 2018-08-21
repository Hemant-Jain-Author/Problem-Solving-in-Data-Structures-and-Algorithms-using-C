#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int matchExpUtil(char *exp, char *str, int i, int j)
{
    if (i == strlen(exp) && j == strlen(str))
        return 1;

    if ((i == strlen(exp) && j != strlen(str)) || (i != strlen(exp) && j == strlen(str)))
        return 0;

    if (exp[i] == '?' || exp[i] == str[j])
        return matchExpUtil(exp, str, i + 1, j + 1);

    if (exp[i] == '*')
        return matchExpUtil(exp, str, i + 1, j) || matchExpUtil(exp, str, i, j + 1) || matchExpUtil(exp, str, i + 1, j + 1);
    return 0;
}

int matchExp(char *exp, char *str)
{
    return matchExpUtil(exp, str, 0, 0);
}

int match(char *source, char *pattern)
{
    int iSource = 0;
    int iPattern = 0;
    int sourceLen = strlen(source);
    int patternLen = strlen(pattern);

    for (iSource = 0; iSource < sourceLen; iSource++)
    {
        if (source[iSource] == pattern[iPattern])
        {
            iPattern++;
        }
        if (iPattern == patternLen)
        {
            return 1;
        }
    }
    return 0;
}

int myAtoi(const char *str)
{
    int value = 0;
    while (*str)
    {
        value = (value << 3) + (value << 1) + (*str - '0');
        str++;
    }
    return value;
}

int isUniqueChar(char *s)
{
    int bitarr = 0;
    int size = strlen(s);
    for (int i = 0; i < size; i++)
    {
        char c = s[i];
        if ('A' <= c && 'Z' >= c)
        {
            c = c - 'A';
        }
        else if ('a' <= c && 'z' >= c)
        {
            c = c - 'a';
        }
        else
        {
            printf("Unknown Char!\n");
            return 0;
        }

        if (bitarr & (1 << c))
        {
            printf("Duplicate detected!\n");
            return 0;
        }
        bitarr |= (1 << c);
    }
    printf("No duplicate detected!\n");
    return 1;
}

char ToUpper(char s)
{
    if (s >= 97 && s <= (97 + 25))
        s = s - 32;
    return s;
}

char ToLower(char s)
{
    if (s >= 65 && s <= (65 + 25))
        s = s + 32;
    return s;
}

int isPermutation(char *s1, char *s2)
{
    int count[256];

    int length = strlen(s1);
    if (strlen(s2) != length)
    {
        printf("is permutation return 0\n");
        return 0;
    }
    for (int i = 0; i < 256; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < length; i++)
    {
        char ch = s1[i];
        count[ch]++;
        ch = s2[i];
        count[ch]--;
    }

    for (int i = 0; i < length; i++)
    {
        if (count[i])
        {
            printf("is permutation return false\n");
            return 0;
        }
    }
    printf("is permutation return true\n");
    return 1;
}

int isPalindrome(char *str)
{
    int i = 0, j = strlen(str) - 1;
    while (i < j && str[i] == str[j])
    {
        i++;
        j--;
    }
    if (i < j)
    {
        printf("String is not a Palindrome");
        return 0;
    }
    else
    {
        printf("String is a Palindrome");
        return 1;
    }
}
void myItoa(char *buffer, int value)
{
    static int index = -1;
    int remender = value % 10;
    value /= 10;
    if (value)
        myItoa(buffer, value);
    buffer[++index] = '0' + remender;
    buffer[index + 1] = '\0';
}
float MyAtof(char *str)
{
    float num = 0.0F;
    float fraction = 0.1F;
    int decimalStart = 0;
    int size = strlen(str);

    for (int i = 0; i < size; i++)
    {
        if (str[i] == '.')
        {
            decimalStart = 1;
            continue;
        }
        if (!decimalStart)
        {
            num = (num * 10) + (str[i] - '0');
        }
        else
        {
            num += (str[i] - '0') * fraction;
            fraction *= 0.1F;
        }
    }
    return num;
}
/* lower to upper */
char LowerUpper(char s)
{
    if (s >= 97 && s <= (97 + 25))
        s = s - 32;
    else if (s >= 65 && s <= (65 + 25))
        s = s + 32;
    return s;
}
char *myStrcpy(char *dst, char *src)
{
    char *ptr = dst;
    while (*dst++ = *src++)
        ;
    return ptr;
}
int Pow(int x, int n)
{
    int value;
    if (n == 0)
        return (1);
    else if (n % 2 == 0)
    {
        value = Pow(x, n / 2);
        return (value * value);
    }
    else
    {
        value = Pow(x, n / 2);
        return (x * value * value);
    }
}
int myStrcmp(char *a, char *b)
{
    while ((*a) == (*b))
    {
        if (*a == '\0')
            return 0;
        a++;
        b++;
    }
    if (*a == '\0')
        return -1;
    if (*b == '\0')
        return 1;
    int value = (*a - *b);
    return value;
}
char *mySubstr(char *src, char *dst, int n)
{
    int count = n;
    char *ptr = dst;
    do
    {
        n--;
        if (n == 0)
        {
            ptr[count - 1] = '\0';
            break;
        }
        else
        {
            dst = src;
            dst++;
            src++;
        }
    } while (src);
    return ptr;
}
char *myStrdup(char *src)
{
    char *dst = (char *)malloc((strlen(src) + 1) * sizeof(char));
    char *ptr = dst;
    while (*dst++ = *src++)
        ;
    return ptr;
}
void mymemcpy(void *destPtr, const void *srcPtr, int size)
{
    char *destTemp = (char *)destPtr;
    const char *srcTemp = (char *)srcPtr;
    while (size--)
    {
        *destTemp++ = *srcTemp++;
    }
}
void reverse(char *s, int N)
{
    char *p, *q;
    char t;
    for (p = s, q = s + N - 1; p < q; ++p, --q)
    {
        t = *q;
        *q = *p;
        *p = t;
    }
}
void mymemmove(void *from, void *to, int size)
{
    char *destTemp = (char *)to;
    char *srcTemp = (char *)from;
    int i;
    if (from == to)
    {
        // Nothing to copy!
    }
    else if (from > to)
    {
        for (i = 0; i < size; i++)
            destTemp[i] = srcTemp[i];
    }
    else
    {
        for (i = size - 1; i >= 0; i--)
            destTemp[i] = srcTemp[i];
    }
#ifdef BIG_ENDIAN
    reverse(destTemp, size);
#endif
}
int myStrlen(char *src)
{
    int length = 0;
    while (*src != '\0')
    {
        length++;
    }
    return length;
}
char *Strcat(char *s1, char *s2)
{
    char *ptr = s1;
    while (*s1++)
        ;
    while (*s2 != '\0')
        *s1++ = *s2++;
    return ptr;
}
void reverseString(char *a, int lower, int upper)
{
    char tempChar;
    while (lower < upper)
    {
        tempChar = a[lower];
        a[lower] = a[upper];
        a[upper] = tempChar;
        lower++;
        upper--;
    }
}
void reverseWords(char *a)
{
    int length = strlen(a);
    int lower, upper = -1;
    lower = 0;
    for (int i = 0; i <= length; i++)
    {
        if (a[i] == ' ' || a[i] == '\0')
        {
            reverseString(a, lower, upper);
            lower = i + 1;
            upper = i;
        }
        else
        {
            upper++;
        }
    }
    reverseString(a, 0, length - 1); //-1 because we do not want to reverse ‘\0’
}

void printAnagramUtil(char *a, int max, int n)
{
    if (max == 1)
        printf(" %s ",a);

    for (int i = -1; i < max - 1; i++)
    {
        if (i != -1)
            a[i] ^= a[max - 1] ^= a[i] ^= a[max - 1];
        printAnagramUtil(a, max - 1, n);
        if (i != -1)
            a[i] ^= a[max - 1] ^= a[i] ^= a[max - 1];
    }
}

void printAnagram(char *a)
{
    int n = strlen(a);
    printAnagramUtil(a, n, n);
}

void shuffle(char ar[], int n)
{
    int count = 0;
    int k = 1;
    char temp = '\0';
    for (int i = 1; i < n; i = i + 2)
    {
        temp = ar[i];
        k = i;
        do
        {
            k = (2 * k) % (2 * n - 1);
            temp ^= ar[k] ^= temp ^= ar[k];
            count++;
        } while (i != k);

        if (count == (2 * n - 2))
        {
            break;
        }
    }
}
char *addBinary(char *first, char *second)
{
    int size1 = strlen(first);
    int size2 = strlen(second);
    int totalIndex;
    char *total;
    if (size1 > size2)
    {
        total = (char *)malloc((size1 + 2) * sizeof(char));
        totalIndex = size1;
    }
    else
    {
        total = (char *)malloc((size2 + 2) * sizeof(char));
        totalIndex = size2;
    }
    total[totalIndex + 1] = '\0';
    int carry = 0;
    int curr = 0;
    size1--;
    size2--;
    while (size1 >= 0 || size2 >= 0)
    {
        int firstValue = (size1 < 0) ? 0 : first[size1] - '0';
        int secondValue = (size2 < 0) ? 0 : second[size2] - '0';
        int sum = firstValue + secondValue + carry;

        carry = sum >> 1;
        sum = sum & 1;

        total[totalIndex] = (sum == 0) ? '0' : '1';

        totalIndex--;
        size1--;
        size2--;
    }
    total[totalIndex] = (carry == 0) ? '0' : '1';
    return total;
}
void removeSpaces(char *str)
{
    char *to = str;
    char *from = str;

    if (str == NULL)
        return;

    while (*from != '\0')
    {
        if (*from == ' ')
        {
            from++;
            continue;
        }

        *to = *from;
        from++;
        to++;
    }
    *to = '\0';
}

int main()
{
    return 0;
}