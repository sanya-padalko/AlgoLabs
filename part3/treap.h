#ifndef _TREAP_H_
#define _TREAP_H_

#include <stdio.h>
#include <stdlib.h>
#include "../asserts.h"

typedef struct DDnode {
	int val;
	int prior;
	struct DDnode* left;
	struct DDnode* right;
} DDnode;

typedef struct DDpair {
	DDnode* first;
	DDnode* second;
} DDpair;

DDnode*		Insert		(DDnode* node, int val)			;
DDnode*		Delete		(DDnode* node, int val)			;
int			Check		(DDnode** node, int val)		;

DDpair		Split		(DDnode* node, int val)			;
DDnode*		Merge		(DDnode* node1, DDnode* node2)	;

DDnode*		DDnodeCtor	(int val)						;
DDpair		DDpairCtor	(DDnode* first, DDnode* second)	;

DDnode*		GetLeft		(DDnode* node)					;
void		ClearTree	(DDnode* node)					;
DDnode*		GetRight	(DDnode* node)					;
int			GetVal		(DDnode* node)					;
int			GetPrior	(DDnode* node)					;

#endif