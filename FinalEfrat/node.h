#pragma once
#ifndef _DEF_
#define _DEF_

// a value not supposed in stack and queue
#define		EMPTY	0x7FFFFFFF

// new types
typedef void* DATA;					// a type for data (easy to change)
typedef enum { False, True } BOOL;	// a boolean type

// Node
typedef struct NODE
{
	DATA			key;
	struct NODE* next;
}NODE;

#endif