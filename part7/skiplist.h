#ifndef _SKIP_LIST_H_
#define _SKIP_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../asserts.h"

#define MAX_LEVEL	20
#define P_FACTOR	0.5

typedef struct SkipNode {
	int val;
	struct SkipNode** next;
} SkipNode;

typedef struct SkipList {
	int max_level;
	int cur_level;
	SkipNode* head;
} SkipList;

void        Insert          (SkipList* list, int val)	;
void        Delete          (SkipList* list, int val)	;

SkipList*   SkipListCtor    ()							;
SkipNode*   SkipNodeCtor    (int val, int level)		;
void        ListDtor        (SkipList* list)			;

#endif