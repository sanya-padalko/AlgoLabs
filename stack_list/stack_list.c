#include "stack_list.h"

struct StackList* StackList_ctr(int elem_size) {

	struct StackList* stacklist = (struct StackList*)calloc(1, sizeof(struct StackList));
	if (!stacklist)		return NULL;

	stacklist->list = List_ctr(elem_size);
	if (!stacklist->list)   return NULL;

	return stacklist;
}

struct StackList* StackList_dtr(struct StackList* stacklist) {
	if (!stacklist)		return NULL;

	List_dtr(stacklist->list);

	free(stacklist);
	return NULL;
}

void StackList_clr(struct StackList* stacklist) {
	if (!stacklist)		return;

	List_clr(stacklist->list);
	
	return;
}

int StackList_push(struct StackList* stacklist, void* elem) {
	if (!stacklist)		return 0;
	if (!elem)			return 0;
	
	int push_result = List_push(stacklist->list, elem);
	if (push_result == BAD_VALUE)   return 0;

	return 1;
}

int StackList_pop(struct StackList* stacklist) {
	if (!stacklist)		return 0;
	
	int pop_result = List_pop(stacklist->list);
	if (pop_result == BAD_VALUE)	return 0;

	return 1;
}

int StackList_top(struct StackList* stacklist) {
	if (!stacklist)		return BAD_VALUE;

	return List_top(stacklist->list);
}