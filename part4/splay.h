#ifndef _SPLAY_H_
#define _SPLAY_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct SplayNode {
	int		 val;
	struct SplayNode* left;
	struct SplayNode* right;
} SplayNode;

SplayNode*	Insert			(SplayNode* node, int val)	;
SplayNode*	Delete			(SplayNode* root, int val)	;

void		ClearTree		(SplayNode* node)			;
SplayNode*	SplayNodeCtor	(int val)					;
void		NodeDtor		(SplayNode* node)			;

SplayNode*	GetLeft			(SplayNode* node)			;
SplayNode*	GetRight		(SplayNode* node)			;
int			GetVal			(SplayNode* node)			;

#endif