#include "stdafx.h"
#include "Trie.h"
#include <algorithm>


Trie::Node::Node()
{
	for (int i = 0; i < CharCount; i++)
		child.push_back(nullptr);
	isLastChar = false;
}

Trie::Trie()
{
	root = new Node(); // first node with dummy value.
}

void Trie::Insert(const std::string &s)
{
	if (s == "")
		return;
	std::string str = s;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	Insert(root, str, 0);
}

Trie::Node *Trie::Insert(Node *curr, const std::string &str, int index)
{
	if (curr == nullptr)
	{
		curr = new Node();
	}

	if (str.length() == index)
	{
		curr->isLastChar = true;
	}
	else
	{
		curr->child[str[index] - 'a'] = Insert(curr->child[str[index] - 'a'], str, index + 1);
	}

	return curr;
}

void Trie::Remove(const std::string &s)
{
	if (s == "")
		return;
	std::string str = s;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	Remove(root, str, 0);
}

void Trie::Remove(Node *curr, const std::string &str, int index)
{
	if (curr == nullptr)		
		return;

	if (str.length() == index)
	{
		if (curr->isLastChar)
		{
			curr->isLastChar = false;
		}
		return;
	}

	Remove(curr->child[str[index] - 'a'], str, index + 1);
}

bool Trie::Find(const std::string &s)
{
	if (s == "")
		return false;

	std::string str = s;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	return Find(root, str, 0);
}

bool Trie::Find(Node *curr, const std::string &str, int index)
{
	if (curr == nullptr)
	{
		return false;
	}
	if (str.length() == index)
	{
		return curr->isLastChar;
	}
	return Find(curr->child[str[index] - 'a'], str, index + 1);
}

int mainhgfh()
{
	Trie *t = new Trie();
	std::string a = "hemant";
	std::string b = "heman";
	std::string c = "hemantjain";
	std::string d = "jain";
	t->Insert(a);
	t->Insert(d);
	std::cout << t->Find(a) << std::endl;
	t->Remove(a);
	t->Remove(d);
	std::cout << t->Find(a) << std::endl;
	std::cout << t->Find(c) << std::endl;
	std::cout << t->Find(d) << std::endl;
	return 0;
}