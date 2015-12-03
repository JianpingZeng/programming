#ifndef __NODE_H
#define __NODE_H

#define NAME_SIZE	128

/*
* This file must be compiled with C language compiler supported C99 standard.
* Because this file contains some features compatibale with C99.
*/

typedef struct Node
{
	struct Node* next;
	char name [NAME_SIZE];
}Node;


/* 
*	Inserts a temporary node into tail of list with head.
* 	After insertion successful, return the head of list.
*/
Node* insert(Node* head, Node* temp);


/* free a linklist with head. */
void free_list(Node* head);


#endif
