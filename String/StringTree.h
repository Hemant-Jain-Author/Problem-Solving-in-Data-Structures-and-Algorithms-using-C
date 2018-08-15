#pragma once

#include <string>
#include <vector>
#include <iostream>

class StringTree
{
private:
	struct Node
	{
		Node(std::string);
		std::string value;
		int count = 0;
		Node *lChild;
		Node *rChild;
	};

	Node *root = nullptr;
	virtual void print(Node *curr); // pre order
	virtual Node *insert(const std::string &value, Node *curr);
	virtual void freeTree(Node *curr);
	virtual bool find(Node *curr, const std::string &value);
	virtual int frequency(Node *curr, const std::string &value);
public:
	virtual void print();
	virtual void insert(const std::string &value);
	virtual void freeTree();
	virtual bool find(const std::string &value);
	virtual int frequency(const std::string &value);
};