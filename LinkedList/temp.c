#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int value;
	struct listNode *next;
	struct listNode *prev;
}Node;


typedef struct list{
	struct listNode *head;
	struct listNode *tail;
}DLList;

/* INSERT VALUE IN FRONT */
int insertNode(DLList* dll,int value)
{
    listNode_t* head = dll->head;
    listNode_t* tail = dll->tail;
	Node* temp=(Node*)malloc(sizeof(Node));
	if(!temp)
		return 0;
	if(!head)
	{
		temp->value=value;
		temp->next=NULL;
		temp->prev=NULL;
		dll->tail = dll->head = temp;
	}
	else
	{
		temp->value=value;
		temp->next=head;
		temp->prev=NULL;
		head->prev=temp;
		dll->head=temp;
	}
	return 1;
}


/* Print A singly linked list */
void printList(DLList* dll)
{
	printf("List is :: ");
    Node* head = dll->head;
	while(head!=NULL)
	{
		printf(" %d  ",head->value);
		head=head->next;
	}
	printf("\n");
}


void printList2(Node* head)
{	
	if(!head)
		return;
    printf("%d,",head->value);
	printList(head->next);
}

/* Reverse a doubly linked List iteratively */
void reverseList(listNode_t **ptrHead,listNode_t **ptrTail)
{
	listPtr head=*ptrHead;
	listPtr tempNode;

	while(head)
	{
		tempNode=head->next;
		head->next=head->prev;
		head->prev=tempNode;

		if(!head->prev)
		{
			*ptrTail=*ptrHead;
			*ptrHead=head;
			return; 
		}
		head=head->prev;
	}
	return;
}

/* Delete a singly linked list */
void deleteList(DLList* dll)
{
	Node* deleteMe=dll->head;
	Node* nextNode;
	while(deleteMe!=NULL)
	{
		nextNode=deleteMe->next;	
		free(deleteMe);
		deleteMe=nextNode;
	}
	dll->head = dll->tail =NULL;
}

/* Delete a node given its pointer */
void deleteNodePtr(DLList* dll, listPtr ptrDel)
{
	Node* currNode=dll->head;
	Node* nextNode;
	if(ptrDel==NULL)
		return;

	if(currNode==ptrDel)/*first node*/
	{
		dll->head=currNode->next;
		if(!dll->head){
            currNode->next->prev = NULL;
        } else {
            dll->tail = NULL;
        }
        free(currNode);
	}
	while(currNode!=NULL)
	{
		nextNode=currNode->next;
		if(nextNode==ptrDel) /*node to be deleated*/
		{
			currNode->next=nextNode->next;
			if(nextNode == dll->tail)
				dll->tail=currNode; /*last node*/
            else 
                currNode->next->prev=currNode;
            free(nextNode);
		}
		else
		{
			currNode=nextNode;
		}
	}
}

/* REMOVE DUPLICATE */
void removeDuplicate(DLList *dll)
{
    Node* curr = dll->head;
	Node* deleteMe;
	while(curr)
	{
		if((curr->next) && curr->value==curr->next->value)
		{
			deleteMe=curr->next;
			curr->next=deleteMe->next;
            if (!curr->next)
                dll->tail=curr;
            else 
                curr->next->prev=curr;
			free(deleteMe);
		}
		else
		{
			curr=curr->next;
		}
	}

}


/* COPY LIST */
void copyListReversed(listPtr head,listPtr* ptrHead2)
{
	printf("copy list");
	listPtr tempNode=NULL;
	listPtr tempNode2=NULL;
	while(head)
	{
		tempNode2=(listPtr)malloc(sizeof(listNode_t));
		tempNode2->value=head->value;
		tempNode2->next=tempNode;
		tempNode2->prev=NULL;


		tempNode=tempNode2;
		head=head->next;
	}

	*ptrHead2=tempNode;
}

/* COPY LIST */
void copyList(listPtr head,listPtr* ptrHead2)
{
	printf("copy list");
	listPtr headNode=NULL;
	listPtr tailNode=NULL;
	listPtr tempNode=NULL;

	if(head==NULL)
		return;
	headNode=(listPtr)malloc(sizeof(listNode_t));
	tailNode=headNode;
	headNode->value=head->value;
	headNode->next=NULL;
	headNode->prev=NULL;

	head=head->next;

	while(head)
	{
		tempNode=(listPtr)malloc(sizeof(listNode_t));
		tempNode->value=head->value;
		tempNode->next=NULL;

		tailNode->next=tempNode;
		tempNode->prev=tailNode;

		tailNode=tailNode->next;

		head=head->next;
	}

	*ptrHead2=headNode;
}



/* COMPARE LIST */
int compareList(listPtr head1,listPtr head2)
{
	printf("compare list");
	if( head1==NULL && head2==NULL )
		return 1;
	else if( (head1==NULL) ||(head2==NULL) || (head1->value!=head2->value) )
		return 0;
	else
		return compareList(head1->next,head2->next);

}

/* COMPARE LIST */
int compareList2(listPtr head1,listPtr head2)
{
	while( head1!=NULL && head2!=NULL )
	{
		if(head1->value!=head2->value)
			return 0;
		head1=head1->next;
		head2=head2->next;


	}
	if(head1==head2)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int main()
{
	listPtr head=NULL;
	listPtr tail=NULL;
	listPtr* ptrHead=&head;
	listPtr* ptrTail=&tail;

	insertNode(ptrHead,ptrTail,1);
	insertNode(ptrHead,ptrTail,2);
	insertNode(ptrHead,ptrTail,3);
	insertNode(ptrHead,ptrTail,4);
	insertNode(ptrHead,ptrTail,5);
	insertNode(ptrHead,ptrTail,6);
	insertNode(ptrHead,ptrTail,7);
	printList(*ptrHead);

	listPtr head2=NULL;
	listPtr tail2=NULL;
	listPtr* ptrHead2=&head2;
	listPtr* ptrTail2=&tail2;

	sortedInsert(ptrHead2,ptrTail2,1);
	sortedInsert(ptrHead2,ptrTail2,2);
	sortedInsert(ptrHead2,ptrTail2,3);
	sortedInsert(ptrHead2,ptrTail2,4);
	sortedInsert(ptrHead2,ptrTail2,5);
	sortedInsert(ptrHead2,ptrTail2,6);
	sortedInsert(ptrHead2,ptrTail2,7);

	printList(*ptrHead2);

	printf("comparision result %d ", compareList(head,head2));

	return 0;

}


