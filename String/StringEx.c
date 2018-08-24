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

int main1()
{
    char *exp = "*hello*?world";
    char *text = "hello  world";
    printf("matchExp :: %d ", matchExp(exp, text));
    return 0;
}

int matchPattern(char *text, char *pattern)
{
    int iText = 0;
    int iPattern = 0;
    int textSize = strlen(text);
    int patternSize = strlen(pattern);

    for (iText = 0; iText < textSize; iText++)
    {
        if (text[iText] == pattern[iPattern])
        {
            iPattern++;
        }
        if (iPattern == patternSize)
        {
            return 1;
        }
    }
    return 0;
}

int main2()
{
    char *pattern = "hello";
    char *text = "ah erlulo  world";
    printf("matchPattern :: %d ", matchPattern(text, pattern));
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

int main3()
{
    char *st = "100";
    printf(" %d ", myAtoi(st));
    return 0;
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
            printf("Unknown Char.\n");
            return 0;
        }

        if (bitarr & (1 << c))
        {
            printf("Duplicate detected.\n");
            return 0;
        }
        bitarr |= (1 << c);
    }
    printf("No duplicate detected.\n");
    return 1;
}

int main4()
{
    char *st = "APLE";
    printf(" %d ", isUniqueChar(st));
    st = "APPLE";
    printf(" %d ", isUniqueChar(st));
    return 0;
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

    for (int i = 0; i < 256; i++)
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

int main5()
{
    char *st = "HELLO";
    char *st2 = "LLOEH";
    char *st3 = "LLPEH";
    printf("IsPermutation %d ", isPermutation(st, st2));
    printf("IsPermutation %d ", isPermutation(st, st3));
    return 0;
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
        printf("String is not a Palindrome.\n");
        return 0;
    }
    else
    {
        printf("String is a Palindrome.\n");
        return 1;
    }
}

int main6()
{
    char *st = "HELLOLLEH";
    printf("isPalindrome %d \n", isPalindrome(st));
    st = "HELLOOLLEH";
    printf("isPalindrome %d \n", isPalindrome(st));
    st = "HELLOOLLEHA";
    printf("isPalindrome %d \n", isPalindrome(st));
    return 0;
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

int main7()
{
    char *st = "HELLOLLEH";
    printf("isPalindrome %d \n", isPalindrome(st));
    st = "HELLOOLLEH";
    printf("isPalindrome %d \n", isPalindrome(st));
    st = "HELLOOLLEHA";
    printf("isPalindrome %d \n", isPalindrome(st));
    return 0;
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

int main8()
{
    printf("%d", Pow(10, 4));
    return 0;
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

int main9()
{
    printf("%d\n", myStrcmp("applaa", "applha"));
    printf("%d\n", myStrcmp("applqa", "applha"));
    printf("%d\n", myStrcmp("applha", "applha"));
    return 0;
}

char *mySubstr(char *src, char *dst, int n)
{
    char *ptr = dst;
    int i = 0;
    for (i = 0; i < n && src; i++)
    {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return ptr;
}

int main10()
{
    char dest[100];
    printf("%s\n", mySubstr("applebanana", dest, 5));
    return 0;
}

char *myStrdup(char *src)
{
    char *dst = (char *)malloc((strlen(src) + 1) * sizeof(char));
    char *ptr = dst;
    while (*dst++ = *src++)
        ;
    return ptr;
}

int main11()
{
    printf("%s\n", myStrdup("applebanana"));
    return 0;
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

void reverse(char *str, int n)
{
    char *start, *end;
    char temp;

    for (start = str, end = str + n - 1; start < end; ++start, --end)
    {
        temp = *start;
        *start = *end;
        *end = temp;
    }
}

int main12()
{
    char ch[] = "Hello";
    reverse(ch, 5);
    printf("%s\n", ch);
    return 0;
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
        src++;
    }
    return length;
}

int main13()
{
    char ch[] = "Hello";
    printf("%d\n", myStrlen(ch));
    return 0;
}

char *Strcat(char *s1, char *s2)
{
    char *ptr = s1;
    while (*s1 != '\0')
        s1++;
    while (*s2 != '\0')
        *s1++ = *s2++;
    return ptr;
}

int main14()
{
    char ch[100] = "Hello";
    printf("%s\n", Strcat(ch, ", World!"));
    return 0;
}

void reverseString2(char *a, int n)
{
    int lower = 0;
    int upper = n – 1;
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

int main15()
{
    char ch[100] = "Hello, World!";
    reverseString(ch, 0, 12);
    printf("%s\n", ch);
    return 0;
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

int main16()
{
    char ch[100] = "Hello, World!";
    reverseWords(ch);
    printf("%s\n", ch);
    return 0;
}

void printAnagramUtil(char *a, int max, int n)
{
    if (max == 1)
        printf(" %s \n", a);

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

int main17()
{
    char ch[] = "Hello";
    printAnagram(ch);
    //printf("%s\n", ch);
    return 0;
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

int main18()
{
    char ch[] = "aaaabbbb";
    shuffle(ch, 4);
    printf("%s\n", ch);
    return 0;
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
    char ch[] = "aa aa bbb b .";
    removeSpaces(ch);
    printf("%s\n", ch);
    return 0;
}