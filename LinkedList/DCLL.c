
typedef struct DoublyCircularLinkedList
{
    Node *head = nullptr;
	Node *tail = nullptr;
	int list_size = 0;
} DCLL;


	struct Node
	{
		int value;
		Node *next;
		Node *prev;
		Node(int v, Node *nxt, Node *prv);
		Node(int v);
	};

	Node *head = nullptr;
	Node *tail = nullptr;
	int list_size = 0;

public:
	DoublyCircularLinkedList();
	virtual int size();
	virtual bool isEmpty();
	virtual int peekHead();
	virtual void addHead(int value);
	virtual int removeHead();
	// Other Methods.

	virtual void addTail(int value);

	virtual int removeTail();
	virtual bool isPresent(int key);
	virtual void freeList();
	virtual void print();
};

int main()
{
	DoublyCircularLinkedList *ll;
	ll->addHead(1);
	ll->addHead(2);
	ll->addHead(3);
	ll->addHead(1);
	ll->addHead(2);
	ll->addHead(3);
	ll->print();
	return 0;
}

Node::Node(int v, Node *nxt, Node *prv)
{
	value = v;
	next = nxt;
	prev = prv;
}

Node::Node(int v)
{
	value = v;
	next = this;
	prev = this;
}

DoublyCircularLinkedList()
{
	list_size = 0;
}

int size()
{
	return list_size;
}

bool isEmpty()
{
	return list_size == 0;
}

int peekHead()
{
	if (isEmpty())
	{
		throw std::exception("EmptyListException");
	}
	return head->value;
}

void addHead(int value)
{
	Node *newNode = new Node(value);
	if (list_size == 0)
	{
		tail = head = newNode;
		newNode->next = newNode;
		newNode->prev = newNode;
	}
	else
	{
		newNode->next = head;
		newNode->prev = head->prev;
		head->prev = newNode;
		newNode->prev->next = newNode;
		head = newNode;
	}
	list_size++;
}

void addTail(int value)
{
	Node *newNode = new Node(value, nullptr, nullptr);
	if (list_size == 0)
	{
		head = tail = newNode;
		newNode->next = newNode;
		newNode->prev = newNode;
	}
	else
	{
		newNode->next = tail->next;
		newNode->prev = tail;
		tail->next = newNode;
		newNode->next->prev = newNode;
		tail = newNode;
	}
	list_size++;
}

int removeHead()
{
	if (list_size == 0)
		throw std::exception("EmptyListException");

	int value = head->value;
	list_size--;

	if (list_size == 0)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		return value;
	}

	Node *next = head->next;
	next->prev = tail;
	tail->next = next;
	delete head;
	head = next;
	return value;
}

int removeTail()
{
	if (list_size == 0)
		throw std::exception("EmptyListException");

	int value = tail->value;
	list_size--;

	if (list_size == 0)
	{
		delete tail;
		head = tail = nullptr;
		return value;
	}

	Node *prev = tail->prev;
	prev->next = head;
	head->prev = prev;
	delete tail;
	tail = prev;
	return value;
}

bool isPresent(int key)
{
	Node *temp = head;
	if (head == nullptr)
		return false;

	do
	{
		if (temp->value == key)
		{
			return true;
		}
		temp = temp->next;
	} while (temp != head);

	return false;
}

void freeList()
{
	if (head == nullptr)
		return;

	Node* curr = head->next;
	Node* next;
	while (curr != head)
	{
		next = curr->next;
		delete curr;
		curr = next;
	}
	delete head;
	head = nullptr;
	tail = nullptr;
	list_size = 0;
}

void print()
{
	if (isEmpty())
		return;

	Node *temp = head;
	do
	{
		std::cout << temp->value << " ";
		temp = temp->next;
	} while (temp != nullptr);
}