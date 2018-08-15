#pragma once

#include <string>
#include <vector>
#include <iostream>

int BruteForceSearch(const std::string &text, const std::string &pattern);

int BruteForceSearch(std::vector<char> &text, std::vector<char> &pattern);

int RobinKarp(const std::string &text, const std::string &pattern);

int RobinKarp(std::vector<char> &text, std::vector<char> &pattern);

void KMPPreprocess(std::vector<char> &pattern, std::vector<int> &ShiftArr);

int KMP(const std::string &text, const std::string &pattern);

int KMP(std::vector<char> &text, std::vector<char> &pattern);

int KMPFindCount(std::vector<char> &text, std::vector<char> &pattern);