#include "stdafx.h"
#include "StringAlgo.h"

bool matchExpUtil(std::string &exp, std::string &str, int i, int j)
{
	if (i == exp.size() && j == str.size())
	{
		return true;
	}
	if ((i == exp.size() && j != str.size()) || (i != exp.size() && j == str.size()))
	{
		return false;
	}
	if (exp[i] == '?' || exp[i] == str[j])
	{
		return matchExpUtil(exp, str, i + 1, j + 1);
	}
	if (exp[i] == '*')
	{
		return matchExpUtil(exp, str, i + 1, j) || matchExpUtil(exp, str, i, j + 1) || matchExpUtil(exp, str, i + 1, j + 1);
	}
	return false;
}

bool matchExp(std::string &exp, std::string &str)
{
	return matchExpUtil(exp, str, 0, 0);
}

int match(std::string &source, std::string &pattern)
{
	int iSource = 0;
	int iPattern = 0;
	int sourceLen = source.size();
	int patternLen = pattern.size();
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



bool isPrime(int n)
{
	bool answer = (n > 1) ? true : false;

	for (int i = 2; i * i < n; ++i)////////////// mistake
	{
		if (n % i == 0)
		{
			answer = false;
			break;
		}
	}
	return answer;
}

int myAtoi(const std::string &str)
{
	int value = 0;

	int size = str.length();
	for (int i = 0; i < size; i++)
	{
		char ch = str[i];
		value = (value << 3) + (value << 1) + (ch - '0');
	}
	return value;
}

bool isUniqueChar(const std::string &str)
{
	std::vector<int> bitarr(26);
	for (int i = 0; i < 26; i++)
	{
		bitarr[i] = 0;
	}
	int size = str.length();
	for (int i = 0; i < size; i++)
	{
		char c = str[i];
		if ('A' <= c && 'Z' >= c)
		{
			c = static_cast<char>(c - 'A');
		}
		else if ('a' <= c && 'z' >= c)
		{
			c = static_cast<char>(c - 'a');
		}
		else
		{
			std::cout << "Unknown Char!" << std::endl;
			return false;
		}
		if (bitarr[c] != 0)
		{
			std::cout << "Duplicate detected!" << std::endl;
			return false;
		}
	}
	std::cout << "No duplicate detected!" << std::endl;
	return true;
}

char ToUpper(char s)
{
	if (s >= 97 && s <= (97 + 25))
	{
		s = static_cast<char>(s - 32);
	}
	return s;
}

char ToLower(char s)
{
	if (s >= 65 && s <= (65 + 25))
	{
		s = static_cast<char>(s + 32);
	}
	return s;
}

char LowerUpper(char s)
{
	if (s >= 97 && s <= (97 + 25))
	{
		s = static_cast<char>(s - 32);
	}
	else if (s >= 65 && s <= (65 + 25))
	{
		s = static_cast<char>(s + 32);
	}
	return s;
}

bool isPermutation(const std::string &s1, const std::string &s2)
{
	std::vector<int> count(256);
	int length = s1.length();
	if (s2.length() != length)
	{
		std::cout << "is permutation return false" << std::endl;
		return false;
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
		if (count[i] != 0)
		{
			std::cout << "is permutation return false" << std::endl;
			return false;
		}
	}
	std::cout << "is permutation return true" << std::endl;
	return true;
}

bool isPalindrome(const std::string &str)
{
	int i = 0, j = str.length() - 1;
	while (i < j && str[i] == str[j])
	{
		i++;
		j--;
	}
	if (i < j)
	{
		std::cout << "String is not a Palindrome" << std::endl;
		return false;
	}
	else
	{
		std::cout << "String is a Palindrome" << std::endl;
		return true;
	}
}

int pow(int x, int n)
{
	int value;
	if (n == 0)
	{
		return (1);
	}
	else if (n % 2 == 0)
	{
		value = pow(x, n / 2);
		return (value * value);
	}
	else
	{
		value = pow(x, n / 2);
		return (x * value * value);
	}
}

int myStrcmp(const std::string &a, const std::string &b)
{
	int index = 0;
	int len1 = a.length();
	int len2 = b.length();
	int minlen = len1;
	if (len1 > len2)
	{
		minlen = len2;
	}

	while (index < minlen && a[index] == b[index])
	{
		index++;
	}

	if (index == len1 && index == len2)
	{
		return 0;
	}
	else if (len1 == index)
	{
		return -1;
	}
	else if (len2 == index)
	{
		return 1;
	}
	else
	{
		return a[index] - b[index];
	}
}

void reverseString(std::string &a)
{
	int lower = 0;
	int upper = a.size() - 1;
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

void reverseString(std::string &a, int lower, int upper)
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

void reverseWords(std::string &a)
{
	int length = a.size();
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
	reverseString(a, 0, length - 1);
}

void printAnagram(std::string  &a)
{
	int n = a.size();
	printAnagram(a, n, n);
}

void printAnagram(std::string &a, int max, int n)
{
	if (max == 1)
	{
		for(auto ch : a)
			std::cout << ch;
	}
	for (int i = -1; i < max - 1; i++)
	{
		if (i != -1)
		{
			a[i] ^= a[max - 1] ^= a[i] ^= a[max - 1];
		}
		printAnagram(a, max - 1, n);
		if (i != -1)
		{
			a[i] ^= a[max - 1] ^= a[i] ^= a[max - 1];
		}
	}
}

void shuffle(std::string &ar)
{
	int n = ar.size() / 2;
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

std::string addBinary(std::string &first, std::string &second)
{
	int size1 = first.size();
	int size2 = second.size();
	int totalIndex;
	std::string total;
	if (size1 > size2)
	{
		total = std::string('0',size1 + 2);
		totalIndex = size1;
	}
	else
	{
		total = std::string('0', size2 + 2);
		totalIndex = size2;
	}
	total[totalIndex + 1] = '\0';
	int carry = 0;
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