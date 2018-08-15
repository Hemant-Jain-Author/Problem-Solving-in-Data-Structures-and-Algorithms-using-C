#pragma once

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Trie
{
private:
	struct Node
	{
		bool isLastChar = false;
		std::vector<Node*> child;
		Node();
	};

	static const int CharCount = 26;
	Node *root = nullptr;
	virtual Node *Insert(Node *curr, const std::string &str, int index);
	virtual void Remove(Node *curr, const std::string &str, int index);
	virtual bool Find(Node *curr, const std::string &str, int index);

public:
	Trie();
	virtual void Insert(const std::string &str);
	virtual void Remove(const std::string &str);
	virtual bool Find(const std::string &str);
};
