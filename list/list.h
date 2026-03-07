#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

struct ListNode {
	void* val;
	struct ListNode *prev;
};

struct List {
	int elem_size;
	int size;
	struct ListNode *tail;
};

enum IMPORTANT_VALUES {
	BAD_VALUE = 0xFEDAFEDA,
};

struct List*		List_ctr		(int elem_size);
void				List_dtr		(struct List* list);
void				List_clr		(struct List* list);

int				 	List_push		(struct List* list, void* elem);
int				 	List_pop		(struct List* list);
int				 	List_top		(struct List* list);

struct ListNode*	GetTail			(struct List* list);
int					GetSize			(struct List* list);
struct ListNode*	GetPrev			(struct ListNode* list_node);
int				 	GetValue		(struct ListNode* list_node);

#endif // _LIST_H_
