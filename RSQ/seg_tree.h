#ifndef _SEG_TREE_H_
#define _SEG_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "asserts.h"

#define NEUTRAL_ELEM	0

typedef struct TreeNode {
	int sum;
} TreeNode;

typedef struct SegTree {
	int	size;
	TreeNode* nodes;
} SegTree;


#ifdef DEBUG
	#define TREE_VERIFY(tree)									\
		ASSERT(tree,		"Нулевой указатель на дерево\n");	\
		ASSERT(tree->size,	"Пустое дерево\n");					\
		ASSERT(tree->nodes, "Дерево без вершин\n");				
#else
	#define TREE_VERIFY(tree)
#endif

int			FindSum			(SegTree* tree, int q_lt, int q_rt)	;
void		ChangeVal		(SegTree* tree, int ind, int val)	;

SegTree*	SegTreeArrCtor	(int size, int* arr)				;
SegTree*	SegTreeCtor		(int size)							;
void		SegTreeDtor		(SegTree* tree)						;

int			NodeMerge		(TreeNode* left, TreeNode* right)	;
int			GetSum			(TreeNode* node)					;

#endif