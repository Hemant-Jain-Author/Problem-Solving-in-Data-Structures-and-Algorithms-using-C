/*
   For any linked list there are only three cases zero element ,one element,general
   Any program which is likely to change head pointer is to be passed a double pointer 

   for doubly linked list we have few more things 

   0> NULL values
   1> only element (tail case)
   2> first element
   3> general case
   4> last element (tail case)
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct listNode{
	int value;
	struct listNode *next;
	struct listNode *prev;
}listNode_t;

typedef listNode_t* listPtr;


/* INSERT VALUE IN FRONT */

int insertNode(listPtr* ptrHead,listPtr* ptrTail,int value)
{
	listPtr temp=(listPtr)malloc(sizeof(listNode_t));
	if(!temp)
		return 0;

	listPtr head=*ptrHead;
	if(!head)
	{
		temp->value=value;
		temp->next=NULL;
		temp->prev=NULL;
		*ptrTail=temp;
		*ptrHead=temp;
	}
	else
	{
		temp->value=value;
		temp->next=head;
		temp->prev=NULL;
		head->prev=temp;
		*ptrHead=temp;
	}
	return 1;
}


/* SORTED INSERT DECREASING ORDER */
int sortedInsert(listPtr* ptrHead,listPtr* ptrTail,int value)
{
	listPtr temp=(listPtr)malloc(sizeof(listNode_t));
	if(!temp)
		return 0;
	temp->value=value;

	listPtr head=*ptrHead;

	if(!head)/*first element*/
	{
		temp->next=NULL;
		temp->prev=NULL;
		*ptrHead=temp;
		*ptrTail=temp;
		return 1;	
	}
	if(head->value <= value)/*at the begining*/
	{
		temp->next=head;
		temp->prev=NULL;
		head->prev=temp;
		*ptrHead=temp;
		return 1;	
	}

	while(head->next && head->next->value > value)/*treversal*/
	{
		head=head->next;
	}


	if(!head->next)/*at the end*/
	{
		*ptrTail=temp;
		temp->next=NULL;
		temp->prev=head;
		head->next=temp;
	}
	else/*all other*/
	{

		temp->next=head->next;
		temp->prev=head;
		head->next=temp;
		temp->next->prev=temp;
	}
	return 1;
}

/* Print A singly linked list */
void printList(listPtr head)
{
	printf("List is :: ");
	while(head!=NULL)
	{
		printf(" %d  ",head->value);
		head=head->next;
	}
	printf("\n");
}


/* While traversing a linked list be cautious for checking end of list . */
void printBackList(listPtr head)
{	
	if(!head)
		return;

	printBackList(head->next);
	printf("%d,",head->value);

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
void deleteList(listPtr* ptrHead,listPtr* ptrTail)
{
	listPtr deleteMe=*ptrHead;
	listPtr nextNode;
	while(deleteMe!=NULL)
	{
		nextNode=deleteMe->next;	
		free(deleteMe);
		deleteMe=nextNode;
	}

	*ptrTail=NULL;
	*ptrHead=NULL;
}



/* Delete a node given its pointer */
void deleteNodePtr(listPtr* ptrHead,listPtr* ptrTail,listPtr ptrDel)
{
	listPtr currNode=*ptrHead;
	listPtr nextNode;

	if(ptrDel==NULL)
		return;

	if(currNode==ptrDel)/*first node*/
	{
		*ptrHead=currNode->next;
		currNode->next->prev=NULL;
		if(currNode==*ptrTail)/*only node*/
			*ptrTail=currNode->prev;
		free(currNode);
	}
	while(currNode!=NULL)
	{
		nextNode=currNode->next;	
		if(nextNode==ptrDel)/*node to be deleated*/
		{
			currNode->next=nextNode->next;
			nextNode->next->prev=currNode;
			if(nextNode==*ptrTail)
				*ptrTail=nextNode->prev;/*last node*/
			free(nextNode);
		}
		else
		{
			/*check for tail*/
			currNode=nextNode;
		}
	}
}

/* REMOVE DUPLICATE */
void removeDuplicate(listNode_t *head)
{
	listPtr deleteMe;
	while(head)
	{
		if((head->next) && head->value==head->next->value)
		{
			deleteMe=head->next;
			head->next=deleteMe->next;
			head->next->prev=head;
			free(deleteMe);
		}
		else
		{

			/*check for tail*/
			head=head->next;
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


