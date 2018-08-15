#pragma once

#include <string>
#include <vector>
#include <iostream>

bool matchExpUtil(std::string &exp, std::string &str, int i, int j);

bool matchExp(std::string &exp, std::string &str);

int match(std::string &source, std::string &pattern);

bool isPrime(int n);

int myAtoi(const std::string &str);

bool isUniqueChar(const std::string &str);

char ToUpper(char s);

char ToLower(char s);

char LowerUpper(char s);

bool isPermutation(const std::string &s1, const std::string &s2);

bool isPalindrome(const std::string &str);

int pow(int x, int n);

int myStrcmp(const std::string &a, const std::string &b);

void reverseString(std::string &a);

void reverseString(std::string &a, int lower, int upper);

void reverseWords(std::string &a);

void printAnagram(std::string  &a);

void printAnagram(std::string  &a, int max, int n);

void shuffle(std::string  &ar);

std::string addBinary(std::string &first, std::string &second);