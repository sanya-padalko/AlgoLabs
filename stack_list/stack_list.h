#ifndef _STACK_LIST_H_
#define _STACK_LIST_H_

#include "../list/list.h"

struct StackList {
	struct List* list;
};

struct StackList*	StackList_ctr		(int elem_size);
struct StackList*	StackList_dtr		(struct StackList* stacklist);
void				StackList_clr		(struct StackList* stacklist);

int 				StackList_push		(struct StackList* stacklist, void* elem);
int					StackList_pop		(struct StackList* stacklist);
int					StackList_top		(struct StackList* stacklist);


#endif