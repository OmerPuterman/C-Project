#pragma once
/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_

#include "node.h"


/*** Definitions ***/

// List
typedef struct
{
	NODE head;
}LIST;


/*** Function prototypes ***/

BOOL L_init(LIST* pList);					// create new list

NODE* L_insert(NODE* pNode, DATA Value);	// add new node after *pNode

BOOL L_delete(NODE* pNode, void (*freeKey)(void*));					// erase node after *pNode

const NODE* L_find(const NODE* pNode, DATA Value, int (*compare)(void*, void*));		// return a pointer to the node 

BOOL L_free(LIST* pList, void (*freeKey)(void*));					// free list memory

int L_print(const LIST* pList, void (*print)(void*));					// print the list content

#endif


