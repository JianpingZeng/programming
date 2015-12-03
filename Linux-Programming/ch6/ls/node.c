#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* 
*	Inserts a temporary node into tail of list with head.
* 	After insertion successful, return the head of list.
*/
Node* insert(Node* list, Node* temp)
{
	if (temp == NULL) return list;
	if (list == NULL) return list = temp;
	Node* head = list;
	while (list->next != NULL) list = list->next;
	
	temp->next = NULL;
	list->next = temp;
	return head;
}

/* free a linklist with head. */
void free_list(Node* head)
{
	Node* h = NULL;
	while(head != NULL)
	{
		h = head;
		head = head->next;
		free(h);
	}
}	
