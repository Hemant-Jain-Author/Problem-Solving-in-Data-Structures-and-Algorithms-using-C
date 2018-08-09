// LinkedList.cpp : Defines the entry point for the console application.
//

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
	int value;
	struct Node *next;
}DLLNode;

typedef DLLNode* NodePtr;

int InsertNode(NodePtr* ptrHead, int value)
{
	printf("Insert Node:: %d\n",value);
	NodePtr tempNode = (NodePtr)malloc(sizeof(DLLNode));
	if(!tempNode)
		return -1;
	tempNode->value=value;
	tempNode->next=*ptrHead;
	*ptrHead=tempNode;
	return 1;	
}

int findLenght(NodePtr head)
{
	int count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return count;
}

NodePtr nthNodeFromBegening(NodePtr head, int index)
{
	int count = 0;
	while (head && count < index-1)
	{
		count++;
		head = head->next;
	}

	if (head)
		return head;
	else
		return NULL;
}

NodePtr nthNodeFromEnd1(NodePtr head, int index)
{
	int size = findLenght(head);
	int startIndex;
	if (size && size < index)
	{
		printf("list does not have % elements", index);
		return NULL;
	}
	startIndex = size - index + 1;
	return nthNodeFromBegening(head, index);
}


NodePtr nthNodeFromEnd2(NodePtr head, int index)
{
	int count = 0;
	NodePtr temp = NULL;
	NodePtr curr = head;
	while (curr && count < index - 1)
	{
		count++;
		curr = curr->next;
	}
	
	if (!curr)
		return NULL;

	temp = head;
	
	while (curr)
	{
		temp = temp->next;
		curr = curr->next;
	}
	return temp;
}


NodePtr nthNodeFromEnd3(NodePtr head, int index)
{
	static int count=0;
	NodePtr retval;
	
	if (!head)
		return NULL;
	
	retval = nthNodeFromEnd3(head->next, index);
	if (retval)
		return retval;
	
	count++;
	if (count == index)
		return head;
	else
		return NULL;
}

void PrintList(NodePtr head)
{
	printf("PrintLIst: ");
	while(head)
	{
		printf(" %d ", head->value);
		head=head->next;
	}	
	printf("\n");
}


int SortedInsert(NodePtr* ptrHead,int value)
{
	NodePtr head=*ptrHead;
	NodePtr tempNode = (NodePtr)malloc(sizeof(DLLNode));
	printf("Insert element %d \n",value);
	if(!tempNode)
		return -1;
	tempNode->value=value;
	tempNode->next=NULL;
	if(head==NULL  || head->value>value)
	{
		tempNode->next=*ptrHead;
		*ptrHead=tempNode;
		return  1;
	}
	while(head->next != NULL && 
		head->next->value < value)
	{
		head=head->next;
	}
	tempNode->next=head->next;
	head->next=tempNode;
	return 1;
}
int InsertAtEnd(NodePtr* ptrHead, int value)
{
	printf("insert element %d \n",value);
	NodePtr head=*ptrHead;
	NodePtr tempNode = 	 	 	 	 (NodePtr)malloc(sizeof(DLLNode));
	if(!tempNode)
		return -1;
	tempNode->value=value;
	tempNode->next=NULL;
	if(head==NULL  )
	{
		tempNode->next=*ptrHead;
		*ptrHead=tempNode;
		return  1;
	}
	while(head->next!=NULL)
	{
		head=head->next;
	}
	tempNode->next=head->next;
	head->next=tempNode;
	return 1;
}
int InsertNodeEnd2(NodePtr* ptrHead, NodePtr* ptrTail, int value)
{
	printf("Insert Node:: %d",value);
	NodePtr tempPtr= (NodePtr)malloc(sizeof(DLLNode));
	if(!tempPtr)
		return -1;
	tempPtr->value=value;
	tempPtr->next=NULL;
	if(*ptrHead == NULL)
	{
		*ptrTail=*ptrHead=tempPtr;
	}
	else
	{
		NodePtr tail = *ptrTail;
		tail->next=tempPtr;
		*ptrTail=tempPtr;
	}
	return 1;
}
int SearchList(NodePtr head, int value)
{
	while(head)
	{
		if(head->value == value)
		{
			printf("\nThe value is found\n");
			return 1;
		}
		head=head->next;
	}
	printf("\nThe value not found\n");
	return 0;
}
void DeleteNode(NodePtr* ptrHead, int delValue)
{
	printf("\nDelete Node \n");
	NodePtr currNode=*ptrHead;
	NodePtr nextNode;

	if(currNode->value==delValue)/*first node */
	{
		*ptrHead=currNode->next;
		free(currNode);
		return;
	}

	while(currNode!=NULL)
	{
		nextNode=currNode->next;	
		if(nextNode && nextNode->value == delValue)
		{
			currNode->next = nextNode->next;
			free(nextNode);
			return;
		}
		else
		{
			currNode=nextNode;
		}
	}
}

void DeleteFirstNodes(NodePtr* ptrHead, int delValue)
{
	printf("\nDelete First Node \n");
	NodePtr currNode=*ptrHead;
	NodePtr nextNode;
	
	if(currNode==NULL)
		return;

	nextNode = currNode->next;
	free(currNode);

	*ptrHead = nextNode;
}



void DeleteNodes(NodePtr* ptrHead, int delValue)
{
	printf("\nDelete Node \n");
	NodePtr currNode=*ptrHead;
	NodePtr nextNode;
	NodePtr delNode;

	while(currNode!=NULL && currNode->value==delValue)/*first node */
	{
		*ptrHead=currNode->next;
		delNode=currNode;
		currNode=currNode->next;
		free(delNode);
	}

	while(currNode!=NULL)
	{
		nextNode=currNode->next;	
		if(nextNode && nextNode->value == delValue)
		{
			currNode->next = nextNode->next;
			free(nextNode);
		}
		else
		{
			currNode=nextNode;
		}
	}
}


void DeleteNodePtr(NodePtr* ptrHead, NodePtr ptrDel)
{
	printf("\nDeleteNode\n");
	NodePtr currNode=*ptrHead;
	NodePtr nextNode;

	if(ptrDel==NULL)
		return;

	if(currNode==ptrDel)/*first node*/
	{
		*ptrHead=currNode->next;
		free(currNode);
		return;
	}
	while(currNode!=NULL)
	{
		nextNode=currNode->next;	
		if(nextNode==ptrDel)/*node to be deleated*/
		{
			currNode->next=nextNode->next;
			free(nextNode);
			return;
		}
		else
		{
			currNode=nextNode;
		}
	}
}

void DeleteList(NodePtr* ptrHead)
{
	printf("\nDelete List\n");
	NodePtr deleteMe=*ptrHead;
	NodePtr nextNode;
	while(deleteMe!=NULL)
	{
		nextNode=deleteMe->next;	
		free(deleteMe);
		deleteMe=nextNode;
	}
	*ptrHead=NULL;
}
void ReverseList(NodePtr* ptrHead)
{
	NodePtr tempNode=*ptrHead;
	NodePtr prevNode;
	NodePtr nextNode;
	if(!tempNode)
	{
		return;
	}
	if(!tempNode->next)
	{
		return;
	}
	prevNode=tempNode;
	tempNode=tempNode->next;
	prevNode->next=NULL;
	while(tempNode)
	{
		nextNode=tempNode->next;
		tempNode->next=prevNode;
		prevNode=tempNode;
		tempNode=nextNode;

	}
	*ptrHead=prevNode;
}
NodePtr ReverseRecurse2(NodePtr currentNode, NodePtr nextNode)
{
	NodePtr ret;
	if(!currentNode)
		return NULL;

	if(!currentNode->next)
	{
		currentNode->next=nextNode;
		return	currentNode;
	}

	ret=ReverseRecurse2 (currentNode->next,currentNode);
	currentNode->next=nextNode;

	return ret;
}

void reverseRecurse(NodePtr* ptrHead)
{
	*ptrHead=ReverseRecurse2(*ptrHead,NULL);	
}
void RemoveDuplicate(NodePtr head)
{
	NodePtr deleteMe;
	while(head)
	{
		if((head->next) && head->value == head->next->value)
		{
			deleteMe=head->next;
			head->next=deleteMe->next;
			free(deleteMe);
		}
		else
		{
			head=head->next;
		}
	}
}
void CopyListReversed(NodePtr head, NodePtr* ptrHead2)
{
	printf("copy list");
	NodePtr tempNode=NULL;
	NodePtr tempNode2=NULL;
	while(head)
	{
		tempNode2 = (NodePtr)malloc( sizeof(DLLNode));
		tempNode2->value=head->value;
		tempNode2->next=tempNode;
		tempNode=tempNode2;
		head=head->next;
	}
	*ptrHead2=tempNode;
}
void CopyList(NodePtr head, NodePtr* ptrHead2)
{
	printf("copy list");
	NodePtr headNode=NULL;
	NodePtr tailNode=NULL;
	NodePtr tempNode=NULL;

	if(head==NULL)
		return;
	headNode=(NodePtr)malloc(sizeof(DLLNode));
	tailNode=headNode;
	headNode->value=head->value;
	headNode->next=NULL;
	head=head->next;

	while(head)
	{
		tempNode=(NodePtr)malloc( sizeof(DLLNode));
		tempNode->value=head->value;
		tempNode->next=NULL;
		tailNode->next=tempNode;
		tailNode=tailNode->next;
		head=head->next;
	}
	*ptrHead2=headNode;
}
int LoopDetect(NodePtr head)
{
	printf("loop detect");
	NodePtr slowPtr;
	NodePtr fastPtr;
	slowPtr=fastPtr=head;

	while(fastPtr->next&&fastPtr->next->next)
	{
		slowPtr=slowPtr->next;
		fastPtr=fastPtr->next->next;
		if(slowPtr==fastPtr)
		{
			printf("\nloop found \n");
			return 1;
		}
	}
	printf("\nloop not found \n");
	return 0;
}

int LoopTypeDetect(NodePtr const head)
{
	printf("loop type detect :: ");
	NodePtr slowPtr;
	NodePtr fastPtr;

	slowPtr=fastPtr=head;
	while(fastPtr->next && fastPtr->next->next)
	{

		if(head==fastPtr->next || head==fastPtr->next->next)
		{
			printf("circular list detected\n");
			return 2;
		}

		slowPtr=slowPtr->next;
		fastPtr=fastPtr->next->next;

		if(slowPtr==fastPtr)
		{
			printf("loop detected\n");
			return 1;
		}
	}
	printf("No loop detected\n");
	return 0;
}

void MakeLoop(NodePtr head)
{
	NodePtr temp = head;
	while(temp)
	{
		if(temp->next == NULL)
		{
			temp->next = head;
			return;
		}
		temp=temp->next;
	}
}

void RemoveLoop(NodePtr* ptrHead)
{
	int loopLength;
	NodePtr slowPtr,fastPtr, head;
	slowPtr=fastPtr=head=*ptrHead;
	NodePtr loopNode=NULL;
	while(fastPtr->next && fastPtr->next->next )
	{
		fastPtr=fastPtr->next->next;
		slowPtr=slowPtr->next;

		if(fastPtr==slowPtr || fastPtr->next==slowPtr)
		{
			loopNode=slowPtr;
			break;
		}
	}

	if(loopNode)
	{
		NodePtr temp=loopNode->next;
		loopLength=1;
		while(temp!=loopNode)
		{
			loopLength++;
			temp=temp->next;
		}
		temp=head;
		NodePtr breakNode=head;

		for(int i=1;i<loopLength;i++)
		{
			breakNode=breakNode->next;
		}

		while(temp != breakNode->next)
		{
			temp=temp->next;
			breakNode=breakNode->next;
		}
		breakNode->next=NULL;
	}
	//printf("\nloop length is %d \n",loopLength);
}

NodePtr findIntersecton(NodePtr head, NodePtr head2)
{
	int l1=0;
	int l2=0;
	NodePtr tempHead=head;
	NodePtr tempHead2=head2;

	while(tempHead)
	{
		l1++;
		tempHead=tempHead->next;
	}
	while(tempHead2)
	{
		l2++;
		tempHead2=tempHead2->next;
	}

	int diff;
	if(l1<12)
	{
		NodePtr temp=head;
		head=head2;
		head2=temp;
		diff=l2-l1;
	}
	else
	{
		diff=l1-l2;
	}

	for(;diff>0;diff--)
	{
		head=head->next;
	}
	while(head!=head2)
	{
		head=head->next;
		head2=head2->next;
	}

	return head;
}


int main()
{

	int arr[5]={1,2,3,4,5};
	NodePtr head=NULL;
	int i;
	
	for(i=0;i<5;i++)
	{
		InsertNode(&head, arr[i]);
	}
	NodePtr head2=head;
	for(i=0;i<3;i++)
	{
		InsertNode(&head, 10);
	}
	for(i=0;i<5;i++)
	{
		InsertNode(&head2, 20);
	}

	PrintList(head);
	PrintList(head2);

    NodePtr intersection = findIntersecton(head,head2);
	printf("\nvalue at the intersection is %d \n",intersection->value);
	
	for(i=0;i<5;i++)
	{
	InsertNode(&head, arr[i]);
	}

	PrintList(head);

	DeleteList(&head);

	PrintList(head);

	int arr2[5]={1,5,3,2,4};

	head=NULL;

	for(i=0;i<5;i++)
	{
	SortedInsert(&head,arr2[i]);
	}
	PrintList(head);

	SearchList(head,6);
	SearchList(head,5);

	DeleteNode(&head,5);
	PrintList(head);

	DeleteNode(&head,3);
	PrintList(head);

	for(i=0;i<5;i++)
	{
	SortedInsert(&head,arr2[i]);
	}
	PrintList(head);

	RemoveDuplicate(head);
	PrintList(head);

	ReverseList(&head);
	PrintList(head);

	reverseRecurse(&head);
	PrintList(head);

	DeleteNode(&head,1);
	PrintList(head);

	DeleteNode(&head,5);
	PrintList(head);

	DeleteNode(&head,3);
	PrintList(head);

	for(i=0;i<5;i++)
	{
	InsertNode(&head, arr[i]);
	InsertNode(&head, arr[i]);
	InsertNode(&head, arr[i]);
	}
	PrintList(head);

	CopyList(head,&head2);
	PrintList(head2);

	NodePtr head3;
	CopyListReversed(head,&head3);
	PrintList(head3);

	DeleteNodes(&head,5);
	PrintList(head);

	DeleteNodes(&head,1);
	PrintList(head);

	DeleteNodes(&head,4);
	PrintList(head);

	LoopDetect(head);
	LoopTypeDetect(head);

	MakeLoop(head);
	for(i=0;i<5;i++)
	{
	InsertNode(&head, arr[i]);
	}
	LoopDetect(head);
	LoopTypeDetect(head);

	RemoveLoop(&head);
	PrintList(head);
	
	return 0;
}