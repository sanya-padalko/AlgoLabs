#include "list.h"

struct List* List_ctr(int elem_size) {

	struct List* list = (struct List*)calloc(1, sizeof(struct List));
	assert(list);

	list->elem_size = elem_size;
	list->size = 0;
	list->tail = NULL;
	return list;
}

void List_dtr(struct List* list) {
	if (!list)	return;
	
	List_clr(list);
	list->elem_size = 0;

	free(list);
}

void List_clr(struct List* list) {
	if (!list)	return;
	
	while (GetTail(list)) {
		struct ListNode* last = GetTail(list);
		list->tail = GetPrev(GetTail(list));
		
		free(last->val);
		free(last);
	}
	list->size = 0;
	list->tail = NULL;
}

int List_push(struct List* list, void* elem) {
	if (!list)		return BAD_VALUE;
	
	struct ListNode* new_node = (struct ListNode*)malloc(sizeof(struct ListNode));
	if (!new_node)	return BAD_VALUE;
	
	new_node->val = malloc(list->elem_size);
	memcpy(new_node->val, elem, list->elem_size);
	new_node->prev = GetTail(list);
	
	++list->size;
	list->tail = new_node;

	return *(int*)elem;
}

int List_pop(struct List* list) {
	if (!list)			return BAD_VALUE;
	if (!GetTail(list))	return BAD_VALUE;
	
	struct ListNode* last_node = GetTail(list);
	int last_val = GetValue(last_node);

	--list->size;
	list->tail = (list->tail)->prev;

	free(last_node);
	return last_val;
}

int List_top(struct List* list) {
	if (!list)	return BAD_VALUE;

	return GetValue(GetTail(list));
}

struct ListNode* GetTail(struct List* list) {
	if (!list)	return NULL;

	return list->tail;
}

int GetSize(struct List* list) {
	if (!list)	return -1;

	return list->size;
}

struct ListNode* GetPrev(struct ListNode* list_node) {
	if (!list_node)
		return NULL;

	return list_node->prev;
}

int GetValue(struct ListNode* list_node) {
	if (!list_node || !(list_node->val))	return BAD_VALUE;

	return *(int*)(list_node->val);
}
