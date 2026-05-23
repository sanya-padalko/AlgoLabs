#ifndef _FENWICK_H_
#define _FENWICK_H_

#include <stdio.h>
#include <stdlib.h>
#include "../asserts.h"

#define NEUTRAL_ELEM	0

typedef struct FenNode {
	int sum;
} FenNode;

typedef struct Fenwick {
	int	size;
	FenNode* pref;
} Fenwick;

#undef TREE_VERIFY
#ifdef DEBUG
	#define TREE_VERIFY(tree)										\
		MY_ASSERT(tree,			"Нулевой указатель на дерево\n");	\
		MY_ASSERT(tree->size,	"Пустое дерево\n");					\
		MY_ASSERT(tree->pref, 	"Дерево без элементов\n");				
#else
	#define TREE_VERIFY(fen)
#endif

Fenwick*	FenArrCtor	(int size, int* arr)				;

void		AddVal		(Fenwick* tree, int ind, int delta)	;
int			SegSum		(Fenwick* tree, int lt, int rt)		;
int			PrefSum		(Fenwick* tree, int ind)			;

Fenwick*	FenCtor		(int size)							;
void		FenDtor		(Fenwick* tree)						;

#endif