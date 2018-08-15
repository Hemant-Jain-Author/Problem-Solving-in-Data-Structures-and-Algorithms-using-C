#include "stdafx.h"
#include "StringTree.h"

StringTree::Node::Node(std::string val)
{
	value = val;
	lChild = rChild = nullptr;
	count = 1;
}

void StringTree::print()
{
	print(root);
}

void StringTree::print(Node *curr)
{
	if (curr != nullptr)
	{
		std::cout << " value is ::" << curr->value;
		std::cout << " count is :: " << curr->count << std::endl;
		print(curr->lChild);
		print(curr->rChild);
	}
}

void StringTree::insert(const std::string &value)
{
	root = insert(value, root);
}

StringTree::Node *StringTree::insert(const std::string &value, Node *curr)
{
	int compare;
	if (curr == nullptr)
	{
		curr = new Node(value);
	}
	else
	{
		compare = curr->value.compare(value);
		if (compare == 0)
		{
			curr->count++;
		}
		else if (compare == 1)
		{
			curr->lChild = insert(value, curr->lChild);
		}
		else
		{
			curr->rChild = insert(value, curr->rChild);
		}
	}
	return curr;
}

void StringTree::freeTree()
{
	freeTree(root);
	root = nullptr;
}

void StringTree::freeTree(Node* node)
{
	if (node)
	{
		freeTree(node->lChild);
		freeTree(node->rChild);
		delete(node);
	}
}

bool StringTree::find(const std::string &value)
{
	bool ret = find(root, value);
	std::cout << "Find " << value << " Return " << ret << std::endl;
	return ret;
}

bool StringTree::find(Node *curr, const std::string &value)
{
	int compare;
	if (curr == nullptr)
	{
		return false;
	}
	compare = curr->value.compare(value);
	if (compare == 0)
	{
		return true;
	}
	else
	{
		if (compare == 1)
		{
			return find(curr->lChild, value);
		}
		else
		{
			return find(curr->rChild, value);
		}
	}
}

int StringTree::frequency(const std::string &value)
{
	return frequency(root, value);

}

int StringTree::frequency(Node *curr, const std::string &value)
{
	int compare;
	if (curr == nullptr)
	{
		return 0;
	}

	compare = curr->value.compare(value);
	if (compare == 0)
	{
		return curr->count;
	}
	else
	{
		if (compare > 0)
		{
			return frequency(curr->lChild, value);
		}
		else
		{
			return frequency(curr->rChild, value);
		}
	}
}

int main6()
{
	StringTree *tt = new StringTree();
	tt->insert("banana");
	tt->insert("apple");
	tt->insert("mango");
	tt->insert("banana");
	tt->insert("apple");
	tt->insert("mango");
	std::cout << "Search results for apple, banana, grapes and mango :" << std::endl;
	tt->find("apple");
	tt->find("banana");
	tt->find("banan");
	tt->find("applkhjkhkj");
	tt->find("grapes");
	tt->find("mango");

	tt->print();
	std::cout << "frequency returned :: " << tt->frequency("apple") << std::endl;
	std::cout << "frequency returned :: " << tt->frequency("banana") << std::endl;
	std::cout << "frequency returned :: " << tt->frequency("mango") << std::endl;
	std::cout << "frequency returned :: " << tt->frequency("hemant") << std::endl;
	return 0;
}