#include "stdafx.h"
#include "Algo.h"

int main1()
{
	std::string st1 = "hello, world!";
	std::string st2 = "world";
	std::cout << "BruteForceSearch return : " << BruteForceSearch(st1, st2) << std::endl;
	std::cout << "RobinKarp return : " << RobinKarp(st1, st2) << std::endl;
	std::cout << "KMP return : " << KMP(st1, st2) << std::endl;
	return 0;
}

int BruteForceSearch(const std::string &text, const std::string &pattern)
{
	std::vector<char> txt(text.begin(), text.end());
	std::vector<char> ptn(pattern.begin(), pattern.end());
	return BruteForceSearch(txt, ptn);
}

int BruteForceSearch(std::vector<char> &text, std::vector<char> &pattern)
{
	int i = 0, j = 0;
	const int n = text.size();
	const int m = pattern.size();
	while (i <= n - m)
	{
		j = 0;
		while (j < m && pattern[j] == text[i + j])
		{
			j++;
		}
		if (j == m)
		{
			return (i);
		}
		i++;
	}
	return -1;
}

int RobinKarp(const std::string &text, const std::string &pattern)
{
	std::vector<char> txt(text.begin(), text.end());
	std::vector<char> ptn(pattern.begin(), pattern.end());
	return RobinKarp(txt, ptn);
}

int RobinKarp(std::vector<char> &text, std::vector<char> &pattern)
{
	int n = text.size();
	int m = pattern.size();
	int i, j;
	int prime = 101;
	int powm = 1;
	int TextHash = 0, PatternHash = 0;
	if (m == 0 || m > n)
	{
		return -1;
	}

	for (i = 0; i < m - 1; i++)
	{
		powm = (powm << 1) % prime;
	}

	for (i = 0; i < m; i++)
	{
		PatternHash = ((PatternHash << 1) + pattern[i]) % prime;
		TextHash = ((TextHash << 1) + text[i]) % prime;
	}

	for (i = 0; i <= (n - m); i++)
	{
		if (TextHash == PatternHash)
		{
			for (j = 0; j < m; j++)
			{
				if (text[i + j] != pattern[j])
				{
					break;
				}
			}
			if (j == m)
			{
				return i;
			}
		}
		TextHash = (((TextHash - text[i] * powm) << 1) + text[i + m]) % prime;
		if (TextHash < 0)
		{
			TextHash = (TextHash + prime);
		}
	}
	return -1;
}

void KMPPreprocess(std::vector<char> &pattern, std::vector<int> &ShiftArr)
{
	const int m = pattern.size();
	int i = 0, j = -1;
	ShiftArr[i] = -1;
	while (i < m)
	{
		while (j >= 0 && pattern[i] != pattern[j])
		{
			j = ShiftArr[j];
		}
		i++;
		j++;
		ShiftArr[i] = j;
	}
}

int KMP(const std::string &text, const std::string &pattern)
{
	std::vector<char> txt(text.begin(), text.end());
	std::vector<char> ptn(pattern.begin(), pattern.end());
	return KMP(txt, ptn);
}

int KMP(std::vector<char> &text, std::vector<char> &pattern)
{
	int i = 0, j = 0;
	const int n = text.size();
	const int m = pattern.size();
	std::vector<int> ShiftArr(m + 1);
	KMPPreprocess(pattern, ShiftArr);
	while (i < n)
	{
		while (j >= 0 && text[i] != pattern[j])
		{
			j = ShiftArr[j];
		}
		i++;
		j++;
		if (j == m)
		{
			return (i - m);
		}
	}
	return -1;
}

int KMPFindCount(std::vector<char> &text, std::vector<char> &pattern)
{
	int i = 0, j = 0, count = 0;
	const int n = text.size();
	const int m = pattern.size();
	std::vector<int> ShiftArr(m + 1);
	KMPPreprocess(pattern, ShiftArr);
	while (i < n)
	{
		while (j >= 0 && text[i] != pattern[j])
		{
			j = ShiftArr[j];
		}
		i++;
		j++;
		if (j == m)
		{
			count++;
			j = ShiftArr[j];
		}
	}
	return count;
}