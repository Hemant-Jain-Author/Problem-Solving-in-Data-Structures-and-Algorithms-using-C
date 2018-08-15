#pragma once

#include <string>
#include <vector>
#include <iostream>

class TST
{
private:
	struct  Node
	{
		char data = '\0';
		bool isLastChar = false;
		Node *left, *equal, *right;
		Node(TST *outerInstance, char d);
	};
	Node *root;
	Node *insert(Node *curr, const std::string &word, int wordIndex);
public:
	virtual void insert(const std::string &word);
	bool find(Node *curr, const std::string &word, int wordIndex);
	virtual bool find(const std::string &word);
};
